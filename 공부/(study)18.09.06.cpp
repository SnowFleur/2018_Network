#pragma comment(lib,"ws2_32")
#include<iostream>
#include<WinSock2.h>

struct Flags {
	union {
		struct {
			unsigned short a:3;
			unsigned short b:4;
			unsigned short c:7;
			unsigned short d:2;


		};
		unsigned short e;

	};

};

int main() {

	

	int c = 2;

   #define MAKEWORD(a, b)      (    (WORD)     (    (   (BYTE)   (   (   (DWORD_PTR)    (a)   ) & 0xff  )    ) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8    )    )

	std::cout << (DWORD_PTR)c << std::endl;

	
	system("pause");

}