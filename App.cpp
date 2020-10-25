#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class App : public wxApp {
public:
	virtual bool OnInit() override;
};

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
	void OnQuit(wxCommandEvent& event);
	void OnSettings(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

private:
	wxDECLARE_EVENT_TABLE();
};

namespace Commands {
	enum {
		Quit = wxID_EXIT,
		About = wxID_ABOUT,
		Settings
	};
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(Commands::Quit, MainFrame::OnQuit)
EVT_MENU(Commands::Settings, MainFrame::OnSettings)
EVT_MENU(Commands::About, MainFrame::OnAbout)
wxEND_EVENT_TABLE()


wxIMPLEMENT_APP(App);


bool App::OnInit() {
	if (!wxApp::OnInit())
		return false;
	MainFrame* frame = new MainFrame("Шифратор");
	frame->Show(true);
	return true;
}

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
	//SetIcon(wxICON(sample));

#if wxUSE_MENUBAR

	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(Commands::Settings, "Настройки");
	fileMenu->Append(Commands::Quit, "Выход\tAlt+F4");

	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(Commands::About, "О программе\tF1");

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "Файл");
	menuBar->Append(helpMenu, "Справка");

	SetMenuBar(menuBar);
#endif

}


// event handlers

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
	Close(true);
}

void MainFrame::OnSettings(wxCommandEvent& event) {}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
	wxMessageBox(
		"Курсовая работа студента 3-го курса Смирнова С.Ю.",
		"О программе Шифратор",
		wxOK | wxICON_INFORMATION,
		this
	);
}
