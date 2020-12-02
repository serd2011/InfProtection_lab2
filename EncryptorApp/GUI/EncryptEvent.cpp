#include "pch.h"

#include "EncryptEvent.h"

wxDEFINE_EVENT(START_ENCRYPT_EVENT, StartEncryptEvent);
wxDEFINE_EVENT(CANCEL_ENCRYPT_EVENT, CancelEncryptEvent);

wxEvent* StartEncryptEvent::Clone() const {
	return new StartEncryptEvent(*this);
}

std::string StartEncryptEvent::getInputFile() const {
	return this->inputFile_;
}

std::string StartEncryptEvent::getOutputFile() const {
	return this->outputFile_;
}

std::string StartEncryptEvent::getPass() const {
	return this->pass_;
}

size_t StartEncryptEvent::getType() const {
	return this->type_;
}

StartEncryptEvent::Actions StartEncryptEvent::getAction() const{
	return this->action_;
}

wxEvent* CancelEncryptEvent::Clone() const {
	return new CancelEncryptEvent(*this);
}
