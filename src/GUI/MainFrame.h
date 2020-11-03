#pragma once

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/filepicker.h>

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
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	// UI Update Hadlers
	void InputFilePicker_OnFileChanged(wxFileDirPickerEvent& event);
	void OutputFilePicker_OnFileChanged(wxFileDirPickerEvent& event);
	void EncryptionType_OnRadioBox(wxCommandEvent& event);
	void StartButton_OnButtonClick(wxCommandEvent& event);

private:
	wxStaticText* InputFileStaticText;
	wxFilePickerCtrl* InputFilePicker;
	wxStaticText* OutputFileStaticText;
	wxFilePickerCtrl* OutputFilePicker;
	wxRadioBox* EncryptionType;
	wxStaticText* m_staticText3;
	wxTextCtrl* Password;
	wxButton* StartButton;
	wxStatusBar* StatusBar;
};
