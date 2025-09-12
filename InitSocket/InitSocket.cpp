#include "Common.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(0x0202, &wsa) != 0)
		return 1;
	printf("[�˸�] ���� �ʱ�ȭ ����\n");

	std::cout << (int)LOBYTE(wsa.wVersion) << "." << (int)HIBYTE(wsa.wVersion) << std::endl
		<< (int)LOBYTE(wsa.wHighVersion) << "." << (int)HIBYTE(wsa.wHighVersion) << std::endl
		<< wsa.szDescription << std::endl << wsa.szSystemStatus << std::endl;

	// ���� ����
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	printf("[�˸�] ���� ���� ����\n");

	// ���� �ݱ�
	closesocket(sock);


	// ���� ����
	WSACleanup();
	return 0;
}