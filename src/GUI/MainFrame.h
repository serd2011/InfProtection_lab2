#pragma once

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/filepicker.h"

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
	void onQuit(wxCommandEvent& event);
	void onAbout(wxCommandEvent& event);

	// UI Update Handlers
	void inputFilePicker_onFileChanged(wxFileDirPickerEvent& event);
	void inputFilePicker_onDropFiles(wxDropFilesEvent& event);
	void outputFilePicker_onFileChanged(wxFileDirPickerEvent& event);
	void encryptionType_onChange(wxCommandEvent& event);
	void startButton_onClick(wxCommandEvent& event);

private:
	wxStaticText* inputFileStaticText;
	wxFilePickerCtrl* inputFilePicker;
	wxStaticText* outputFileStaticText;
	wxFilePickerCtrl* outputFilePicker;
	wxRadioBox* encryptionType;
	wxStaticText* passwordInputStaticText;
	wxTextCtrl* passwordInputField;
	wxButton* startButton;
	StatusBar* statusBar;
};
