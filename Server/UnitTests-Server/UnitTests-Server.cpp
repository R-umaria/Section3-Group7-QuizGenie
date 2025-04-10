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
    };
}
