#pragma once

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/filepicker.h"

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
	void onQuit(wxCommandEvent& event);
	void onAbout(wxCommandEvent& event);

	// UI Update Handlers
	void inputFilePicker_onFileChanged(wxFileDirPickerEvent& event);
	void outputFilePicker_onFileChanged(wxFileDirPickerEvent& event);
	void encryptionType_onRadioBox(wxCommandEvent& event);
	void startButton_onButtonClick(wxCommandEvent& event);

private:
	wxStaticText* inputFileStaticText;
	wxFilePickerCtrl* inputFilePicker;
	wxStaticText* outputFileStaticText;
	wxFilePickerCtrl* outputFilePicker;
	wxRadioBox* encryptionType;
	wxStaticText* passwordInputStaticText;
	wxTextCtrl* passwordInputField;
	wxButton* startButton;
	wxStatusBar* statusBar;
};
