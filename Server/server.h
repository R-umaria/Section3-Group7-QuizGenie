 #ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring>

#define PORT 27000
#define BUFFER_SIZE 2048

enum SessionState {
    WAITING_FOR_LOGIN,
    IN_PROGRESS,
    FINISHED
};

struct Session {
    std::string username;
    int currentQuestionIndex = 0;
    int score = 0;
    SessionState state = WAITING_FOR_LOGIN;
    std::vector<std::string> correctAnswers;
};

class Server {
public:
    void run();

private:
    int serverSocket;
    fd_set masterSet;
    std::unordered_map<int, Session> sessions;

    void loadCorrectAnswers(Session& session, const std::string& filePath);
    void handleClientMessage(int clientSocket, const std::string& message);
};

#endif // SERVER_H
