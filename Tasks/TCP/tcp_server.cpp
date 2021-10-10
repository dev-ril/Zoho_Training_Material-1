#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define MAX_CLIENTS_IN_QUEUE 5
#define BUFLEN 512

using namespace std;

int main()
{
	//WinSockApplication - Contains information about the Windows Sockets implementation
	WSADATA wsaData;
	struct sockaddr_in  TCPServerAddress;
	struct sockaddr_in TCPClientAddress;

	SOCKET TCPServerSocket;
	SOCKET TCPClientSocket;

	char buffer[BUFLEN];


	cout << "SERVER" << "\n" << endl;

	// 1.WSAStartup

	int iWSAStartupResult; // To store the initiation result

	//Initiate use of WS2_32.dll.
	iWSAStartupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	// To check successful initialization
	if (iWSAStartupResult != 0)
	{
		cout << "WSA Startup failed !!" << endl;
		return 1;
	}


	TCPServerAddress.sin_family = AF_INET; // IPV4 family
	TCPServerAddress.sin_port = htons(8000);
	TCPServerAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	// 2.Creating socket

	TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (TCPServerSocket == INVALID_SOCKET)
	{
		cout << "Socket creation failed !!.\n Error:" << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	cout << "1.Socket\nSocket created successfully\n" << endl;

	// 3. Binding socket

	int iBind; // To store the binding result

	iBind = bind(TCPServerSocket, (SOCKADDR*)&TCPServerAddress, sizeof(TCPServerAddress));
	if (iBind == SOCKET_ERROR)
	{
		cout << "Socket binding failed !!.\n Error:" << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	cout << "2.Bind\nSocket binded successfully\n" << endl;

	// 4.Listen for client request

	int iListen; // To listen for the clients 

	iListen = listen(TCPServerSocket, MAX_CLIENTS_IN_QUEUE);

	if (iListen == SOCKET_ERROR)
	{
		cout << "Listening failed !!.\n Error:" << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	cout << "3.Listen\nListened successfully\n" << endl;

	// 5.Accept the client request

	int iTCPClientAddress = (sizeof(TCPClientAddress));
	TCPClientSocket = accept(TCPServerSocket, (SOCKADDR*)&TCPClientAddress, &iTCPClientAddress);
	if (TCPClientSocket == INVALID_SOCKET)
	{
		cout << "Failed to Accept client!!.\n Error:" << WSAGetLastError() << endl;
		closesocket(TCPClientSocket);
		WSACleanup();
		return 1;
	}
	cout << "4.Accept\nClient accepted successfully\n" << endl;

	// Allocating the buffer
	memset(buffer, '\0', BUFLEN);

	// 6. Receiving data from the client

	int iReceive;
	iReceive = recv(TCPClientSocket, buffer, BUFLEN, 0);
	if (iReceive == SOCKET_ERROR)
	{
		cout << "Data not received!!.\n Error:" << WSAGetLastError() << endl;
		closesocket(TCPClientSocket);
		WSACleanup();
		return 1;
	}
	cout << "Data received: "<< buffer << "\n" << endl;

	// 7. Sending data to the client

	int iSend;

	iSend = send(TCPClientSocket, buffer, BUFLEN, 0);
	if (iSend == SOCKET_ERROR)
	{
		cout << "Data not send!!.\n Error:" << WSAGetLastError() << endl;
		return 1;
	}
	cout << "Data sent!!" << "\n" << endl;

	// 8.Closing the socket

	int iCloseSocket;

	iCloseSocket = closesocket(TCPServerSocket);
	if (iCloseSocket == SOCKET_ERROR)
	{
		cout << "Socket closing failed!!. \nError:" << WSAGetLastError() << endl;
		return 1;
	}
	cout << "Socket closed successfully" << "\n" << endl;

	// 9.WSACleanup
	int iWSACleanup;
	iWSACleanup = WSACleanup();
	if (iWSACleanup == SOCKET_ERROR)
	{
		cout << "Cleanup failed!!.\n Error:" << WSAGetLastError() << endl;
		return 1;
	}
	cout << "Cleaned up" << "\n" << endl;
	system("PAUSE");

	return 0;
}