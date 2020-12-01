#pragma once

#include <stdexcept>

namespace Encryptor {

	class EncryptorException : public std::exception {
	public:
		explicit EncryptorException(const char* message) : std::exception(message) {};
	};

}
