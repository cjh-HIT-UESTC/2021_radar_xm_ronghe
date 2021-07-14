#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <process.h>  
#include<iostream>
using namespace std;
#pragma warning(disable:4996)
#include<winsock2.h>
#include<windows.h>
#pragma comment(lib, "ws2_32.lib")
#include<stdint.h>
//头文件
#include"udpcode.h"
#include"ADSB1.h"//Data1
#include"gdgps2.h"//Data2
#include"hj3.h"//Data3
#include"hw4.h"//Data4
#include"dj5.h"//Data5
#include"constnum.h"
#include"structtothread.h"//Datathread

extern int iUDP;
//定义一些循环标记
int closethread = 0;//关闭线程2的标记
int udpget1dex = 0;
int udpget2dex = 0;
int udpget3dex = 0;
int udpget4dex = 0;
int udpget5dex = 0;
int udpget1overflow = 0;
int udpget2overflow = 0;
int udpget3overflow = 0;
int udpget4overflow = 0;
int udpget5overflow = 0;

Data1 udpget1[SIZEA];//存放所有未经处理的数据
Data2 udpget2[SIZEA];//存放所有未经处理的数据
Data3 udpget3[SIZEA];//存放所有未经处理的数据
Data4 udpget4[SIZEA];//存放所有未经处理的数据
Data5 udpget5[SIZEA];//存放所有未经处理的数据

//线程1函数
DWORD WINAPI ThreadOne(Ui::udpgetClass lpParameter) {
	//取出传入的数组数据
	Ui::udpgetClass ui = lpParameter;

	typedef struct sockaddr_in SockAddrIn;
	SockAddrIn  remoteAddr;//用来处理网络通信的地址 结构体 描述接受数据或者发送数据的地址等信息的（端口、ip等）

	int iAddrSize = sizeof(remoteAddr);//得到sockaddr_in结构体的大小

	char acRecvStr[iSize]; //每次接收数据的缓存区

	//定义超时时间
	struct timeval timeout;
	fd_set fdRead;//用于超时管理
	timeout.tv_sec = 360;//单位为： 秒
	timeout.tv_usec = 0;//单位为： 豪秒

	while (1) {
		//超时设置
		FD_ZERO(&fdRead);
		FD_SET(iUDP, &fdRead);
		int ret = select(0, &fdRead, NULL, NULL, &timeout);
		//超时
		if (ret == 0) {
			MessageBox(NULL, TEXT("线程1超时退出"), TEXT("提示"), MB_OK);
			break;
		}

		// 接收数据
		//判断是否接收成功
		if ((recvfrom(iUDP, acRecvStr, iSize, 0, (struct sockaddr*)&remoteAddr, &iAddrSize) != -1)) {
			//判断接收到的数据是哪个端口的数据
			int cjh = 0; 
			if (ntohs(remoteAddr.sin_port) == iClientPort[cjh]) {
				if (type[cjh] == 1) {
					if (udpget1dex >= SIZEA) {
						udpget1dex = udpget1dex % SIZEA;
						udpget1overflow = 1;
					}
					memcpy(&udpget1[udpget1dex], acRecvStr, sizeof(Data1));//将接收到的数据全部存到udpget里面
					++udpget1dex;
				}
				else if (type[cjh] == 2) {
					if (udpget2dex >= SIZEA) {
						udpget2dex = udpget2dex % SIZEA;
						udpget2overflow = 1;
					}
					memcpy(&udpget2[udpget2dex], acRecvStr, sizeof(Data2));//将接收到的数据全部存到udpget里面
					++udpget2dex;
				}
				else if (type[cjh] == 3) {
					if (udpget3dex >= SIZEA) {
						udpget3dex = udpget3dex % SIZEA;
						udpget3overflow = 1;
					}
					memcpy(&udpget3[udpget3dex], acRecvStr, sizeof(Data3));//将接收到的数据全部存到udpget里面
					++udpget3dex;
				}
				else if (type[cjh] == 4) {
					if (udpget4dex >= SIZEA) {
						udpget4dex = udpget4dex % SIZEA;
						udpget4overflow = 1;
					}
					memcpy(&udpget4[udpget4dex], acRecvStr, sizeof(Data4));//将接收到的数据全部存到udpget里面
					++udpget4dex;
				}
				else if (type[cjh] == 5) {
					if (udpget5dex >= SIZEA) {
						udpget5dex = udpget5dex % SIZEA;
						udpget5overflow = 1;
					}
					memcpy(&udpget5[udpget5dex], acRecvStr, sizeof(Data5));//将接收到的数据全部存到udpget里面
					++udpget5dex;
				}
			}
			//if (udpget3dex == 1) {
			//	MessageBox(NULL, TEXT("开始接收数据！"), TEXT("提示"), MB_OK);
			//}
		}
	}
	Sleep(3000);//停止3秒，确保线程2有足够时间处理好
	closethread = 1;//告诉线程2可以退出了

	_endthread();
	return 0;
}