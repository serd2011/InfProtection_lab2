#include "EncryptFactory.h"

#include "Implementation/EncryptCaesar.h"
#include "Implementation/EncryptVigenere.h"
#include "Implementation/EncryptEnigma.h"

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

		default:
			throw std::runtime_error("Invalid Encrypt Strategy Type");
			break;

		}
			
}
