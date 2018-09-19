#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32")

#include<iostream>
#include<WinSock2.h>

int main(int argc, char* argv[]) {
	WORD max, min;
	int retval;
	if (argc == 4) {
		min = atoi(argv[2]);
		max = atoi(argv[3]);

		WSADATA wsa;

		WSAStartup(MAKEWORD(2, 2), &wsa);
		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == INVALID_SOCKET)
			return 0;

		
		HOSTENT* host = gethostbyname(const_cast<const char*>(argv[1]));
		in_addr addr;
		SOCKADDR_IN server_addr;

		addr.s_addr = *reinterpret_cast<DWORD*>(host->h_addr_list[0]);
		std::cout << inet_ntoa(addr) << std::endl;
		std::cout << "-----------------------" << std::endl << std::endl;


		//connect
		for (WORD count = min; count <= max; count++) {
			ZeroMemory(&server_addr, sizeof(server_addr));
			server_addr.sin_family = AF_INET;
			server_addr.sin_port = htons(count);
			server_addr.sin_addr.s_addr = *reinterpret_cast<DWORD*>(host->h_addr_list[0]);

			retval = connect(sock, reinterpret_cast<SOCKADDR*>(&server_addr), sizeof(server_addr));
			if (retval != SOCKET_ERROR)
				std::cout << "IP :" << inet_ntoa(server_addr.sin_addr) << " " << "포트번호:" << ntohs(server_addr.sin_port) << " " << "상태:LISTENING" << std::endl;
			else
				std::cout << "IP :" << inet_ntoa(server_addr.sin_addr) << " " << "포트번호: " << ntohs(server_addr.sin_port) << " " << "상태: not LISTENING" << std::endl;
		}
		WSACleanup();
	}
	else {
		std::cout << "3개의 인자를 입력하세요" << std::endl;
		return 0;
	}


	system("pause");
	return 0;
}
