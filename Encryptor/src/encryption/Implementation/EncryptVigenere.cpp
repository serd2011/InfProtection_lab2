#include "encryption/Implementation/EncryptVigenere.h"

void ENC::EncryptVigenere::encrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	if (pass == "")	throw Encryptor::EncryptorException("Password can't be empty");

	this->progress = 0;

	const char* beginPass = pass.c_str();
	const char* endPass = beginPass + pass.size();
	const char* iteratorPass = beginPass;

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
			*(bufferIterator) += *iteratorPass;
			bufferIterator++;
			this->progress++;
			iteratorPass++;
			if (iteratorPass == endPass) iteratorPass = beginPass;
		}

		outputStream.write(buffer, ENC_BUFFER_SIZE);
	}

}

void ENC::EncryptVigenere::decrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	std::string newPass = pass;
	for (char& c : newPass) { c = -c; }
	this->encrypt(inputStream, outputStream, newPass);
}
