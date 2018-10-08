/*
ExThread1에제를 수정하여, Point3D 구조체를 malloc() 함수 또는 new 연산자로 동적으로
생성해 스레드에 전달하시오, MyThread() 함수에서는 전달된 Point3D 구조체를 사용한 후
free()함수 또는 delete연산자로 메모리르 해제해야한다.
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

	//첫번째 Thread
	HANDLE Thread = CreateThread(NULL, 0, MyThread, point3d, 0, NULL);

	//1번방법
  // SetThreadPriority(Thread, THREAD_PRIORITY_TIME_CRITICAL);
	if (Thread == NULL)
		std::cout << "CreateThread error" << std::endl;
	//2번방법
	WaitForSingleObject(Thread, INFINITE);
	point3d = new Point3D{ 20,30,40 };
	//두번째 Thread
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
우선순위설정을 안하거나 wait함수를 사용하지 않으면 출력중간에 CPU가 스케줄링을 하기떄문에 값이 이상하게 나온다

생각한 첫번째 방법은 처음 스레드의 우선순위를 제일 최고로 놓는다
결과: 부분정상출력 우선순위를 제일높게준다고 1등을 끝나는건 아니라는걸 알 수 있었음

생각한 두번쨰 방법은 처음 스레드가 끝날때까지 기다린다.
결과:정상출력 wait함수의 위치를 어디에 놓으면 더 좋을시 생각해봐야 할거같고 handle을 잃어버리면 멈추기 힘들거같다.


*/