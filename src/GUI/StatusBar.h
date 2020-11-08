#pragma once

#include "wx/statusbr.h"
#include "wx/gauge.h"
#include "wx/stattext.h"

class StatusBar : public wxStatusBar {

public:
	StatusBar(wxWindow* parent, wxWindowID id);
	
	void setStatus(const wxString& status);

	void hideProgress();
	void showProgress(int range);
	void setProgress(int value);

private:
	wxGauge* progressBar;
	wxStaticText* statusStaticText;

};

