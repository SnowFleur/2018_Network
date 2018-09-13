#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32")
#include<iostream>
#include<WinSock2.h>

#define SERVER_PORT 9000
#define BUF_SIZE 512


void ErrQuit(char*);
void ErrDisPlay(char*);
int main() {

	WSADATA wsa;
	int retval=0;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
 

	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (listen_sock == INVALID_SOCKET)
		ErrQuit(const_cast<char*>("socket()"));


	/*bind*/
	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr=htonl( INADDR_ANY);
	serverAddr.sin_port = htons(SERVER_PORT);
	
	retval = bind(listen_sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (retval == SOCKET_ERROR) {
		ErrQuit(const_cast<char*>("bind()"));
	}

	//listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
		ErrQuit(const_cast<char*>("listen()"));


	//������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN client_addr;
	int addrlen;
	char buf[BUF_SIZE + 1];
	while (1) {

		//accept()

		addrlen = sizeof(client_addr);
		client_sock = accept(listen_sock, (SOCKADDR*)&client_addr, &addrlen);

		if (client_sock == INVALID_SOCKET) {
			ErrDisPlay(const_cast<char*>("accept()"));
			break;
		}


		//������ Ŭ���̾�Ʈ ���� ���
		std::cout << "\n [TCP����] Ŭ���̾�Ʈ ����: IP�ּ�" << inet_ntoa(client_addr.sin_addr) << "��Ʈ��ȣ:" << ntohs(client_addr.sin_port);


		//Ŭ���̾�Ʈ�� ������ ���
		while (1) {
			//������ �ޱ�
			retval = recv(client_sock, buf, BUF_SIZE, 0);
			if (retval == SOCKET_ERROR) {
				ErrDisPlay(const_cast<char*>("recv()"));
				break;
			}
		else if (retval == 0)
			break;
			
			//���� ������ ���
			buf[retval] = '\0';
			std::cout << "TCP" << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port)<<"]"<<buf << std::endl;

			//������ ������
			retval = send(client_sock, buf, retval, 0);
			if (retval == SOCKET_ERROR) {
				ErrDisPlay(const_cast<char*>("send()"));
				break;
			}
		}
		//closesocket()
		closesocket(client_sock);
		std::cout << "[TCP ����]Ŭ���̾�Ʈ ����: IP�ּ�:" << inet_ntoa(client_addr.sin_addr) << "��Ʈ��ȣ=" << ntohs(client_addr.sin_port);
	}
	closesocket(listen_sock);

	WSACleanup();
	system("pause");
}


void ErrQuit(char* msg) {

	std::cout << msg << std::endl;

}
void ErrDisPlay(char* msg) {
	std::cout << msg << std::endl;

}