#pragma once

#include "DriverInterface.h"
#include "SSDCommandInvoker.h"

#include <iostream>
#include <vector>

using namespace std;

class Shell
{
public:
	Shell(DriverInterface* pSSDDriver);
	virtual ~Shell();

	void Run(istream& input, ostream& output);

private:

	void handleCommand(string lineString, ostream& output);

	vector<string> SplitLine(string& strCommandLine);

private:
	DriverInterface* m_pSSDDriver;
	SSDCommandInvoker* m_pCommandInvoker;
};

