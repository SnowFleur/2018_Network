#pragma comment(lib,"ws2_32")
#include<iostream>
#include<WinSock2.h>

#define SERVERPORT 9000
int main() {
	int retval;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;


	SOCKET listen_sock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN serverAddr;

	ZeroMemory(&serverAddr, sizeof(serverAddr));

	serverAddr.sin_port = htons(SERVERPORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_family = AF_INET;
	
	/*
	���ε�: �����Ƿ��� IP,���� ��Ʈ ����
	*/
	retval = bind(listen_sock, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr));

	if (retval == SOCKET_ERROR)
		return;


}