#include "tcpget.h"
#include<iostream>
#include<unordered_map>
#pragma warning(disable:4996)
#include"global_variable.h"
#include"thread1.h"
#include"thread2.h"
#include"thread3.h"

using namespace std;

/***���캯��***/
tcpget::tcpget(QWidget *parent)
    : QMainWindow(parent)
{
	//| Qt::WindowStaysOnTopHint
	setWindowFlags(Qt::Dialog  | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui.setupUi(this);
	ui.textEdit->document()->setMaximumBlockCount(7);
	ui.textEdit_2->document()->setMaximumBlockCount(7);

	/***��ʼ��***/
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);//���ɰ汾��2.2
	if (WSAStartup(wVersionRequested, &wsaData) == SOCKET_ERROR)
	{
		MessageBox(NULL, TEXT("���� socket ʧ��"), TEXT("��ʾ"), MB_OK);
		WSACleanup();
		exit(0);
	}
	/****�����׽���***/
	// �½� socket��TCP��
	if ((sock_client = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		MessageBox(NULL, TEXT("�½� socket ʧ��"), TEXT("��ʾ"), MB_OK);
		WSACleanup();//���winsock
		exit(0);
	}
	//����M����M��������֪���״����Ψһȷ�������������������MATLAB���У���
	MATFile* pmatFile = matOpen("C:/Users/Administrator.DESKTOP-D4RD60B/Desktop/��Ŀ���/����M����/M.mat", "r");
	mxArray* pMxArray = matGetVariable(pmatFile, "M");
	MxArray_M = (double*)mxGetData(pMxArray);


}

DWORD WINAPI set1(Ui::tcpgetClass);
void tcpget::begin(QWidget* parent)
{
	/****��д��������ַ***/
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
	
	HANDLE Hone1;//�߳�_���߳�
	Hone1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)set1, &ui, 0, NULL);
	ui.ADSzt->setText(QString::fromLocal8Bit("�ȴ���ADS-B����..."));
	ui.pushButton->setEnabled(false);
	
}

DWORD WINAPI set1(Ui::tcpgetClass lpParameter) {
	Ui::tcpgetClass ui = lpParameter;
	/***��ʼ��winsock DLL***/
	openUDP(acIpAddr, iServerPort, iClientPort);
	
	memset((void*)&server_addr, 0, addr_len);//��ַ�ṹ��0
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(IP);

	/****���������������***/
	if (connect(sock_client, (struct sockaddr*)&server_addr, addr_len) != 0) {
		MessageBox(NULL, TEXT("���������������ʧ��"), TEXT("��ʾ"), MB_OK);
		closesocket(sock_client);
		closeUDP();
		WSACleanup();
		exit(0);
	}
	
	ui.ADSzt->setText(QString::fromLocal8Bit("��ADS-B���ӳɹ�"));
	/***���߳�1���ϵĽ������ݣ�ֻ�е�����Ϊ2��3��4ʱ�Ž��գ�***/
	HANDLE Hone;//�߳�1
	Hone = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadOne, &ui, 0, NULL);

	/***���߳�2���ϵĴ������ݣ�ƴ�ӵȲ�����***/
	HANDLE Htwo;//�߳�2
	Htwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadTwo, &ui, 0, NULL);

	/***���߳�3��������***/
	HANDLE Hthree;//�߳�3
	Hthree = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadThree, &ui, 0, NULL);

	//�ȴ��߳�ȫ��������
	WaitForSingleObject(Hone, INFINITE);
	WaitForSingleObject(Htwo, INFINITE);
	WaitForSingleObject(Hthree, INFINITE);

	closesocket(sock_client);
	closeUDP();
	WSACleanup();
	ui.ADSzt->setText(QString::fromLocal8Bit("��ʱ�������ݽ��գ������˳�"));

}

/***������ť***/
void tcpget::endbutton(QWidget* parent) {
	//delete MxArray_M;
	closesocket(sock_client);
	closeUDP();
	WSACleanup();
	exit(0);
}