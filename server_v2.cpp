#include <iostream>
#include <winsock2.h>

#define IP_ADDRESS "127.0.0.1"
#define PORT_NO 55555

using namespace std;

int main() 
{
    //Initialize WSA variables
    WSADATA wsaData;
    int wsa_error;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsa_error = WSAStartup(wVersionRequested, &wsaData);

    //Check for initialization success
    if(wsa_error != 0)
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
    if(serverSocket == INVALID_SOCKET)
    {
        cout << "Error at socket(): " <<WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else
        cout << "Socket is OK" << endl;

    //Bind the socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    service.sin_port = htons(PORT_NO); //choose a port number

    //Use the bind function 
    if(bind(serverSocket, reinterpret_cast<SOCKADDR*>))
}