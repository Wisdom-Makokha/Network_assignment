#include <iostream>
#include <winsock2.h>

#define IP_ADDRESS "127.0.0.1"
#define PORT_NO 55555

using namespace std;

int main()
{
    // Initialize WSA variables
    WSADATA wsaData;
    int wsa_error;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsa_error = WSAStartup(wVersionRequested, &wsaData);

    // Check for initialization success
    if (wsa_error != 0)
    {
        cout << "The Winsock dll not found!" << endl;
        return 0;
    }
    else
    {
        cout << "The Winsock dll found" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;
    }

    // Create a socket
    SOCKET serverSocket;
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Check for socket creation success
    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
        cout << "Socket is OK" << endl;

    // Bind the socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    service.sin_port = htons(PORT_NO); // choose a port number

    // Use the bind function
    if (bind(serverSocket, reinterpret_cast<SOCKADDR *>(&service), sizeof(service)) == SOCKET_ERROR)
    {
        cout << "bind() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else
        cout << "bind() is OK!" << endl;

    // Listen for incoming connections
    if (listen(serverSocket, 1) == SOCKET_ERROR)
        cout << "Listen(): Error listening on socket: " << WSAGetLastError() << endl;
    else
        cout << "Listen() is OK! I'm waiting for new connections... " << endl;

    // Accept incoming connections
    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, nullptr, nullptr);

    // Check for successful connection
    if (acceptSocket == INVALID_SOCKET)
    {
        cout << "Accept failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }
    else
        cout << "Accept() is OK!" << endl;

    //Receive data from the client
    char receiveBuffer[200];
    int receiveByteCount = recv(acceptSocket, receiveBuffer, 200, 0);
    if(receiveByteCount < 0)
    {
        cout << "Server recv error: " << WSAGetLastError() << endl;
        return 0;
    }
    else
        cout << "Received data: " << receiveBuffer << endl;

    //Send a response to the client
    char buffer[200];
    cout << "Enter the message: ";
    cin.getline(buffer, 200);
    int sendByteCount = send(acceptSocket, buffer, 200, 0);
    if(sendByteCount == SOCKET_ERROR)
    {
        cout << "Server send error: " << WSAGetLastError() << endl;
        return -1;
    }
    else
        cout << "Server: Sent " << sendByteCount << " bytes" << endl;

    return 0;
}