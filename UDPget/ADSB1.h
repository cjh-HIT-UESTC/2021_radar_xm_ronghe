#pragma once
#pragma once
typedef struct {
	//ADS-B数据帧格式
	unsigned short Header;				//帧同步 0XA00A
	unsigned short Data_length;			//报文长度 除同步字、结束符和校验码以外所有数据长度的字节数，0X32
	unsigned char FlightNum_7;			//航班号 8字节ASCII码，数据帧中按照接收顺序，从高到低顺序解析。
	unsigned char FlightNum_6;			//航班号 例如，按顺序收到字节“0X43，0X45，0X53，0X35，0X31，0X35，0X38，0X20”，
	unsigned char FlightNum_5;			//航班号       解析后应为“CES5158 ”
	unsigned char FlightNum_4;			//航班号
	unsigned char FlightNum_3;			//航班号
	unsigned char FlightNum_2;			//航班号
	unsigned char FlightNum_1;			//航班号
	unsigned char Temperatur0;			//航班号
	unsigned char ADD_7;				//飞机标识 8字节ASCII码，数据帧中按照接收顺序，从高到低顺序解析。只有前6个字节有效。
	unsigned char ADD_6;				//飞机标识
	unsigned char ADD_5;				//飞机标识
	unsigned char ADD_4;				//飞机标识
	unsigned char ADD_3;				//飞机标识
	unsigned char ADD_2;				//飞机标识
	unsigned char ADD_1;				//飞机标识
	unsigned char ADD_0;				//飞机标识
	unsigned int Long;						//经度 单位：度
	unsigned int Lat;							//纬度 单位：度
	int Alt;							//高度 单位：英尺
	int Alt_flight;						//飞机高度 单位：英尺
	unsigned char	 Day;				//日 1~31
	unsigned char  Month;				//月 1~12
	unsigned char  Year;				//年 00~99
	unsigned char Hour;					//时 0~23
	unsigned char  Minute;				//分 0~59
	unsigned char  Second;				//秒 0~59
	unsigned short  ms;					//毫秒 0~999
	unsigned short CRC;					//校验码
	unsigned char ETX;					//结束符 0XCC
}Data1;