#include "EncriptionContainer.h"

Utils::EncryptionContainer::EncryptionContainer() {
    instances_ = std::map<ENC::EncryptTypes, ENC::IEncryptStrategy*>();
    factory_ = ENC::EncryptFactory();
}

Utils::EncryptionContainer::~EncryptionContainer() {}

ENC::IEncryptStrategy& Utils::EncryptionContainer::getStrategy(ENC::EncryptTypes type) {

    auto it = instances_.find(type);

    if (it != instances_.end()) {
        return *(it->second);
    }

    instances_[type] = factory_.getEncrypt(type);
    return *(instances_[type]);
}
