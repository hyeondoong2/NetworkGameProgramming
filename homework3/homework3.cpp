#include "Common.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// 윈속 초기화
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
		std::cout << "ip 주소 : "
			<< inet_ntoa(*(in_addr*)hostptr->h_addr_list[i])
			<< std::endl;
	}

	for (int i = 0; hostptr->h_aliases[i] != NULL; ++i) {
		std::cout << "별명 " << i + 1 << " : " << hostptr->h_aliases[i] << std::endl;
	}

	// 윈속 종료
	WSACleanup();
	return 0;
}