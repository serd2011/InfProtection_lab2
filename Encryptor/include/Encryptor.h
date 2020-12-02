#pragma once

#include <string>

#include "encryption/EncryptStrategy.h"

#include "EncryptorException.h"

namespace Encryptor {

	class Encryptor {

	public:
		Encryptor();
		~Encryptor();

		void encrypt(const std::string& inputFile, const std::string& pass, const std::string& outputFile);
		void decrypt(const std::string& inputFile, const std::string& pass, const std::string& outputFile);

		void changeType(ENC::IEncryptStrategy& strategy);

		void cancel();
		double getProgress();

		bool isRunning();

	private:
		ENC::IEncryptStrategy* strategy_;

		enum class cryptType {
			encrypt,
			decrypt
		};

		void crypt(cryptType type, const std::string& inputFile, const std::string& pass, const std::string& outputFile);

	};

}
