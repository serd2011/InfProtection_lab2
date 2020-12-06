#pragma once

#include "../EncryptStrategy.h"

namespace ENC {

	class EncryptExtra : public IEncryptStrategy {

	public:
		virtual void encrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) override;
		virtual void decrypt(std::istream& inputStream, std::ostream& outputStream, const std::string& pass) override;

	};

}
