#include<iostream>
#include<Windows.h>
#define MAXCNT 100000000

int g_count = 0;
CRITICAL_SECTION cs;

DWORD WINAPI MyThread1(LPVOID);
DWORD WINAPI MyThread2(LPVOID);



int main() {
	std::cout << "main진입" << std::endl;
	//임계 영역 초기화
	InitializeCriticalSection(&cs);

	//스레드 두개 생성
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, MyThread1, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, MyThread2, NULL, 0, NULL);

	//스레드 두개 종료대기
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	//임계 영역삭제
	DeleteCriticalSection(&cs);

	std::cout << "값:" << g_count << std::endl;

	system("pause");
	return 0;
}

DWORD WINAPI MyThread1(LPVOID arg) {
	std::cout << "1번쓰레드진입" << std::endl;
	for (int i = 0; i < MAXCNT; ++i) {
		EnterCriticalSection(&cs);
		g_count += 2;
		LeaveCriticalSection(&cs);
	}

	return 0;
}

DWORD WINAPI MyThread2(LPVOID arg) {
	std::cout << "2번쓰레드진입" << std::endl;

	for (int i = 0; i < MAXCNT; ++i) {
		EnterCriticalSection(&cs);
		g_count -= 2;
		LeaveCriticalSection(&cs);
	}

	return 0;
}
