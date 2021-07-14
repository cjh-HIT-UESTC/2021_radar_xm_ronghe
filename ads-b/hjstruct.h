#pragma once
/****定义航迹帧格式的数据结构***/
#pragma pack(1)//结构体对齐的代码
typedef struct {
	//航迹帧格式
	int Header;						//帧同步 A5A5A5A5
	unsigned int track_num;			//航迹编号							ICAO
	unsigned int time_of_updata;	//更新时间 UTC时间								时间
	unsigned short track_status;	//航迹状态 0：真实；1：外推；2：删除
	unsigned short track_att_2;		//尺寸属性 1：大；2：中；3：小
	unsigned short track_att_3;		//海目标属性 1：民船；2：海船；3：未知
	unsigned int tgt_rng;			//目标距离 m							计算得到
	float rdr_vel;					//径向速度 m/s					乘以角度
	float tgt_az;					//目标方位 正北系，顺时针，0~360°			根据经纬度转换
	float cruise_velocity;			//载机航速 m/s							GroundSpeed
	float cruise_heading;			//载机航向 正北系，顺时针，0~360°					Track
	unsigned int frm_number;		//扫描帧号 		
	unsigned int target_ad;			//回波强度 
}hjData;
