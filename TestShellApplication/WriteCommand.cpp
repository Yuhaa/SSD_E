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

	m_nLBA = std::stoi(m_commandList[0], nullptr, 10);
	m_nData = std::stol(m_commandList[1], nullptr, 16);
}
