#include "Encryptor.h"

Encryptor::Encryptor::Encryptor() {
	this->strategy_ = nullptr;
}

Encryptor::Encryptor::~Encryptor() {}

void Encryptor::Encryptor::encrypt(const std::string& inputfile, const std::string& pass, const std::string& outputfile) {
	crypt(cryptType::encrypt, inputfile, pass, outputfile);
}

void Encryptor::Encryptor::decrypt(const std::string& inputfile, const std::string& pass, const std::string& outputfile) {
	crypt(cryptType::decrypt, inputfile, pass, outputfile);
}

void Encryptor::Encryptor::changeType(ENC::IEncryptStrategy& strategy) {
	if (this->strategy_ != nullptr && !this->strategy_->isCanceled.load()) throw EncryptorException("Encryption is in progress");
	this->strategy_ = &strategy;
}

void Encryptor::Encryptor::cancel() {
	this->strategy_->isCanceled = true;
}

double Encryptor::Encryptor::getProgress() {
	if (this->strategy_ == nullptr) throw EncryptorException("Encryption is not set");
	if (this->strategy_->isCanceled.load())	return -1;
	return this->strategy_->progress.load() / (double)this->strategy_->total.load();
}

void Encryptor::Encryptor::crypt(cryptType type, const std::string& inputfile, const std::string& pass, const std::string& outputfile) {
	if (this->strategy_ == nullptr)	throw EncryptorException("Encryption type is not set");

	this->strategy_->isCanceled = false;

	std::string outputFileName = outputfile == "" ? inputfile + ".enc" : outputfile;
	std::ifstream inputFileStream(inputfile, std::ios::binary);
	std::ofstream outputFileStream(outputFileName, std::ios::binary | std::ios::trunc);
	if (!inputFileStream.is_open() || !outputFileStream.is_open()) {
		this->strategy_->isCanceled = true;
		throw EncryptorException("Can't open file");
	}

	if (type == cryptType::encrypt) {
		this->strategy_->encrypt(inputFileStream, outputFileStream, pass);
	}
	else {
		this->strategy_->decrypt(inputFileStream, outputFileStream, pass);
	}

	inputFileStream.close();
	outputFileStream.close();

	if (this->strategy_->isCanceled.load())
		std::remove(outputFileName.c_str());

	this->strategy_->isCanceled = true;
}

bool Encryptor::Encryptor::isRunning() {
	if (this->strategy_ == nullptr) return false;
	if (this->strategy_->isCanceled.load()) return false;
	return true;
}