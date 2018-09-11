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


	////호스트 바이트->네트워크 바이트
	//std::cout << "[호스트 바이트-> 네트워크 바이트]" << std::endl;

	//x2 = htons(x1);
	//std::cout << "0x" << std::hex << x1 << "---->" << "Ox" << std::hex << x2 << std::endl;
	//std::cout << "0x" << std::hex << y1 << "---->" << "Ox" << std::hex << y2 << htonl(y1) << std::endl;

	////네트워크 바이트 -> 호스트 바이트

	//std::cout << "[네트워크 바이트-> 호스트 바이트]" << std::endl;

	//std::cout << std::hex << x1 << ntohs(x2) << std::endl;
	//std::cout << std::hex << y2 << ntohs(y2) << std::endl;

	////잘못된 사용예

	//std::cout << std::endl;
	//std::cout << "잘못된 사용 예" << std::endl;


	IsLittleEndian();
	//if (IsLittleEndian())
	//	std::cout << "리틀 엔디안" << std::endl;
	//
	//if (IsBigEndian())
	//	std::cout << "빅 엔디안" << std::endl;
	
	WSACleanup();
	system("pause");
}

/*리틀엔디안*/
BOOL IsLittleEndian() {
	u_short test = 0x4321;
	u_short result;
	
	SOCKET netsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKET hostsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);



//	result = ntohs(test);
	/*if (WSANtohs(netsock, test, &result) == 0)
		std::cout << "오류" << std::endl;
*/
	if(WSAHtons(netsock,test,&result)!=0)
		std::cout << "오류" << std::endl;


	std::cout <<std::hex<< test << std::endl;
	std::cout <<std::hex<< result << std::endl;

	if (test != result)
		return TRUE;

	return FALSE;
}

/*빅엔디안*/
BOOL IsBigEndian() {
	u_short test = 0x4321;
	u_short result = 0x0;
	result = htons(test);
		
	if (test == result)
		return TRUE;

	return FALSE;
}