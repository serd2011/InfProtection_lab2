#pragma once

#include "EncryptStrategy.h"

#include "Implementation/EncryptCaesar.h"
#include "Implementation/EncryptVigenere.h"
#include "Implementation/EncryptEnigma.h"

namespace ENC {

	enum class EncryptTypes {
		Caesar,
		Vigenere,
		Enigma
	};

	class EncryptFactory {

	public:
		EncryptStrategy* getEncrypt(EncryptTypes type);

	};

}
