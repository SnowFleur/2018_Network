#include<Windows.h>
#include<iostream>
#define BUFSIZE 10


HANDLE hReadEvent;
HANDLE hWriteEvent;
int buf[BUFSIZE];

DWORD WINAPI WriteThread(LPVOID);
DWORD WINAPI ReadThread(LPVOID);



int main() {

	
	//�ڵ� ���� �̺�Ʈ �ΰ� ����(���� ���ȣ,��ȣ ����)

	//�ڵ�,���ȣ
	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hWriteEvent == NULL)
		return 1;
	//�ڵ�,��ȣ
	hReadEvent = CreateEvent(NULL, FALSE, TRUE, NULL);

	if (hReadEvent == NULL)
		return 1;

	//������ ���� 3��
	HANDLE hThread[3];
	hThread[0] = CreateThread(NULL, 0, WriteThread, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, ReadThread, NULL, 0, NULL);
	hThread[2] = CreateThread(NULL, 0, ReadThread, NULL, 0, NULL);

	//������ ���� ���� ���

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	//�̺�Ʈ����
	CloseHandle(hWriteEvent);
	CloseHandle(hReadEvent);

	return 0;
}


DWORD WINAPI WriteThread(LPVOID arg) {
	DWORD retval;
	for (int k = 1; k <= 500; ++k) {
		//�б� �Ϸ� ���
		
		//������ ���� ��ٸ��� �Լ� 
		//ù��°����: ���Ḧ ��ٸ� ��� ������
		//�ι�°����: ���ð� INFINIT==���������� ���Ѵ��
		retval = WaitForSingleObject(hReadEvent, INFINITE);
		
		if (retval != WAIT_OBJECT_0)
			break;
		//���� ���ۿ� ������ ����
		for (int i = 0; i < BUFSIZE; ++i) {
			buf[i] = k;
		}
		//���� �Ϸ� �˸�
		//���ȣ�����̺�Ʈ�� ��ȣ�����̺�Ʈ�� �ٲٴ� �Լ�
		//���� �̺�Ʈ�� ��ȣ���·� ����� �� �б� ������ �� �ϳ��� ��� ���¿��� �����.
		//�ƿ�� �ڽ��� ���ȣ�� �� (�ڵ�����)
		SetEvent(hWriteEvent);

	}
	return 0;

}
DWORD WINAPI ReadThread(LPVOID arg) {
	DWORD retval;

	while (1) {
		//���� �Ϸ� ���
		//���� �̺�Ʈ�� Ȱ��ȭ �ɶ����� ��ٸ���.
		retval = WaitForSingleObject(hWriteEvent, INFINITE);

		//0���������� �۾��� ������ �ƴϸ� �����.(ù��°������)
		if (retval != WAIT_OBJECT_0)
			break;

		//���������� ���
		std::cout << "Thread" << GetCurrentThreadId() << "  ";
		
		for (int i = 0; i < BUFSIZE; ++i) {
			std::cout << buf[i]<<"    ";
		}
		std::cout << std::endl;

		//�����ʱ�ȭ
		ZeroMemory(buf, sizeof(buf));

		//�б� �Ϸ� �˸�
		//ReadEvent�� ��ȣ���·� �ٲٰ� �ڱ��ڽ��� ���ȣ���·� �ٲ۴�(�ڵ�����)
		SetEvent(hReadEvent);

	}


	return 0;
}