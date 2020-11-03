#pragma once

#include <fstream>

namespace ENC {
	
	class IEncryptStrategy {

	public:
		virtual ~IEncryptStrategy() {};

		virtual void encrypt(std::istream inputStream, std::ostream outputStream, std::string pass) = 0;
		virtual void decrypt(std::ostream outputStream, std::istream inputStream, std::string pass) = 0;

	};

}
