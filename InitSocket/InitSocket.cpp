#include "Common.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(0x0202, &wsa) != 0)
		return 1;
	printf("[알림] 윈속 초기화 성공\n");

	std::cout << (int)LOBYTE(wsa.wVersion) << "." << (int)HIBYTE(wsa.wVersion) << std::endl
		<< (int)LOBYTE(wsa.wHighVersion) << "." << (int)HIBYTE(wsa.wHighVersion) << std::endl
		<< wsa.szDescription << std::endl << wsa.szSystemStatus << std::endl;

	// 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	printf("[알림] 소켓 생성 성공\n");

	// 소켓 닫기
	closesocket(sock);


	// 윈속 종료
	WSACleanup();
	return 0;
}