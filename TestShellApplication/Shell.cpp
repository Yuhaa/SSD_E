#include "Shell.h"
#include "ReadCommand.h"
#include "WriteCommand.h"
#include "FullWriteCommand.h"
#include "FullReadCommand.h"

Shell::Shell(DriverInterface* pSSDDriver)
	: m_pSSDDriver(pSSDDriver)
{
}

void Shell::Run(istream& input, ostream& output)
{
    string line;
    while (getline(input, line)) {
        handleCommand(line, output);
    }
}

void Shell::handleCommand(string strCommandLine, ostream& output)
{
    vector<string> vCommandList = SplitLine(strCommandLine);
    
    string strCommand = vCommandList[0];
    vCommandList.erase(vCommandList.begin());

    if (strCommand == "read") {
        ReadCommand read(vCommandList, m_pSSDDriver, output);
        read.Execute();
    }
    else if (strCommand == "fullread") {
        FullReadCommand cmd(vCommandList, m_pSSDDriver, output);
        cmd.Execute();
    }
    else if (strCommand == "write") {
        WriteCommand cmd(vCommandList, m_pSSDDriver, output);
        cmd.Execute();
    }
    else if (strCommand == "fullwrite") {
        FullWriteCommand cmd(vCommandList, m_pSSDDriver, output);
        cmd.Execute();
    }
}

vector<string> Shell::SplitLine(string& strCommandLine)
{
    vector<string> vCommandList;
    strCommandLine += " ";
    auto nPos = strCommandLine.find(" ");
    while (nPos != string::npos) {
        vCommandList.push_back(strCommandLine.substr(0, nPos));
        strCommandLine = strCommandLine.substr(nPos + 1);
        nPos = strCommandLine.find(" ");
    }
    return vCommandList;
}
