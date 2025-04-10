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

        // Test for the saveToFile function
        // Note: Since saveToFile writes to a hard-coded "log.txt", we back up any existing content,
        // call saveToFile, then check the appended log, and finally restore the original log.

        TEST_METHOD(TestSaveToFile_AppendsLogMessage)
        {
            const char* logFilename = "log.txt";
            std::string backup;

            // Backup existing log.txt content if it exists
            std::ifstream infile(logFilename, std::ios::binary);
            if (infile.good())
            {
                std::stringstream buffer;
                buffer << infile.rdbuf();
                backup = buffer.str();
                infile.close();
            }

            // Remove existing log.txt to have a clean file for testing
            remove(logFilename);

            std::string testMessage = "Unit test log message.\n";
            saveToFile(testMessage);

            // Verify that log.txt was created and contains our test message.
            std::ifstream logfile(logFilename);
            Assert::IsTrue(logfile.good(), L"log.txt was not created after calling saveToFile.");

            std::string logContent;
            std::getline(logfile, logContent);
            // Because saveToFile prepends a timestamp, we check if our message appears in the logged line.
            Assert::IsTrue(logContent.find("Unit test log message.") != std::string::npos, L"Test log message not found in log.txt.");
            logfile.close();

            // Restore original log.txt if it was backed up; otherwise, clean up.
            if (!backup.empty())
            {
                std::ofstream outfile(logFilename, std::ios::binary);
                outfile << backup;
                outfile.close();
            }
            else
            {
                remove(logFilename);
            }
        }
    };
}
