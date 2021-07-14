#pragma once
#include"global_variable.h"
#include "tcpget.h"
//线程2函数
//处理线程1中保存的数据
DWORD WINAPI ThreadTwo(Ui::tcpgetClass lpParameter) {
	Ui::tcpgetClass ui = lpParameter;

	while (1) {
		//线程1已经结束并且等待了10s，线程2也退出
		if (closethread == 1) {
			//cout << "线程2退出" << endl;
			break;
		}
		if (ithreadtwo < ithreadone || overflow == 1) {
			//溢出控制
			if (ithreadtwo >= SIZEA) {
				ithreadtwo = ithreadtwo % SIZEA;
				overflow = 0;
			}
			//溢出控制(要发送的数据缓存区)
			if (irawsenddata >= SIZEA) {
				irawsenddata = irawsenddata % SIZEA;
				overflowrawsenddata = 1;
			}
			//如果类型为2，直接存到rawsenddata中
			if (threadonedata[ithreadtwo].data[4] == '2') {
				//ui.ADSdata->setText("找到了类型2数据");
				//cout << "  找到了类型2数据！" << endl;
				memcpy(&rawsenddata[irawsenddata].data, threadonedata[ithreadtwo].data, sizeof(threadonedata[ithreadtwo].data));
				++irawsenddata;
			}
			else {
				//类型要么为3要么为4
				//先提取ICAO，查找有无对应的编号，无就创造，有就放进去比较类型
				char ICAO[7];
				strncpy(ICAO, &threadonedata[ithreadtwo].data[0] + 16, 6);
				ICAO[6] = '\0';
				if (connectdata.find(ICAO) == connectdata.end()) {
					//没有找到当前的ICAO   就直接放进去等待拼接
					//cout << "编号为：" << ICAO << "  找到了第一段正在等待拼接！" << endl;
					connectdata[ICAO] = threadonedata[ithreadtwo].data;
				}
				else if (connectdata[ICAO][4] == threadonedata[ithreadtwo].data[4]) {
					//找到了，但是类型相同了，就覆盖之前的（删除再放入）
					connectdata.erase(ICAO);
					//cout << "编号为："<<ICAO<<"  找到了但是类似相同了，已覆盖，等待拼接！" << endl;
					connectdata[ICAO] = threadonedata[ithreadtwo].data;
				}
				else {
					//找到了，而且与之前类型不同
					//当前这个为类型3(拼接后前为4类型，后为3类型)
					if (threadonedata[ithreadtwo].data[4] == '3') {
						//cout << "编号为：" << ICAO << "  正在进行43拼接！" << endl;
						char cjh[iSize] = "43";//在拼接后的数据包最前面为43
						char cds[2] = ",";//确保拼接的中间由逗号隔开
						//开始拼接
						strcat(cjh, connectdata[ICAO]);
						strcat(cjh, cds);
						strcat(cjh, threadonedata[ithreadtwo].data);
						//存入rawsenddata
						memcpy(&rawsenddata[irawsenddata].data, cjh, sizeof(cjh));
						//消除map里的数据使得下次能够拼接
						connectdata.erase(ICAO);
						++irawsenddata;
					}
					else {
						//当前类型为4(拼接后前为4类型，后为3类型)
						//cout << "编号为：" << ICAO << "  正在进行34拼接！" << endl;
						char cjh[iSize] = "34";// 在拼接后的数据包最前面为34
						char cds[2] = ",";
						//开始拼接
						strcat(cjh, connectdata[ICAO]);
						strcat(cjh, cds);
						strcat(cjh, threadonedata[ithreadtwo].data);
						//存入rawsenddata
						memcpy(&rawsenddata[irawsenddata].data, cjh, sizeof(cjh));
						//消除map里的数据使得下次能够拼接
						connectdata.erase(ICAO);
						++irawsenddata;
					}
				}
			}
			++ithreadtwo;
		}
	}
	Sleep(10);//等待10S让线程3有时间完成
	closethread2 = 1;
	_endthread();//结束线程2
	return 0;
}

