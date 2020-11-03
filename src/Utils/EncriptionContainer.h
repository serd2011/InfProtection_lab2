#pragma once

#include <map>
#include <string>

#include "Encryptor/encryption/EncryptFactory.h"

namespace Utils {

    using EncryptTypes = ENC::EncryptTypes;

    class EncryptionContainer {

    public:
        EncryptionContainer();
        ~EncryptionContainer();

        ENC::IEncryptStrategy& getStrategy(ENC::EncryptTypes type);

    private:
        EncryptionContainer(const EncryptionContainer&);
        EncryptionContainer& operator=(const EncryptionContainer&);

        std::map<ENC::EncryptTypes, ENC::IEncryptStrategy*> instances_;

        ENC::EncryptFactory factory_;
    };
}