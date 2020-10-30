#pragma once

#include "../EncryptStrategy.h"

namespace ENC {

	class EncryptEnigma : public EncryptStrategy {

	public:
		virtual void encrypt(std::istream inputStream, std::ostream outputStream, std::string pass) override;
		virtual void decrypt(std::ostream outputStream, std::istream inputStream, std::string pass) override;

	};

}
