#include "encryption/Implementation/EncryptVigenere.h"

void ENC::EncryptVigenere::encrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	if (pass == "")	throw Encryptor::EncryptorException(PASSWORD_IS_TOO_SHORT);

	this->progress = 0;

	inputStream.seekg(0, inputStream.end);
	this->total = inputStream.tellg();
	inputStream.seekg(0, inputStream.beg);

	const unsigned char* beginPass = reinterpret_cast<const unsigned char*>(pass.c_str());
	const unsigned char* endPass = beginPass + pass.size();
	const unsigned char* iteratorPass = beginPass;

	unsigned char buffer[ENC_BUFFER_SIZE]{};
	unsigned char* bufferIterator;
	unsigned char* bufferEndPtr = buffer + ENC_BUFFER_SIZE;

	while (!inputStream.eof() && !this->isCanceled.load()) {
		inputStream.read(reinterpret_cast<char*>(buffer), ENC_BUFFER_SIZE);

		bufferIterator = buffer;
		while (bufferIterator != bufferEndPtr) {
			*(bufferIterator) += *iteratorPass;
			bufferIterator++;
			this->progress++;
			iteratorPass++;
			if (iteratorPass == endPass) iteratorPass = beginPass;
		}

		outputStream.write(reinterpret_cast<char*>(buffer), inputStream.gcount());
	}

}

void ENC::EncryptVigenere::decrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) {
	std::string newPass = pass;
	for (char& c : newPass) { c = -c; }
	this->encrypt(inputStream, outputStream, newPass);
}
