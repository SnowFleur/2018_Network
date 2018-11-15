#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"ws2_32")
#include<iostream>
#include<winsock2.h>
#include<Windows.h>
#include<fstream>

#define SERVERPORT 9000
#define BUFSIZE 140
using ifstrem = std::ifstream;
using ofstrem = std::ofstream;
DWORD WINAPI FileSendTherad(LPVOID arg);
CRITICAL_SECTION cs;

#pragma pack(1)
struct FileInfor {
	char name[255];
	DWORD fileSize;
};
#pragma pack()
int recvn(SOCKET s, char* buf, int len, int flag);
int main() {
	int retval;
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	InitializeCriticalSection(&cs);
	//socket
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_sock == INVALID_SOCKET)
		return 0;
	//bind
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, reinterpret_cast<SOCKADDR*>(&serveraddr), sizeof(serveraddr));
	if (retval == SOCKET_ERROR) {
		std::cout << "bind error" << std::endl;
		return 0;
	}
	//listen
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) {
		std::cout << "listen error" << std::endl;
		return 0;
	}
	//��ſ� ����� ����
	SOCKET client_socket;
	SOCKADDR_IN client_addr;
	HANDLE hThread;
	int addrlen;
	while (1) {
		//accept
		addrlen = sizeof(client_addr);
		client_socket = accept(listen_sock, reinterpret_cast<SOCKADDR*>(&client_addr), &addrlen);
		if (client_socket == INVALID_SOCKET) {
			std::cout << "accept error" << std::endl;
			break;
		}
		std::cout << "[TCP����] Ŭ���̾�Ʈ���� IP�ּ�: " << inet_ntoa(client_addr.sin_addr) << " ��Ʈ��ȣ: " << ntohs(client_addr.sin_port) << std::endl << std::endl;
		hThread = CreateThread(NULL, 0, FileSendTherad, reinterpret_cast<LPVOID>(client_socket), 0, NULL);
	}
	//closesocket
	closesocket(listen_sock);
	WSACleanup();
	system("pause");
	return 0;
}

DWORD WINAPI FileSendTherad(LPVOID arg) {
	SOCKET client_socket = reinterpret_cast<SOCKET>(arg);
	SOCKADDR_IN client_addr;
	int retval;
	int addrlen;
	FileInfor file;
	char buf[BUFSIZE + 1];
	char name[255];


	retval = recvn(client_socket, reinterpret_cast<char*>(&buf), sizeof(buf), 0);
		if (retval == SOCKET_ERROR) {
		std::cout << "recvn error" << std::endl;
	}
		std::cout<<"�̸�:"<< buf << std::endl;

	EnterCriticalSection(&cs);
	ifstrem uploadFile(buf, std::ios::binary | std::ios::in);	
	if (uploadFile.fail())
		std::cout << "������ ���� ���߽��ϴ�." << std::endl;
	LeaveCriticalSection(&cs);
	//������ ���������� ������ �ű�
	uploadFile.seekg(0, std::ios::end);
	//���ϻ���� ����
	file.fileSize = uploadFile.tellg();
	// �ٽ� ������ ó������ �����͸� �ű�
	uploadFile.seekg(0, std::ios::beg);


	retval = send(client_socket, reinterpret_cast<char*>(&file), sizeof(file), 0);
	if (retval == SOCKET_ERROR) {
		std::cout << "���� ����" << std::endl;
	}

	EnterCriticalSection(&cs);
	std::cout << "���� �����̸�:" << buf << std::endl;
	std::cout << "���� ����ũ��:" << file.fileSize << std::endl;
	LeaveCriticalSection(&cs);

	int count = file.fileSize / BUFSIZE;
	int saveCount = count;

	addrlen = sizeof(client_addr);
	getpeername(client_socket, reinterpret_cast<SOCKADDR*>(&client_addr), &addrlen);

	while (count) {
		if (retval == 0)
			break;
		uploadFile.read(buf, BUFSIZE);
		retval = send(client_socket, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			std::cout << "���� ����" << std::endl;
			exit(1);
		}
		--count;
	}
	//���� ũ�� ����
	int remainData = file.fileSize - (saveCount*BUFSIZE);
	uploadFile.read(buf, remainData);
	retval = send(client_socket, buf, remainData, 0);
	if (retval == SOCKET_ERROR) {
		std::cout << "���� ����" << std::endl;
		exit(1);
	}
	return 0;
}




int recvn(SOCKET s, char* buf, int len, int flag) {
	int received;
	char* ptr = buf;
	int left = len;
	static int i = 0;
	while (left > 0) {
		received = recv(s, ptr, left, flag);
		if (received == SOCKET_ERROR)
			return 0;

		else if (received == 0)
			break;

		left -= received;
		ptr += received;
	}

	return (len - left);
}
