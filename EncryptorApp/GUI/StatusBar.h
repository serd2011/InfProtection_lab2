#pragma once

#include "pch.h"

class StatusBar : public wxStatusBar {

public:
	StatusBar(wxFrame* parent, wxWindowID id);
	
	void clearStatus();
	void setStatus(const wxString& status);

	void hideProgress();
	void showProgress(unsigned int range);

	void setProgress(unsigned int value);
	unsigned int getProgress();

private:
	wxGauge* progressBar;
	wxStaticText* statusStaticText;

#ifdef __WXMSW__ 
	wxTaskBarButton* taskBarPtr;
#endif

};

