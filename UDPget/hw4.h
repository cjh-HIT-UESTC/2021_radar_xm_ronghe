#pragma once
typedef struct {
	//����Ŀ�꺽�����ĸ�ʽ
	int Header;							//֡ͬ�� FFFFFFFF
	unsigned int track_num;				//������� 
	unsigned int time_of_update;		//����ʱ�� UTCʱ��
	unsigned int Pitch;						//Ŀ�긩�� ��
	unsigned int Azimuth;						//Ŀ�귽λ ��
	unsigned int Area;							//ͶӰ��� m2
	unsigned int Contrast;						//�Աȶ�
}Data4;