#pragma once
#define SIZEA 300000 //��������С
#define iSize 256	//ÿ�ν��յ����ݰ�����󳤶�

//���屣��N���ͻ���ip��ַ������
char** acIpAddr = new char* [1];

//�������鱣���Ӧ�ͻ��˵ĵ��Զ˿�
int* iClientPort = new int[1];

//���������Ŷ�Ӧ�ͻ�����ѡ��Ľ���Э������
int* type = new int[1];

QString PathName, current_File;
QDateTime current_File_time;