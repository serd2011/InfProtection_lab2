#pragma once

#include <string>

#include "encryption/EncryptStrategy.h"

namespace Encryptor {
	
	class Encryptor {

	public:
		Encryptor();
		~Encryptor();

		void encode(std::string file, std::string pass);
		void decode(std::string file, std::string pass);

		void changeType(ENC::IEncryptStrategy& strategy);

	private:
		ENC::IEncryptStrategy* strategy_;

	};

}