#pragma once
typedef struct {
	//红外目标航迹报文格式
	int Header;							//帧同步 FFFFFFFF
	unsigned int track_num;				//航迹编号 
	unsigned int time_of_update;		//更新时间 UTC时间
	unsigned int Pitch;						//目标俯仰 度
	unsigned int Azimuth;						//目标方位 度
	unsigned int Area;							//投影面积 m2
	unsigned int Contrast;						//对比度
}Data4;