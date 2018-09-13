#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32")
#include<iostream>
#include<WinSock2.h>

#define SERVER_PORT 9000
#define SERVER_IP "192.168.103.94"
#define BUF_SIZE 512

/*����� ���� ������ �����Լ�*/
int recvn(SOCKET, char*, int, int);
void ErrDisPlay(char*);
int main() {
	int retval;

	//���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		ErrDisPlay(const_cast<char*>("socket()"));

	//connect
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVER_PORT);
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		ErrDisPlay(const_cast<char*>("connect()"));

	//��������ſ� ����� ����

	char buf[BUF_SIZE + 1];
	int len;

	//������ ������ ���
	while (1) {
		//������ �Է�
		std::cout << "\n[���� ������]";
		if (fgets(buf, BUF_SIZE + 1, stdin) == NULL)
			break;

		// \n���� ����
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		//������ ������
		retval = send(sock, buf, strlen(buf), 0);

		if (retval == SOCKET_ERROR){
			ErrDisPlay(const_cast<char*>("send()"));
			break;
		}

		std::cout << "[TCP Ŭ���̾�Ʈ]" << retval << "����Ʈ�� ���½��ϴ�." << std::endl;

		//������ �ޱ�
		retval = recvn(sock, buf, retval, 0);
		if (retval == SOCKET_ERROR) {
			ErrDisPlay(const_cast<char*>("recvn()"));
			break;
		}
		else if (retval == 0)
			break;

		//���� ������ ���
		buf[retval] = '\0';

		std::cout << "[TCP Ŭ���̾�Ʈ]" << retval << "����Ʈ�� �޾ҽ��ϴ�.";
		std::cout << "[���� ������]" << buf;


	}
	closesocket(sock);


	WSACleanup();
	system("pause");
}


int recvn(SOCKET socket, char* pbuf, int len, int flags) {
	int received;
	char* ptr = pbuf;
	int left = len;

	while (left > 0) {
		received = recv(socket, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
	return (len - left);
}

void ErrDisPlay(char*){}