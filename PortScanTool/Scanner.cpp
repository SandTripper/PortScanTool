#include "pch.h"

#include "Scanner.h"

//#include <atlstr.h>
//#include <winsock.h>
#include <thread>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

Scanner::Scanner()
{
}

Scanner::~Scanner()
{
	WSACleanup();
}



void  Scanner::PortOpen(CString IP, int port,int *val,int *stopit)
{

	AfxSocketInit();
	WORD w_req = MAKEWORD(2, 2);//�汾��
	WSADATA wsadata;
	WSAStartup(w_req, &wsadata);
	struct sockaddr_in mysock;
	memset(&mysock, 0, sizeof(mysock));
	mysock.sin_family = AF_INET;  //���õ�ַ����
	mysock.sin_port = htons(port);  //���ö˿�
	//inet_pton(AF_INET,(char*)(LPCTSTR)IP, (void*)&mysock.sin_addr.s_addr);  //���õ�ַ
	char cip[30];
	wcstombs(cip, IP, IP.GetLength() * 2);
	mysock.sin_addr.s_addr = inet_addr(cip);
	SOCKET m_server = socket(AF_INET, SOCK_STREAM, 0);
	int con = connect(m_server, (SOCKADDR*)&mysock, sizeof(mysock))!=-1;
	closesocket(m_server);
	if ((*stopit) != 1)
		* val = con;
}


