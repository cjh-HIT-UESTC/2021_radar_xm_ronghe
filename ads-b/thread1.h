#pragma once
#include"global_variable.h"
#include"UDPcode.h"
//线程1函数
DWORD WINAPI ThreadOne(Ui::tcpgetClass  lpParameter) {
	Ui::tcpgetClass ui = lpParameter;
	//定义超时时间
	struct timeval timeout;
	fd_set fdRead;//用于超时管理
	timeout.tv_sec = 600;//单位为： 秒
	timeout.tv_usec = 0;//单位为： 豪秒

	while (1) {
		//超时设置
		FD_ZERO(&fdRead);
		FD_SET(sock_client, &fdRead);
		int ret = select(0, &fdRead, NULL, NULL, &timeout);
		//超时
		if (ret == 0) {
			MessageBox(NULL, TEXT("线程1超时退出"), TEXT("提示"), MB_OK);
			break;
		}
		// 接收数据
		//判断是否接收成功
		int size;
		char msgbuffer[iSize];//接收/发送信息的缓存区
		if ((size = recv(sock_client, msgbuffer, sizeof(msgbuffer), 0)) > 0) {
			//只接收类型为2、3、4的数据
			//经过实验发现很偶尔的，会发送错误数据，开头不为MSG，所以加一个判断
			if ((msgbuffer[4] == '2' || msgbuffer[4] == '3' || msgbuffer[4] == '4') && msgbuffer[0] == 'M') {
				//溢出控制
				if (ithreadone >= SIZEA) {
					ithreadone = ithreadone % SIZEA;
					overflow = 1;
				}
				int bufsize = 0;
				while (msgbuffer[bufsize] != '\n') {
					++bufsize;
				}
				memcpy(&threadonedata[ithreadone].data, msgbuffer, bufsize - 1);//将接收到的数据全部存到udpget里面
				++ithreadone;
			}
		}
		else if (size == 0) {
			//printf("对方已关闭连接\n");
			MessageBox(NULL, TEXT("对方已关闭连接"), TEXT("提示"), MB_OK);
			Sleep(10000);//停止10秒，确保线程2有足够时间处理好
			closethread = 1;
			closesocket(sock_client);
			closeUDP();
			WSACleanup();
			exit(0);
		}
		else {
			MessageBox(NULL, TEXT("接收信息失败"), TEXT("提示"), MB_OK);
			//printf("接收信息失败\n");
			Sleep(10000);//停止3秒，确保线程2有足够时间处理好
			closethread = 1;
			closesocket(sock_client);
			closeUDP();
			WSACleanup();
			exit(0);
		}
	}
	Sleep(10000);//停止3秒，确保线程2有足够时间处理好
	closethread = 1;

	_endthread();//结束线程1
	return 0;
}
