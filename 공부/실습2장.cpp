#pragma comment(lib,"ws2_32")
#include<iostream>
#include<WinSock2.h>



/***************************
practice 2-1 ������ ���� �ʱ�ȭ
**************************/

//int main() {
//	/*������ ���� �ʱ�ȭ*/
//	WSADATA wsa;
//	if(WSAStartup((2.2),&wsa)!=0)
//		return 1;
//
//	MessageBox(NULL, "���� �ʱ�ȭ ����", "�˸�", MB_OK);
//
//	/*������ ���� ����*/
//	WSACleanup();
//
//}




/***************************
practice 2-2 ������ ���� ����
**************************/

//
//void err_quit(const char*);
//int main() {
//
//
//	/*���� �ʱ�ȭ*/
//	WSADATA wsa; //���ϱ���ü
//
//
//
//	/*���� �ʱ�ȭ �Լ�*/
//	/*0�� ��ȯ�Ǹ� �ʱ�ȭ����*/
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//		return 1;
//
//	MessageBox(NULL, "�����ʱ�ȭ����", "�˸�", MB_OK);
//
//	//socket()
//
//	SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	
//	if (tcp_sock == INVALID_SOCKET)
//		err_quit("socket()");
//	
//	MessageBox(NULL, "TCP ���� ���� ����", "�˸�", MB_OK);
//
//	//closesocket()
//	closesocket(tcp_sock);
//
//	//����
//	WSACleanup();
//	
//}
//
//void err_quit(const char* msg) {
//
//
//	/*voidv������*/
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
��������
*/


/*
1�� 
��:å�� �ʱ���
*/
//int main() {
//	/*������ ���� �ʱ�ȭ*/
//	WSADATA wsa;
//	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0)
//		return 1;
//
//
//	std::cout << "���� 2.2����" << std::endl;
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
//	std::cout << "���� 1.1����" << std::endl;
//	std::cout << wsa2.wVersion << std::endl;
//	std::cout << wsa2.wHighVersion << std::endl;
//	std::cout << wsa2.szDescription << std::endl;
//	std::cout << wsa2.szSystemStatus << std::endl;
//
//
//
//	MessageBox(NULL, "���� �ʱ�ȭ ����", "�˸�", MB_OK);
//
//	/*������ ���� ����*/
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
//	/*���� �ʱ�ȭ*/
//	WSADATA wsa; //���ϱ���ü
//
//
//
//	/*���� �ʱ�ȭ �Լ�*/
//	/*0�� ��ȯ�Ǹ� �ʱ�ȭ����*/
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//		return 1;
//
//	MessageBox(NULL, "�����ʱ�ȭ����", "�˸�", MB_OK);
//
//	//socket()
//
//	SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	
//	/*2������*/
//	SOCKET udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//
//	/*3������*/
//	SOCKET tcp_sock64 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
//
//	/*4������*/
//	SOCKET udp_sock64 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
//
//	if (tcp_sock == INVALID_SOCKET)
//		err_quit("socket()");
//	
//	MessageBox(NULL, "TCP ���� ���� ����", "�˸�", MB_OK);
//
//	//closesocket()
//	closesocket(tcp_sock);
//	closesocket(tcp_sock64);
//	closesocket(udp_sock);
//	closesocket(udp_sock64);
//
//	//����
//	WSACleanup();
//	
//}
//void err_quit(const char* msg) {
//
//
//	/*voidv������*/
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
5��
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


	/*voidv������*/
	LPVOID lpMsgbuf;
	
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,NULL,WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&lpMsgbuf), 0, NULL);

	MessageBox(NULL, reinterpret_cast<LPSTR>(lpMsgbuf), msg, MB_ICONERROR);
	LocalFree(lpMsgbuf);
	exit(1);
}
