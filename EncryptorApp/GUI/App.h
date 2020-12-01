#pragma once
#include "pch.h"

// Encryptor
#include "Encryptor.h"
// GUI
#include "MainFrame.h"
#include "EncryptEvent.h"
#include "defines.h"
// STD
#include <thread>
#include <future>

class App : public wxApp {

public:

	~App();

	virtual bool OnInit() override;
	virtual int OnExit() override;

	virtual bool OnExceptionInMainLoop() override;

	void OnEncryptStart(StartEncryptEvent&);
	void OnEncryptCancel(CancelEncryptEvent&);

	void OnTimer(wxTimerEvent&);

private:
	MainFrame* mainFrame = nullptr;

	wxTimer* timer = nullptr;

	std::future<void> future_;

	Encryptor::Encryptor encryptor;
	Utils::EncryptionContainer encryptions;

	States state = States::standBy;
};