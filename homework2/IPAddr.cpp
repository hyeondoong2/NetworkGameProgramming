#include "Common.h"

int main(int argc, char* argv[])
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	const char* ipv4test = "147.46.114.70";
	printf("IPv4 �ּ�(��ȯ ��) = %s\n", ipv4test);

	struct in_addr ipv4num;
	inet_pton(AF_INET, ipv4test, &ipv4num);
	printf("IPv4 �ּ�(��ȯ ��) = %#x\n", ipv4num.s_addr);

	char ipv4str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &ipv4num, ipv4str, sizeof(ipv4str));
	printf("IPv4 �ּ�(�ٽ� ��ȯ ��) = %s\n", ipv4str);
	printf("\n");

	const char* ipv6test = "2001:0230:abcd:ffab:0023:eb00:ffff:1111";
	printf("Pv6 �ּ�(��ȯ ��) = %s\n", ipv6test);

	struct in6_addr ipv6num;
	inet_pton(AF_INET6, ipv6test, &ipv6num);
	printf("IPv6 �ּ�(��ȯ ��) = 0x");
	for (int i = 0; i < 16; i++)
		printf("%02x", ipv6num.s6_addr[i]);
	printf("\n");

	char ipv6str[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6, &ipv6num, ipv6str, sizeof(ipv6str));
	printf("IPv6 �ּ�(�ٽ� ��ȯ ��) = %s\n", ipv6str);

	WSACleanup();
	return 0;
}