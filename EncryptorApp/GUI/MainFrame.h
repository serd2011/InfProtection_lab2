#pragma once
#include "pch.h"

#include "StatusBar.h"
#include "defines.h"

class MainFrame : public wxFrame {

public:

	MainFrame(wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxString& title = wxEmptyString,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxCLOSE_BOX | wxMINIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLIP_CHILDREN
	);

	void OnClose(wxCloseEvent&);

	// Menu Commands
	void onQuit(wxCommandEvent&);
	void onAbout(wxCommandEvent&);

	// UI Update Handlers
	void inputFilePicker_onDropFiles(wxDropFilesEvent&);
	void encryptButton_onClick(wxCommandEvent& event);
	void decryptButton_onClick(wxCommandEvent& event);
	void cancelButton_onClick(wxCommandEvent& event);
	void ui_onChange(wxCommandEvent& event);
		
	// Frame Update Handlers
	void setState(States state);
	void updateProgress(unsigned int progress);

	void startButtonsClicked(States action);

private:
	wxStaticText* inputFileStaticText;
	wxFilePickerCtrl* inputFilePicker;
	wxStaticText* outputFileStaticText;
	wxFilePickerCtrl* outputFilePicker;
	wxRadioBox* encryptionType;
	wxStaticText* passwordInputStaticText;
	wxTextCtrl* passwordInputField;
	wxBoxSizer* startButtonsSizer;
	wxButton* encryptButton;
	wxButton* decryptButton;
	wxButton* cancelButton;
	StatusBar* statusBar;

	States state;
};
