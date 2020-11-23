#pragma once

#include "pch.h"

#include "StatusBar.h"

class MainFrame : public wxFrame {

public:

	MainFrame(wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxString& title = wxEmptyString,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxCLOSE_BOX | wxMINIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLIP_CHILDREN
	);

	// Menu Commands
	void onQuit(wxCommandEvent&);
	void onAbout(wxCommandEvent&);

	// UI Update Handlers
	void inputFilePicker_onDropFiles(wxDropFilesEvent&);
	void startButton_onClick(wxCommandEvent& event);
	void cancelButton_onClick(wxCommandEvent& event);

	// Frame Update Handlers
	void standByState();
	void startState();
	void updateProgress(unsigned int progress);

private:
	wxStaticText* inputFileStaticText;
	wxFilePickerCtrl* inputFilePicker;
	wxStaticText* outputFileStaticText;
	wxFilePickerCtrl* outputFilePicker;
	wxRadioBox* encryptionType;
	wxStaticText* passwordInputStaticText;
	wxTextCtrl* passwordInputField;
	wxButton* startButton;
	wxButton* cancelButton;
	StatusBar* statusBar;
};
