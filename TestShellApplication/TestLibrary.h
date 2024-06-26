#pragma once
#include "Device.h"
#include "TestLibraryInterface.h"

#include <iomanip>
#include <iostream>

class TestLibWrite : public TestLibrary {
public:
	TestLibWrite(Device& pstDevice);
	bool execute() const override;
private:
	Device& m_pstDevice;

};

class TestLibRead : public TestLibrary {
public:
	TestLibRead(Device& pstDevice);
	bool execute() const override;
private:
	Device& m_pstDevice;
};

class TestLibErase : public TestLibrary {
public:
	TestLibErase(Device& pstDevice);
	bool execute() const override;
private:
	Device& m_pstDevice;
};

class TestLibFlush : public TestLibrary {
public:
	TestLibFlush(Device& pstDevice);
	bool execute() const override;
private:
	Device& m_pstDevice;
};

class TestLibFullWrite : public TestLibrary {
public:
	TestLibFullWrite(Device& pstDevice);
	bool execute() const override;
private:
	Device& m_pstDevice;
};

class TestLibFullRead : public TestLibrary {
public:
	TestLibFullRead(Device& pstDevice);
	bool execute() const override;
private:
	Device& m_pstDevice;
};

class TestLibWriteRange : public TestLibrary {
public:
	TestLibWriteRange(Device& pstDevice);
	bool execute() const override;
private:
	Device& m_pstDevice;
};

class TestLibReadRange : public TestLibrary {
public:
	TestLibReadRange(Device& pstDevice);
	bool execute() const override;
private:
	Device& m_pstDevice;
};

class TestLibEraseRange : public TestLibrary {
public:
	TestLibEraseRange(Device& pstDevice);
	bool execute() const override;
private:
	Device& m_pstDevice;
};