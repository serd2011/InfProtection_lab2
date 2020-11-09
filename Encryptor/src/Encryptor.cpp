#include "Encryptor.h"

Encryptor::Encryptor::Encryptor() {
	strategy_ = nullptr;
}

Encryptor::Encryptor::~Encryptor() {}

void Encryptor::Encryptor::changeType(ENC::IEncryptStrategy& strategy) {
	strategy_ = &strategy;
}
