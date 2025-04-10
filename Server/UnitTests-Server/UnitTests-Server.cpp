#include "pch.h"
#include "CppUnitTest.h"
#include "../TestServer/server.h"

#include <fstream>
#include <sstream>
#include <cstdio>  // for remove()

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests_Server
{
    TEST_CLASS(ServerTests)
    {
    public:
        // Tests for the splitPacket function

        TEST_METHOD(TestSplitPacket_EmptyInput)
        {
            std::string packet = "";
            std::vector<std::string> parts = splitPacket(packet);
            // Expect one element (empty string)
            Assert::AreEqual(static_cast<size_t>(1), parts.size());
            Assert::AreEqual(std::string(""), parts[0]);
        }

        TEST_METHOD(TestSplitPacket_SingleDelimiter)
        {
            std::string packet = "A|B";
            std::vector<std::string> parts = splitPacket(packet);
            Assert::AreEqual(static_cast<size_t>(2), parts.size());
            Assert::AreEqual(std::string("A"), parts[0]);
            Assert::AreEqual(std::string("B"), parts[1]);
        }

        TEST_METHOD(TestSplitPacket_MultipleDelimiters)
        {
            std::string packet = "AUTH|13|some,data";
            std::vector<std::string> parts = splitPacket(packet);
            Assert::AreEqual(static_cast<size_t>(3), parts.size());
            Assert::AreEqual(std::string("AUTH"), parts[0]);
            Assert::AreEqual(std::string("13"), parts[1]);
            Assert::AreEqual(std::string("some,data"), parts[2]);
        }

        // Test for the generateCSV function

        TEST_METHOD(TestGenerateCSV_FileCreationAndContent)
        {
            std::string testCsv = "unittest.csv";

            // Remove any existing file for a clean start
            remove(testCsv.c_str());

            generateCSV(testCsv);

            std::ifstream file(testCsv);
            Assert::IsTrue(file.good(), L"CSV file was not created.");

            // Read the first line (header line)
            std::string header;
            std::getline(file, header);
            Assert::IsTrue(header.find("Question") != std::string::npos, L"CSV file header not found.");

            file.close();
            // Cleanup test file
            remove(testCsv.c_str());
        }

        // Test that saveToFile function can open a file and saves to that file
        TEST_METHOD(TestSaveToFile_Open_and_WriteToFile)
        {
            //Remove log.txt if it exists
            std::remove("log.txt");

            std::string testMessage = "Test message\n";
            saveToFile(testMessage);

            //Open file to verify contents
            std::ifstream file("log.txt");
            Assert::IsTrue(file.is_open(), L"Failed to open log.txt after writing.");

            //Read entire file
            std::string fileContents;
            std::string line;
            while (std::getline(file, line))
            {
                fileContents += line + "\n";
            }
            file.close();

            //Check that file contains message
            Assert::IsTrue(fileContents.find(testMessage) != std::string::npos);
            std::remove("log.txt");
        }
    };
}
