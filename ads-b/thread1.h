#pragma once
#include"global_variable.h"
#include"UDPcode.h"
//�߳�1����
DWORD WINAPI ThreadOne(Ui::tcpgetClass  lpParameter) {
	Ui::tcpgetClass ui = lpParameter;
	//���峬ʱʱ��
	struct timeval timeout;
	fd_set fdRead;//���ڳ�ʱ����
	timeout.tv_sec = 600;//��λΪ�� ��
	timeout.tv_usec = 0;//��λΪ�� ����

	while (1) {
		//��ʱ����
		FD_ZERO(&fdRead);
		FD_SET(sock_client, &fdRead);
		int ret = select(0, &fdRead, NULL, NULL, &timeout);
		//��ʱ
		if (ret == 0) {
			MessageBox(NULL, TEXT("�߳�1��ʱ�˳�"), TEXT("��ʾ"), MB_OK);
			break;
		}
		// ��������
		//�ж��Ƿ���ճɹ�
		int size;
		char msgbuffer[iSize];//����/������Ϣ�Ļ�����
		if ((size = recv(sock_client, msgbuffer, sizeof(msgbuffer), 0)) > 0) {
			//ֻ��������Ϊ2��3��4������
			//����ʵ�鷢�ֺ�ż���ģ��ᷢ�ʹ������ݣ���ͷ��ΪMSG�����Լ�һ���ж�
			if ((msgbuffer[4] == '2' || msgbuffer[4] == '3' || msgbuffer[4] == '4') && msgbuffer[0] == 'M') {
				//�������
				if (ithreadone >= SIZEA) {
					ithreadone = ithreadone % SIZEA;
					overflow = 1;
				}
				int bufsize = 0;
				while (msgbuffer[bufsize] != '\n') {
					++bufsize;
				}
				memcpy(&threadonedata[ithreadone].data, msgbuffer, bufsize - 1);//�����յ�������ȫ���浽udpget����
				++ithreadone;
			}
		}
		else if (size == 0) {
			//printf("�Է��ѹر�����\n");
			MessageBox(NULL, TEXT("�Է��ѹر�����"), TEXT("��ʾ"), MB_OK);
			Sleep(10000);//ֹͣ10�룬ȷ���߳�2���㹻ʱ�䴦���
			closethread = 1;
			closesocket(sock_client);
			closeUDP();
			WSACleanup();
			exit(0);
		}
		else {
			MessageBox(NULL, TEXT("������Ϣʧ��"), TEXT("��ʾ"), MB_OK);
			//printf("������Ϣʧ��\n");
			Sleep(10000);//ֹͣ3�룬ȷ���߳�2���㹻ʱ�䴦���
			closethread = 1;
			closesocket(sock_client);
			closeUDP();
			WSACleanup();
			exit(0);
		}
	}
	Sleep(10000);//ֹͣ3�룬ȷ���߳�2���㹻ʱ�䴦���
	closethread = 1;

	_endthread();//�����߳�1
	return 0;
}
