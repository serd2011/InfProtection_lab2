#include "pch.h"

#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	if (!wxApp::OnInit()) return false;

	this->mainFrame = new MainFrame(NULL, wxID_ANY, L"Шифратор");
	this->mainFrame->Bind(START_ENCRYPT_EVENT, &App::OnEncryptStart, this);
	this->mainFrame->Bind(CANCEL_ENCRYPT_EVENT, &App::OnEncryptCancel, this);
	this->mainFrame->Show(true);

	return true;
}

int App::OnExit() {
	//this->encryptionThread->join();
	//delete this->encryptionThread;
	return 0;
}

void App::OnUnhandledException() {
	try { throw; } catch (std::exception& e) {
		wxMessageBox(e.what(), "Необработанное исключение", wxICON_ERROR);
	}
}

void App::OnEncryptStart(StartEncryptEvent&) {
	this->mainFrame->startState();
}

void App::OnEncryptCancel(CancelEncryptEvent&) {
	this->mainFrame->standByState();
}
