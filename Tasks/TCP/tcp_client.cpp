#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include <ws2tcpip.h>
#include<iostream>

#pragma comment(lib, "Ws2_32.lib")

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

	char sender_data[BUFLEN];
	char receiver_data[BUFLEN];


	cout << "CLIENT" << "\n" << endl;

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

	TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (TCPClientSocket == INVALID_SOCKET)
	{
		cout << "Socket creation failed !!.\n Error:" << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	else
		cout << "1.Socket\nSocket created successfully" << "\n" << endl;

	// 3.Connect to the server

	int iConnect;
	iConnect = connect(TCPClientSocket, (SOCKADDR*)&TCPServerAddress, sizeof(TCPServerAddress));
	if (iConnect == SOCKET_ERROR)
	{
		cout << "Connection failed!!.\n Error:" << WSAGetLastError() << endl;
		return 1;
	}
	else 
	{
		cout << "2.Connect\nConnected successfully" << "\n" << endl;
	}

	// 4. Sending data to the server

	int iSend;

	cout << "Enter the data to send: ";
	cin >> sender_data;

	iSend = send(TCPClientSocket, sender_data, BUFLEN, 0);
	if (iSend == SOCKET_ERROR)	
	{
		cout << "Data not send!!.\n Error:" << WSAGetLastError() << endl;
		return 1;
	}
	else
		cout << "Data Sending Success " << "\n" << endl;


	memset(sender_data, '\0', BUFLEN);

	// 5. Receiving data from the server
	
	int iReceive;
	iReceive = recv(TCPClientSocket, receiver_data, BUFLEN, 0);
	if (iReceive == SOCKET_ERROR)
	{
		cout << "Data not received!!.\n Error:" << WSAGetLastError() << endl;
		return 1;
	}
	else
		cout << "Data received: " << receiver_data << "\n" << endl;

	// 8.Closing the socket

	int iCloseSocket;

	iCloseSocket = closesocket(TCPClientSocket);
	if (iCloseSocket == SOCKET_ERROR)
	{
		cout << "Socket closing failed!!. \nError:" << WSAGetLastError() << endl;
		return 1;
	}
	else
		cout << "Socket closed successfully" << "\n" << endl;

	// 9.WSACleanup
	int iWSACleanup;
	iWSACleanup = WSACleanup();
	if (iWSACleanup == SOCKET_ERROR)
	{
		cout << "Cleanup failed!!.\n Error:" << WSAGetLastError() << endl;
		return 1;
	}
	else
		cout << "Cleaned up" << "\n" << endl;
	system("PAUSE");

	return 0;
}