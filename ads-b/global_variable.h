#pragma once
#include <process.h>  
#include <string.h>  
#include<winsock2.h>
#include<windows.h>
#pragma comment(lib, "ws2_32.lib")
#include<iostream>
#include<unordered_map>
using namespace std;

/***ADS-B端口设置和缓存区大小设置***/
//#define PORT 30003		//定义要访问的服务器端口常量
#define SIZEA 300000 //缓存区大小
#define iSize 1000	//每次接收的数据包的最大长度

/****定义类型3和类型4的数据结构(方便用于拼接)***/
typedef struct {
	char data[iSize];
}Data;

/***定义TCP相关变量***/
int sock_client;//定义客户端套接字
struct sockaddr_in server_addr;//定义存放服务器端地址的结构变量
int addr_len = sizeof(sockaddr_in);//地址结构变量长度

/****线程1接收到类型为2，3，4的数据***/
Data threadonedata[SIZEA];//线程1的缓存区
int ithreadone = 0;//控制线程1数据区的变量
int overflow = 0;//溢出标识符
int closethread = 0;//提示线程2关闭

/****线程2处理拼接线程1存下来的数据***/
int ithreadtwo = 0;//控制线程2的数据区
unordered_map<char*, char* >connectdata;//哈希表用于拼接时，查找有无ICAO出现过
int closethread2 = 0;//提示线程3关闭

/***线程3处理未经过翻译的要发送的数据***/
/****存放未经过翻译的要发送数据***/
Data rawsenddata[SIZEA];//存放未经过翻译的要发送数据
int irawsenddata = 0;//控制该缓存区的变量
int overflowrawsenddata = 0;//溢出标识符
int ithreadthree = 0;//控制线程3数据区的变量

//导入M矩阵（M矩阵由已知的雷达参数唯一确定（具体产生方法根据MATLAB进行））
double* MxArray_M;

//服务器的一些参数
char IP[30];
char acIpAddr[30];
int iClientPort;
int iServerPort;
int PORT;