/*
ExThread3 예제를 수정하여,WaitForSingleObject()함수의 두 번째 인자에 적당한 타임아웃 값을 사용하시오.

num 변수의 초깃값을 충분히 크게 하면 MyThread()함수가 종류하지 않은 상태에서 WaitForSingleObject()함수가 타임아웃 때문에 리턴한다.

그러면 화면에 '*'를 출력하고 다시 WatiForSingleObject()함수를 호출하도록 하시오

*/
#include<iostream>
#include<Windows.h>


DWORD sum = 0;
DWORD WINAPI MyThread(LPVOID);

int main() {

	int num = 9999999;
	DWORD retval = 0;
	HANDLE hThread = CreateThread(NULL, 0, MyThread, reinterpret_cast<LPVOID>(num), CREATE_SUSPENDED, NULL);

	if (hThread == NULL)
		return 1;

	std::cout << "스레드 실행전 계산결과" << sum << std::endl;

	ResumeThread(hThread);

	while (WAIT_TIMEOUT== WaitForSingleObject(hThread, 1) ){
		std::cout << "*" << std::endl;
	
	}



	/*retval=WaitForSingleObject(hThread,1);

	if (retval == WAIT_TIMEOUT) {
		std::cout << "*" << std::endl;
	}
*/

	std::cout << "스레드 실행후 계산결과" << sum << std::endl;


	system("pause");
	return 0;
}
DWORD WINAPI MyThread(LPVOID arg) {
	int num = reinterpret_cast<int>(arg);

	for (int i = 1; i <= num; i++) 
		sum += i;

	return 0;
}

