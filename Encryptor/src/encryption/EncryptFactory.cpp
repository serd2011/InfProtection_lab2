#include "encryption/EncryptFactory.h"

#include "encryption/Implementation/EncryptCaesar.h"
#include "encryption/Implementation/EncryptVigenere.h"
#include "encryption/Implementation/EncryptEnigma.h"
#include "encryption/Implementation/EncryptExtra.h"

ENC::IEncryptStrategy* ENC::EncryptFactory::getEncrypt(EncryptTypes type) {

	switch (type) {

	case ENC::EncryptTypes::Caesar:
		return new EncryptCaesar();
		break;

	case ENC::EncryptTypes::Vigenere:
		return new EncryptVigenere();
		break;

	case ENC::EncryptTypes::Enigma:
		return new EncryptEnigma();
		break;

	case ENC::EncryptTypes::Extra:
		return new EncryptExtra();
		break;

	default:
		throw std::runtime_error("Invalid Encrypt Strategy Type");
		break;
	}

}
