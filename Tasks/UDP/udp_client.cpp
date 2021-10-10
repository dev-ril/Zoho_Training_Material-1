#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

#define BUFLEN 1025

using namespace std;

int main()
{
	WSADATA wsaData;

	struct sockaddr_in ClientAddress;
	int ClientAddressSize = (int)sizeof(ClientAddress);



	int iWSAStartupResult; // To store the initiation result

	int rec_buf;
	char serverBuf[1025];
	int serverBufLen = 1024;

	// 1.WSAStartup

	iWSAStartupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iWSAStartupResult != 0)
	{
		cout << "WSA Startup failed !!" << endl;
		return 1;
	}

	ClientAddress.sin_family = AF_INET;
	ClientAddress.sin_port = htons(8000);
	ClientAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	// 2.Creating socket

	SOCKET UDPClientSocket;
	UDPClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (UDPClientSocket == INVALID_SOCKET) {
		cout << "Socket creation failed !!.\n Error:" << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	cout << "1.Socket\nSocket created successfully\n" << endl;

	cout << "2.Send/Receive\n" << endl;

	//3.Sending data

	int iResult = 0;
	char send_buf[BUFLEN];

	cout << "Enter data to send:";
	cin >> send_buf;

	int sendBufLen = (int)(sizeof(send_buf) - 1);
	int sendResult = sendto(UDPClientSocket, send_buf, sendBufLen, 0, (SOCKADDR*)&ClientAddress, ClientAddressSize);

	if (iResult == SOCKET_ERROR) 
	{
		cout << "Data not sent!!.\n Error:" << WSAGetLastError() << endl;
		return 1;
	}
	cout << "Data sent!!" << "\n" << endl;

	
	//4.Receiving data

	rec_buf = recvfrom(UDPClientSocket, serverBuf, serverBufLen, 0 , (SOCKADDR*)&ClientAddress, &ClientAddressSize);

	if (rec_buf == SOCKET_ERROR) 
	{
		cout << "Data not received!!.\n Error:" << WSAGetLastError() << endl;
		closesocket(UDPClientSocket);
		WSACleanup();
		return 1;
	}
	serverBuf[rec_buf] = '\0';

	cout << "Data received: " << serverBuf << "\n" << endl;

	// 5.Closing the socket

	int iCloseSocket;

	iCloseSocket = closesocket(UDPClientSocket);
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
