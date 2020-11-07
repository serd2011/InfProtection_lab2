#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	if (!wxApp::OnInit())
		return false;
	MainFrame* frame = new MainFrame(NULL, wxID_ANY, L"Шифратор");
	frame->Show(true);
	return true;
}