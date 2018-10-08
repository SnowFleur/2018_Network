/*
ExThread1������ �����Ͽ�, Point3D ����ü�� malloc() �Լ� �Ǵ� new �����ڷ� ��������
������ �����忡 �����Ͻÿ�, MyThread() �Լ������� ���޵� Point3D ����ü�� ����� ��
free()�Լ� �Ǵ� delete�����ڷ� �޸𸮸� �����ؾ��Ѵ�.
*/

#include<iostream>
#include<Windows.h>

struct Point3D {
public:
	int x, y, z;
	~Point3D() {
		std::cout << "Delete" << std::endl;
	}

};

DWORD WINAPI MyThread(LPVOID);
int main() {
	Point3D* point3d = NULL;
	point3d = new Point3D{ 10,20,30 };

	//ù��° Thread
	HANDLE Thread = CreateThread(NULL, 0, MyThread, point3d, 0, NULL);

	//1�����
  // SetThreadPriority(Thread, THREAD_PRIORITY_TIME_CRITICAL);
	if (Thread == NULL)
		std::cout << "CreateThread error" << std::endl;
	//2�����
	WaitForSingleObject(Thread, INFINITE);
	point3d = new Point3D{ 20,30,40 };
	//�ι�° Thread
	Thread = CreateThread(NULL, 0, MyThread, point3d, 0, NULL);

	if (Thread == NULL)
		std::cout << "CreateThread error" << std::endl;
	system("pause");
	return 0;
}

DWORD WINAPI MyThread(LPVOID arg) {
	Point3D* point3d = reinterpret_cast<Point3D*>(arg);
	std::cout << "Thread ID:" << GetCurrentThreadId()
		      << " Value:" << point3d->x << "," << point3d->y << "," << point3d->z << std::endl;
	delete(point3d);
	return 0;
}

/*
�켱���������� ���ϰų� wait�Լ��� ������� ������ ����߰��� CPU�� �����ٸ��� �ϱ⋚���� ���� �̻��ϰ� ���´�

������ ù��° ����� ó�� �������� �켱������ ���� �ְ�� ���´�
���: �κ�������� �켱������ ���ϳ����شٰ� 1���� �����°� �ƴ϶�°� �� �� �־���

������ �ι��� ����� ó�� �����尡 ���������� ��ٸ���.
���:������� wait�Լ��� ��ġ�� ��� ������ �� ������ �����غ��� �ҰŰ��� handle�� �Ҿ������ ���߱� ����Ű���.


*/