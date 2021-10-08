#include "functions.h"

#include <unordered_map>

#include "encryption/ExceptionMessages.h"

static std::unordered_map<int, std::wstring> messages = {
	{0, L"Произошло неожиданное исключение"},
	{PASSWORD_CANT_BE_EMPTY_ID, L"Пароль не может быть пустым"},
	{PASSWORD_IS_TOO_SHORT_ID, L"Пароль слишком короткий"},
	{PASSWORD_CANT_BE_USED_ID, L"Пароль не может быть использован"} };

const std::wstring& Utils::getLocalizedMessage(int exceptionId) {
	auto search = messages.find(exceptionId);
	if (search == messages.end())
		return messages.at(0);
	return search->second;
}
