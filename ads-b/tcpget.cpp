#include "tcpget.h"
#include<iostream>
#include<unordered_map>
#pragma warning(disable:4996)
#include"global_variable.h"
#include"thread1.h"
#include"thread2.h"
#include"thread3.h"

using namespace std;

/***构造函数***/
tcpget::tcpget(QWidget *parent)
    : QMainWindow(parent)
{
	//| Qt::WindowStaysOnTopHint
	setWindowFlags(Qt::Dialog  | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui.setupUi(this);
	ui.textEdit->document()->setMaximumBlockCount(7);
	ui.textEdit_2->document()->setMaximumBlockCount(7);

	/***初始化***/
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);//生成版本号2.2
	if (WSAStartup(wVersionRequested, &wsaData) == SOCKET_ERROR)
	{
		MessageBox(NULL, TEXT("启用 socket 失败"), TEXT("提示"), MB_OK);
		WSACleanup();
		exit(0);
	}
	/****创建套接字***/
	// 新建 socket（TCP）
	if ((sock_client = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		MessageBox(NULL, TEXT("新建 socket 失败"), TEXT("提示"), MB_OK);
		WSACleanup();//清空winsock
		exit(0);
	}
	//导入M矩阵（M矩阵由已知的雷达参数唯一确定（具体产生方法根据MATLAB进行））
	MATFile* pmatFile = matOpen("C:/Users/Administrator.DESKTOP-D4RD60B/Desktop/项目相关/产生M矩阵/M.mat", "r");
	mxArray* pMxArray = matGetVariable(pmatFile, "M");
	MxArray_M = (double*)mxGetData(pMxArray);


}

DWORD WINAPI set1(Ui::tcpgetClass);
void tcpget::begin(QWidget* parent)
{
	/****填写服务器地址***/
	bool ok;
	char* temp;

	QString tempStr;
	QString ADSip = ui.ADSip->text();
	QByteArray ba;
	ba = ADSip.toLatin1();
	temp = ba.data();
	strncpy(IP, temp, 30);

	QString ADSport = ui.ADSport->text();
	PORT= ADSport.toInt(&ok);

	QString serverip = ui.serverip->text();
	ba = serverip.toLatin1();
	temp = ba.data();
	strncpy(acIpAddr, temp, 30);

	QString serverport = ui.serverport->text();
	iClientPort = serverport.toInt(&ok);

	QString iclientPort = ui.iclientPort->text();
	iServerPort = iclientPort.toInt(&ok);
	
	HANDLE Hone1;//线程_主线程
	Hone1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)set1, &ui, 0, NULL);
	ui.ADSzt->setText(QString::fromLocal8Bit("等待与ADS-B连接..."));
	ui.pushButton->setEnabled(false);
	
}

DWORD WINAPI set1(Ui::tcpgetClass lpParameter) {
	Ui::tcpgetClass ui = lpParameter;
	/***初始化winsock DLL***/
	openUDP(acIpAddr, iServerPort, iClientPort);
	
	memset((void*)&server_addr, 0, addr_len);//地址结构清0
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(IP);

	/****与服务器建立连接***/
	if (connect(sock_client, (struct sockaddr*)&server_addr, addr_len) != 0) {
		MessageBox(NULL, TEXT("与服务器建立连接失败"), TEXT("提示"), MB_OK);
		closesocket(sock_client);
		closeUDP();
		WSACleanup();
		exit(0);
	}
	
	ui.ADSzt->setText(QString::fromLocal8Bit("与ADS-B连接成功"));
	/***用线程1不断的接收数据（只有当类型为2、3、4时才接收）***/
	HANDLE Hone;//线程1
	Hone = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadOne, &ui, 0, NULL);

	/***用线程2不断的处理数据（拼接等操作）***/
	HANDLE Htwo;//线程2
	Htwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadTwo, &ui, 0, NULL);

	/***用线程3翻译数据***/
	HANDLE Hthree;//线程3
	Hthree = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadThree, &ui, 0, NULL);

	//等待线程全部运行完
	WaitForSingleObject(Hone, INFINITE);
	WaitForSingleObject(Htwo, INFINITE);
	WaitForSingleObject(Hthree, INFINITE);

	closesocket(sock_client);
	closeUDP();
	WSACleanup();
	ui.ADSzt->setText(QString::fromLocal8Bit("长时间无数据接收，程序退出"));

}

/***结束按钮***/
void tcpget::endbutton(QWidget* parent) {
	//delete MxArray_M;
	closesocket(sock_client);
	closeUDP();
	WSACleanup();
	exit(0);
}