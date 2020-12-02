#include "encryption/Implementation/EncryptCaesar.h"

void ENC::EncryptCaesar::encrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	if (pass == "")	throw Encryptor::EncryptorException("Password can't be empty");

	this->progress = 0;
	int offset = pass[0];

	inputStream.seekg(0, inputStream.end);
	this->total = inputStream.tellg();
	inputStream.seekg(0, inputStream.beg);

	char buffer[ENC_BUFFER_SIZE]{};
	char* bufferIterator;
	char* bufferEndPtr = buffer + ENC_BUFFER_SIZE;

	while (!inputStream.eof() && !this->isCanceled.load()) {
		inputStream.read(buffer, ENC_BUFFER_SIZE);

		bufferIterator = buffer;
		while (bufferIterator != bufferEndPtr) {
			*(bufferIterator) += offset;
			bufferIterator++;
			this->progress++;
		}

		outputStream.write(buffer, inputStream.gcount());
	}
}

void ENC::EncryptCaesar::decrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	std::string newPass = pass;
	newPass[0] = -newPass[0];
	this->encrypt(inputStream, outputStream, newPass);
}
