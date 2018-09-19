#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32")
#include<iostream>
#include<winSock2.h>
#include<WS2tcpip.h>
void GetIPAddr(char*);
int main(int argc, char* argv[]) {
	WSADATA wsa;
	HOSTENT* result = NULL;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	GetIPAddr(const_cast<char*>("www.naver.com"));

	if (argv[1]) {
		GetIPAddr(argv[1]);
	}
	WSACleanup();
	system("pause");
}

void GetIPAddr(char* name) {
	IN_ADDR addr;
	HOSTENT* ptrHostent = gethostbyname(name);

	std::cout << "ÁÖDNS:" << ptrHostent->h_name << std::endl;

	for (auto subname = ptrHostent->h_aliases; *subname != NULL; ++subname)
		std::cout<<"¼­ºêDNS:" << *subname << std::endl;

	for (int i = 0; ptrHostent->h_addr_list[i] != NULL; ++i) {
			addr.s_addr = *(u_long *)ptrHostent->h_addr_list[i++];
			printf("\tIPv4 Address #%d: %s\n", i, inet_ntoa(addr));
	}

}

