#pragma once

#include <map>
#include <string>

#include "encryption/EncryptFactory.h"

namespace Utils {

    using EncryptTypes = ENC::EncryptTypes;

    class EncryptionContainer {

    public:
        EncryptionContainer();
        ~EncryptionContainer();

        ENC::IEncryptStrategy& getEncryption(ENC::EncryptTypes type);

    private:
        EncryptionContainer(const EncryptionContainer&) = delete;
        EncryptionContainer& operator=(const EncryptionContainer&) = delete;

        std::map<ENC::EncryptTypes, ENC::IEncryptStrategy*> instances_;

        ENC::EncryptFactory factory_;
    };

}
