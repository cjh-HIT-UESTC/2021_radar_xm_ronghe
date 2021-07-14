#pragma once
/****定义翻译数据之后的结构体***/
typedef struct {
	unsigned int tgt_rng;			//目标距离 m							计算得到
	float rdr_vel;					//径向速度 m/s					乘以角度
	float tgt_az;					//目标方位 正北系，顺时针，0~360°			根据经纬度转换
	float cruise_velocity;			//载机航速 m/s							GroundSpeed
	float cruise_heading;			//载机航向 正北系，顺时针，0~360°					Track
}Data_trainslat;

/****定义得到ECEF坐标系数据的的结构体***/
typedef struct {
	double x_tar;
	double y_tar;
	double z_tar;
}Data_ECEF;
