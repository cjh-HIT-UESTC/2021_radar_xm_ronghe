#pragma once
#include<windows.h>
void sleepUDP(int iSleep)
{
	Sleep(iSleep);//在windows下是已毫秒为单位，而Linux是以秒为单位
}

void closeUDP(int iUDP)
{
	// Winsows 关闭 socket
	closesocket(iUDP);
	WSACleanup();
}