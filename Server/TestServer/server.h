#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>

// Constants
constexpr int SERVER_PORT = 27000;
constexpr int CHUNK_SIZE = 1024;

// Function declarations
void sendAll(SOCKET clientSocket, const std::string& data);
std::vector<std::string> splitPacket(const std::string& packet);
void generateCSV(const std::string& csvFilePath);
void sendImage(SOCKET clientSocket, const std::string& imagePath);
void saveToFile(const std::string& message);

#endif // SERVER_H
