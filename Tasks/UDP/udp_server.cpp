
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define BUFLEN 1025

using namespace std;

int main()
{
	WSADATA wsaData;
	struct sockaddr_in UDPServerAddress;

	struct sockaddr_in SenderAddress;
	int SenderAddressSize = sizeof(SenderAddress);

	int iWSAStartupResult; // To store the initiation result

	int bytes_received;
	char serverBuf[1025];
	int serverBufLen = 1024;

	cout << "UDP SERVER" << "\n" << endl;

	// 1.WSAStartup

	iWSAStartupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iWSAStartupResult != 0)
	{
		cout << "WSA Startup failed !!" << endl;
		return 1;
	}

	//1.Socket creation
	SOCKET UDPServerSocket = INVALID_SOCKET;
	UDPServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (UDPServerSocket == INVALID_SOCKET) 
	{
		cout << "Socket creation failed !!.\n Error:" << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	cout << "1.Socket\nSocket created successfully\n" << endl;

	//2.Binding

	UDPServerAddress.sin_family = AF_INET;
	UDPServerAddress.sin_port = htons(8000);
	UDPServerAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(UDPServerSocket, (SOCKADDR*)&UDPServerAddress, sizeof(UDPServerAddress))) 
	{
		cout << "Socket binding failed !!.\n Error:" << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	cout << "2.Bind\nSocket binded successfully\n" << endl;

	cout << "3.Send/Receive\n" << endl;

	//3.Receiving data

	bytes_received = recvfrom(UDPServerSocket, serverBuf, serverBufLen, 0 , (SOCKADDR*)&SenderAddress, &SenderAddressSize);
	if (bytes_received == SOCKET_ERROR) 
	{
		cout << "Data not received!!.\n Error:" << WSAGetLastError() << endl;
		closesocket(UDPServerSocket);
		WSACleanup();
		return 1;
	}
	serverBuf[bytes_received] = '\0';

	cout << "Data received: " << serverBuf << "\n" << endl;

	//4.Sending data

	char sendBuf[BUFLEN];

	int iResult = 0;
	int sendBufLen = (int)(sizeof(serverBuf) - 1);
	int sendResult = sendto(UDPServerSocket, serverBuf, sendBufLen, 0, (SOCKADDR*)&SenderAddress, SenderAddressSize);

	if (iResult == SOCKET_ERROR) {
		cout << "Data not sent!!.\n Error:" << WSAGetLastError() << endl;
		return 1;
	}
	cout << "Data sent!!" << "\n" << endl;

	// 5.Closing the socket

	int iCloseSocket;

	iCloseSocket = closesocket(UDPServerSocket);
	if (iCloseSocket == SOCKET_ERROR)
	{
		cout << "Socket closing failed!!. \nError:" << WSAGetLastError() << endl;
		return 1;
	}
	cout << "Socket closed successfully" << "\n" << endl;

	// 6.WSACleanup

	int iWSACleanup;
	iWSACleanup = WSACleanup();
	if (iWSACleanup == SOCKET_ERROR)
	{
		cout << "Cleanup failed!!.\n Error:" << WSAGetLastError() << endl;
		return 1;
	}
	cout << "Cleaned up" << "\n" << endl;
	return 0;
}
