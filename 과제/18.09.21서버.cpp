#pragma comment(lib,"ws2_32")
#include<iostream>
#include<WinSock2.h>

#define SERVERPORT 9000
#define BUFSIZE 50


void err_quit(const char*);
void err_display(const char*);
int recvn(SOCKET, char*, int, int);
int main() {






	system("pause");
}
void err_quit(const char* msg) {
	LPVOID lpMsgBuf;
	
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPTSTR>(&lpMsgBuf), 0, NULL);
	MessageBox(NULL, reinterpret_cast<LPCTSTR>(lpMsgBuf),reinterpret_cast<LPCWSTR>(msg), MB_ICONERROR);
	LocalFree(lpMsgBuf);

	exit(1);
}
void err_display(const char* msg){
}
int recvn(SOCKET s, char* buf, int len, int flag) {

}