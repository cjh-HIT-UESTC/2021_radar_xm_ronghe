#pragma once
/***�õ�����Ϊ2��34��43�����ݵĽṹ��***/

typedef struct {
	//����2��ʽ
	char MSG[3];
	char type[2];
	char num3[3];
	char num4[5];
	char ICAO[6];
	char num6[6];
	char time1[30];
	char time2[30];
	char time3[30];
	char time4[30];
	char Altitude[15];
	char GroundSpeed[15];
	char Track[15];
	char Lat[15];
	char Long[15];
}Data_2;

typedef struct {
	//����34��ʽ��ƴ�Ӻ�ģ�
	char MSG3[5];
	char type3[2];
	char num33[3];
	char num43[5];
	char ICAO3[6];
	char num63[6];
	char time13[30];
	char time23[30];
	char time33[30];
	char time43[30];
	char Altitude3[15];
	char Lat3[15];
	char Long3[15];
	char Alert3[15];
	char Emergency3[15];
	char SPI3[15];
	char IsOnGround3[15];
	//����Ϊ4���͵�����
	char MSG[3];
	char type[2];
	char num3[3];
	char num4[5];
	char ICAO[6];
	char num6[6];
	char time1[30];
	char time2[30];
	char time3[30];
	char time4[30];
	char GroundSpeed[15];
	char Track[15];
	char VerticalRate[15];
}Data_34;

typedef struct {
	//����43��ʽ��ƴ�Ӻ�ģ�
	char MSG[5];
	char type[2];
	char num3[3];
	char num4[5];
	char ICAO[6];
	char num6[6];
	char time1[30];
	char time2[30];
	char time3[30];
	char time4[30];
	char GroundSpeed[15];
	char Track[15];
	char VerticalRate[15];
	//����Ϊ3���͵�����
	char MSG3[3];
	char type3[2];
	char num33[3];
	char num43[5];
	char ICAO3[6];
	char num63[6];
	char time13[30];
	char time23[30];
	char time33[30];
	char time43[30];
	char Altitude3[15];
	char Lat3[15];
	char Long3[15];
	char Alert3[15];
	char Emergency3[15];
	char SPI3[15];
	char IsOnGround3[15];
}Data_43;