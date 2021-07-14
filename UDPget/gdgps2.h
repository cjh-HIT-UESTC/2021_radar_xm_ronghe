#pragma once
typedef struct {
	//�ߵ�/GPS����֡��ʽ
	unsigned short Header;				//֡ͬ�� AA55
	unsigned char Info_type;			//��Ϣ���� 0X01
	unsigned char Data_type;			//�������� 0X53��minimal��ʽ
	unsigned short Data_length;			//֡���� 0X0153
	unsigned short Corud_angle;			//����� ����ϵ��˳ʱ��Ϊ����0~360�㣬��λ0.01��
	short Pitch;						//������ ˮƽΪ0����ͷ����Ϊ������λ0.01��
	short Roll;							//����� ˮƽΪ0����������Ϊ������λ0.01��
	short Dev_status;					//�豸״̬ Ĭ��0x0000
	short Power_vol;					//�����ѹ ��λ0.01��
	short Temperature;					//�豸�¶� ��λ0.01���϶�
	int Lat;							//γ�� ��λ10-7degree
	int Long;							//���� ��λ10-7degree
	int Alt;							//�߶�  ��λ0.01m
	int Speed_vx;						//�����ٶ� ��λ0.01m/s
	int Speed_vy;						//�����ٶ� ��λ0.01m/s
	int Speed_vz;						//�����ٶ� ��λ0.01m/s
	int Time_ms;						//ʱ�� ��ÿ������0ʱ��ʼ�����ms��
	unsigned char Gnss_info;			//GNSS��Ϣ
	unsigned char Satellite_num;		//���ǿ���
	short Check_sum;					//У���
}Data2;