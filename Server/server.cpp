#include "server.h"

void Server::loadCorrectAnswers(Session& session, const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string question, answer;
        if (std::getline(ss, question, ',') && std::getline(ss, answer)) {
            session.correctAnswers.push_back(answer);
        }
    }
}

void Server::handleClientMessage(int clientSocket, const std::string& message) {
    Session& session = sessions[clientSocket];

    if (message.rfind("AUTH", 0) == 0) {
        size_t pos1 = message.find(',');
        size_t pos2 = message.find(',', pos1 + 1);
        size_t pos3 = message.find(',', pos2 + 1);
        if (pos3 != std::string::npos) {
            session.username = message.substr(pos2 + 1);
            session.state = IN_PROGRESS;
            loadCorrectAnswers(session, "pdf_mcq_generator/output/mcq_output.csv");
            std::string successMsg = "Authentication successful\n";
            send(clientSocket, successMsg.c_str(), successMsg.size(), 0);
        } else {
            std::string errorMsg = "Invalid authentication packet.\n";
            send(clientSocket, errorMsg.c_str(), errorMsg.size(), 0);
        }
    } else if (session.state == IN_PROGRESS && message.rfind("ANSWER", 0) == 0) {
        size_t comma = message.find(',');
        if (comma == std::string::npos) {
            std::string errorMsg = "Invalid answer format.\n";
            send(clientSocket, errorMsg.c_str(), errorMsg.size(), 0);
            return;
        }

        std::string userAnswer = message.substr(comma + 1);
        std::transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::toupper);

        int index = session.currentQuestionIndex;
        if (index < session.correctAnswers.size()) {
            std::string correct = session.correctAnswers[index];
            std::transform(correct.begin(), correct.end(), correct.begin(), ::toupper);
            if (userAnswer == correct) {
                session.score++;
                std::string msg = "Correct!\n";
                send(clientSocket, msg.c_str(), msg.size(), 0);
            } else {
                std::string msg = "Wrong! Correct answer was: " + correct + "\n";
                send(clientSocket, msg.c_str(), msg.size(), 0);
            }
            session.currentQuestionIndex++;
        }

        if (session.currentQuestionIndex >= session.correctAnswers.size()) {
            session.state = FINISHED;
            std::ostringstream result;
            result << "Quiz finished. Your score: " << session.score << "/" << session.correctAnswers.size() << "\n";
            send(clientSocket, result.str().c_str(), result.str().size(), 0);
        } else {
            std::string msg = "Next question...\n";
            send(clientSocket, msg.c_str(), msg.size(), 0);
        }
    } else {
        std::string msg = "Invalid or unexpected input.\n";
        send(clientSocket, msg.c_str(), msg.size(), 0);
    }
}

void Server::run() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, SOMAXCONN) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server started on port " << PORT << std::endl;

    FD_ZERO(&masterSet);
    FD_SET(serverSocket, &masterSet);

    while (true) {
        fd_set readSet = masterSet;
        if (select(FD_SETSIZE, &readSet, nullptr, nullptr, nullptr) < 0) {
            perror("select error");
            break;
        }

        for (int i = 0; i < FD_SETSIZE; ++i) {
            if (FD_ISSET(i, &readSet)) {
                if (i == serverSocket) {
                    int clientSocket = accept(serverSocket, nullptr, nullptr);
                    if (clientSocket >= 0) {
                        FD_SET(clientSocket, &masterSet);
                        sessions[clientSocket] = Session();
                        std::cout << "New client connected.\n";
                    }
                } else {
                    char buffer[BUFFER_SIZE] = {0};
                    int bytesReceived = recv(i, buffer, BUFFER_SIZE, 0);
                    if (bytesReceived <= 0) {
                        close(i);
                        FD_CLR(i, &masterSet);
                        sessions.erase(i);
                        std::cout << "Client disconnected.\n";
                    } else {
                        std::string message(buffer, bytesReceived);
                        handleClientMessage(i, message);
                    }
                }
            }
        }
    }

    close(serverSocket);
}
