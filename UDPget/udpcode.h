#pragma once
#include<windows.h>
void sleepUDP(int iSleep)
{
	Sleep(iSleep);//��windows�����Ѻ���Ϊ��λ����Linux������Ϊ��λ
}

void closeUDP(int iUDP)
{
	// Winsows �ر� socket
	closesocket(iUDP);
	WSACleanup();
}