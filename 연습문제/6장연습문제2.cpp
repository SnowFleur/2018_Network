/*
ExThread3 ������ �����Ͽ�,WaitForSingleObject()�Լ��� �� ��° ���ڿ� ������ Ÿ�Ӿƿ� ���� ����Ͻÿ�.

num ������ �ʱ갪�� ����� ũ�� �ϸ� MyThread()�Լ��� �������� ���� ���¿��� WaitForSingleObject()�Լ��� Ÿ�Ӿƿ� ������ �����Ѵ�.

�׷��� ȭ�鿡 '*'�� ����ϰ� �ٽ� WatiForSingleObject()�Լ��� ȣ���ϵ��� �Ͻÿ�

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

