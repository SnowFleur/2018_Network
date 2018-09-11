#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"ws2_32")

#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<memory.h>
//
//int main() {
//	WSADATA wsa;
//
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//		return 1;
//
//	/*---------------------*/
//	/*        IPv4         */
//	/*---------------------*/
//
//	//������ IPv4 ��ȯ ����
//
//	char* ipv4test = const_cast<char*>("147.46.114.70");
//
//	std::cout << "IPv4�ּҺ�ȯ��:" << ipv4test << std::endl;
//
//	// inet_addr()�Լ� ����
//	//���ڿ��� ��Ʈ��ũ����Ʈ���� ������ 32��Ʈ �������� ��ȯ���ش�.
//	std::cout << "IPv4�ּҺ�ȯ��:" << std::hex << "0x" << inet_addr(ipv4test) << std::endl;
//
//
//
//	//inet_nota()�Լ� ����
//	
//	
//	IN_ADDR ipv4num;/*ipv4 �����ּ� ����ü*/
//	ipv4num.s_addr = inet_addr(ipv4test);
//	std::cout << "�ٽ� �ּҺ�ȯ ��" << inet_ntoa(ipv4num) << std::endl;
//
//
//
//	SOCKADDR_IN ab;
//	IN_ADDR c;
//
//	WSACleanup();
//
//	system("pause");
//}

#define TESTNAME "www.naver.com"



/*���� �Լ� �������*/
void err_display( char* msg) {

	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPTSTR>(&lpMsgBuf), 0, NULL);
		
	std::cout << msg << reinterpret_cast<char*>(lpMsgBuf);
}

// ������->ipv4

BOOL GetIPAddr(char* name, IN_ADDR* ipv4) {



	
	HOSTENT* ptr = gethostbyname(name);

	if (ptr == NULL) {
		err_display(const_cast<char*> ("gethostbyname()"));
		return FALSE;
	}
	if (ptr->h_addrtype != AF_INET) {
		return FALSE;
	}

	memcpy(ipv4, ptr->h_addr, ptr->h_length);
	return TRUE;
}
// ipv4->������

BOOL GetDomainName(IN_ADDR ipv4, char* name, int namelen) {
	
	
	HOSTENT* ptr = gethostbyaddr( ( char*)&ipv4  , sizeof(ipv4), AF_INET);





	if (ptr == NULL) {
		err_display(const_cast<char*>("gethostbyAddr"));
	}
	if (ptr->h_addrtype != AF_INET) {
		return FALSE;
	}
	strncpy(name, ptr->h_name,namelen);

	return TRUE;
}

int main() {
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {

		return 1;

	}
	std::cout << "������ �̸�(��ȯ��)" << TESTNAME << std::endl;

	IN_ADDR addr;

	if (GetIPAddr(const_cast<char*>(TESTNAME), &addr)) {
		std::cout << "IP�ּ� ��ȯ��" << inet_ntoa(addr) << std::endl;
	}

	char name[256];

	if (GetDomainName(addr, name, sizeof(name))) {
		std::cout << "�ٽ� �������̸����� ��ȯ" << name << std::endl;
		
	}





	WSACleanup();
	system("pause");
}