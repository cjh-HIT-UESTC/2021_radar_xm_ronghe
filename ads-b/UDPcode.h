#pragma once
#pragma warning(disable:4996)
#include<winsock2.h>
#include<windows.h>
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>


sockaddr_in serverAddr, remoteAddr, clientAddr;//����һ�ֽṹ�� ����ṹ�������������������ݻ��߷������ݵĵ�ַ����Ϣ�ģ��˿ڡ�ip�ȣ�
// �˿ں�

// �½� socket ��Ϣ
int iUDP;

void sleepUDP(int iSleep)
{
	Sleep(iSleep);//��windows�����Ѻ���Ϊ��λ����Linux������Ϊ��λ
}

void openUDP(const char* acIpAddr, int iServerPort, int iClientPort)
{
	// Winsows ���� socket
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(1, 1), &wsadata) == SOCKET_ERROR)
	{
		MessageBox(NULL, TEXT("UDP���� socket ʧ��"), TEXT("��ʾ"), MB_OK);
		WSACleanup();
		exit(0);
	}
	// �½� socket
	if ((iUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		MessageBox(NULL, TEXT("UDP�½� socket ʧ��"), TEXT("��ʾ"), MB_OK);
		WSACleanup();
		exit(0);
	}
	// ����
	memset(&serverAddr, 0, sizeof(serverAddr));
	memset(&clientAddr, 0, sizeof(clientAddr));
	// ����Э�� IP ��ַ�� Port
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(iServerPort);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(iClientPort);
	clientAddr.sin_addr.s_addr = inet_addr(acIpAddr);
	 //�󶨶˿ڣ������˿�
	if (::bind(iUDP, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
	{
		MessageBox(NULL, TEXT("UDP�󶨶˿�ʧ��"), TEXT("��ʾ"), MB_OK);
		closesocket(iUDP);
		WSACleanup();
		exit(0);
	}
}

void closeUDP(void)
{
	// Winsows �ر� socket
	closesocket(iUDP);
	//WSACleanup();
}