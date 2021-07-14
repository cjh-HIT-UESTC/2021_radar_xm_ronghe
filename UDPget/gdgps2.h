#pragma once
typedef struct {
	//惯导/GPS数据帧格式
	unsigned short Header;				//帧同步 AA55
	unsigned char Info_type;			//信息类型 0X01
	unsigned char Data_type;			//数据类型 0X53：minimal格式
	unsigned short Data_length;			//帧长度 0X0153
	unsigned short Corud_angle;			//航向角 正北系，顺时针为正，0~360°，单位0.01°
	short Pitch;						//俯仰角 水平为0，机头向上为正，单位0.01°
	short Roll;							//横滚角 水平为0，左翼向上为正，单位0.01°
	short Dev_status;					//设备状态 默认0x0000
	short Power_vol;					//供电电压 单位0.01伏
	short Temperature;					//设备温度 单位0.01摄氏度
	int Lat;							//纬度 单位10-7degree
	int Long;							//经度 单位10-7degree
	int Alt;							//高度  单位0.01m
	int Speed_vx;						//东向速度 单位0.01m/s
	int Speed_vy;						//北向速度 单位0.01m/s
	int Speed_vz;						//天向速度 单位0.01m/s
	int Time_ms;						//时间 从每个周日0时开始计算的ms数
	unsigned char Gnss_info;			//GNSS信息
	unsigned char Satellite_num;		//卫星颗数
	short Check_sum;					//校验和
}Data2;