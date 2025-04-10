#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "server.h" 
#include < iostream> 
#include <string> 
#include <vector> 
#include <fstream> 
#include <chrono> 
#include <ctime> 
#include <cstdlib> // Required for system() calls

#pragma comment(lib, "Ws2_32.lib")

void sendAll(SOCKET clientSocket, const std::string &data) {
    int totalSent = 0;
    int dataSize = static_cast<int>(data.size());
    while (totalSent < dataSize) {
        int sent = send(clientSocket, data.c_str() + totalSent, dataSize - totalSent, 0);
        std::cout << "sent " << totalSent << " bytes of data" << std::endl;
        if (sent == SOCKET_ERROR) {
            std::cerr << "Send failed.\n";
            return;
        }
        totalSent += sent;
    }
}

std::vector<std::string> splitPacket(const std::string& packet) {
    std::vector<std::string> parts;
    size_t start = 0;
    size_t end = packet.find('|');
    while (end != std::string::npos) {
        parts.push_back(packet.substr(start, end - start));
        start = end + 1;
        end = packet.find('|', start);
    }
    parts.push_back(packet.substr(start)); // Add the remaining data
    return parts; // Ensure the function returns the vector
}

    // This function is kept as a dummy fallback for CSV generation if needed. 
void generateCSV(const std::string& csvFilePath) { 
    std::ofstream file(csvFilePath); 
    if (file.is_open()) { 
        file << "Question, OptionA, OptionB, OptionC, OptionD, Answer\n"; 
        file << "What is 2+2?,3,4,5,6,4\n"; 
        file.close(); 
        std::cout << "CSV file generated: " << csvFilePath << "\n";
    } 
    else { 
        std::cerr << "Failed to create CSV file.\n"; 
    } 
}

void sendImage(SOCKET clientSocket, const std::string &imagePath){
        std::ifstream file(imagePath, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Failed to open image file.\n";
            return;
        }

        // Get the file size
        file.seekg(0, std::ios::end);
        int fileSize = static_cast<int>(file.tellg());
        file.seekg(0, std::ios::beg);
        
        
        sendAll(clientSocket, std::string(reinterpret_cast<char *>(&fileSize), sizeof(fileSize)));
                
        
        char buffer[CHUNK_SIZE];
        int bytesSent = 0;
        
        while (file.read(buffer, CHUNK_SIZE)) {
            std::string chunk(buffer, file.gcount());
            sendAll(clientSocket, chunk);
            bytesSent += chunk.size();
            std::cout << "Sent " << chunk.size() << " bytes, Total sent: " << bytesSent << std::endl;
        }

        // Send any remaining bytes if the file size isn't an exact multiple of CHUNK_SIZE
        if (file.gcount() > 0) {
            std::string remainingData(buffer, file.gcount());
            sendAll(clientSocket, remainingData);
            bytesSent += remainingData.size();
            std::cout << "Sent remaining " << remainingData.size() << " bytes, Total sent: " << bytesSent << std::endl;
        }

        file.close();
        std::cout << "Image file sent successfully.\n";
    }

    void saveToFile(const std::string &message) {
        std::ofstream File("log.txt", std::ios::app);   // Append mode
        if (File.is_open()) {
            // Get current time
            auto now = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(now);
            
            char timeStr[26];
            ctime_s(timeStr, sizeof(timeStr), &time);
            
            File << timeStr << " " << message;
            File.close();
            
            std::cout << "Message saved to log.txt\n";
        }
        else{
            std::cerr << "Failed to open log.txt for writing.\n";
        }
    }

    int main() {
        WSADATA wsaData;
        SOCKET listenSocket = INVALID_SOCKET, clientSocket = INVALID_SOCKET;
        sockaddr_in serverAddr{};
        
        // Initialize Winsock
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed.\n";
            return 1;
        }

        listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (listenSocket == INVALID_SOCKET){
            std::cerr << "Socket creation failed.\n";
            WSACleanup();
            return 1;
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        serverAddr.sin_port = htons(SERVER_PORT);

        if (bind(listenSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Bind failed.\n";
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Listen failed.\n";
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Server listening on port " << SERVER_PORT << "...\n";
        clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed.\n";
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }


        std::cout << "Client connected.\n";
        saveToFile("Connected to Client.\n");

        
        bool running = true;
        char buffer[4096];
        while (running) {
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived <= 0) {
                std::cerr << "Client disconnected.\n";
                saveToFile("Client disconnected.\n");
                break;
            }
            if (bytesReceived > 0) {
                std::string packet(buffer, bytesReceived);
                std::vector<std::string> parts = splitPacket(packet);

                if (parts.size() >= 3){
                    std::string packetType = parts[0];
                    int dataSize = std::stoi(parts[1]);
                    std::string data = packet.substr(packetType.size() + parts[1].size() + 2);

                    if (packetType == "AUTH") {
                        std::string username = data.substr(0, data.find(','));
                        std::string password = data.substr(data.find(',') + 1);
                        std::cout << "Auth received: " << username << " / " << password << "\n";
                        saveToFile("Authentication received from Client.\n");
                        
                        if (username == "admin" && password == "1234") {
                            saveToFile("Valid authentication sent to Client.\n");
                            sendAll(clientSocket, "Authentication successful");
                        }
                        else {
                            saveToFile("Invalid authentication sent to Client.\n");
                            sendAll(clientSocket, "Authentication failed");
                        }
                    }
                    else if (packetType == "PDF") {
                        std::cout << "PDF received, size: " << dataSize << " bytes\n";
                        saveToFile("PDF header received from Client.\n");

                        // Save the incoming PDF file
                        std::string inputPdfPath = "../pdf_mcq_generator/input/received_file.pdf";
                        std::ofstream outFile(inputPdfPath, std::ios::binary);

                        if (!outFile){
                            std::cerr << "Failed to create output file.\n";
                            break;
                        }

                        
                        int totalReceived = 0;
                        while (totalReceived < dataSize){
                            int chunkSize = recv(clientSocket, buffer, sizeof(buffer), 0);
                            if (chunkSize == SOCKET_ERROR) {
                                std::cerr << "Error receiving chunk.\n";
                                saveToFile("Error receiving chunk from Client.\n");
                                break;
                            }
                            outFile.write(buffer, chunkSize);
                            totalReceived += chunkSize;
                            std::cout << "Received " << totalReceived << " bytes...\n";
                            saveToFile("Received " + std::to_string(totalReceived) + " bytes from Client.\n");
                        }
                        
                        
                        outFile.close();
                        std::cout << "PDF file received successfully.\n";
                        saveToFile("PDF received from Client.\n");

                        // ----------------------- Python integration starts here -----------------------
                        std::string outputFolderPath = "../pdf_mcq_generator/output";
                        std::string pythonScriptPath = "../pdf_mcq_generator/main.py";

                        // Ensure the output folder exists
                        system(("mkdir \"" + outputFolderPath + "\"").c_str());

                        // Run the Python script with both arguments
                        std::string command = "python \"" + pythonScriptPath + "\" \"" + inputPdfPath + "\" \"" + outputFolderPath + "\"";
                        std::cout << "Executing Python script: " << command << "\n";
                        int retCode = system(command.c_str());
                        if (retCode != 0) {
                            std::cerr << "Python script execution failed with error code: " << retCode << "\n";
                            saveToFile("Python script execution failed.\n");
                            sendAll(clientSocket, "Failed to process PDF with Python script.");
                            continue;
                        }
                        saveToFile("Python script executed successfully.\n");

                        // ----------------------- Python integration ends here -----------------------


                        // Read the CSV file generated by the Python project
                        std::string csvFilePath = outputFolderPath + "/mcq_output.csv";
                        std::ifstream file(csvFilePath, std::ios::binary);

                        if (file.is_open())
                        {
                            std::string csvContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                            file.close();

                            // Send the CSV content to the client
                            sendAll(clientSocket, csvContent);
                            std::cout << "CSV file sent successfully" << std::endl;
                            saveToFile("CSV sent to Client.\n");
                        }
                        else
                        {
                            std::cerr << "Failed to read CSV file.\n";
                            saveToFile("Failed to read CSV file.\n");
                        }
                    }
                    else if (packetType == "SCORE") {
                        std::cout << "Score packet received.\n";

                        // Extract the actual score from the payload
                        try {
                            int score = std::stoi(data);
                            std::cout << "Score received: " << score << "\n";
                            saveToFile("Score received from Client.\n");
                            
                            // Append the score to scores.txt
                            std::ofstream scoreFile("scores.txt", std::ios::app);
                            if (scoreFile.is_open()) {
                                scoreFile << "Client Score: " << score << "/10" << "\n";
                                std::cout << "score: " << score << "/10";
                                scoreFile.close();
                                if (score >= 5) {
                                    std::string imageFilePath = "win.jpg";
                                    sendImage(clientSocket, imageFilePath);
                                    saveToFile("Win Image sent to Client.\n");
                                }
                                else if (score < 5) {
                                    std::string imageFilePath = "lose.jpg";
                                    sendImage(clientSocket, imageFilePath);
                                    saveToFile("Lose Image sent to Client.\n");
                                }
                            }
                            else{
                                std::cerr << "Failed to open scores.txt for writing.\n";
                            }
                        }
                        catch (const std::exception &e) {
                            std::cerr << "Invalid score payload: " << data << "\n";
                            sendAll(clientSocket, "Invalid score format.\n");
                        }
                    }
                    else {
                        sendAll(clientSocket, "Unknown packet type");
                    }
                }
                else
                {
                    std::cerr << "Malformed packet received.\n";
                }
            }
        }

        closesocket(clientSocket);
        closesocket(listenSocket);
        WSACleanup();
        return 0;
    }