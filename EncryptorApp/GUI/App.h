#pragma once

#include "pch.h"

#include "Encryptor.h"
#include "Utils/EncriptionContainer.h"

#include "EncryptEvent.h"
#include "MainFrame.h"

#include <thread>

using EncryptTypes = Utils::EncryptTypes;

class App : public wxApp {

public:
	virtual bool OnInit() override;
	virtual int OnExit() override;

	virtual void OnUnhandledException() override;

	void OnEncryptStart(StartEncryptEvent&);
	void OnEncryptCancel(CancelEncryptEvent&);

private:
	MainFrame* mainFrame = nullptr;

	std::thread* encryptionThread = nullptr;
	Encryptor::Encryptor encryptor;
	Utils::EncryptionContainer encryptions;
};
