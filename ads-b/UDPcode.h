#pragma once
#pragma warning(disable:4996)
#include<winsock2.h>
#include<windows.h>
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>


sockaddr_in serverAddr, remoteAddr, clientAddr;//定义一种结构体 这个结构体是用来描述接受数据或者发送数据的地址等信息的（端口、ip等）
// 端口号

// 新建 socket 信息
int iUDP;

void sleepUDP(int iSleep)
{
	Sleep(iSleep);//在windows下是已毫秒为单位，而Linux是以秒为单位
}

void openUDP(const char* acIpAddr, int iServerPort, int iClientPort)
{
	// Winsows 启用 socket
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(1, 1), &wsadata) == SOCKET_ERROR)
	{
		MessageBox(NULL, TEXT("UDP启用 socket 失败"), TEXT("提示"), MB_OK);
		WSACleanup();
		exit(0);
	}
	// 新建 socket
	if ((iUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		MessageBox(NULL, TEXT("UDP新建 socket 失败"), TEXT("提示"), MB_OK);
		WSACleanup();
		exit(0);
	}
	// 清零
	memset(&serverAddr, 0, sizeof(serverAddr));
	memset(&clientAddr, 0, sizeof(clientAddr));
	// 设置协议 IP 地址及 Port
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(iServerPort);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(iClientPort);
	clientAddr.sin_addr.s_addr = inet_addr(acIpAddr);
	 //绑定端口，监听端口
	if (::bind(iUDP, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
	{
		MessageBox(NULL, TEXT("UDP绑定端口失败"), TEXT("提示"), MB_OK);
		closesocket(iUDP);
		WSACleanup();
		exit(0);
	}
}

void closeUDP(void)
{
	// Winsows 关闭 socket
	closesocket(iUDP);
	//WSACleanup();
}