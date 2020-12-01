#include "pch.h"

#include "MainFrame.h"
#include "EncryptEvent.h"

#include "messages.h"

namespace Commands {
	enum {
		Quit = wxID_EXIT,
		About = wxID_ABOUT
	};
}

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style) {

	wxMenu* fileMenu = new wxMenu;
	auto m_menuItem = new wxMenuItem(fileMenu, Commands::Quit, MESSAGE_EXIT_MENU_ITEM_TITLE, wxEmptyString, wxITEM_NORMAL);
	fileMenu->Append(m_menuItem);

	wxMenu* helpMenu = new wxMenu;
	m_menuItem = new wxMenuItem(helpMenu, Commands::About, MESSAGE_ABOUT_MENU_ITEM_TITLE, wxEmptyString, wxITEM_NORMAL);
	helpMenu->Append(m_menuItem);

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, MESSAGE_FILE_MENU_TITLE);
	menuBar->Append(helpMenu, MESSAGE_HELP_MENU_TITLE);

	SetMenuBar(menuBar);

	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onQuit), this, Commands::Quit);
	helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onAbout), this, Commands::About);

	this->SetBackgroundColour(wxColour(255, 255, 255));

	wxBoxSizer* MainSizer;
	MainSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* FilePickersSizer;
	FilePickersSizer = new wxFlexGridSizer(2, 2, 0, 0);
	FilePickersSizer->AddGrowableCol(1);
	FilePickersSizer->SetFlexibleDirection(wxHORIZONTAL);
	FilePickersSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	this->inputFileStaticText = new wxStaticText(this, wxID_ANY, MESSAGE_INPUT_FILE_TITLE, wxDefaultPosition, wxDefaultSize, 0);
	FilePickersSizer->Add(inputFileStaticText, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxRIGHT, 5);

	this->inputFilePicker = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, MESSAGE_CHOOSE_FILE_MESSAGE, L"*.*", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_SMALL | wxFLP_USE_TEXTCTRL | wxFLP_CHANGE_DIR | wxFLP_FILE_MUST_EXIST);
	this->inputFilePicker->SetMinSize(wxSize(300, -1));
	this->inputFilePicker->DragAcceptFiles(true);
	FilePickersSizer->Add(this->inputFilePicker, 0, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxLEFT, 5);

	this->outputFileStaticText = new wxStaticText(this, wxID_ANY, MESSAGE_OUTPUT_FILE_TITLE, wxDefaultPosition, wxDefaultSize, 0);
	FilePickersSizer->Add(this->outputFileStaticText, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxRIGHT, 5);

	this->outputFilePicker = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, MESSAGE_CHOOSE_FILE_MESSAGE, L"*.enc", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_SMALL | wxFLP_USE_TEXTCTRL | wxFLP_CHANGE_DIR | wxFLP_OVERWRITE_PROMPT);
	this->inputFilePicker->SetMinSize(wxSize(300, -1));
	FilePickersSizer->Add(this->outputFilePicker, 0, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxLEFT, 5);

	MainSizer->Add(FilePickersSizer, 0, wxEXPAND | wxALL, 10);

	constexpr size_t count = EncriptionDescriptions.size();
	wxString EncryptionTypeChoices[count];
	for (size_t i = 0; i < count; i++) {
		EncryptionTypeChoices[i] = EncriptionDescriptions[i].name;
	}
	this->encryptionType = new wxRadioBox(this, wxID_ANY, MESSAGE_ENCRYPTION_TYPE_TITLE, wxDefaultPosition, wxDefaultSize, count, EncryptionTypeChoices, 1, wxRA_SPECIFY_ROWS);
	this->encryptionType->SetSelection(0);
	MainSizer->Add(this->encryptionType, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM | wxRIGHT | wxLEFT, 10);

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer2->AddGrowableCol(1);
	fgSizer2->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	this->passwordInputStaticText = new wxStaticText(this, wxID_ANY, MESSAGE_PASS_TITLE, wxDefaultPosition, wxDefaultSize, 0);
	this->passwordInputStaticText->Wrap(-1);
	fgSizer2->Add(this->passwordInputStaticText, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxRIGHT, 5);

	this->passwordInputField = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	fgSizer2->Add(this->passwordInputField, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND | wxTOP | wxBOTTOM | wxLEFT, 5);

	MainSizer->Add(fgSizer2, 0, wxEXPAND | wxBOTTOM | wxRIGHT | wxLEFT, 10);

	this->startButton = new wxButton(this, wxID_ANY, MESSAGE_ENCRYPT_BUTTON_TITLE, wxDefaultPosition, wxSize(-1, 36), 0);
	MainSizer->Add(this->startButton, 0, wxEXPAND | wxBOTTOM | wxRIGHT | wxLEFT, 10);

	this->cancelButton = new wxButton(this, wxID_ANY, MESSAGE_CANCEL_BUTTON_TITLE, wxDefaultPosition, wxSize(-1, 36), 0);
	MainSizer->Add(this->cancelButton, 0, wxEXPAND | wxBOTTOM | wxRIGHT | wxLEFT, 10);
	this->cancelButton->Hide();

	this->statusBar = new StatusBar(this, wxID_ANY);
	this->SetStatusBar(this->statusBar);

	this->SetSizerAndFit(MainSizer);

	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	this->inputFilePicker->Bind(wxEVT_DROP_FILES, &MainFrame::inputFilePicker_onDropFiles, this);
	this->startButton->Bind(wxEVT_BUTTON, &MainFrame::startButton_onClick, this);
	this->cancelButton->Bind(wxEVT_BUTTON, &MainFrame::cancelButton_onClick, this);

	this->setState(States::standBy);
}

// event handlers

void MainFrame::onQuit(wxCommandEvent& WXUNUSED(event)) {
	Close(true);
}

void MainFrame::onAbout(wxCommandEvent& WXUNUSED(event)) {
	wxMessageBox(
		MESSAGE_ABOUT_MESSAGE,
		MESSAGE_ABOUT_TITLE,
		wxOK | wxICON_INFORMATION,
		this
	);
}

void MainFrame::inputFilePicker_onDropFiles(wxDropFilesEvent& event) {
	if (event.GetNumberOfFiles() > 0) {
		wxString* dropped = event.GetFiles();
		if (wxDirExists(dropped[0])) {
			this->inputFilePicker->SetPath(L"");
		}
		else {
			this->inputFilePicker->SetPath(dropped[0]);
		}
	}
	else {
		this->inputFilePicker->SetPath(L"");
	}
	event.Skip();
}

void MainFrame::startButton_onClick(wxCommandEvent& event) {
	std::string inputFile = this->inputFilePicker->GetPath();
	std::string outputFile = this->outputFilePicker->GetPath();
	std::string pass = this->passwordInputField->GetLineText(0);
	size_t type = this->encryptionType->GetSelection();
	StartEncryptEvent encryptEvent(inputFile, outputFile, pass, type);
	wxPostEvent(this, encryptEvent);
}

void MainFrame::cancelButton_onClick(wxCommandEvent& event) {
	wxPostEvent(this, CancelEncryptEvent());
}

void MainFrame::setState(States state) {
	switch (state) {
	case States::standBy:
		this->cancelButton->Hide();
		this->startButton->Show();
		this->inputFilePicker->Enable(true);
		this->outputFilePicker->Enable(true);
		this->encryptionType->Enable(true);
		this->passwordInputField->Enable(true);
		this->cancelButton->Enable(true);
		this->statusBar->clearStatus();
		this->statusBar->hideProgress();
		break;
	case States::encrypt:
		this->cancelButton->Show();
		this->startButton->Hide();
		this->inputFilePicker->Enable(false);
		this->outputFilePicker->Enable(false);
		this->encryptionType->Enable(false);
		this->passwordInputField->Enable(false);
		this->cancelButton->Enable(true);
		this->statusBar->setStatus(MESSAGE_ENCRIPTION_IN_PROGRESSS_TATUS);
		this->statusBar->showProgress(100);
		break;
	case States::cancel:
		this->cancelButton->Enable(false);
		this->statusBar->setStatus(MESSAGE_CANCELING_STATUS);
		break;
	}
	this->Layout();
}

void MainFrame::updateProgress(unsigned int progress) {
	this->statusBar->setProgress(progress);
	this->Layout();
}