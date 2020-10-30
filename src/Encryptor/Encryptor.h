#pragma once

#include <string>

#include "encryption/EncryptStrategy.h"

class Encryptor {

public:
	Encryptor();
	~Encryptor();

	void encode(std::string file, std::string pass);
	void decode(std::string file, std::string pass);

	void changeType(ENC::EncryptStrategy& strategy);

private:
	ENC::EncryptStrategy* strategy_;

};
