#include "encryption/Implementation/EncryptCaesar.h"

void ENC::EncryptCaesar::encrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	if (pass == "")	throw Encryptor::EncryptorException(PASSWORD_CANT_BE_EMPTY);

	this->progress = 0;

	inputStream.seekg(0, inputStream.end);
	this->total = inputStream.tellg();
	inputStream.seekg(0, inputStream.beg);

	int offset = pass[0];

	unsigned char buffer[ENC_BUFFER_SIZE]{};
	unsigned char* bufferIterator;
	unsigned char* bufferEndPtr = buffer + ENC_BUFFER_SIZE;

	while (!inputStream.eof() && !this->isCanceled.load()) {
		inputStream.read(reinterpret_cast<char*>(buffer), ENC_BUFFER_SIZE);

		bufferIterator = buffer;
		while (bufferIterator != bufferEndPtr) {
			*(bufferIterator) += offset;
			bufferIterator++;
			this->progress++;
		}

		outputStream.write(reinterpret_cast<char*>(buffer), inputStream.gcount());
	}
}

void ENC::EncryptCaesar::decrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	std::string newPass = pass;
	newPass[0] = -newPass[0];
	this->encrypt(inputStream, outputStream, newPass);
}
