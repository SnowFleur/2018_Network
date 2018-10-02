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

	std::cout << "파일이름을 입력하세요:";
	std::cin >> file.name;

	ifstrem uploadFile(file.name, std::ios::binary | std::ios::in);


	if (uploadFile.fail())
		std::cout << "파일을 열지 못했습니다." << std::endl;

	//파일의 마지막으로 포인터 옮김
	uploadFile.seekg(0, std::ios::end);
	//파일사이즈를 구함
	file.fileSize = uploadFile.tellg();
	// 다시 파일의 처음으로 포인터를 옮김
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



	char buf[BUFSIZE]; //한번에 보낼 양
	if (retval == SOCKET_ERROR) {
		std::cout << "connect error" << std::endl;
		return 0;
	}


	/*
	파일크기 고정전송
	*/
	retval = send(sock, reinterpret_cast<char*>(&file), sizeof(file), 0);
	if (retval == SOCKET_ERROR) {
		std::cout << "고정 오류" << std::endl;
	}


	std::cout << "보낸 파일이름:" << file.name << std::endl;
	std::cout << "보낸 파일크기:" << file.fileSize << std::endl;


	int count = file.fileSize / BUFSIZE;
	int saveCount = count;
	while (count) {

		if (retval == 0)
			break;

		uploadFile.read(buf, BUFSIZE);
		retval = send(sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			std::cout << "가변 오류" << std::endl;
			exit(1);
		}
		std::cout << "진행률"<<(saveCount-count)*100/saveCount << std::endl;

		--count;
	}

	//남은 크기 전송
	 int remainData= file.fileSize-(saveCount*BUFSIZE) ;


	uploadFile.read(buf, remainData);
	retval = send(sock, buf, remainData, 0);
	if (retval == SOCKET_ERROR) {
		std::cout << "가변 오류" << std::endl;
		exit(1);
	}
	 std::cout << "진행률100%" << std::endl;

	
	closesocket(sock);
	WSACleanup();

	system("pause");

}