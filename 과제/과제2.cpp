#pragma comment(lib,"ws2_32")
#include<iostream>
#include<WinSock2.h>
BOOL IsLittleEndian();
BOOL IsBigEndian();
int main() {

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	u_short x1 = 0x431;
	u_long y1 = 0x12345678;
	u_short x2 = 0;
	u_long y2 = 0;


	////ȣ��Ʈ ����Ʈ->��Ʈ��ũ ����Ʈ
	//std::cout << "[ȣ��Ʈ ����Ʈ-> ��Ʈ��ũ ����Ʈ]" << std::endl;

	//x2 = htons(x1);
	//std::cout << "0x" << std::hex << x1 << "---->" << "Ox" << std::hex << x2 << std::endl;
	//std::cout << "0x" << std::hex << y1 << "---->" << "Ox" << std::hex << y2 << htonl(y1) << std::endl;

	////��Ʈ��ũ ����Ʈ -> ȣ��Ʈ ����Ʈ

	//std::cout << "[��Ʈ��ũ ����Ʈ-> ȣ��Ʈ ����Ʈ]" << std::endl;

	//std::cout << std::hex << x1 << ntohs(x2) << std::endl;
	//std::cout << std::hex << y2 << ntohs(y2) << std::endl;

	////�߸��� ��뿹

	//std::cout << std::endl;
	//std::cout << "�߸��� ��� ��" << std::endl;


	IsLittleEndian();
	//if (IsLittleEndian())
	//	std::cout << "��Ʋ �����" << std::endl;
	//
	//if (IsBigEndian())
	//	std::cout << "�� �����" << std::endl;
	
	WSACleanup();
	system("pause");
}

/*��Ʋ�����*/
BOOL IsLittleEndian() {
	u_short test = 0x4321;
	u_short result;
	
	SOCKET netsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKET hostsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);



//	result = ntohs(test);
	/*if (WSANtohs(netsock, test, &result) == 0)
		std::cout << "����" << std::endl;
*/
	if(WSAHtons(netsock,test,&result)!=0)
		std::cout << "����" << std::endl;


	std::cout <<std::hex<< test << std::endl;
	std::cout <<std::hex<< result << std::endl;

	if (test != result)
		return TRUE;

	return FALSE;
}

/*�򿣵��*/
BOOL IsBigEndian() {
	u_short test = 0x4321;
	u_short result = 0x0;
	result = htons(test);
		
	if (test == result)
		return TRUE;

	return FALSE;
}