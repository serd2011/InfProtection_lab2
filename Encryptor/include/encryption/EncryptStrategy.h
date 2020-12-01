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
		std::atomic<bool> isCanceled;
		std::atomic<unsigned long long> total;
		std::atomic<unsigned long long> progress;

		friend Encryptor::Encryptor;

	};

}
