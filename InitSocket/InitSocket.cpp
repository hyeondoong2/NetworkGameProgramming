#include "Common.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(0x0202, &wsa) != 0)
		return 1;
	printf("[�˸�] ���� �ʱ�ȭ ����\n");

	std::cout << "wVersion : " << wsa.wVersion 
		<< ", wHighVersion : " << wsa.wHighVersion
		<< ", szDescription : " << wsa.szDescription 
		<< ", szSystemStatus : " << wsa.szSystemStatus << '\n';

	// ���� ����
	WSACleanup();
	return 0;
}