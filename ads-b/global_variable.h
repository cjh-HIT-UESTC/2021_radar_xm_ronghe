#pragma once
#include <process.h>  
#include <string.h>  
#include<winsock2.h>
#include<windows.h>
#pragma comment(lib, "ws2_32.lib")
#include<iostream>
#include<unordered_map>
using namespace std;

/***ADS-B�˿����úͻ�������С����***/
//#define PORT 30003		//����Ҫ���ʵķ������˿ڳ���
#define SIZEA 300000 //��������С
#define iSize 1000	//ÿ�ν��յ����ݰ�����󳤶�

/****��������3������4�����ݽṹ(��������ƴ��)***/
typedef struct {
	char data[iSize];
}Data;

/***����TCP��ر���***/
int sock_client;//����ͻ����׽���
struct sockaddr_in server_addr;//�����ŷ������˵�ַ�Ľṹ����
int addr_len = sizeof(sockaddr_in);//��ַ�ṹ��������

/****�߳�1���յ�����Ϊ2��3��4������***/
Data threadonedata[SIZEA];//�߳�1�Ļ�����
int ithreadone = 0;//�����߳�1�������ı���
int overflow = 0;//�����ʶ��
int closethread = 0;//��ʾ�߳�2�ر�

/****�߳�2����ƴ���߳�1������������***/
int ithreadtwo = 0;//�����߳�2��������
unordered_map<char*, char* >connectdata;//��ϣ������ƴ��ʱ����������ICAO���ֹ�
int closethread2 = 0;//��ʾ�߳�3�ر�

/***�߳�3����δ���������Ҫ���͵�����***/
/****���δ���������Ҫ��������***/
Data rawsenddata[SIZEA];//���δ���������Ҫ��������
int irawsenddata = 0;//���Ƹû������ı���
int overflowrawsenddata = 0;//�����ʶ��
int ithreadthree = 0;//�����߳�3�������ı���

//����M����M��������֪���״����Ψһȷ�������������������MATLAB���У���
double* MxArray_M;

//��������һЩ����
char IP[30];
char acIpAddr[30];
int iClientPort;
int iServerPort;
int PORT;