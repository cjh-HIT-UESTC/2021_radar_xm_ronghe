#pragma once
typedef struct {
	//目标点迹数据帧格式 备注：每一帧点迹数量dtcnum不超过M， M根据链路的传输速率确定
	int Header;						//帧同步 E7E7E7E7
	int dtcnum;						//点迹数量 以下（02H~07H）根据点迹数量重复
	unsigned int time_of_det;		//检测时间 UTC时间
	unsigned int target_rng;		//目标距离 m
	unsigned int target_az;				//目标方位 正北系，顺时针，0~360°
	unsigned int rdr_vel;					//径向速度 m/s
	unsigned int frm_number;		//信噪比 
	unsigned int target_ad;			//背景噪声 
}Data5;