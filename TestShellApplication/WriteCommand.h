#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

class WriteCommand
	: public BaseSSDCommand
{
public:
	WriteCommand(vector<string>commandList, DriverInterface* pSSDDriver);

protected:
	void _execute() override;
	void _parseCommand() override;

private:
	int _checkAndGetLBA(string paramString);
	int _checkAndGetData(string paramString);

private:
	DriverInterface* m_pSSDDriver;

	int m_nLBA;
	int m_nData;
};
