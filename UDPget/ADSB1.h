#pragma once
#pragma once
typedef struct {
	//ADS-B����֡��ʽ
	unsigned short Header;				//֡ͬ�� 0XA00A
	unsigned short Data_length;			//���ĳ��� ��ͬ���֡���������У���������������ݳ��ȵ��ֽ�����0X32
	unsigned char FlightNum_7;			//����� 8�ֽ�ASCII�룬����֡�а��ս���˳�򣬴Ӹߵ���˳�������
	unsigned char FlightNum_6;			//����� ���磬��˳���յ��ֽڡ�0X43��0X45��0X53��0X35��0X31��0X35��0X38��0X20����
	unsigned char FlightNum_5;			//�����       ������ӦΪ��CES5158 ��
	unsigned char FlightNum_4;			//�����
	unsigned char FlightNum_3;			//�����
	unsigned char FlightNum_2;			//�����
	unsigned char FlightNum_1;			//�����
	unsigned char Temperatur0;			//�����
	unsigned char ADD_7;				//�ɻ���ʶ 8�ֽ�ASCII�룬����֡�а��ս���˳�򣬴Ӹߵ���˳�������ֻ��ǰ6���ֽ���Ч��
	unsigned char ADD_6;				//�ɻ���ʶ
	unsigned char ADD_5;				//�ɻ���ʶ
	unsigned char ADD_4;				//�ɻ���ʶ
	unsigned char ADD_3;				//�ɻ���ʶ
	unsigned char ADD_2;				//�ɻ���ʶ
	unsigned char ADD_1;				//�ɻ���ʶ
	unsigned char ADD_0;				//�ɻ���ʶ
	unsigned int Long;						//���� ��λ����
	unsigned int Lat;							//γ�� ��λ����
	int Alt;							//�߶� ��λ��Ӣ��
	int Alt_flight;						//�ɻ��߶� ��λ��Ӣ��
	unsigned char	 Day;				//�� 1~31
	unsigned char  Month;				//�� 1~12
	unsigned char  Year;				//�� 00~99
	unsigned char Hour;					//ʱ 0~23
	unsigned char  Minute;				//�� 0~59
	unsigned char  Second;				//�� 0~59
	unsigned short  ms;					//���� 0~999
	unsigned short CRC;					//У����
	unsigned char ETX;					//������ 0XCC
}Data1;