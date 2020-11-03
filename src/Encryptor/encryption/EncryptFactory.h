#pragma once

#include "EncryptStrategy.h"

namespace ENC {

	enum class EncryptTypes {
		Caesar,
		Vigenere,
		Enigma
	};

	class EncryptFactory {

	public:
		IEncryptStrategy* getEncrypt(EncryptTypes type);

	};

}
