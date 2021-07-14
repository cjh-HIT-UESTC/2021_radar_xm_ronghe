#pragma once
#define SIZEA 300000 //缓存区大小
#define iSize 256	//每次接收的数据包的最大长度

//定义保存N个客户端ip地址的数组
char** acIpAddr = new char* [1];

//定义数组保存对应客户端的电脑端口
int* iClientPort = new int[1];

//定义数组存放对应客户端所选择的接收协议类型
int* type = new int[1];

QString PathName, current_File;
QDateTime current_File_time;