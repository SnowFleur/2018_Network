#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32")
#include<iostream>
#include<winSock2.h>
#include<WS2tcpip.h>
void GetIPAddr(char*,IN_ADDR&,HOSTENT*);


int main(int argc,char* argv[]) {

	WSADATA wsa;
	IN_ADDR addr;
	HOSTENT* result=NULL;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;


	GetIPAddr(const_cast<char*>("www.naver.com"), addr, result);

	std::cout << "IP林家" << inet_ntoa(addr) << std::endl;
	


	if (argv[1]) {
		GetIPAddr(argv[1], addr,result);

		std::cout<<"IP林家"<< inet_ntoa(addr);

	
		
	
	}





	WSACleanup();
	system("pause");
}
void GetIPAddr(char* name, IN_ADDR& addr,HOSTENT* result) {

	HOSTENT* ptrHostent = gethostbyname(name);
	result = ptrHostent;
	
	std::cout << inet_ntoa(ptrHostent->h_aliases) << std::endl;

	memcpy(&addr, ptrHostent->h_addr, ptrHostent->h_length);

	//addrinfo* presult;
	//getaddrinfo(name,NULL, NULL, &presult);
	//if (presult == NULL)
	//	return;

	//
	//if (presult->ai_family != AF_INET)
	//	return;
	//memcpy(&addr, presult->ai_addr, presult->ai_addrlen);

}