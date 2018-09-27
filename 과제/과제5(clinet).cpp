#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32")
#include<WinSock2.h>
#include<iostream>
#include<fstream>
#define SERVERPORT 9000
#define SERVERIP "127.0.0.1"
#define BUFSIZE 516


using ifstrem = std::ifstream;
using ofstrem = std::ofstream;

int main() {


	ifstrem uploadFile("test.jpg", std::ios::binary | std::ios::in);

	if (uploadFile.fail())
		std::cout << "파일을 열지 못했습니다." << std::endl;
	//파일의 마지막으로 포인터 옮김
	uploadFile.seekg(0, std::ios::end);
	//파일사이즈를 구함
	int fileSize = uploadFile.tellg();
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
	retval = send(sock, reinterpret_cast<char*>(&fileSize), sizeof(fileSize), 0);
	if (retval == SOCKET_ERROR) {
		std::cout << "고정 오류" << std::endl;
	}



	/*
	가변전송
	*/
	/*
	DWORD start;
	DWORD end;
		//std::cout << "전송:" << (start - end) * 100 / start << std::endl;
		//end--;
	전송 속도(KB/sec) = 현재까지 전송된 파일크기 /  현재까지 전송이 진행된 시간(TotalSeconds);

	start = end = fileSize / BUFSIZE;
	*/


	int i = 0, j = 0;
	static int count = 0;
	char data ;
	//while (uploadFile >> data) {

	//	if (data != EOF)
	//	buf[i++] = data;

	//	if (i == BUFSIZE) {
	//	//	buf[i] = '\0';
	//		retval = send(sock, buf, BUFSIZE, 0);
	//		std::cout << "send"<<retval<< std::endl;
	//		if (retval == SOCKET_ERROR) {
	//			std::cout << "가변 오류" << std::endl;
	//			break;
	//		}
	//		i = 0;
	//	}

	//}
	while (1) {
		 std::cout << retval << std::endl;
		 if (retval == 0)
			break;

		uploadFile.read(buf, BUFSIZE);
		retval = send(sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			std::cout << "가변 오류" << std::endl;
			exit(1);
		}


	
	}



	closesocket(sock);
	WSACleanup();

	system("pause");

}