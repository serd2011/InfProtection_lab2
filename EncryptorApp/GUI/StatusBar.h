#pragma once

#include "pch.h"

class StatusBar : public wxStatusBar {

public:
	StatusBar(wxWindow* parent, wxWindowID id);
	
	void setStatus(const wxString& status);

	void hideProgress();
	void showProgress(unsigned int range);

	void setProgress(unsigned int value);
	unsigned int getProgress();

private:
	wxGauge* progressBar;
	wxStaticText* statusStaticText;

};

