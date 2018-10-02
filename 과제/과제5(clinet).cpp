#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32")
#include<WinSock2.h>
#include<iostream>
#include<fstream>
#define SERVERPORT 9000
#define SERVERIP "127.0.0.1"
#define BUFSIZE 1400


using ifstrem = std::ifstream;
using ofstrem = std::ofstream;


struct FileInfor {
	char name[255];
	DWORD fileSize;

};

int main() {
	char name[255];
	FileInfor file;

	std::cout << "�����̸��� �Է��ϼ���:";
	std::cin >> file.name;

	ifstrem uploadFile(file.name, std::ios::binary | std::ios::in);


	if (uploadFile.fail())
		std::cout << "������ ���� ���߽��ϴ�." << std::endl;

	//������ ���������� ������ �ű�
	uploadFile.seekg(0, std::ios::end);
	//���ϻ���� ����
	file.fileSize = uploadFile.tellg();
	// �ٽ� ������ ó������ �����͸� �ű�
	uploadFile.seekg(0, std::ios::beg);



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



	char buf[BUFSIZE]; //�ѹ��� ���� ��
	if (retval == SOCKET_ERROR) {
		std::cout << "connect error" << std::endl;
		return 0;
	}


	/*
	����ũ�� ��������
	*/
	retval = send(sock, reinterpret_cast<char*>(&file), sizeof(file), 0);
	if (retval == SOCKET_ERROR) {
		std::cout << "���� ����" << std::endl;
	}


	std::cout << "���� �����̸�:" << file.name << std::endl;
	std::cout << "���� ����ũ��:" << file.fileSize << std::endl;


	int count = file.fileSize / BUFSIZE;
	int saveCount = count;
	while (count) {

		if (retval == 0)
			break;

		uploadFile.read(buf, BUFSIZE);
		retval = send(sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			std::cout << "���� ����" << std::endl;
			exit(1);
		}
		std::cout << "�����"<<(saveCount-count)*100/saveCount << std::endl;

		--count;
	}

	//���� ũ�� ����
	 int remainData= file.fileSize-(saveCount*BUFSIZE) ;


	uploadFile.read(buf, remainData);
	retval = send(sock, buf, remainData, 0);
	if (retval == SOCKET_ERROR) {
		std::cout << "���� ����" << std::endl;
		exit(1);
	}
	 std::cout << "�����100%" << std::endl;

	
	closesocket(sock);
	WSACleanup();

	system("pause");

}