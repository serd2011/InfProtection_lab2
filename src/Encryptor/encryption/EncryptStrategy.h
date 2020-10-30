#pragma once

#include <fstream>

namespace ENC {

	class EncryptStrategy {
	public:
		virtual ~EncryptStrategy() {};
		virtual void encrypt(std::istream inputStream, std::ostream outputStream, std::string pass) = 0;
		virtual void decrypt(std::ostream outputStream, std::istream inputStream, std::string pass) = 0;
	};

}
