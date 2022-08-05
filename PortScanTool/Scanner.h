#pragma once


class Scanner
{
public:
	Scanner();
	~Scanner();

	//返回指定端口是否开启
	static void  Scanner::PortOpen(CString IP, int port, int* val, int* stopit);

};