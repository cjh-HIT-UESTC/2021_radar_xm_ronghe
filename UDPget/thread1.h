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
//ͷ�ļ�
#include"udpcode.h"
#include"ADSB1.h"//Data1
#include"gdgps2.h"//Data2
#include"hj3.h"//Data3
#include"hw4.h"//Data4
#include"dj5.h"//Data5
#include"constnum.h"
#include"structtothread.h"//Datathread

extern int iUDP;
//����һЩѭ�����
int closethread = 0;//�ر��߳�2�ı��
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

Data1 udpget1[SIZEA];//�������δ�����������
Data2 udpget2[SIZEA];//�������δ�����������
Data3 udpget3[SIZEA];//�������δ�����������
Data4 udpget4[SIZEA];//�������δ�����������
Data5 udpget5[SIZEA];//�������δ�����������

//�߳�1����
DWORD WINAPI ThreadOne(Ui::udpgetClass lpParameter) {
	//ȡ���������������
	Ui::udpgetClass ui = lpParameter;

	typedef struct sockaddr_in SockAddrIn;
	SockAddrIn  remoteAddr;//������������ͨ�ŵĵ�ַ �ṹ�� �����������ݻ��߷������ݵĵ�ַ����Ϣ�ģ��˿ڡ�ip�ȣ�

	int iAddrSize = sizeof(remoteAddr);//�õ�sockaddr_in�ṹ��Ĵ�С

	char acRecvStr[iSize]; //ÿ�ν������ݵĻ�����

	//���峬ʱʱ��
	struct timeval timeout;
	fd_set fdRead;//���ڳ�ʱ����
	timeout.tv_sec = 360;//��λΪ�� ��
	timeout.tv_usec = 0;//��λΪ�� ����

	while (1) {
		//��ʱ����
		FD_ZERO(&fdRead);
		FD_SET(iUDP, &fdRead);
		int ret = select(0, &fdRead, NULL, NULL, &timeout);
		//��ʱ
		if (ret == 0) {
			MessageBox(NULL, TEXT("�߳�1��ʱ�˳�"), TEXT("��ʾ"), MB_OK);
			break;
		}

		// ��������
		//�ж��Ƿ���ճɹ�
		if ((recvfrom(iUDP, acRecvStr, iSize, 0, (struct sockaddr*)&remoteAddr, &iAddrSize) != -1)) {
			//�жϽ��յ����������ĸ��˿ڵ�����
			int cjh = 0; 
			if (ntohs(remoteAddr.sin_port) == iClientPort[cjh]) {
				if (type[cjh] == 1) {
					if (udpget1dex >= SIZEA) {
						udpget1dex = udpget1dex % SIZEA;
						udpget1overflow = 1;
					}
					memcpy(&udpget1[udpget1dex], acRecvStr, sizeof(Data1));//�����յ�������ȫ���浽udpget����
					++udpget1dex;
				}
				else if (type[cjh] == 2) {
					if (udpget2dex >= SIZEA) {
						udpget2dex = udpget2dex % SIZEA;
						udpget2overflow = 1;
					}
					memcpy(&udpget2[udpget2dex], acRecvStr, sizeof(Data2));//�����յ�������ȫ���浽udpget����
					++udpget2dex;
				}
				else if (type[cjh] == 3) {
					if (udpget3dex >= SIZEA) {
						udpget3dex = udpget3dex % SIZEA;
						udpget3overflow = 1;
					}
					memcpy(&udpget3[udpget3dex], acRecvStr, sizeof(Data3));//�����յ�������ȫ���浽udpget����
					++udpget3dex;
				}
				else if (type[cjh] == 4) {
					if (udpget4dex >= SIZEA) {
						udpget4dex = udpget4dex % SIZEA;
						udpget4overflow = 1;
					}
					memcpy(&udpget4[udpget4dex], acRecvStr, sizeof(Data4));//�����յ�������ȫ���浽udpget����
					++udpget4dex;
				}
				else if (type[cjh] == 5) {
					if (udpget5dex >= SIZEA) {
						udpget5dex = udpget5dex % SIZEA;
						udpget5overflow = 1;
					}
					memcpy(&udpget5[udpget5dex], acRecvStr, sizeof(Data5));//�����յ�������ȫ���浽udpget����
					++udpget5dex;
				}
			}
			//if (udpget3dex == 1) {
			//	MessageBox(NULL, TEXT("��ʼ�������ݣ�"), TEXT("��ʾ"), MB_OK);
			//}
		}
	}
	Sleep(3000);//ֹͣ3�룬ȷ���߳�2���㹻ʱ�䴦���
	closethread = 1;//�����߳�2�����˳���

	_endthread();
	return 0;
}