#include "WriteCommand.h"

#include <iostream>
#include <iomanip>

using std::string;

WriteCommand::WriteCommand(vector<string> commandList, DriverInterface* pSSDDriver)
	: BaseSSDCommand(commandList)
	, m_pSSDDriver(pSSDDriver)
	, m_nLBA(-1)
	, m_nData(0x00000000)
{
}

void WriteCommand::_execute()
{
	m_pSSDDriver->Write(m_nLBA, m_nData);
}

void WriteCommand::_parseCommand()
{
	constexpr int REQUIRED_COMMAND_COUNT = 2;
	if (m_commandList.size() != REQUIRED_COMMAND_COUNT) {
		throw std::exception();
	}

	m_nLBA = _checkAndGetLBA(m_commandList[0]);
	m_nData = _checkAndGetData(m_commandList[1]);
}

int WriteCommand::_checkAndGetLBA(string paramString)
{
	for (const char ch : paramString) {
		if ((ch >= '0') && (ch <= '9')) continue;
		throw std::exception("[Invalid LBA] Not Decimal Character");
	}
	int result = std::stoi(paramString, nullptr, 10);
	if (result < 0 || result > 99) {
		throw std::exception("[Invalid LBA] LBA Must be 0 ~ 99");
	}

	return result;
}

int WriteCommand::_checkAndGetData(string paramString)
{
	if (paramString.substr(0, 2).compare("0x") != 0) {
		throw std::exception("[Invalid Data] Not Start 0x");
	}
	paramString = paramString.substr(2);

	if (paramString.size() != 8) {
		throw std::exception("[Invalid Data] Not 8 Character");
	}

	for (const char ch : paramString) {
		if ((ch >= '0') && (ch <= '9')) continue;
		if ((ch >= 'a') && (ch <= 'f')) continue;
		if ((ch >= 'A') && (ch <= 'F')) continue;
		throw std::exception("[Invalid Data] Not Hex Character");
	}

	return std::stoi(paramString, nullptr, 16);
}
