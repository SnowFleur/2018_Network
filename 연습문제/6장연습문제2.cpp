/*
ExThread3 ������ �����Ͽ�,WaitForSingleObject()�Լ��� �� ��° ���ڿ� ������ Ÿ�Ӿƿ� ���� ����Ͻÿ�.

num ������ �ʱ갪�� ����� ũ�� �ϸ� MyThread()�Լ��� �������� ���� ���¿��� WaitForSingleObject()�Լ��� Ÿ�Ӿƿ� ������ �����Ѵ�.

�׷��� ȭ�鿡 '*'�� ����ϰ� �ٽ� WatiForSingleObject()�Լ��� ȣ���ϵ��� �Ͻÿ�

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

	std::cout << "������ ������ �����" << sum << std::endl;

	ResumeThread(hThread);

	while (WAIT_TIMEOUT== WaitForSingleObject(hThread, 1) ){
		std::cout << "*" << std::endl;
	
	}



	/*retval=WaitForSingleObject(hThread,1);

	if (retval == WAIT_TIMEOUT) {
		std::cout << "*" << std::endl;
	}
*/

	std::cout << "������ ������ �����" << sum << std::endl;


	system("pause");
	return 0;
}
DWORD WINAPI MyThread(LPVOID arg) {
	int num = reinterpret_cast<int>(arg);

	for (int i = 1; i <= num; i++) 
		sum += i;

	return 0;
}

