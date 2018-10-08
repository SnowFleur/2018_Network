/*
ExThread3 예제를 수정하여,WaitForSingleObject()함수의 두 번째 인자에 적당한 타임아웃 값을 사용하시오.

num 변수의 초깃값을 충분히 크게 하면 MyThread()함수가 종류하지 않은 상태에서 WaitForSingleObject()함수가 타임아웃 때문에 리턴한다.

그러면 화면에 '*'를 출력하고 다시 WatiForSingleObject()함수를 호출하도록 하시오

*/
#include<iostream>
#include<Windows.h>


int sum = 0;
DWORD WINAPI MyThread(LPVOID);

int main() {
	int num = 100;
	
	int* iptr = NULL;

	iptr = reinterpret_cast<int*>(num);



	printf("%d\n",num);
	printf("%d\n",iptr);

	std::cout << &iptr << std::endl;

//	HANDLE hTread = CreateThread(NULL, 0, MyThread, reinterpret_cast<LPVOID>(num), 0, NULL);


	system("pause");
	return 0;
}
DWORD WINAPI MyThread(LPVOID arg) {

}

