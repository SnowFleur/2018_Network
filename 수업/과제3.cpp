#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32")
#include<iostream>
#include<winSock2.h>
#include<WS2tcpip.h>
void GetIPAddr(char*);
int main(int argc, char* argv[]) {
	WSADATA wsa;
	IN_ADDR addr;
	HOSTENT* result = NULL;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	if (argv[1]) {
		GetIPAddr(argv[1]);
	}
	WSACleanup();
	system("pause");
}

void GetIPAddr(char* name) {
	IN_ADDR addr;
	HOSTENT* ptrHostent = gethostbyname(name);

	std::cout << "주DNS:" << ptrHostent->h_name << std::endl;

	for (auto subname = ptrHostent->h_aliases; *subname != NULL; ++subname)
		std::cout<<"서브DNS:" << *subname << std::endl;

	for (auto ip = ptrHostent->h_addr_list; *ip != NULL; ++ip) {

		memcpy(&addr, *ip, ptrHostent->h_length);
		std::cout << "IP주소" << inet_ntoa(addr) << std::endl;
	}
}
