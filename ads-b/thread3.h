#pragma once
#include"global_variable.h"
#include"hjstruct.h"
#include"struct_2_34_43.h"
#include"Translation_results.h"
#include"UDPcode.h"
#include<stdlib.h>
#include<string.h>
#include <QDebug>
#pragma pack(1)//结构体对齐的代码
//线程3函数
//处理线程2中保存的数据
DWORD WINAPI ThreadThree(Ui::tcpgetClass lpParameter) {
	Ui::tcpgetClass ui = lpParameter;

	
	/***使用UDP传输数据***/
	while (1) {
		if (closethread2 == 1) {
			//cout << "线程3退出" << endl;
			break;
		}
		if (ithreadthree < irawsenddata || overflowrawsenddata == 1) {
			//溢出控制
			if (ithreadthree >= SIZEA) {
				ithreadthree = ithreadthree % SIZEA;
				overflowrawsenddata = 0;
			}
			//处理类型为2的数据（第一个字符为M）
			if (rawsenddata[ithreadthree].data[0] == 'M') {
				//定义要发送的数据
				hjData senddata;
				Data_2 senddata_old;

				char delims[] = ",";//设置以逗号为分割符
				char* result = NULL;
				result = strtok(rawsenddata[ithreadthree].data, delims);
				strcpy(senddata_old.MSG, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.type, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.num3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.num4, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.ICAO, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.num6, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time1, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time2, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time4, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Altitude, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.GroundSpeed, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Track, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Lat, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Long, result);

				ui.textEdit->append( QString::fromStdString(senddata_old.ICAO)+ QString::fromStdString(",")
					+ QString::fromStdString(senddata_old.Altitude) + QString::fromStdString(",") + QString::fromStdString(senddata_old.GroundSpeed) + QString::fromStdString(",") +
					QString::fromStdString(senddata_old.Track) + QString::fromStdString(",") + QString::fromStdString(senddata_old.Lat) + QString::fromStdString(",") + QString::fromStdString(senddata_old.Long));

				/***翻译数据***/
				Data_trainslat Translation_result = Translation(senddata_old.Long, senddata_old.Lat, senddata_old.Altitude, senddata_old.Track, senddata_old.GroundSpeed);
				/***打包数据，准备发送***/
				senddata.Header = htonl(0xA5A5A5A5);
				senddata.track_num = htonl(0xA5A51111);
				senddata.time_of_updata = htonl(0x00000000);
				senddata.track_status = htons(0x00000000);
				senddata.track_att_2 = htons(0x00000001);
				senddata.track_att_3 = htons(0x00000001);
				senddata.tgt_rng = htons(Translation_result.tgt_rng);
				senddata.rdr_vel = (Translation_result.rdr_vel);
				senddata.tgt_az = (Translation_result.tgt_az);
				senddata.cruise_velocity = (Translation_result.cruise_velocity);
				senddata.cruise_heading = (Translation_result.cruise_heading);
				senddata.frm_number = htons(0xA5A5A5A5);
				senddata.target_ad = htons(0xA5A5A5A5);

				/***UDP发送数据***/
				//ui.ADSdata->setText("发送类型2数据");
				//cout << "发送类型2数据" << endl;
				//QString::fromLocal8Bit("发送类型2数据：")
				ui.textEdit_2->append(QString::number(senddata.tgt_rng) + QString::fromStdString(",") + QString::number(senddata.rdr_vel) + QString::fromStdString(",") +
					QString::number(senddata.tgt_az) + QString::fromStdString(",") + QString::number(senddata.cruise_velocity) + QString::fromStdString(",") + QString::number(senddata.cruise_heading));

				sendto(iUDP, (char*)&senddata, sizeof(senddata), 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
			}
			//处理类型为34的数据（第一个字符为3）
			else if (rawsenddata[ithreadthree].data[0] == '3') {
				//定义要发送的数据
				hjData senddata;
				Data_34 senddata_old;

				char delims[] = ",";//设置以逗号为分割符
				char* result = NULL;
				result = strtok(rawsenddata[ithreadthree].data, delims);
				strcpy(senddata_old.MSG3, result);
				result = strtok(NULL, delims);
				try {
					strcpy(senddata_old.type3, result);
				}
				catch (...) {
					//cout << "34处，类型3数据type3出错" << endl;
					++ithreadthree;
					continue;
				}
				result = strtok(NULL, delims);
				strcpy(senddata_old.num33, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.num43, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.ICAO3, result);
				//qDebug("ssss %s ",senddata_old.ICAO3);
				result = strtok(NULL, delims);
				strcpy(senddata_old.num63, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time13, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time23, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time33, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time43, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Altitude3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Lat3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Long3, result);
				if (senddata_old.Long3[1] == '\0') {
					//cout << "34处，类型3数据出错" << endl;
					++ithreadthree;
					continue;
				}
				result = strtok(NULL, delims);
				strcpy(senddata_old.Alert3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Emergency3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.SPI3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.IsOnGround3, result);
				result = strtok(NULL, delims);
				//以上为类型3的数据，以下为类型4的数据
				strcpy(senddata_old.MSG, result);
				result = strtok(NULL, delims);
				try {
					strcpy(senddata_old.type, result);
				}
				catch (...) {
					//cout << "34处，类型3数据type出错" << endl;
					++ithreadthree;
					continue;
				}
				result = strtok(NULL, delims);
				strcpy(senddata_old.num3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.num4, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.ICAO, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.num6, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time1, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time2, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time4, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.GroundSpeed, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Track, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.VerticalRate, result);

				char icao[6];
				memcpy(icao, senddata_old.ICAO, 6);
				QString stricao(icao);
				//QString str1(senddata_old.GroundSpeed);
				//ui.textEdit->insertPlainText(str);
				ui.textEdit->append(stricao + QString::fromStdString(" , ") +
					QString::fromStdString(senddata_old.Altitude3) + QString::fromStdString(" , ") + 
					QString::fromStdString(senddata_old.GroundSpeed) + QString::fromStdString(" , ")+
					QString::fromStdString(senddata_old.Track) + QString::fromStdString(" , ") +
					QString::fromStdString(senddata_old.Lat3) + QString::fromStdString(" , ") +
					QString::fromStdString(senddata_old.Long3));

				/***翻译数据***/
				Data_trainslat Translation_result = Translation(senddata_old.Long3, senddata_old.Lat3, senddata_old.Altitude3, senddata_old.Track, senddata_old.GroundSpeed);
				/***打包数据，准备发送***/
				senddata.Header = htonl(0xA5A5A5A5);
				senddata.track_num = htonl(0xA5A51111);
				senddata.time_of_updata = htonl(0x00000000);
				senddata.track_status = htons(0x00000000);
				senddata.track_att_2 = htons(0x00000001);
				senddata.track_att_3 = htons(0x00000001);
				senddata.tgt_rng = htons(Translation_result.tgt_rng);
				senddata.rdr_vel = (Translation_result.rdr_vel);
				senddata.tgt_az = (Translation_result.tgt_az);
				senddata.cruise_velocity = (Translation_result.cruise_velocity);
				senddata.cruise_heading = (Translation_result.cruise_heading);
				senddata.frm_number = htons(0xA5A5A5A5);
				senddata.target_ad = htons(0xA5A5A5A5);

				/***UDP发送数据***/
				//ui.textEdit_2->append(QString::number(senddata.tgt_rng) + QString::fromStdString(" , ") + QString::number(senddata.rdr_vel) + QString::fromStdString(" , ") +
				//	QString::number(senddata.tgt_az) + QString::fromStdString(" , ") + QString::number(senddata.cruise_velocity) + QString::fromStdString(" , ") + QString::number(senddata.cruise_heading));


				ui.textEdit_2->append(stricao + QString::fromStdString(" , ") + QString::number(senddata.tgt_rng) + QString::fromStdString(" , ") + QString::number(senddata.rdr_vel) + QString::fromStdString(" , ") +
					QString::number(senddata.tgt_az) + QString::fromStdString(" , ") + QString::number(senddata.cruise_velocity) + QString::fromStdString(" , ") + QString::number(senddata.cruise_heading));


				sendto(iUDP, (char*)&senddata, sizeof(senddata), 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
			}
			//处理类型为43的数据（第一个字符为4）
			else if (rawsenddata[ithreadthree].data[0] == '4') {
				//定义要发送的数据
				hjData senddata;
				Data_43 senddata_old;

				char delims[] = ",";//设置以逗号为分割符
				char* result = NULL;
				result = strtok(rawsenddata[ithreadthree].data, delims);
				strcpy(senddata_old.MSG, result);
				result = strtok(NULL, delims);
				try {
					strcpy(senddata_old.type, result);
					//cout << "cdscjh: " << senddata_old.type;
				}
				catch (...) {
					//cout << "43处，类型3数据type出错" << endl;
					++ithreadthree;
					continue;
				}
				result = strtok(NULL, delims);
				strcpy(senddata_old.num3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.num4, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.ICAO, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.num6, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time1, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time2, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time4, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.GroundSpeed, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Track, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.VerticalRate, result);
				result = strtok(NULL, delims);
				//以上为类型4的数据，以下为类型3的数据

				strcpy(senddata_old.MSG3, result);
				result = strtok(NULL, delims);
				try {
					strcpy(senddata_old.type3, result);
				}
				catch (...) {
					//cout << "43处，类型3数据type3出错" << endl;
					++ithreadthree;
					continue;
				}
				result = strtok(NULL, delims);
				strcpy(senddata_old.num33, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.num43, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.ICAO3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.num63, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time13, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time23, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time33, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.time43, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Altitude3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Lat3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Long3, result);
				if (senddata_old.Long3[1] == '\0') {
					//cout << "43处，类型3数据出错" << endl;
					++ithreadthree;
					continue;
				}
				result = strtok(NULL, delims);
				strcpy(senddata_old.Alert3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.Emergency3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.SPI3, result);
				result = strtok(NULL, delims);
				strcpy(senddata_old.IsOnGround3, result);

				char icao[6];
				memcpy(icao, senddata_old.ICAO, 6);
				QString stricao(icao);
				//QString str1(senddata_old.GroundSpeed);
				//ui.textEdit->insertPlainText(str);
				ui.textEdit->append(stricao + QString::fromStdString(" , ") +
					QString::fromStdString(senddata_old.Altitude3) + QString::fromStdString(" , ") +
					QString::fromStdString(senddata_old.GroundSpeed) + QString::fromStdString(" , ") +
					QString::fromStdString(senddata_old.Track) + QString::fromStdString(" , ") +
					QString::fromStdString(senddata_old.Lat3) + QString::fromStdString(" , ") +
					QString::fromStdString(senddata_old.Long3));


				/***翻译数据***/    //出错是因为发送的数据出错了 如：（MSG,3,111,11111,7810A2,111111,2021/05/26,12:29:18.373,2021/05/26,12:29:18.373,,5450,,,,,,,0,0,0,0）
				Data_trainslat Translation_result = Translation(senddata_old.Long3, senddata_old.Lat3, senddata_old.Altitude3, senddata_old.Track, senddata_old.GroundSpeed);
				/***打包数据，准备发送***/
				senddata.Header = htonl(0xA5A5A5A5);
				senddata.track_num = htonl(0xA5A51111);
				senddata.time_of_updata = htonl(0x00000000);
				senddata.track_status = htons(0x00000000);
				senddata.track_att_2 = htons(0x00000001);
				senddata.track_att_3 = htons(0x00000001);
				senddata.tgt_rng = htons(Translation_result.tgt_rng);
				senddata.rdr_vel = (Translation_result.rdr_vel);
				senddata.tgt_az = (Translation_result.tgt_az);
				senddata.cruise_velocity = (Translation_result.cruise_velocity);
				senddata.cruise_heading = (Translation_result.cruise_heading);
				senddata.frm_number = htons(0xA5A5A5A5);
				senddata.target_ad = htons(0xA5A5A5A5);

				ui.textEdit_2->append(stricao + QString::fromStdString(" , ") + QString::number(senddata.tgt_rng) + QString::fromStdString(" , ") + QString::number(senddata.rdr_vel) + QString::fromStdString(" , ") +
					QString::number(senddata.tgt_az) + QString::fromStdString(" , ") + QString::number(senddata.cruise_velocity) + QString::fromStdString(" , ") + QString::number(senddata.cruise_heading));

				/***UDP发送数据***/
				//ui.ADSdata->setText("发送类型43数据");
				//cout << "发送类型43数据" << endl;
				sendto(iUDP, (char*)&senddata, sizeof(senddata), 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr));

			}
			++ithreadthree;
		}
	}
	_endthread();//关闭线程3
	return 0;
}