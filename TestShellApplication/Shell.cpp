#include "Shell.h"

Shell::Shell(DriverInterface* pSSDDriver)
	: m_pSSDDriver(pSSDDriver)
    , m_pCommandInvoker(nullptr)
{
}

Shell::~Shell()
{
    if (m_pCommandInvoker != nullptr) {
        delete m_pCommandInvoker;
        m_pCommandInvoker = nullptr;
    }
}

void Shell::Run(istream& input, ostream& output)
{
    m_pCommandInvoker = new SSDCommandInvoker(m_pSSDDriver, output);

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

    SSDComamnd* pCommand = m_pCommandInvoker->GetCommand(strCommand);
    if (pCommand) {
        pCommand->SetCommandList(vCommandList);
        pCommand->Execute();
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
