#pragma comment(lib,"ws2_32")
#include<iostream>
#include<WinSock2.h>



/***************************
practice 2-1 윈도우 소켓 초기화
**************************/

//int main() {
//	/*윈도우 소켓 초기화*/
//	WSADATA wsa;
//	if(WSAStartup((2.2),&wsa)!=0)
//		return 1;
//
//	MessageBox(NULL, "윈속 초기화 성공", "알림", MB_OK);
//
//	/*윈도우 소켓 종료*/
//	WSACleanup();
//
//}




/***************************
practice 2-2 윈도우 소켓 생성
**************************/

//
//void err_quit(const char*);
//int main() {
//
//
//	/*윈속 초기화*/
//	WSADATA wsa; //소켓구조체
//
//
//
//	/*윈속 초기화 함수*/
//	/*0이 반환되면 초기화성공*/
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//		return 1;
//
//	MessageBox(NULL, "윈속초기화성공", "알림", MB_OK);
//
//	//socket()
//
//	SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	
//	if (tcp_sock == INVALID_SOCKET)
//		err_quit("socket()");
//	
//	MessageBox(NULL, "TCP 소켓 생성 성공", "알림", MB_OK);
//
//	//closesocket()
//	closesocket(tcp_sock);
//
//	//종료
//	WSACleanup();
//	
//}
//
//void err_quit(const char* msg) {
//
//
//	/*voidv포인터*/
//	LPVOID lpMsgbuf;
//	
//	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,NULL,WSAGetLastError(),
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&lpMsgbuf), 0, NULL);
//
//	MessageBox(NULL, reinterpret_cast<LPSTR>(lpMsgbuf), msg, MB_ICONERROR);
//	LocalFree(lpMsgbuf);
//	exit(1);
//}
//






/*
연습문제
*/


/*
1번 
답:책에 필기함
*/
//int main() {
//	/*윈도우 소켓 초기화*/
//	WSADATA wsa;
//	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0)
//		return 1;
//
//
//	std::cout << "윈속 2.2버전" << std::endl;
//	std::cout << wsa.wVersion << std::endl;
//	std::cout << wsa.wHighVersion << std::endl;
//	std::cout << wsa.szDescription << std::endl;
//	std::cout << wsa.szSystemStatus << std::endl;
//
//
//	std::cout << "--------------------------------------" << std::endl;
//	std::cout << "--------------------------------------" << std::endl;
//	std::cout << "--------------------------------------" << std::endl;
//
//	WSADATA wsa2;
//
//	if (WSAStartup(MAKEWORD(1, 1), &wsa2) != 0)
//		return 1;
//
//
//	std::cout << "윈속 1.1버전" << std::endl;
//	std::cout << wsa2.wVersion << std::endl;
//	std::cout << wsa2.wHighVersion << std::endl;
//	std::cout << wsa2.szDescription << std::endl;
//	std::cout << wsa2.szSystemStatus << std::endl;
//
//
//
//	MessageBox(NULL, "윈속 초기화 성공", "알림", MB_OK);
//
//	/*윈도우 소켓 종료*/
//	WSACleanup();
//	WSACleanup();
//
//	
//	system("pause");
//}


/*
2,3,4

*/
//
//void err_quit(const char*);
//int main() {
//
//
//	/*윈속 초기화*/
//	WSADATA wsa; //소켓구조체
//
//
//
//	/*윈속 초기화 함수*/
//	/*0이 반환되면 초기화성공*/
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//		return 1;
//
//	MessageBox(NULL, "윈속초기화성공", "알림", MB_OK);
//
//	//socket()
//
//	SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	
//	/*2번문제*/
//	SOCKET udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//
//	/*3번문제*/
//	SOCKET tcp_sock64 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
//
//	/*4번문제*/
//	SOCKET udp_sock64 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
//
//	if (tcp_sock == INVALID_SOCKET)
//		err_quit("socket()");
//	
//	MessageBox(NULL, "TCP 소켓 생성 성공", "알림", MB_OK);
//
//	//closesocket()
//	closesocket(tcp_sock);
//	closesocket(tcp_sock64);
//	closesocket(udp_sock);
//	closesocket(udp_sock64);
//
//	//종료
//	WSACleanup();
//	
//}
//void err_quit(const char* msg) {
//
//
//	/*voidv포인터*/
//	LPVOID lpMsgbuf;
//	
//	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,NULL,WSAGetLastError(),
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&lpMsgbuf), 0, NULL);
//
//	MessageBox(NULL, reinterpret_cast<LPSTR>(lpMsgbuf), msg, MB_ICONERROR);
//	LocalFree(lpMsgbuf);
//	exit(1);
//}





/*
5번
*/

void err_quit(const char*);
int f(int);
int main() {


	int retval = f(-1);

	if (retval == SOCKET_ERROR)
		err_quit("f()");



	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;


	SOCKET tcp_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP,NULL,0,0);



	WSACleanup();

	system("pause");
	
}
int f(int x) {


	if (x >= 0) {
		WSASetLastError(0);
		return 0;
	}
	else {
		WSASetLastError(WSAEMSGSIZE);
		return SOCKET_ERROR;
	}

}
void err_quit(const char* msg) {


	/*voidv포인터*/
	LPVOID lpMsgbuf;
	
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,NULL,WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&lpMsgbuf), 0, NULL);

	MessageBox(NULL, reinterpret_cast<LPSTR>(lpMsgbuf), msg, MB_ICONERROR);
	LocalFree(lpMsgbuf);
	exit(1);
}
