#pragma once
typedef struct {
	//Ŀ��㼣����֡��ʽ ��ע��ÿһ֡�㼣����dtcnum������M�� M������·�Ĵ�������ȷ��
	int Header;						//֡ͬ�� E7E7E7E7
	int dtcnum;						//�㼣���� ���£�02H~07H�����ݵ㼣�����ظ�
	unsigned int time_of_det;		//���ʱ�� UTCʱ��
	unsigned int target_rng;		//Ŀ����� m
	unsigned int target_az;				//Ŀ�귽λ ����ϵ��˳ʱ�룬0~360��
	unsigned int rdr_vel;					//�����ٶ� m/s
	unsigned int frm_number;		//����� 
	unsigned int target_ad;			//�������� 
}Data5;