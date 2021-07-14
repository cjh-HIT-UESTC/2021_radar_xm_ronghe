#pragma once
#include"thread1.h"

Data1 getdata1;//存放所有经过判断后的数据
Data2 getdata2;//存放所有经过判断后的数据
Data3 getdata3;//存放所有经过判断后的数据
Data4 getdata4;//存放所有经过判断后的数据
Data5 getdata5;//存放所有经过判断后的数据

//用于保证当udpget数组里有数时才运行线程2里的操作，避免线程不同步
int getdata1dex = 0;
int getdata2dex = 0;
int getdata3dex = 0;
int getdata4dex = 0;
int getdata5dex = 0;


//线程2函数
DWORD WINAPI ThreadTwo(Ui::udpgetClass lpParameter) {
	//取出传入的数组数据
	Ui::udpgetClass ui = lpParameter;
	FILE* fp1;

	char* Path;
	QByteArray path1 = PathName.toLatin1();
	Path = path1.data();
	fp1 = fopen(Path, "w");

	//在本程序里 假定线程1和线程2的速度差距不是特别巨大
	while (1) {
		if (getdata1dex < udpget1dex || udpget1overflow == 1)//保证不超过udpget里面的数据个数
		{
			if (getdata1dex >= SIZEA) {
				getdata1dex = getdata1dex % SIZEA;
				udpget1overflow = 0;
			}
			//协议1类型
			if (ntohs(udpget1[getdata1dex].Header) == 0XA00A && udpget1[getdata1dex].ETX == 0XCC)
			{
				getdata1.Header = ntohs(udpget1[getdata1dex].Header);
				getdata1.Data_length = ntohs(udpget1[getdata1dex].Data_length);
				getdata1.FlightNum_7 = udpget1[getdata1dex].FlightNum_7;
				getdata1.FlightNum_6 = udpget1[getdata1dex].FlightNum_6;
				getdata1.FlightNum_5 = udpget1[getdata1dex].FlightNum_5;
				getdata1.FlightNum_4 = udpget1[getdata1dex].FlightNum_4;
				getdata1.FlightNum_3 = udpget1[getdata1dex].FlightNum_3;
				getdata1.FlightNum_2 = udpget1[getdata1dex].FlightNum_2;
				getdata1.FlightNum_1 = udpget1[getdata1dex].FlightNum_1;
				getdata1.Temperatur0 = udpget1[getdata1dex].Temperatur0;
				getdata1.ADD_7 = udpget1[getdata1dex].ADD_7;
				getdata1.ADD_6 = udpget1[getdata1dex].ADD_6;
				getdata1.ADD_5 = udpget1[getdata1dex].ADD_5;
				getdata1.ADD_4 = udpget1[getdata1dex].ADD_4;
				getdata1.ADD_3 = udpget1[getdata1dex].ADD_3;
				getdata1.ADD_2 = udpget1[getdata1dex].ADD_2;
				getdata1.ADD_1 = udpget1[getdata1dex].ADD_1;
				getdata1.ADD_0 = udpget1[getdata1dex].ADD_0;
				getdata1.Long = ntohl(udpget1[getdata1dex].Long);
				getdata1.Lat = ntohl(udpget1[getdata1dex].Lat);
				getdata1.Alt = ntohl(udpget1[getdata1dex].Alt);
				getdata1.Alt_flight = ntohl(udpget1[getdata1dex].Alt_flight);
				getdata1.Day = udpget1[getdata1dex].Day;
				getdata1.Month = udpget1[getdata1dex].Month;
				getdata1.Year = udpget1[getdata1dex].Year;
				getdata1.Hour = udpget1[getdata1dex].Hour;
				getdata1.Minute = udpget1[getdata1dex].Minute;
				getdata1.Second = udpget1[getdata1dex].Second;
				getdata1.ms = ntohs(udpget1[getdata1dex].ms);
				getdata1.CRC = ntohs(udpget1[getdata1dex].CRC);
				getdata1.ETX = udpget1[getdata1dex].ETX;
				ui.textEdit->append(QString::number(getdata1dex)+ QString::fromStdString(": ")+QString::fromLocal8Bit("接收到协议1数据"));
				fwrite(&getdata1, sizeof(Data1), 1, fp1);
			}
			getdata1dex++;
		}
		if (getdata2dex < udpget2dex || udpget2overflow == 1)//保证不超过udpget里面的数据个数
		{
			if (getdata2dex >= SIZEA) {
				getdata2dex = getdata2dex % SIZEA;
				udpget2overflow = 0;
			}
			//协议2类型
			if (ntohs(udpget2[getdata2dex].Header) == 0XAA55)
			{

				getdata2.Header = ntohs(udpget2[getdata2dex].Header);
				getdata2.Info_type = udpget2[getdata2dex].Info_type;
				getdata2.Data_type = udpget2[getdata2dex].Data_type;
				getdata2.Data_length = ntohs(udpget2[getdata2dex].Data_length);
				getdata2.Corud_angle = ntohs(udpget2[getdata2dex].Corud_angle);
				getdata2.Pitch = ntohs(udpget2[getdata2dex].Pitch);
				getdata2.Roll = ntohs(udpget2[getdata2dex].Roll);
				getdata2.Dev_status = ntohs(udpget2[getdata2dex].Dev_status);
				getdata2.Power_vol = ntohs(udpget2[getdata2dex].Power_vol);
				getdata2.Temperature = ntohs(udpget2[getdata2dex].Temperature);
				getdata2.Lat = ntohl(udpget2[getdata2dex].Lat);
				getdata2.Long = ntohl(udpget2[getdata2dex].Long);
				getdata2.Alt = ntohl(udpget2[getdata2dex].Alt);
				getdata2.Speed_vx = ntohl(udpget2[getdata2dex].Speed_vx);
				getdata2.Speed_vy = ntohl(udpget2[getdata2dex].Speed_vy);
				getdata2.Speed_vz = ntohl(udpget2[getdata2dex].Speed_vz);
				getdata2.Time_ms = ntohl(udpget2[getdata2dex].Time_ms);
				getdata2.Gnss_info = udpget2[getdata2dex].Gnss_info;
				getdata2.Satellite_num = udpget2[getdata2dex].Satellite_num;
				getdata2.Check_sum = ntohs(udpget2[getdata2dex].Check_sum);
				ui.textEdit->append(QString::number(getdata2dex) + QString::fromStdString(": ") + QString::fromLocal8Bit("接收到协议2数据"));
				fwrite(&getdata2, sizeof(Data2), 1, fp1);
			}
			getdata2dex++;
		}
		if (getdata3dex < udpget3dex || udpget3overflow == 1)//保证不超过udpget里面的数据个数
		{
			if (getdata3dex >= SIZEA) {
				getdata3dex = getdata3dex % SIZEA;
				udpget3overflow = 0;
			}
			//协议3类型
			if (ntohl(udpget3[getdata3dex].Header) == 0XA5A5A5A5)
			{

				getdata3.Header = ntohl(udpget3[getdata3dex].Header);
				getdata3.track_num = ntohl(udpget3[getdata3dex].track_num);
				getdata3.time_of_updata = ntohl(udpget3[getdata3dex].time_of_updata);
				getdata3.track_status = ntohs(udpget3[getdata3dex].track_status);
				getdata3.track_att_2 = ntohs(udpget3[getdata3dex].track_att_2);
				getdata3.track_att_3 = ntohs(udpget3[getdata3dex].track_att_3);
				getdata3.tgt_rng = ntohl(udpget3[getdata3dex].tgt_rng);
				getdata3.rdr_vel = ntohl(udpget3[getdata3dex].rdr_vel);
				getdata3.tgt_az = ntohl(udpget3[getdata3dex].tgt_az);
				getdata3.cruise_velocity = ntohl(udpget3[getdata3dex].cruise_velocity);
				getdata3.cruise_heading = ntohl(udpget3[getdata3dex].cruise_heading);
				getdata3.frm_number = ntohl(udpget3[getdata3dex].frm_number);
				getdata3.target_ad = ntohl(udpget3[getdata3dex].target_ad);
				ui.textEdit->append(QString::number(getdata3dex) + QString::fromStdString(": ") + QString::fromLocal8Bit("接收到协议3数据"));
				fwrite(&getdata3, sizeof(Data3), 1, fp1);
			}
			getdata3dex++;
		}
		if (getdata4dex < udpget4dex || udpget4overflow == 1)//保证不超过udpget里面的数据个数
		{
			if (getdata4dex >= SIZEA) {
				getdata4dex = getdata4dex % SIZEA;
				udpget4overflow = 0;
			}
			//协议4类型
			if (ntohl(udpget4[getdata4dex].Header) == 0XFFFFFFFF)
			{

				getdata4.Header = ntohl(udpget4[getdata4dex].Header);
				getdata4.track_num = ntohl(udpget4[getdata4dex].track_num);
				getdata4.time_of_update = ntohl(udpget4[getdata4dex].time_of_update);
				getdata4.Pitch = ntohl(udpget4[getdata4dex].Pitch);
				getdata4.Azimuth = ntohl(udpget4[getdata4dex].Azimuth);
				getdata4.Area = ntohl(udpget4[getdata4dex].Area);
				getdata4.Contrast = ntohl(udpget4[getdata4dex].Contrast);
				ui.textEdit->append(QString::number(getdata4dex) + QString::fromStdString(": ") + QString::fromLocal8Bit("接收到协议4数据"));
				fwrite(&getdata4, sizeof(Data4), 1, fp1);
			}
			getdata4dex++;
		}
		if (getdata5dex < udpget5dex || udpget5overflow == 1)//保证不超过udpget里面的数据个数
		{
			if (getdata5dex >= SIZEA) {
				getdata5dex = getdata5dex % SIZEA;
				udpget5overflow = 0;
			}
			//协议5类型
			if (ntohl(udpget5[getdata5dex].Header) == 0XE7E7E7E7)
			{

				getdata5.Header = ntohl(udpget5[getdata5dex].Header);
				getdata5.dtcnum = ntohl(udpget5[getdata5dex].dtcnum);
				getdata5.time_of_det = ntohl(udpget5[getdata5dex].time_of_det);
				getdata5.target_rng = ntohl(udpget5[getdata5dex].target_rng);
				getdata5.target_az = ntohl(udpget5[getdata5dex].target_az);
				getdata5.rdr_vel = ntohl(udpget5[getdata5dex].rdr_vel);
				getdata5.frm_number = ntohl(udpget5[getdata5dex].frm_number);
				getdata5.target_ad = ntohl(udpget5[getdata5dex].target_ad);
				ui.textEdit->append(QString::number(getdata5dex) + QString::fromStdString(": ") + QString::fromLocal8Bit("接收到协议5数据"));
				fwrite(&getdata5, sizeof(Data5), 1, fp1);
			}
			getdata5dex++;
		}
		if (closethread == 1) {

			break;
		}
	}
	fclose(fp1);//关闭文件


	_endthread();
	return 0;
}