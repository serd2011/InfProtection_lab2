#pragma once

#include <fstream>
#include <atomic>

#include "defs.h"

#include "EncryptorException.h"

namespace Encryptor {
	class Encryptor;
}

namespace ENC {

	class IEncryptStrategy {

	public:
		virtual ~IEncryptStrategy() {};

		virtual void encrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) = 0;
		virtual void decrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) = 0;

	protected:
		std::atomic<bool> isCanceled = true;
		std::atomic<unsigned long long> total = 1;
		std::atomic<unsigned long long> progress = 0;

		friend Encryptor::Encryptor;

	};

}
