#pragma once

#include "Utils/EncriptionContainer.h"

#include <array>

enum class States {
	standBy,
	encrypt,
	cancel
};

struct EncriptionDescription {
	std::wstring name;
	Utils::EncryptTypes type;
};

std::array<const EncriptionDescription, 3> const EncriptionDescriptions{ {
	{L"Цезарь", Utils::EncryptTypes::Caesar},
	{L"Виженер", Utils::EncryptTypes::Vigenere},
	{L"Энигма", Utils::EncryptTypes::Enigma}
} };
