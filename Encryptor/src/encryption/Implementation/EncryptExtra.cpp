#include "encryption/Implementation/EncryptExtra.h"

static const unsigned char reflector[256]{ 169, 58, 74, 25, 225, 47, 205, 232, 240, 168, 214, 56, 185, 217, 129, 145, 48, 204, 213, 226, 231, 215, 99, 105, 207, 3, 98, 166, 62, 40, 223, 82, 102, 120, 192, 65, 147, 199, 91, 180, 29, 124, 112, 229, 183, 182, 71, 5, 16, 202, 188, 54, 144, 78, 51, 88, 11, 149, 1, 123, 116, 66, 28, 152, 227, 35, 61, 89, 203, 195, 209, 46, 79, 197, 2, 151, 96, 246, 53, 72, 239, 133, 31, 142, 186, 175, 155, 181, 55, 67, 208, 38, 153, 187, 134, 184, 76, 126, 26, 22, 158, 200, 32, 122, 148, 23, 219, 172, 238, 251, 160, 237, 42, 143, 119, 250, 60, 178, 194, 114, 33, 174, 103, 59, 41, 198, 97, 190, 150, 14, 210, 221, 164, 81, 94, 159, 236, 228, 216, 212, 156, 176, 83, 113, 52, 15, 253, 36, 104, 57, 128, 75, 63, 92, 170, 86, 140, 224, 100, 135, 110, 245, 252, 218, 132, 230, 27, 249, 9, 0, 154, 242, 107, 244, 121, 85, 141, 222, 117, 193, 39, 87, 45, 44, 95, 12, 84, 93, 50, 196, 127, 254, 34, 179, 118, 69, 189, 73, 125, 37, 101, 206, 49, 68, 17, 6, 201, 24, 90, 70, 130, 255, 139, 18, 10, 21, 138, 13, 163, 106, 247, 131, 177, 30, 157, 4, 19, 64, 137, 43, 165, 20, 7, 248, 235, 234, 136, 111, 108, 80, 8, 243, 171, 241, 173, 161, 77, 220, 233, 167, 115, 109, 162, 146, 191, 211 };

void ENC::EncryptExtra::encrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	if (pass.size() < 2) throw Encryptor::EncryptorException(PASSWORD_IS_TOO_SHORT);

	this->progress = 0;

	inputStream.seekg(0, inputStream.end);
	this->total = inputStream.tellg();
	inputStream.seekg(0, inputStream.beg);

	unsigned char rotation = pass[0];

	const unsigned char* beginPass = reinterpret_cast<const unsigned char*>(pass.c_str()) + 1;
	const unsigned char* endPass = beginPass - 1 + pass.size();
	const unsigned char* iteratorPass = beginPass;

	unsigned char buffer[ENC_BUFFER_SIZE]{};
	unsigned char* bufferIterator;
	unsigned char* bufferEndPtr = buffer + ENC_BUFFER_SIZE;

	unsigned char temp;

	while (!inputStream.eof() && !this->isCanceled.load()) {
		inputStream.read(reinterpret_cast<char*>(buffer), ENC_BUFFER_SIZE);

		bufferIterator = buffer;
		while (bufferIterator != bufferEndPtr) {
			temp = *(bufferIterator) + rotation;
			temp = reflector[temp] - rotation;
			*(bufferIterator) = temp + *iteratorPass;

			rotation++;
			if (++iteratorPass == endPass) iteratorPass = beginPass;

			bufferIterator++;
			this->progress++;
		}

		outputStream.write(reinterpret_cast<char*>(buffer), inputStream.gcount());
	}
}
void ENC::EncryptExtra::decrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	if (pass.size() < 2) throw Encryptor::EncryptorException(PASSWORD_IS_TOO_SHORT);

	this->progress = 0;

	inputStream.seekg(0, inputStream.end);
	this->total = inputStream.tellg();
	inputStream.seekg(0, inputStream.beg);

	unsigned char rotation = pass[0];

	const unsigned char* beginPass = reinterpret_cast<const unsigned char*>(pass.c_str()) + 1;
	const unsigned char* endPass = beginPass - 1 + pass.size();
	const unsigned char* iteratorPass = beginPass;

	unsigned char buffer[ENC_BUFFER_SIZE]{};
	unsigned char* bufferIterator;
	unsigned char* bufferEndPtr = buffer + ENC_BUFFER_SIZE;

	unsigned char temp;

	while (!inputStream.eof() && !this->isCanceled.load()) {
		inputStream.read(reinterpret_cast<char*>(buffer), ENC_BUFFER_SIZE);

		bufferIterator = buffer;
		while (bufferIterator != bufferEndPtr) {
			temp = *(bufferIterator) + rotation - *iteratorPass;
			temp = reflector[temp] - rotation;
			*(bufferIterator) = temp;

			rotation++;
			if (++iteratorPass == endPass) iteratorPass = beginPass;

			bufferIterator++;
			this->progress++;
		}

		outputStream.write(reinterpret_cast<char*>(buffer), inputStream.gcount());
	}
}