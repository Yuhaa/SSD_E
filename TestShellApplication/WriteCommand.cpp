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
	if (m_commandList.size() != 2) {
		throw std::exception();
	}

	string lbaString = m_commandList[0];
	for (const char ch : lbaString) {
		if ((ch >= '0') && (ch <= '9')) continue;
		throw std::exception("[Invalid LBA] Not Decimal Character");
	}
	int lba = std::stoi(lbaString, nullptr, 10);
	if (lba < 0 || lba > 99) {
		throw std::exception("[Invalid LBA] LBA Must be 0 ~ 99");
	}
	m_nLBA = lba;

	string dataString = m_commandList[1];
	if (dataString.substr(0, 2).compare("0x") != 0) {
		throw std::exception("[Invalid Data] Not Start 0x");
	}
	dataString = dataString.substr(2);

	if (dataString.size() != 8) {
		throw std::exception("[Invalid Data] Not 8 Character");
	}

	for (const char ch : dataString) {
		if ((ch >= '0') && (ch <= '9')) continue;
		if ((ch >= 'a') && (ch <= 'f')) continue;
		if ((ch >= 'A') && (ch <= 'F')) continue;
		throw std::exception("[Invalid Data] Not Hex Character");
	}
	m_nData = std::stoi(dataString, nullptr, 16);
}
