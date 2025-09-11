#include "Common.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(0x0202, &wsa) != 0)
		return 1;
	printf("[알림] 윈속 초기화 성공\n");

	std::cout << "wVersion : " << wsa.wVersion 
		<< ", wHighVersion : " << wsa.wHighVersion
		<< ", szDescription : " << wsa.szDescription 
		<< ", szSystemStatus : " << wsa.szSystemStatus << '\n';

	// 윈속 종료
	WSACleanup();
	return 0;
}