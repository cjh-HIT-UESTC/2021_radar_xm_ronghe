#pragma once

extern int N;
typedef struct {
	//传给线程的参数包结构体（端口号，协议类型）
	int* iClientPort;
	int* type;
	QString PathName;
}Datathread;