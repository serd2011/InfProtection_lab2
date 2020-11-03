#pragma once

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Encryptor/Encryptor.h"
#include "Utils/EncriptionContainer.h"


using EncryptTypes = Utils::EncryptTypes;

class App : public wxApp {

public:
	virtual bool OnInit() override;

private:
	Encryptor::Encryptor encryptor;
	Utils::EncryptionContainer encryptions;
};