#pragma once

#include "EncryptStrategy.h"

namespace ENC {

	enum class EncryptTypes {
		Caesar,
		Vigenere,
		Enigma,
		Extra
	};

	class EncryptFactory {

	public:
		IEncryptStrategy* getEncrypt(EncryptTypes type);

	};

}
