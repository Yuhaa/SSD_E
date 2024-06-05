#include "FileManager.h"
using namespace std;

FileManager::FileManager(string sFileName) :
	m_sFileName(sFileName) {}

void FileManager::OpenReadStream() {
	m_ifstreamRead.open(m_sFileName);

	if (m_ifstreamRead.is_open() == false) {
		throw exception("Open input file fail");
	}
}

void FileManager::OpenWriteStream() {
	m_ofstreamWrite.open(m_sFileName);

	if (m_ofstreamWrite.is_open() == false) {
		throw exception("Open input file fail");
	}
}

void FileManager::CloseReadStream() {
	m_ifstreamRead.close();
}

void FileManager::CloseWriteStream() {
	m_ofstreamWrite.close();
}

bool FileManager::IsFileExist() {
	m_ifstreamRead.open(m_sFileName);

	if (m_ifstreamRead.good()) {
		m_ifstreamRead.close();

		return true;
	}
	m_ifstreamRead.close();

	return false;
}

string FileManager::Read() {
	string sData;
	getline(m_ifstreamRead, sData);

	return sData;
}

void FileManager::Write(string sData) {
	m_ofstreamWrite << sData << std::endl;
}