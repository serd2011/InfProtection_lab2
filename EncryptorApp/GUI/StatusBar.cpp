#include "pch.h"

#include "StatusBar.h"

StatusBar::StatusBar(wxFrame* parent, wxWindowID id) : wxStatusBar(parent, id, wxSTB_SIZEGRIP) {

	parent->SetStatusBarPane(-1);

	wxFlexGridSizer* fgSizer = new wxFlexGridSizer(1, 2, 10, 0);
	fgSizer->AddGrowableCol(0);
	fgSizer->AddGrowableRow(0);
	fgSizer->SetFlexibleDirection(wxBOTH);
	fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	this->statusStaticText = new wxStaticText(this, wxID_ANY, wxEmptyString);
	fgSizer->Add(this->statusStaticText, 0, wxALIGN_CENTER_VERTICAL | wxRESERVE_SPACE_EVEN_IF_HIDDEN | wxLEFT, 10);

	this->progressBar = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(150, -1));
	progressBar->Hide();
	fgSizer->Add(this->progressBar, 0, wxALIGN_CENTER_VERTICAL | wxRESERVE_SPACE_EVEN_IF_HIDDEN | wxRIGHT | wxALIGN_RIGHT, 20);

	this->SetSizer(fgSizer);

#ifdef __APP_PROGRESS_AVAILABLE__ 
	this->appProgress = new wxAppProgressIndicator();
#endif
}

StatusBar::~StatusBar() {
#ifdef __APP_PROGRESS_AVAILABLE__ 
	delete this->appProgress;
#endif
}

void StatusBar::clearStatus() {	
	this->statusStaticText->SetLabel("");
}

void StatusBar::setStatus(const wxString& status) {
	this->statusStaticText->SetLabel(status);
}

void StatusBar::hideProgress() {
	this->progressBar->Hide();

#ifdef __APP_PROGRESS_AVAILABLE__ 
	this->appProgress->SetValue(0);
#endif
}

void StatusBar::showProgress(unsigned int range) {
	this->progressBar->SetRange(range);
	this->progressBar->SetValue(0);
	this->progressBar->Show();

#ifdef __APP_PROGRESS_AVAILABLE__ 
	this->appProgress->SetRange(range);
	this->appProgress->SetValue(0);
#endif
}

void StatusBar::setProgress(unsigned int value) {
	this->progressBar->SetValue(value);

#ifdef __APP_PROGRESS_AVAILABLE__ 
	this->appProgress->SetValue(value);
#endif
}

unsigned int StatusBar::getProgress() {
	return this->progressBar->GetValue();
}
