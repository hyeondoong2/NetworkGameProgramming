#include "Common.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	const char* DomainName = argv[1];
	struct hostent* hostptr = gethostbyname(DomainName); 

	if (hostptr == NULL) {
		err_display("gethostbyname()");
		return false;
	}
	if (hostptr->h_addrtype != AF_INET)
		return false;

	for (int i = 0; hostptr->h_addr_list[i] != NULL; ++i) {
		std::cout << "ip �ּ� : "
			<< inet_ntoa(*(in_addr*)hostptr->h_addr_list[i])
			<< std::endl;
	}

	for (int i = 0; hostptr->h_aliases[i] != NULL; ++i) {
		std::cout << "���� " << i + 1 << " : " << hostptr->h_aliases[i] << std::endl;
	}

	// ���� ����
	WSACleanup();
	return 0;
}