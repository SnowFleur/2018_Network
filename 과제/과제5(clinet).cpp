#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32")
#include<WinSock2.h>
#include<iostream>
#include<fstream>
#define SERVERPORT 9000
#define SERVERIP "127.0.0.1"
#define BUFSIZE 256


using ifstrem = std::ifstream;
using ofstrem = std::ofstream;

int main() {


	ifstrem open;

	open.open("test.jpg", std::ios::binary | std::ios::out);

	if (!open.is_open())
		std::cout << "������ ���� ���߽��ϴ�." << std::endl;
	//������ ���������� ������ �ű�
	open.seekg(0, std::ios::end);
	//���ϻ���� ����
	int fileSize = open.tellg();
	// �ٽ� ������ ó������ �����͸� �ű�
	open.seekg(0, std::ios::beg);



	WSADATA wsa;
	int retval;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		std::cout << "WSAStartUP error" << std::endl;
		return 0;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		std::cout << "INVALID_SOCKET" << std::endl;
		return 0;
	}

	//connet
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	retval = connect(sock, reinterpret_cast<SOCKADDR*>(&serveraddr), sizeof(serveraddr));

	char data;
	char buf[BUFSIZE]; //�ѹ��� ���� ��
	if (retval == SOCKET_ERROR) {
		std::cout << "connect error" << std::endl;
		return 0;
	}


	/*
	����ũ�� ��������
	*/
	retval = send(sock, reinterpret_cast<char*>(&fileSize), sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		std::cout << "���� ����" << std::endl;
	}



	/*
	��������
	*/
	/*
	���� �ӵ�(KB/sec) = ������� ���۵� ����ũ�� /  ������� ������ ����� �ð�(TotalSeconds);

	*/

	int i = 0;
//	while (open.tellg()!=EOF) {
		open.read(buf,fileSize);
		retval = send(sock, buf, fileSize, 0);


		if (retval == SOCKET_ERROR) {
			std::cout << "���� ����" << std::endl;
	//		break;
		}
	
		std::cout<<retval<< "�����͸� ���½��ϴ� ."<<++i << std::endl;
	//	open.seekg(fileSize,std::ios::cur);
//	}





		/*retval = send(sock, reinterpret_cast<char*>(&open), fileSize, 0);
		if (retval == SOCKET_ERROR) {
			std::cout << "���� ����" << std::endl;
		}*/


	std::cout << "���� ����������" << retval << std::endl;




	closesocket(sock);
	WSACleanup();
	
	system("pause");

}