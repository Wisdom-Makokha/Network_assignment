#include <iostream>
#include <winsock2.h>

#define IP_ADDRESS "127.0.0.1"
#define PORT_NO 55555

using namespace std;

int main()
{
    // Initialize WSA variables
    WSADATA wsaData;
    int wsaErr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaErr = WSAStartup(wVersionRequested, &wsaData);

    // check for initialization success
    if (wsaErr != 0)
    {
        cout << "The winsock dll not found" << endl;
        return 0;
    }
    else
    {
        cout << "The winsock dll found" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;
    }

    // create a socket
    SOCKET clientSocket;
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Check for socket creation socket success
    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
        cout << "Socket is OK!" << endl;

    // Connnect to the server
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(IP_ADDRESS); // Replace with server's ip address
    clientService.sin_port = htons(PORT_NO);               // Use the same port as the server

    // Use the connect function
    if (connect(clientSocket, reinterpret_cast<SOCKADDR *>(&clientService), sizeof(clientService)) == SOCKET_ERROR)
    {
        cout << "Client: connect() -Failed to connect: " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
    {
        cout << "Client: Connect() is OK!" << endl;
        cout << "Client: Can start sending and receiving data.. " << endl;
    }

    //Sendinf data to the server
    char buffer[200];
    cout << "Enter the message: ";
    cin.getline(buffer, 200);
    int sendByteCount = send(clientSocket, buffer, 200, 0);
    if(sendByteCount == SOCKET_ERROR)
    {
        cout << "Client send error: " << WSAGetLastError() << endl;
        return -1;
    }
    else
        cout << "Client: Sent " << sendByteCount << " bytes" << endl;

    //Receivinf data from the server
    char receiveBuffer[200];
    int receiveByteCount = recv(clientSocket, receiveBuffer, 200, 0);
    if (receiveByteCount < 0)
    {
        cout << "Client recv error: " << WSAGetLastError() << endl;
        return 0;
    }
    else
        cout << "Client: Received data: " << receiveBuffer << endl;

    return 0;
}