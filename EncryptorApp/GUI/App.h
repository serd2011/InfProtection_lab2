#pragma once

#include "pch.h"

#include "Encryptor.h"
#include "Utils/EncriptionContainer.h"


using EncryptTypes = Utils::EncryptTypes;

class App : public wxApp {

public:
	virtual bool OnInit() override;

private:
	Encryptor::Encryptor encryptor;
	Utils::EncryptionContainer encryptions;
};