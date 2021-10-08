#pragma once

#include "Utils/EncriptionContainer.h"

#include <array>

enum class States {
	standBy,
	encrypt,
	decrypt,
	cancel,
	done,
	error
};

#define isWorkingState(state) (state == States::encrypt || state == States::decrypt || state == States::cancel)

struct EncriptionDescription {
	std::wstring name;
	Utils::EncryptTypes type;
};

std::array<const EncriptionDescription, 4> const EncriptionDescriptions{ {
	{L"Цезарь", Utils::EncryptTypes::Caesar},
	{L"Виженер", Utils::EncryptTypes::Vigenere},
	{L"Энигма", Utils::EncryptTypes::Enigma},
	{L"Шифр Хилла", Utils::EncryptTypes::Hill }
} };
