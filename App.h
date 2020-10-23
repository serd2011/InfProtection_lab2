#pragma once

#include <string>

#include "EncryptStrategy.h"

class App {

public:
	App();
	~App();

	void encode(std::string file, std::string pass);
	void decode(std::string file, std::string pass);

	void changeType(ENC::EncryptStrategy& strategy);

private:
	ENC::EncryptStrategy* strategy_;

};
