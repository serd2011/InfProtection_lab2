#include "MainFrame.h"

namespace Commands {
	enum {
		Quit = wxID_EXIT,
		About  = wxID_ABOUT
	};
}

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style) {

#if wxUSE_MENUBAR

	wxMenu* fileMenu = new wxMenu;
	auto m_menuItem = new wxMenuItem(fileMenu, Commands::Quit, wxString(wxT("Выход\tAlt+F4")), wxEmptyString, wxITEM_NORMAL);
	fileMenu->Append(m_menuItem);

	wxMenu* helpMenu = new wxMenu;
	m_menuItem = new wxMenuItem(helpMenu, Commands::About, wxString(wxT("О программе\tF1")), wxEmptyString, wxITEM_NORMAL);
	helpMenu->Append(m_menuItem);

	wxMenuBar* menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "Файл"); 
	menuBar->Append(helpMenu, "Справка");

	SetMenuBar(menuBar);

	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnQuit), this, Commands::Quit);
	helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnAbout), this, Commands::About);

#endif

	this->SetBackgroundColour(wxColour(255, 255, 255));

	wxBoxSizer* MainSizer;
	MainSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* FilePickersSizer;
	FilePickersSizer = new wxFlexGridSizer(2, 2, 0, 0);
	FilePickersSizer->AddGrowableCol(1);
	FilePickersSizer->SetFlexibleDirection(wxHORIZONTAL);
	FilePickersSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	InputFileStaticText = new wxStaticText(this, wxID_ANY, wxT("Входной файл"), wxDefaultPosition, wxDefaultSize, 0);
	FilePickersSizer->Add(InputFileStaticText, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxRIGHT, 5);

	InputFilePicker = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Выберите файл"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE | wxFLP_FILE_MUST_EXIST | wxFLP_SMALL);
	InputFilePicker->SetMinSize(wxSize(300, -1));
	FilePickersSizer->Add(InputFilePicker, 0, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxLEFT, 5);

	OutputFileStaticText = new wxStaticText(this, wxID_ANY, wxT("Выходной файл"), wxDefaultPosition, wxDefaultSize, 0);
	FilePickersSizer->Add(OutputFileStaticText, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxRIGHT, 5);

	OutputFilePicker = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Выберите файл"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_SMALL | wxFLP_USE_TEXTCTRL);
	InputFilePicker->SetMinSize(wxSize(300, -1));
	FilePickersSizer->Add(OutputFilePicker, 0, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxLEFT, 5);

	MainSizer->Add(FilePickersSizer, 0, wxEXPAND | wxALL, 10);

	wxString EncryptionTypeChoices[] = { wxT("Цезарь"), wxT("Виженер"), wxT("Энигма") };
	int EncryptionTypeNChoices = sizeof(EncryptionTypeChoices) / sizeof(wxString);
	EncryptionType = new wxRadioBox(this, wxID_ANY, wxT("Тип шифрования"), wxDefaultPosition, wxDefaultSize, EncryptionTypeNChoices, EncryptionTypeChoices, 1, wxRA_SPECIFY_ROWS);
	EncryptionType->SetSelection(0);
	MainSizer->Add(EncryptionType, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM | wxRIGHT | wxLEFT, 10);

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer2->AddGrowableCol(1);
	fgSizer2->SetFlexibleDirection(wxHORIZONTAL);
	fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("Пароль"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	fgSizer2->Add(m_staticText3, 0, wxALIGN_CENTER_VERTICAL | wxTOP | wxBOTTOM | wxRIGHT, 5);

	Password = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	fgSizer2->Add(Password, 0, wxALIGN_CENTER_VERTICAL | wxEXPAND | wxTOP | wxBOTTOM | wxLEFT, 5);

	MainSizer->Add(fgSizer2, 0, wxEXPAND | wxBOTTOM | wxRIGHT | wxLEFT, 10);

	StartButton = new wxButton(this, wxID_ANY, wxT("Шифровать"), wxDefaultPosition, wxSize(-1, 36), 0);
	MainSizer->Add(StartButton, 0, wxEXPAND | wxBOTTOM | wxRIGHT | wxLEFT, 10);

	StatusBar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);
	SetStatusText(wxT("Ready"), 0);

	this->SetSizerAndFit(MainSizer);

	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	InputFilePicker->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(MainFrame::InputFilePicker_OnFileChanged), NULL, this);
	OutputFilePicker->Connect(wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler(MainFrame::OutputFilePicker_OnFileChanged), NULL, this);
	EncryptionType->Connect(wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(MainFrame::EncryptionType_OnRadioBox), NULL, this);
	StartButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::StartButton_OnButtonClick), NULL, this);
}


// event handlers

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
	wxMessageBox(
		"Курсовая работа студента 3-го курса Смирнова С.Ю.",
		"О программе Шифратор",
		wxOK | wxICON_INFORMATION,
		this
	);
}

void MainFrame::InputFilePicker_OnFileChanged(wxFileDirPickerEvent& event) {
	event.Skip();
}

void MainFrame::OutputFilePicker_OnFileChanged(wxFileDirPickerEvent& event) {
	event.Skip();
}

void MainFrame::EncryptionType_OnRadioBox(wxCommandEvent& event) {
	event.Skip();
}

void MainFrame::StartButton_OnButtonClick(wxCommandEvent& event) {
	event.Skip();
}
