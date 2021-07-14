#pragma once
/****���巭������֮��Ľṹ��***/
typedef struct {
	unsigned int tgt_rng;			//Ŀ����� m							����õ�
	float rdr_vel;					//�����ٶ� m/s					���ԽǶ�
	float tgt_az;					//Ŀ�귽λ ����ϵ��˳ʱ�룬0~360��			���ݾ�γ��ת��
	float cruise_velocity;			//�ػ����� m/s							GroundSpeed
	float cruise_heading;			//�ػ����� ����ϵ��˳ʱ�룬0~360��					Track
}Data_trainslat;

/****����õ�ECEF����ϵ���ݵĵĽṹ��***/
typedef struct {
	double x_tar;
	double y_tar;
	double z_tar;
}Data_ECEF;
