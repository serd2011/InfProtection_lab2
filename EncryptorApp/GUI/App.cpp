#include "pch.h"

#include "App.h"
#include <wx/filefn.h> 

#include "messages.h"
#include "Utils/functions.h"

#include "EncryptorException.h"

static std::map<Utils::EncryptTypes, unsigned int> minPasswordLenght{ {Utils::EncryptTypes::Caesar,1},{Utils::EncryptTypes::Vigenere,1},{Utils::EncryptTypes::Enigma,5},{Utils::EncryptTypes::Extra,2},{Utils::EncryptTypes::Hill,16} };

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
	this->timer->Stop();
	delete this->timer;
	this->encryptor.cancel();
	if (this->future_.valid()) this->future_.get();
	return 0;
}

bool App::OnExceptionInMainLoop() {
	try {
		throw;
	} catch (...) {
		wxMessageBox(MESSAGE_UNHANDLED_EXCEPTION_MESSAGE, MESSAGE_UNHANDLED_EXCEPTION_TITLE, wxICON_ERROR);
	}
	return false;
}

void App::OnEncryptStart(StartEncryptEvent& event) {
	if (this->state != States::standBy) return;

	Utils::EncryptTypes type = EncriptionDescriptions[event.getType()].type;
	std::string& inputFile = event.getInputFile();
	std::string& outputFile = event.getOutputFile();
	std::string& pass = event.getPass();
	auto action = event.getAction();
	this->encryptor.changeType(this->encryptions.getEncryption(type));
	auto function = (action == StartEncryptEvent::Actions::encrypt ? &Encryptor::Encryptor::encrypt : &Encryptor::Encryptor::decrypt);

	//Validation

	if (!wxFileExists(inputFile)) {
		wxMessageBox(MESSAGE_INPUT_FILE_DOESNT_EXIST_MESSAGE, MESSAGE_INPUT_VALIDATION_ERROR_TITLE, wxICON_INFORMATION);
		return;
	}

	if (pass.length() < minPasswordLenght[type]) {
		wxMessageBox(MESSAGE_PASS_TOO_SHORT + std::to_wstring(minPasswordLenght[type]), MESSAGE_INPUT_VALIDATION_ERROR_TITLE, wxICON_INFORMATION);
		return;
	}

	// Encryption start
	this->state = States::encrypt;
	this->mainFrame->setState(action == StartEncryptEvent::Actions::encrypt ? States::encrypt : States::decrypt);

	this->future_ = std::async(std::launch::async, function, this->encryptor, inputFile, pass, outputFile);

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
		if (!this->future_.valid()) {
			this->mainFrame->setState(States::error);
			this->state = States::cancel;
			return;
		}
		try {
			this->future_.get();
		} catch (const Encryptor::EncryptorException& e) {
			this->mainFrame->setState(States::error);
			this->state = States::cancel;
			wxMessageBox(Utils::getLocalizedMessage(e.getId()), MESSAGE_ENCRYPTOR_EXCEPTION_TITLE, wxICON_ERROR);
		} catch (...) {
			this->mainFrame->setState(States::error);
			this->state = States::cancel;
			wxMessageBox(MESSAGE_ENCRYPTOR_EXCEPTION_MESSAGE, MESSAGE_ENCRYPTOR_EXCEPTION_TITLE, wxICON_ERROR);
		}
		if (this->state == States::cancel) {
			this->mainFrame->setState(States::standBy);
		} else {
			this->mainFrame->setState(States::done);
		}
		this->state = States::standBy;
	} else {
		this->mainFrame->updateProgress(progress);
	}
}
