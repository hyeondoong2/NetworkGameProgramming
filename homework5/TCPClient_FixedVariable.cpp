#include "Common.h"
#include <iostream>
#include <fstream>

char* SERVERIP = (char*)"127.0.0.1";
#define SERVERPORT 9000
#define BUFSIZE    1024

int main(int argc, char* argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// ������ ��ſ� ����� ����
	const char* FileName{};
	if (argc > 1) FileName = argv[1];

	// ���� �̸� ����
	int FileNameLen = strlen(FileName);

	// ���� �о����
	std::ifstream in{ FileName, std::ios::binary };
	if (!in) throw 0;

	//������ ����� ���ȴٸ� ũ�� ���ϱ�
	in.seekg(0, std::ios::end);
	int FileSize = in.tellg();
	in.seekg(0, std::ios::beg);
	printf("���� ũ��: %ld bytes\n", FileSize);

	// ���� �̸� ���� (���� ����)
	retval = send(sock, (char*)&FileNameLen, sizeof(int), 0);
	if (retval == SOCKET_ERROR) err_display("send()");

	// �̸� (���� ����)
	retval = send(sock, FileName, FileNameLen, 0);
	if (retval == SOCKET_ERROR) err_display("send()");

	// ������ ũ��
	retval = send(sock, (char*)&FileSize, sizeof(int), 0);
	if (retval == SOCKET_ERROR) err_display("send()");

	char buf[BUFSIZE + 1];
	int alreadySendSize = 0;
	int sendSize = BUFSIZE;

	//������
	while (1)
	{
		if (alreadySendSize > (FileSize - BUFSIZE))
			sendSize = FileSize - alreadySendSize;

		in.read(buf, sendSize);

		// ������ ������(���� ����)
		retval = send(sock, buf, sendSize, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}

		alreadySendSize += sendSize;
		if (alreadySendSize >= FileSize) break;
	}


	// ���� �ݱ�
	closesocket(sock);

	// ���� ����
	WSACleanup();
	return 0;
}