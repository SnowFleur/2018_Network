#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32")
#include<iostream>
#include<winsock2.h>
#include<fstream>
#define SERVERPORT 9000
#define BUFSIZE 1400


struct FileInfor {
	char name[255];
	DWORD fileSize;

};

using ifstrem = std::ifstream;
using ofstrem = std::ofstream;

int recvn(SOCKET, char*, int, int);
int main() {

	int retval;
	FileInfor file;
	ofstrem filedownload;


	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
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
	//통신에 사용할 변수
	SOCKET client_socket;
	SOCKADDR_IN client_addr;
	

	int addrlen;
	char buf[BUFSIZE + 1];
	int len = 0, ab;
	int fileCount;
	unsigned int count;
	while (1) {
		//accept
		addrlen = sizeof(client_addr);
		client_socket = accept(listen_sock, reinterpret_cast<SOCKADDR*>(&client_addr), &addrlen);

		if (client_socket == INVALID_SOCKET) {
			std::cout << "accept error" << std::endl;
			break;
		}

		std::cout << "[TCP서버] 클라이언트접속 IP주소: " << inet_ntoa(client_addr.sin_addr) << " 포트번호: " << ntohs(client_addr.sin_port) << std::endl;

		//데이터 받기 (고정길이)
		retval = recvn(client_socket, reinterpret_cast<char*>(&file), sizeof(file), 0);
		if (retval == SOCKET_ERROR) {
			std::cout << "recvn error" << std::endl;
			break;
		}
		else if (retval == 0)
			break;

		std::cout << "받은 파일이름:" << file.name << std::endl;
		std::cout << "받은 파일크기:" << file.fileSize << std::endl;

		filedownload.open(file.name, std::ios::binary);

		
		 int count = file.fileSize / BUFSIZE;
		 int saveCount = count;
	
		 while (count) {
			//데이터 받기 (가변길이)
			retval = recvn(client_socket, buf,
				BUFSIZE, 0);

			if (retval == SOCKET_ERROR) {
				std::cout << "recvn error" << std::endl;
				break;
			}
			else if (retval == 0)
				break;


			std::cout << "받은데이터양" << retval << std::endl;
			filedownload.write(buf, BUFSIZE);
			
			--count;
		}


		//남은길이
		 int remainData = file.fileSize - (saveCount*BUFSIZE);
		 retval = recvn(client_socket, buf, remainData, 0);
		 std::cout << "받은데이터양" << retval << std::endl;

		filedownload.write(buf,remainData);
		filedownload.close();



		std::cout << "TCP" << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << "]" << std::endl;


	}

	//closesocket
	closesocket(listen_sock);
	WSACleanup();

	system("pause");
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