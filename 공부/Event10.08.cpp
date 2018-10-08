#include<Windows.h>
#include<iostream>
#define BUFSIZE 10


HANDLE hReadEvent;
HANDLE hWriteEvent;
int buf[BUFSIZE];

DWORD WINAPI WriteThread(LPVOID);
DWORD WINAPI ReadThread(LPVOID);



int main() {

	
	//자동 리셋 이벤트 두개 생성(각각 비신호,신호 상태)

	//자동,비신호
	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hWriteEvent == NULL)
		return 1;
	//자동,신호
	hReadEvent = CreateEvent(NULL, FALSE, TRUE, NULL);

	if (hReadEvent == NULL)
		return 1;

	//스레드 생성 3개
	HANDLE hThread[3];
	hThread[0] = CreateThread(NULL, 0, WriteThread, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, ReadThread, NULL, 0, NULL);
	hThread[2] = CreateThread(NULL, 0, ReadThread, NULL, 0, NULL);

	//스레드 세개 종료 대기

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	//이벤트제거
	CloseHandle(hWriteEvent);
	CloseHandle(hReadEvent);

	return 0;
}


DWORD WINAPI WriteThread(LPVOID arg) {
	DWORD retval;
	for (int k = 1; k <= 500; ++k) {
		//읽기 완료 대기
		
		//쓰레드 종료 기다리는 함수 
		//첫번째인자: 종료를 기다릴 대상 스레드
		//두번째인자: 대기시간 INFINIT==끝날때까지 무한대기
		retval = WaitForSingleObject(hReadEvent, INFINITE);
		
		if (retval != WAIT_OBJECT_0)
			break;
		//공유 버퍼에 데이터 저장
		for (int i = 0; i < BUFSIZE; ++i) {
			buf[i] = k;
		}
		//쓰기 완료 알림
		//비신호상태이벤트를 신호상태이벤트로 바꾸는 함수
		//쓰기 이벤트를 신호상태로 만들어 두 읽기 스레드 중 하나를 대기 상태에서 깨운다.
		//꺠운뒤 자신은 비신호가 됨 (자동리셋)
		SetEvent(hWriteEvent);

	}
	return 0;

}
DWORD WINAPI ReadThread(LPVOID arg) {
	DWORD retval;

	while (1) {
		//쓰기 완료 대기
		//쓰기 이벤트가 활성화 될때까지 기다린다.
		retval = WaitForSingleObject(hWriteEvent, INFINITE);

		//0번쓰레드의 작업이 끝난게 아니면 멈춘다.(첫번째스레드)
		if (retval != WAIT_OBJECT_0)
			break;

		//읽은데이터 출력
		std::cout << "Thread" << GetCurrentThreadId() << "  ";
		
		for (int i = 0; i < BUFSIZE; ++i) {
			std::cout << buf[i]<<"    ";
		}
		std::cout << std::endl;

		//버퍼초기화
		ZeroMemory(buf, sizeof(buf));

		//읽기 완료 알림
		//ReadEvent를 신호상태로 바꾸고 자기자신은 비신호상태로 바꾼다(자동리셋)
		SetEvent(hReadEvent);

	}


	return 0;
}