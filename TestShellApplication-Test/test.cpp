#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TestShellApplication/SSDCommand.cpp"
#include "../TestShellApplication/ReadCommand.cpp"
#include "../TestShellApplication/WriteCommand.cpp"
#include "../TestShellApplication/Shell.cpp"

using namespace testing;

class SsdDeviceDriverMock : public DriverInterface {
public:
	MOCK_METHOD(int, Read, (int lba), (override));
	MOCK_METHOD(void, Write, (int lba, int dat), (override));
};

class TestShellApplicationTestFixture : public testing::Test {
public:
	SsdDeviceDriverMock ssdMock;

protected:
	void SetUp() override {
	}
};

TEST_F(TestShellApplicationTestFixture, ReadZeroTest) {
	EXPECT_CALL(ssdMock, Read)
		.Times(1)
		.WillRepeatedly(Return(0x00000000));
	std::string expected = "0x00000000\n";

	Shell shell(&ssdMock);
	std::istringstream input("read 10\n");
	std::ostringstream output;

	shell.Run(input, output);

	EXPECT_EQ(output.str(), expected);
}

TEST_F(TestShellApplicationTestFixture, WriteAndReadOnceTest) {
	EXPECT_CALL(ssdMock, Write(10, 0xAA))
		.Times(1);
	EXPECT_CALL(ssdMock, Read(10))
		.Times(1)
		.WillRepeatedly(Return(0x000000AA));
	std::string expected = "0x000000AA\n";

	Shell shell(&ssdMock);
	std::istringstream input("write 10 0x000000AA\nread 10\n");
	std::ostringstream output;

	shell.Run(input, output);

	EXPECT_EQ(output.str(), expected);
}

TEST_F(TestShellApplicationTestFixture, WriteInvalidCharacterLBATest) {
	Shell shell(&ssdMock);
	std::istringstream input("write 0A 0x000000AA");
	std::ostringstream output;

	EXPECT_THROW(shell.Run(input, output), std::exception);
}

TEST_F(TestShellApplicationTestFixture, WriteInvalidRangeLBATest) {
	Shell shell(&ssdMock);
	std::istringstream input("write 101 0x000000AA");
	std::ostringstream output;

	EXPECT_THROW(shell.Run(input, output), std::exception);
}

TEST_F(TestShellApplicationTestFixture, WriteInvalidCharacterDataTest) {
	Shell shell(&ssdMock);
	std::istringstream input("write 10 0x0000GED0");
	std::ostringstream output;

	EXPECT_THROW(shell.Run(input, output), std::exception);
}

TEST_F(TestShellApplicationTestFixture, WriteNotStart0xDataTest) {
	Shell shell(&ssdMock);
	std::istringstream input("write 10 000000AA");
	std::ostringstream output;

	EXPECT_THROW(shell.Run(input, output), std::exception);
}

TEST_F(TestShellApplicationTestFixture, WriteNot8CharacterDataTest) {
	Shell shell(&ssdMock);
	std::istringstream input("write 10 0x123456");
	std::ostringstream output;

	EXPECT_THROW(shell.Run(input, output), std::exception);
}
