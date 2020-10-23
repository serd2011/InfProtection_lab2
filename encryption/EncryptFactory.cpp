#include "EncryptFactory.h"

ENC::EncryptStrategy* ENC::EncryptFactory::getEncrypt(EncryptTypes type) {

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
