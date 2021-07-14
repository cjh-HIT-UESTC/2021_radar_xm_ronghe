#pragma once
/****���庽��֡��ʽ�����ݽṹ***/
#pragma pack(1)//�ṹ�����Ĵ���
typedef struct {
	//����֡��ʽ
	int Header;						//֡ͬ�� A5A5A5A5
	unsigned int track_num;			//�������							ICAO
	unsigned int time_of_updata;	//����ʱ�� UTCʱ��								ʱ��
	unsigned short track_status;	//����״̬ 0����ʵ��1�����ƣ�2��ɾ��
	unsigned short track_att_2;		//�ߴ����� 1����2���У�3��С
	unsigned short track_att_3;		//��Ŀ������ 1���񴬣�2��������3��δ֪
	unsigned int tgt_rng;			//Ŀ����� m							����õ�
	float rdr_vel;					//�����ٶ� m/s					���ԽǶ�
	float tgt_az;					//Ŀ�귽λ ����ϵ��˳ʱ�룬0~360��			���ݾ�γ��ת��
	float cruise_velocity;			//�ػ����� m/s							GroundSpeed
	float cruise_heading;			//�ػ����� ����ϵ��˳ʱ�룬0~360��					Track
	unsigned int frm_number;		//ɨ��֡�� 		
	unsigned int target_ad;			//�ز�ǿ�� 
}hjData;
