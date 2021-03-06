// 넷겜플윈API.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "넷겜플윈API.h"

#define MAX_LOADSTRING 100



#define MAX_LOADSTRING 100
#define SERVERPORT 9000
#define SERVERIP "127.0.0.1"
#define BUFSIZE 140


using ifstrem = std::ifstream;
using ofstrem = std::ofstream;



#pragma pack(1)
struct FileInfor {
	char name[255];
	DWORD fileSize;
};
#pragma pack()

HWND hedit1;
HWND hprogress, hSendButton;
HANDLE hWrite;
HANDLE hDraw;
char buf[BUFSIZE+1];
int progressPos;
int retval;
int recvn(SOCKET s, char* buf, int len, int flag);


BOOL CALLBACK DigProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI FileDownLoadThread(LPVOID arg);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN serveraddr;
	//connet
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	retval = connect(client_sock, reinterpret_cast<SOCKADDR*>(&serveraddr), sizeof(serveraddr));

	if (retval == SOCKET_ERROR) {
		std::cout << "connet error" << std::endl;
	}
	hWrite = CreateEvent(NULL, TRUE, FALSE, NULL);
	hDraw = CreateEvent(NULL, TRUE, TRUE, NULL);
	CreateThread(NULL, 0, FileDownLoadThread, reinterpret_cast<LPVOID>(client_sock), 0, NULL);
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MY_DIALOG), NULL, DigProc);
}




BOOL CALLBACK DigProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	static int retval;
	switch (message) {
	case WM_INITDIALOG:
		SetTimer(hDlg, 0, 10, NULL);
		hedit1 = GetDlgItem(hDlg, IDC_EDIT1);
		hSendButton = GetDlgItem(hDlg, IDOK);
		hprogress = GetDlgItem(hDlg, IDC_PROGRESS1);
		SendMessage(hprogress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
		SendMessage(hprogress, PBM_SETPOS, progressPos, 0);
		return TRUE;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT1, buf, BUFSIZE + 1);
			EnableWindow(hSendButton, FALSE); // 보내기 버튼 비활성화
			retval = WaitForSingleObject(hDraw, INFINITE);
			SetEvent(hWrite);
			
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
	case WM_TIMER:
		SendMessage(hprogress, PBM_SETPOS, progressPos, 0);

		return TRUE;
	}
	return FALSE;
}

DWORD WINAPI FileDownLoadThread(LPVOID arg) {

	SOCKET client_socket = reinterpret_cast<SOCKET>(arg);
	int retval = 0;
	FileInfor file;
	ofstrem filedownload;
	int len;

	retval = WaitForSingleObject(hWrite, INFINITE);


	retval = send(client_socket, reinterpret_cast<char*>(&buf), sizeof(buf), 0);
	if (retval == SOCKET_ERROR) {
		std::cout << "send error" << std::endl;
	}

	while (1) {
		retval = recvn(client_socket, reinterpret_cast<char*>(&file), sizeof(file), 0);
		if (retval == SOCKET_ERROR) {
			std::cout << "recvn error" << std::endl;
		}

		filedownload.open(buf, std::ios::binary);
		int count = file.fileSize / BUFSIZE;
		int saveCount = count;

		std::cout << "받은크기" << file.fileSize << std::endl;

		//데이터 받기 (가변길이)
		while (count) {
			retval = recvn(client_socket, buf, BUFSIZE, 0);
			if (retval == SOCKET_ERROR) {
				std::cout << "recvn error" << std::endl;
				break;
			}
			else if (retval == 0)
				break;

			--count;

			progressPos = (saveCount - count) * 100 / saveCount;
			filedownload.write(buf, BUFSIZE);


		}
		//남은길이

		int remainData = file.fileSize - (saveCount*BUFSIZE);
		retval = recvn(client_socket, buf, remainData, 0);
		filedownload.write(buf, remainData);
		filedownload.close();
		ResetEvent(hDraw);


		EnableWindow(hSendButton, TRUE);
		break;
	}
	return 0;
}





int recvn(SOCKET s, char* buf, int len, int flag) {
	int received;
	char* ptr = buf;
	int left = len;
	static int i = 0;
	while (left > 0) {
		received = recv(s, ptr, left, flag);
		if (received == SOCKET_ERROR)
			return 0;

		else if (received == 0)
			break;

		left -= received;
		ptr += received;
	}

	return (len - left);
}
