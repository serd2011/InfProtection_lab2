#pragma once

#include "../EncryptStrategy.h"

namespace ENC {

	class EncryptVigenere : public IEncryptStrategy {

	public:
		virtual void encrypt(std::istream inputStream, std::ostream outputStream, std::string pass) override;
		virtual void decrypt(std::ostream outputStream, std::istream inputStream, std::string pass) override;

	};

}
