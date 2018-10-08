#include<iostream>
#include<Windows.h>
#define MAXCNT 100000000

int g_count = 0;
CRITICAL_SECTION cs;

DWORD WINAPI MyThread1(LPVOID);
DWORD WINAPI MyThread2(LPVOID);



int main() {
	std::cout << "main����" << std::endl;
	//�Ӱ� ���� �ʱ�ȭ
	InitializeCriticalSection(&cs);

	//������ �ΰ� ����
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, MyThread1, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, MyThread2, NULL, 0, NULL);

	//������ �ΰ� ������
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	//�Ӱ� ��������
	DeleteCriticalSection(&cs);

	std::cout << "��:" << g_count << std::endl;

	system("pause");
	return 0;
}

DWORD WINAPI MyThread1(LPVOID arg) {
	std::cout << "1������������" << std::endl;
	for (int i = 0; i < MAXCNT; ++i) {
		EnterCriticalSection(&cs);
		g_count += 2;
		LeaveCriticalSection(&cs);
	}

	return 0;
}

DWORD WINAPI MyThread2(LPVOID arg) {
	std::cout << "2������������" << std::endl;

	for (int i = 0; i < MAXCNT; ++i) {
		EnterCriticalSection(&cs);
		g_count -= 2;
		LeaveCriticalSection(&cs);
	}

	return 0;
}
