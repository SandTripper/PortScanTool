#pragma once


class Scanner
{
public:
	Scanner();
	~Scanner();

	//����ָ���˿��Ƿ���
	static void  Scanner::PortOpen(CString IP, int port, int* val, int* stopit);

};