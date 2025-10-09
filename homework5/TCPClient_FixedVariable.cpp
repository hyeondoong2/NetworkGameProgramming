#include "Common.h"
#include <iostream>
#include <fstream>

char* SERVERIP = (char*)"127.0.0.1";
#define SERVERPORT 9000
#define BUFSIZE    1024

int main(int argc, char* argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
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

	// 데이터 통신에 사용할 변수
	const char* FileName{};
	if (argc > 1) FileName = argv[1];

	// 파일 이름 길이
	int FileNameLen = strlen(FileName);

	// 파일 읽어오기
	std::ifstream in{ FileName, std::ios::binary };
	if (!in) throw 0;

	//파일이 제대로 열렸다면 크기 구하기
	in.seekg(0, std::ios::end);
	int FileSize = in.tellg();
	in.seekg(0, std::ios::beg);
	printf("파일 크기: %ld bytes\n", FileSize);

	// 파일 이름 길이 (고정 길이)
	retval = send(sock, (char*)&FileNameLen, sizeof(int), 0);
	if (retval == SOCKET_ERROR) err_display("send()");

	// 이름 (가변 길이)
	retval = send(sock, FileName, FileNameLen, 0);
	if (retval == SOCKET_ERROR) err_display("send()");

	// 데이터 크기
	retval = send(sock, (char*)&FileSize, sizeof(int), 0);
	if (retval == SOCKET_ERROR) err_display("send()");

	char buf[BUFSIZE + 1];
	int alreadySendSize = 0;
	int sendSize = BUFSIZE;

	//데이터
	while (1)
	{
		if (alreadySendSize > (FileSize - BUFSIZE))
			sendSize = FileSize - alreadySendSize;

		in.read(buf, sendSize);

		// 데이터 보내기(가변 길이)
		retval = send(sock, buf, sendSize, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}

		alreadySendSize += sendSize;
		if (alreadySendSize >= FileSize) break;
	}


	// 소켓 닫기
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}