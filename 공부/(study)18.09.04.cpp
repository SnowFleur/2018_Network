#pragma comment(lib,"ws2_32")
#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
int main() {

	union{

	struct { u_char s_1, s_2, s_3, s_4; }abc;
	struct { u_short s_1, s_2; }efg;

	u_long S_addr;
	}S_UN;

	std::cout << sizeof(float) << std::endl;
	std::cout << sizeof(double) << std::endl;

	std::cout << sizeof(ULONGLONG) << std::endl;

	std::cout << sizeof(S_UN) << std::endl;

system("pause");
} 