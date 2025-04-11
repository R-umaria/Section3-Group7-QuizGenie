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
        //SPLIT PACKET TESTS

        //Tests for empty input
        TEST_METHOD(SP001_EmptyInput)
        {
            std::string packet = "";
            std::vector<std::string> parts = splitPacket(packet);
            Assert::AreEqual(static_cast<size_t>(1), parts.size());
            Assert::AreEqual(std::string(""), parts[0]);
        }

        //Tests for 1 element with no delimiter
        TEST_METHOD(SP002_NoDelimiter)
        {
            std::string packet = "A";
            std::vector<std::string> parts = splitPacket(packet);
            Assert::AreEqual(static_cast<size_t>(1), parts.size());
            Assert::AreEqual(std::string("A"), parts[0]);
        }

        //Tests for 1 delimiter
        TEST_METHOD(SP003_SingleDelimiter)
        {
            std::string packet = "A|B";
            std::vector<std::string> parts = splitPacket(packet);
            Assert::AreEqual(static_cast<size_t>(2), parts.size());
            Assert::AreEqual(std::string("A"), parts[0]);
            Assert::AreEqual(std::string("B"), parts[1]);
        }

        //Tests for 2 delimiters
        TEST_METHOD(SP004_MultipleDelimiters)
        {
            std::string packet = "AUTH|13|some,data";
            std::vector<std::string> parts = splitPacket(packet);
            Assert::AreEqual(static_cast<size_t>(3), parts.size());
            Assert::AreEqual(std::string("AUTH"), parts[0]);
            Assert::AreEqual(std::string("13"), parts[1]);
            Assert::AreEqual(std::string("some,data"), parts[2]);
        }

        //GENERATECSV TESTS

        //Test generateCSV can open/create a file, and store information
        TEST_METHOD(GCSV001_FileCreation)
        {
            std::string filePath = "test.csv";
            remove(filePath.c_str());

            generateCSV(filePath);

            std::ifstream file(filePath);
            Assert::IsTrue(file.is_open());

            //Read first line
            std::string header;
            std::getline(file, header);
            Assert::IsTrue(header.find("Question") != std::string::npos);

            file.close();
            //Remove test file
            remove(filePath.c_str());
        }

        //SAVETOFILE TESTS

        //Test that saveToFile function can create/open a file and save to that file
        TEST_METHOD(STF001_Open_and_WriteToFile)
        {
            //Remove log.txt if it exists
            std::remove("log.txt");

            std::string testMessage = "Test message\n";
            saveToFile(testMessage);

            //Open file to verify contents
            std::ifstream file("log.txt");
            Assert::IsTrue(file.is_open());

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

        // Additional Unit Tests

       // Test if saveToFile writes multiple lines correctly
        TEST_METHOD(STF002_MultipleWrites)
        {
            std::remove("log.txt");
            saveToFile("First line\n");
            saveToFile("Second line\n");

            std::ifstream file("log.txt");
            Assert::IsTrue(file.is_open());

            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();

            Assert::IsTrue(content.find("First line") != std::string::npos);
            Assert::IsTrue(content.find("Second line") != std::string::npos);
            std::remove("log.txt");
        }

        // Edge case: string with only delimiters
        TEST_METHOD(SP005_OnlyDelimiters)
        {
            std::string packet = "|||";
            std::vector<std::string> parts = splitPacket(packet);
            Assert::AreEqual(static_cast<size_t>(4), parts.size());
            Assert::AreEqual(std::string(""), parts[0]);
            Assert::AreEqual(std::string(""), parts[1]);
            Assert::AreEqual(std::string(""), parts[2]);
            Assert::AreEqual(std::string(""), parts[3]);
        }

        // Test actual content in generated CSV
        TEST_METHOD(GCSV002_ValidateMCQContent)
        {
            std::string filePath = "test.csv";
            std::remove(filePath.c_str());

            generateCSV(filePath);

            std::ifstream file(filePath);
            Assert::IsTrue(file.is_open());

            std::string line;
            std::getline(file, line); // skip header
            std::getline(file, line); // read first MCQ
            Assert::IsTrue(line.find("What is 2+2?") != std::string::npos);
            Assert::IsTrue(line.find("4") != std::string::npos);
            file.close();
            std::remove(filePath.c_str());
        }

        // Simulate packet parsing for AUTH
        TEST_METHOD(AUTH001_ParseValidAuth)
        {
            std::string authPacket = "AUTH|13|admin,1234";
            auto parts = splitPacket(authPacket);
            Assert::AreEqual(std::string("AUTH"), parts[0]);
            Assert::AreEqual(std::string("13"), parts[1]);
            Assert::AreEqual(std::string("admin,1234"), parts[2]);

            std::string username = parts[2].substr(0, parts[2].find(','));
            std::string password = parts[2].substr(parts[2].find(',') + 1);

            Assert::AreEqual(std::string("admin"), username);
            Assert::AreEqual(std::string("1234"), password);
        }

        // Simulate packet parsing for invalid auth
        TEST_METHOD(AUTH002_ParseInvalidAuth)
        {
            std::string authPacket = "AUTH|11|user,wrong";
            auto parts = splitPacket(authPacket);
            std::string username = parts[2].substr(0, parts[2].find(','));
            std::string password = parts[2].substr(parts[2].find(',') + 1);

            Assert::AreNotEqual(std::string("admin"), username);
            Assert::AreNotEqual(std::string("1234"), password);
        }

    };
    TEST_CLASS(ServerExtraTests)
    {
    public:

        TEST_METHOD(SP005_ExtraDelimiters)
        {
            std::string packet = "AUTH|13|some,data|extra|noise";
            std::vector<std::string> parts = splitPacket(packet);
            Assert::AreEqual((size_t)5, parts.size());
            Assert::AreEqual(std::string("AUTH"), parts[0]);
        }

        TEST_METHOD(GCSV002_FailOnInvalidPath)
        {
            std::string badPath = "/invalid/test.csv"; // Likely invalid on most OS
            generateCSV(badPath);  // Should not crash
        }

        TEST_METHOD(STF002_FailToOpenLog)
        {
            // Rename log.txt to simulate lock
            std::rename("log.txt", "temp_log.txt");
            std::ofstream lock("log.txt", std::ios::out);
            lock.close();

            saveToFile("Test when log.txt locked\n"); // Should not crash

            std::remove("log.txt");
            std::rename("temp_log.txt", "log.txt");
        }

        TEST_METHOD(SND001_ZeroDataSendAll)
        {
            SOCKET dummySocket = INVALID_SOCKET;
            sendAll(dummySocket, ""); // Should return gracefully
        }

        TEST_METHOD(SNDIMG001_SendImageNonExistent)
        {
            SOCKET dummySocket = INVALID_SOCKET;
            sendImage(dummySocket, "nonexistent.jpg"); // Should print error
        }
    };
}
