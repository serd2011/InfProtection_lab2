#include "MainFrame.h"

namespace Commands {
	enum {
		Quit = wxID_EXIT,
		About  = wxID_ABOUT
	};
}

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style) {

	wxMenu* fileMenu = new wxMenu;
	auto m_menuItem = new wxMenuItem(fileMenu, Commands::Quit, wxString(L"Выход\tAlt+F4"), wxEmptyString, wxITEM_NORMAL);
	fileMenu->Append(m_menuItem);

	wxMenu* helpMenu = new wxMenu;
	m_menuItem = new wxMenuItem(helpMenu, Commands::About, wxString(L"О программе\tF1"), wxEmptyString, wxITEM_NORMAL);
	helpMenu->Append(m_menuItem);

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, L"Файл"); 
	menuBar->Append(helpMenu, L"Справка");

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

	inputFileStaticText = new wxStaticText(this, wxID_ANY, L"Входной файл", wxDefaultPosition, wxDefaultSize, 0);
	FilePickersSizer->Add(inputFileStaticText, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxRIGHT, 5);

	inputFilePicker = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, L"Выберите файл", L"*.*", wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE | wxFLP_FILE_MUST_EXIST | wxFLP_SMALL);
	inputFilePicker->SetMinSize(wxSize(300, -1));
	FilePickersSizer->Add(inputFilePicker, 0, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxLEFT, 5);

	outputFileStaticText = new wxStaticText(this, wxID_ANY, L"Выходной файл", wxDefaultPosition, wxDefaultSize, 0);
	FilePickersSizer->Add(outputFileStaticText, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxRIGHT, 5);

	outputFilePicker = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, L"Выберите файл", L"*.*", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_SMALL | wxFLP_USE_TEXTCTRL);
	inputFilePicker->SetMinSize(wxSize(300, -1));
	FilePickersSizer->Add(outputFilePicker, 0, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxLEFT, 5);

	MainSizer->Add(FilePickersSizer, 0, wxEXPAND | wxALL, 10);

	wxString EncryptionTypeChoices[] = { L"Цезарь", L"Виженер", L"Энигма" };
	int EncryptionTypeNChoices = sizeof(EncryptionTypeChoices) / sizeof(wxString);
	encryptionType = new wxRadioBox(this, wxID_ANY, L"Тип шифрования", wxDefaultPosition, wxDefaultSize, EncryptionTypeNChoices, EncryptionTypeChoices, 1, wxRA_SPECIFY_ROWS);
	encryptionType->SetSelection(0);
	MainSizer->Add(encryptionType, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM | wxRIGHT | wxLEFT, 10);

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer2->AddGrowableCol(1);
	fgSizer2->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	passwordInputStaticText = new wxStaticText(this, wxID_ANY, L"Пароль", wxDefaultPosition, wxDefaultSize, 0);
	passwordInputStaticText->Wrap(-1);
	fgSizer2->Add(passwordInputStaticText, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxRIGHT, 5);

	passwordInputField = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	fgSizer2->Add(passwordInputField, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND | wxTOP | wxBOTTOM | wxLEFT, 5);

	MainSizer->Add(fgSizer2, 0, wxEXPAND | wxBOTTOM | wxRIGHT | wxLEFT, 10);

	startButton = new wxButton(this, wxID_ANY, L"Шифровать", wxDefaultPosition, wxSize(-1, 36), 0);
	MainSizer->Add(startButton, 0, wxEXPAND | wxBOTTOM | wxRIGHT | wxLEFT, 10);

	statusBar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);
	SetStatusText(wxT("Ready"), 0);

	this->SetSizerAndFit(MainSizer);

	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	inputFilePicker->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(MainFrame::inputFilePicker_onFileChanged), NULL, this);
	outputFilePicker->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(MainFrame::outputFilePicker_onFileChanged), NULL, this);
	encryptionType->Connect(wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(MainFrame::encryptionType_onRadioBox), NULL, this);
	startButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::startButton_onButtonClick), NULL, this);
}


// event handlers

void MainFrame::onQuit(wxCommandEvent& WXUNUSED(event)) {
	Close(true);
}

void MainFrame::onAbout(wxCommandEvent& WXUNUSED(event)) {
	wxMessageBox(
		L"Курсовая работа студента 3-го курса Смирнова С.Ю.",
		L"О программе Шифратор",
		wxOK | wxICON_INFORMATION,
		this
	);
}

void MainFrame::inputFilePicker_onFileChanged(wxFileDirPickerEvent& event) {
	event.Skip();
}

void MainFrame::outputFilePicker_onFileChanged(wxFileDirPickerEvent& event) {
	event.Skip();
}

void MainFrame::encryptionType_onRadioBox(wxCommandEvent& event) {
	event.Skip();
}

void MainFrame::startButton_onButtonClick(wxCommandEvent& event) {
	event.Skip();
}
