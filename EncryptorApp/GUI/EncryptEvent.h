#pragma once

#include "pch.h"

class StartEncryptEvent;
wxDECLARE_EVENT(START_ENCRYPT_EVENT, StartEncryptEvent);

class CancelEncryptEvent;
wxDECLARE_EVENT(CANCEL_ENCRYPT_EVENT, CancelEncryptEvent);

class StartEncryptEvent : public wxEvent {

public:

	enum class Actions {
		encrypt,
		decrypt
	};

	StartEncryptEvent(Actions action, const std::string& inputFile, const std::string& outputFile, const std::string& pass, const size_t& type, int winid = 0)
		: wxEvent(winid, START_ENCRYPT_EVENT),
		inputFile_(inputFile),
		outputFile_(outputFile),
		pass_(pass),
		type_(type),
		action_(action) {};

	virtual wxEvent* Clone() const;

	std::string getInputFile() const;
	std::string getOutputFile() const;
	std::string getPass() const;
	size_t getType() const;
	Actions getAction() const;

private:
	const std::string inputFile_;
	const std::string outputFile_;
	const std::string pass_;
	const size_t type_;
	const Actions action_;

};

class CancelEncryptEvent : public wxEvent {

public:
	CancelEncryptEvent(int winid = 0)
		: wxEvent(winid, CANCEL_ENCRYPT_EVENT) {}

	virtual wxEvent* Clone() const;

};
