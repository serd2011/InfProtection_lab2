#include "pch.h"

#include "App.h"

#include "messages.h"

App::~App() {
	delete this->timer;
}

bool App::OnInit() {
	if (!wxApp::OnInit()) return false;

	this->mainFrame = new MainFrame(NULL, wxID_ANY, MESSAGE_MAIN_FRAME_TITLE);
	this->mainFrame->Bind(START_ENCRYPT_EVENT, &App::OnEncryptStart, this);
	this->mainFrame->Bind(CANCEL_ENCRYPT_EVENT, &App::OnEncryptCancel, this);
	this->mainFrame->Show(true);

	this->timer = new wxTimer();

	this->timer->Bind(wxEVT_TIMER, &App::OnTimer, this);

	return true;
}

int App::OnExit() {
	if (this->state == States::encrypt)	wxPostEvent(this, CancelEncryptEvent());
	return 0;
}

bool App::OnExceptionInMainLoop() {
	try { throw; }
	catch (...) {
		wxMessageBox(MESSAGE_UNHANDLED_EXCEPTION_MESSAGE, MESSAGE_UNHANDLED_EXCEPTION_TITLE, wxICON_ERROR);
	}
	return false;
}

void App::OnEncryptStart(StartEncryptEvent& event) {
	if (this->state != States::standBy) return;
	this->state = States::encrypt;
	this->mainFrame->setState(States::encrypt);

	Utils::EncryptTypes type = EncriptionDescriptions[event.getType()].type;
	std::string& inputFile = event.getInputFile();
	std::string& outputFile = event.getOutputFile();
	std::string& pass = event.getPass();
	this->encryptor.changeType(this->encryptions.getEncryption(type));

	this->future_ = std::async(std::launch::async, &Encryptor::Encryptor::encrypt, this->encryptor, inputFile, pass, outputFile);

	this->timer->Start(10);
}

void App::OnEncryptCancel(CancelEncryptEvent&) {
	if (this->state != States::encrypt) return;
	this->state = States::cancel;
	this->mainFrame->setState(States::cancel);
	this->encryptor.cancel();
}

void App::OnTimer(wxTimerEvent&) {
	if (this->state == States::standBy) {
		this->timer->Stop();
		return;
	}
	int progress = (int)(this->encryptor.getProgress() * 100.0);
	if (progress < 0) {
		this->timer->Stop();
		try {
			this->future_.get();
		}
		catch (...) {
			wxMessageBox(MESSAGE_ENCRYPTOR_EXCEPTION_MESSAGE, MESSAGE_ENCRYPTOR_EXCEPTION_TITLE, wxICON_ERROR);
		}
		this->state = States::standBy;
		this->mainFrame->setState(States::standBy);
	}
	else {
		this->mainFrame->updateProgress(progress);
	}
}
