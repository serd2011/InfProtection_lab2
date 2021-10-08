#pragma once

#include <stdexcept>

namespace Encryptor {

	class EncryptorException : public std::exception {
	public:
		explicit EncryptorException(const char* message, int id = 0) : std::exception(message), id(id) {};
		int getId() const;
	private:
		int id;
	};

}
