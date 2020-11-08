#include "StatusBar.h"

#include "wx/sizer.h"

StatusBar::StatusBar(wxWindow* parent, wxWindowID id) : wxStatusBar(parent, id, wxSTB_SIZEGRIP) {

	wxFlexGridSizer* fgSizer = new wxFlexGridSizer(1, 2, 10, 0);
	fgSizer->AddGrowableCol(0);
	fgSizer->AddGrowableRow(0);
	fgSizer->SetFlexibleDirection(wxBOTH);
	fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	this->statusStaticText = new wxStaticText(this, wxID_ANY, wxEmptyString);
	fgSizer->Add(this->statusStaticText, 0, wxALIGN_CENTER_VERTICAL | wxRESERVE_SPACE_EVEN_IF_HIDDEN | wxLEFT, 10);

	this->progressBar = new wxGauge(this, wxID_ANY, 200, wxDefaultPosition, wxSize(150, -1));
	progressBar->Hide();
	fgSizer->Add(this->progressBar, 0, wxALIGN_CENTER_VERTICAL | wxRESERVE_SPACE_EVEN_IF_HIDDEN | wxRIGHT | wxALIGN_RIGHT, 20);

	this->SetSizer(fgSizer);
}

void StatusBar::setStatus(const wxString& status) {
	this->statusStaticText->SetLabel(status);
}

void StatusBar::hideProgress() {
	this->progressBar->Hide();
}

void StatusBar::showProgress(int range) {
	this->progressBar->SetRange(range);
	this->progressBar->SetValue(0);
	this->progressBar->Show();
}

void StatusBar::setProgress(int value) {
	this->progressBar->SetValue(value);
}
