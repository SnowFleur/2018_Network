#pragma comment(lib,"ws2_32")
#include<iostream>
#include<WinSock2.h>
#include<bitset>


void err_quit(const  char*);
int main() {
		/*윈도우 소켓 초기화*/
		WSADATA wsa;
		if(WSAStartup(MAKEWORD(2,1),&wsa)!=0)
			return 1;
	


	

		WORD hi_bit = 0;
		WORD low_bit = 0;

		hi_bit = wsa.wVersion & 0xff;
		low_bit = (wsa.wVersion >> 8)& 0xff;

		//std::cout <<std::bitset<8> (wsa.wVersion) << std::endl;
		std::cout <<hi_bit <<"."<<low_bit << std::endl;
		//std::cout << wsa.wHighVersion << std::endl;
		std::cout << wsa.szDescription << std::endl;
		std::cout << wsa.szSystemStatus << std::endl;
	

	/*	std::cout <<static_cast<__int8>(hi_bit) << std::endl;
		std::cout << static_cast<__int8>(low_bit) << std::endl;*/



		std::cout << "--------------------------------------" << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		WSADATA wsa2;
	
		if (WSAStartup(MAKEWORD(1, 1), &wsa2) != 0)
			return 1;
	
		hi_bit = wsa2.wVersion & 0xff;
		low_bit = (wsa2.wVersion >> 8) & 0xff;

	
		std::cout << hi_bit << "." << low_bit << std::endl;
		//std::cout << wsa2.wVersion << std::endl;
		std::cout << wsa2.wHighVersion << std::endl;
		std::cout << wsa2.szDescription << std::endl;
		std::cout << wsa2.szSystemStatus << std::endl;
	
	
	//	MessageBox(NULL, reinterpret_cast<LPCWSTR>("윈속 초기화 성공"), reinterpret_cast<LPCWSTR>("알림"), MB_OK);
	
		/*윈도우 소켓 종료*/
		WSACleanup();
		WSACleanup();
	
		
		system("pause");
	}

void err_quit(const char* msg) {


	/*voidv포인터*/
	LPVOID lpMsgbuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&lpMsgbuf), 0, NULL);

	MessageBox(NULL, reinterpret_cast<LPWSTR>(lpMsgbuf),(LPWSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgbuf);
	exit(1);
}
