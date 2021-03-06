#include "encryption/Implementation/EncryptEnigma.h"
#include <algorithm>

static const unsigned char first[256]{ 188, 98, 8, 4, 29, 63, 249, 1, 209, 177, 164, 137, 240, 176, 225, 202, 77, 91, 122, 118, 255, 23, 80, 190, 179, 208, 45, 69, 71, 173, 111, 7, 210, 181, 114, 51, 0, 153, 199, 14, 19, 68, 168, 115, 139, 130, 186, 104, 223, 248, 252, 203, 180, 170, 159, 204, 154, 171, 236, 41, 40, 131, 222, 244, 66, 205, 13, 54, 15, 84, 73, 128, 64, 233, 151, 195, 138, 167, 105, 212, 200, 102, 157, 231, 43, 134, 112, 96, 55, 206, 106, 207, 31, 175, 49, 53, 36, 178, 21, 50, 214, 123, 48, 93, 142, 3, 25, 85, 121, 92, 17, 81, 125, 113, 32, 197, 141, 26, 108, 187, 239, 229, 217, 37, 228, 61, 184, 74, 62, 87, 88, 194, 224, 95, 97, 226, 82, 227, 213, 86, 103, 135, 99, 238, 65, 119, 22, 221, 245, 216, 144, 166, 16, 10, 72, 189, 143, 172, 109, 79, 28, 89, 155, 152, 185, 242, 59, 162, 132, 146, 235, 11, 251, 169, 237, 253, 140, 254, 78, 215, 161, 196, 116, 183, 83, 163, 58, 193, 191, 158, 147, 174, 165, 250, 70, 127, 156, 201, 149, 39, 220, 56, 160, 44, 24, 12, 38, 30, 67, 101, 129, 211, 247, 124, 150, 120, 20, 246, 94, 148, 46, 219, 100, 76, 230, 107, 90, 47, 232, 60, 234, 9, 198, 243, 5, 2, 52, 57, 218, 145, 192, 27, 18, 182, 6, 35, 42, 110, 136, 34, 126, 241, 133, 75, 117, 33 };
static const unsigned char firstReverse[256]{ 36, 7, 235, 105, 3, 234, 244, 31, 2, 231, 153, 171, 205, 66, 39, 68, 152, 110, 242, 40, 216, 98, 146, 21, 204, 106, 117, 241, 160, 4, 207, 92, 114, 255, 249, 245, 96, 123, 206, 199, 60, 59, 246, 84, 203, 26, 220, 227, 102, 94, 99, 35, 236, 95, 67, 88, 201, 237, 186, 166, 229, 125, 128, 5, 72, 144, 64, 208, 41, 27, 194, 28, 154, 70, 127, 253, 223, 16, 178, 159, 22, 111, 136, 184, 69, 107, 139, 129, 130, 161, 226, 17, 109, 103, 218, 133, 87, 134, 1, 142, 222, 209, 81, 140, 47, 78, 90, 225, 118, 158, 247, 30, 86, 113, 34, 43, 182, 254, 19, 145, 215, 108, 18, 101, 213, 112, 250, 195, 71, 210, 45, 61, 168, 252, 85, 141, 248, 11, 76, 44, 176, 116, 104, 156,150, 239, 169, 190, 219, 198, 214, 74, 163, 37, 56, 162, 196, 82, 189, 54, 202, 180, 167, 185, 10, 192, 151, 77, 42, 173, 53, 57, 157, 29, 191, 93, 13, 9, 97, 24, 52, 33, 243, 183, 126, 164, 46, 119, 0, 155, 23, 188, 240, 187, 131, 75, 181, 115, 232, 38, 80, 197, 15, 51, 55, 65, 89, 91, 25, 8, 32, 211, 79, 138, 100, 179, 149, 122, 238, 221, 200, 147,62, 48, 132, 14, 135, 137, 124, 121, 224, 83, 228, 73, 230, 170, 58, 174, 143, 120, 12, 251, 165, 233, 63, 148, 217, 212, 49, 6, 193, 172, 50, 175, 177, 20 };
static const unsigned char second[256]{ 219, 238, 23, 144, 117, 40, 191, 44, 176, 241, 181, 218, 214, 252, 19, 229, 141, 16, 10, 72, 146, 108, 104, 234, 123, 55, 253, 149, 121, 97, 155, 174, 163, 6, 118, 220, 140, 12, 161, 194, 151, 0, 64, 122, 116, 166, 49, 154, 248, 188, 235, 15, 76, 186, 222, 196, 32, 43, 85, 7, 107, 237, 127, 244, 245, 86, 80, 202, 225, 159, 247, 124, 41, 56, 89, 175, 71, 168, 92, 67, 137, 249, 96, 208, 22, 205, 223, 150, 213, 14, 30, 48, 128, 156, 209, 187, 206, 114, 143, 153, 33, 233, 115, 34, 210, 200, 106, 170, 112, 79, 51, 98, 8, 199, 100, 95, 129, 246, 192, 70, 27, 53, 232, 250, 169, 221, 162, 131, 130, 24, 109, 39, 207, 47, 142, 29, 230, 83, 119, 101, 2, 255, 180, 58, 195, 74, 171, 182, 11, 217, 240, 45, 61, 172, 165, 204, 59, 111, 62, 113, 57, 68, 126, 164, 9, 228, 215, 236, 82, 152, 179, 21, 93, 65, 178, 52, 63, 31, 125, 110, 139, 216, 132, 94, 148, 91, 66, 87, 50, 46, 77, 242, 157, 158, 224, 69, 197, 54, 103, 251, 211, 35, 147, 239, 28, 212, 20, 201, 18, 13, 102, 81, 42, 227, 167, 177, 173, 1, 99, 226, 193, 198,254, 145, 243, 135, 38, 17, 37, 5, 190, 25, 88, 75, 60, 138, 84, 78, 73, 4, 189, 183, 185, 203, 134, 136, 133, 120, 90, 231, 105, 36, 26, 3, 184, 160 };
static const unsigned char secondReverse[256]{ 41, 217, 140, 253, 239, 229, 33, 59, 112, 164, 18, 148, 37, 209, 89, 51, 17, 227, 208, 14, 206, 171, 84, 2, 129, 231, 252, 120, 204, 135, 90, 177, 56, 100, 103, 201, 251, 228, 226, 131, 5, 72, 212, 57, 7, 151, 189, 133, 91, 46, 188, 110, 175, 121, 197, 25, 73, 160, 143, 156, 234, 152, 158, 176, 42, 173, 186, 79, 161, 195, 119, 76, 19, 238, 145, 233, 52, 190, 237, 109, 66, 211, 168, 137, 236, 58, 65, 187, 232, 74, 248, 185, 78, 172, 183, 115, 82, 29, 111, 218, 114, 139, 210, 198, 22, 250, 106, 60, 21, 130, 179, 157, 108, 159, 97, 102, 44, 4, 34, 138, 247, 28, 43, 24, 71, 178, 162, 62, 92, 116, 128, 127, 182, 246, 244, 225, 245, 80, 235, 180, 36, 16, 134, 98, 3, 223, 20, 202, 184, 27, 87, 40, 169, 99, 47, 30, 93, 192, 193, 69, 255, 38, 126, 32, 163, 154, 45, 214, 77, 124, 107, 146, 153, 216, 31, 75, 8, 215, 174, 170, 142, 10, 147, 241, 254, 242, 53, 95, 49, 240, 230, 6, 118, 220, 39, 144, 55, 196, 221, 113, 105, 207, 67, 243, 155, 85, 96, 132, 83, 94, 104, 200, 205, 88, 12, 166, 181, 149, 11, 0, 35, 125, 54, 86, 194, 68, 219, 213, 165, 15, 136, 249, 122, 101, 23, 50, 167, 61, 1, 203, 150, 9, 191, 224, 63, 64, 117, 70, 48, 81, 123, 199, 13, 26, 222, 141 };
static const unsigned char third[256]{ 159, 102, 27, 235, 103, 225, 224, 230, 78, 212, 246, 172, 209, 253, 42, 95, 4, 29, 121, 228, 218, 0, 76, 91, 204, 196, 170, 197, 233, 61, 59, 173, 16, 245, 117, 163, 58, 133, 122, 30, 93, 51, 32, 106, 207, 241, 39, 12, 10, 139, 113, 79, 119, 152, 98, 129, 89, 231, 164, 17, 45, 56, 180, 250, 142, 47, 155, 33, 72,118, 217, 135, 108, 141, 213, 249, 232, 208, 41, 254, 189, 234, 162, 54, 184, 101, 88, 97, 174, 214, 178, 160, 137, 176, 221, 69, 70, 248, 187, 236, 203, 34, 50, 145, 24, 144, 6, 150, 26, 105, 44, 123, 167, 43, 53, 37, 149, 8, 148, 63, 48, 130, 237, 57, 114, 116, 154, 82, 166, 110, 20, 151, 92, 49, 18, 100, 38, 5, 124, 255, 134, 71, 153, 23, 65, 252,239, 182, 200, 188, 13, 15, 64, 115, 210, 94, 157, 66, 177, 22, 227, 40, 193, 219, 156, 73, 68, 132, 60, 240, 168, 247, 104, 202, 80, 31, 109, 215, 136, 171, 169, 125, 186, 183, 84, 126, 138, 147, 146, 96, 112, 35, 191, 99, 199, 195, 201, 7, 127, 242, 206, 77, 238, 181, 185, 2, 86, 205, 67, 90, 75, 226, 28, 194, 198, 140, 161, 81, 220, 1, 222, 251, 3, 190, 87, 19, 131, 52, 111, 229, 21, 11, 175, 192, 211, 55, 143, 14, 158, 46, 62, 223, 244, 83, 216, 85, 36, 243, 107, 165, 128, 120, 25, 179, 74, 9 };
static const unsigned char thirdReverse[256]{ 21, 219, 205, 222, 16, 137, 106, 197, 117, 255, 48, 231, 47, 150, 237, 151, 32, 59, 134, 225, 130, 230, 159, 143, 104, 252, 108, 2, 212, 17, 39, 175, 42, 67, 101, 191, 246, 115, 136, 46, 161, 78, 14, 113, 110, 60, 239, 65, 120, 133, 102, 41, 227, 114, 83, 235, 61, 123, 36, 30, 168, 29, 240, 119, 152, 144,157, 208, 166, 95, 96, 141, 68, 165, 254, 210, 22, 201, 8, 51, 174, 217, 127, 243, 184, 245, 206, 224, 86, 56, 209, 23, 132, 40, 155, 15, 189, 87, 54, 193, 135, 85, 1, 4, 172, 109, 43, 248, 72, 176, 129, 228, 190, 50, 124, 153, 125, 34, 69, 52, 251, 18, 38, 111, 138, 181, 185, 198, 250, 55, 121, 226, 167, 37, 140, 71, 178, 92, 186, 49, 215, 73, 64, 236, 105, 103, 188, 187, 118, 116, 107, 131, 53, 142, 126, 66, 164, 156, 238, 0, 91, 216, 82, 35, 58, 249, 128, 112, 170, 180, 26, 179, 11, 31, 88, 232, 93, 158, 90, 253, 62, 203, 147, 183, 84, 204, 182, 98, 149, 80, 223, 192, 233, 162, 213, 195, 25, 27, 214, 194, 148, 196, 173, 100, 24, 207, 200, 44, 77, 12, 154, 234, 9, 74, 89, 177, 244, 70, 20, 163,218, 94, 220, 241, 6, 5, 211, 160, 19, 229, 7, 57, 76, 28, 81, 3, 99, 122, 202, 146, 169, 45, 199, 247, 242, 33, 10, 171, 97, 75, 63, 221, 145, 13, 79, 139 };
static const unsigned char reflector[256]{ 47, 91, 86, 205, 142, 235, 199, 43, 105, 175, 101, 254, 38, 144, 50, 22, 165, 34, 213, 197, 201, 176, 15, 42, 48, 99, 84, 249, 140, 134, 96, 168, 133, 107, 17, 62, 89, 117, 12, 57, 162, 150, 23, 7, 190, 210, 234, 0, 24, 81, 14, 138, 203, 87, 98, 236, 248, 39, 121, 230, 179, 159, 35, 147, 93, 156, 182, 158, 108, 218, 115, 153, 174, 206, 171, 220, 114, 188, 243, 92, 187, 49, 110, 251, 26, 112, 2, 53, 126, 36, 146, 1, 79, 64, 252, 228, 30, 100, 54, 25, 97, 10, 106, 238, 191, 8, 102, 33, 68, 164, 82, 170, 85, 130, 76, 70, 137, 37, 198, 152, 141, 58, 155, 173, 237, 145, 88, 207, 204, 233, 113, 255, 154, 32, 29, 241, 242, 116, 51, 245, 28, 120, 4, 209, 13, 125, 90, 63, 189, 161, 41, 177, 119, 71, 132, 122, 65, 200, 67, 61, 226, 149, 40, 169, 109, 16, 227, 219, 31, 163, 111, 74, 202, 123, 72, 9, 21, 151, 184, 60, 232, 250, 66, 244, 178, 196, 194, 80, 77, 148, 44, 104, 193, 192, 186, 208, 185, 19, 118, 6, 157, 20, 172, 52, 128, 3, 73, 127, 195, 143, 45, 215, 221, 18, 216, 211, 214, 224, 69, 167, 75, 212, 223, 222, 217, 239, 160, 166, 95, 231, 59, 229, 180, 129, 46, 5, 55, 124, 103, 225, 253, 135, 136, 78, 183, 139, 247, 246, 56, 27, 181, 83, 94, 240, 11, 131 };

void ENC::EncryptEnigma::encrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	if (pass.size() < 5) throw Encryptor::EncryptorException(PASSWORD_IS_TOO_SHORT);

	this->progress = 0;

	inputStream.seekg(0, inputStream.end);
	this->total = inputStream.tellg();
	inputStream.seekg(0, inputStream.beg);

	unsigned char firstRotation = pass[0];
	unsigned char secondRotation = pass[1];
	unsigned char thirdRotation = pass[2];

	unsigned char changePanel[256] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106,107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162,163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255 };
	std::string uniquePass = pass.substr(3);
	std::sort(uniquePass.begin(), uniquePass.end());
	auto endUniquePass = std::unique(uniquePass.begin(), uniquePass.end());
	for (auto it = uniquePass.begin(); it != endUniquePass; it += 2) {
		if (it + 1 == endUniquePass) break;
		changePanel[*it] = *(it + 1);
		changePanel[*(it + 1)] = *it;
	}

	unsigned char buffer[ENC_BUFFER_SIZE]{};
	unsigned char* bufferIterator;
	unsigned char* bufferEndPtr = buffer + ENC_BUFFER_SIZE;

	unsigned char temp;

	while (!inputStream.eof() && !this->isCanceled.load()) {
		inputStream.read(reinterpret_cast<char*>(buffer), ENC_BUFFER_SIZE);

		bufferIterator = buffer;
		while (bufferIterator != bufferEndPtr) {
			temp = *(bufferIterator);

			temp = changePanel[temp];
			temp += firstRotation;
			temp = first[temp] - firstRotation;
			temp += secondRotation;
			temp = second[temp] - secondRotation;
			temp += thirdRotation;
			temp = third[temp] - thirdRotation;
			temp = reflector[temp];
			temp += thirdRotation;
			temp = thirdReverse[temp] - thirdRotation;
			temp += secondRotation;
			temp = secondReverse[temp] - secondRotation;
			temp += firstRotation;
			temp = firstReverse[temp] - firstRotation;
			temp = changePanel[temp];

			*(bufferIterator) = temp;

			if (++firstRotation == 0) if (++secondRotation == 0) thirdRotation++;

			bufferIterator++;
			this->progress++;
		}

		outputStream.write(reinterpret_cast<char*>(buffer), inputStream.gcount());
	}
}

void ENC::EncryptEnigma::decrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	this->encrypt(inputStream, outputStream, pass);
}
