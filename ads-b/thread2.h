#pragma once
#include"global_variable.h"
#include "tcpget.h"
//�߳�2����
//�����߳�1�б��������
DWORD WINAPI ThreadTwo(Ui::tcpgetClass lpParameter) {
	Ui::tcpgetClass ui = lpParameter;

	while (1) {
		//�߳�1�Ѿ��������ҵȴ���10s���߳�2Ҳ�˳�
		if (closethread == 1) {
			//cout << "�߳�2�˳�" << endl;
			break;
		}
		if (ithreadtwo < ithreadone || overflow == 1) {
			//�������
			if (ithreadtwo >= SIZEA) {
				ithreadtwo = ithreadtwo % SIZEA;
				overflow = 0;
			}
			//�������(Ҫ���͵����ݻ�����)
			if (irawsenddata >= SIZEA) {
				irawsenddata = irawsenddata % SIZEA;
				overflowrawsenddata = 1;
			}
			//�������Ϊ2��ֱ�Ӵ浽rawsenddata��
			if (threadonedata[ithreadtwo].data[4] == '2') {
				//ui.ADSdata->setText("�ҵ�������2����");
				//cout << "  �ҵ�������2���ݣ�" << endl;
				memcpy(&rawsenddata[irawsenddata].data, threadonedata[ithreadtwo].data, sizeof(threadonedata[ithreadtwo].data));
				++irawsenddata;
			}
			else {
				//����ҪôΪ3ҪôΪ4
				//����ȡICAO���������޶�Ӧ�ı�ţ��޾ʹ��죬�оͷŽ�ȥ�Ƚ�����
				char ICAO[7];
				strncpy(ICAO, &threadonedata[ithreadtwo].data[0] + 16, 6);
				ICAO[6] = '\0';
				if (connectdata.find(ICAO) == connectdata.end()) {
					//û���ҵ���ǰ��ICAO   ��ֱ�ӷŽ�ȥ�ȴ�ƴ��
					//cout << "���Ϊ��" << ICAO << "  �ҵ��˵�һ�����ڵȴ�ƴ�ӣ�" << endl;
					connectdata[ICAO] = threadonedata[ithreadtwo].data;
				}
				else if (connectdata[ICAO][4] == threadonedata[ithreadtwo].data[4]) {
					//�ҵ��ˣ�����������ͬ�ˣ��͸���֮ǰ�ģ�ɾ���ٷ��룩
					connectdata.erase(ICAO);
					//cout << "���Ϊ��"<<ICAO<<"  �ҵ��˵���������ͬ�ˣ��Ѹ��ǣ��ȴ�ƴ�ӣ�" << endl;
					connectdata[ICAO] = threadonedata[ithreadtwo].data;
				}
				else {
					//�ҵ��ˣ�������֮ǰ���Ͳ�ͬ
					//��ǰ���Ϊ����3(ƴ�Ӻ�ǰΪ4���ͣ���Ϊ3����)
					if (threadonedata[ithreadtwo].data[4] == '3') {
						//cout << "���Ϊ��" << ICAO << "  ���ڽ���43ƴ�ӣ�" << endl;
						char cjh[iSize] = "43";//��ƴ�Ӻ�����ݰ���ǰ��Ϊ43
						char cds[2] = ",";//ȷ��ƴ�ӵ��м��ɶ��Ÿ���
						//��ʼƴ��
						strcat(cjh, connectdata[ICAO]);
						strcat(cjh, cds);
						strcat(cjh, threadonedata[ithreadtwo].data);
						//����rawsenddata
						memcpy(&rawsenddata[irawsenddata].data, cjh, sizeof(cjh));
						//����map�������ʹ���´��ܹ�ƴ��
						connectdata.erase(ICAO);
						++irawsenddata;
					}
					else {
						//��ǰ����Ϊ4(ƴ�Ӻ�ǰΪ4���ͣ���Ϊ3����)
						//cout << "���Ϊ��" << ICAO << "  ���ڽ���34ƴ�ӣ�" << endl;
						char cjh[iSize] = "34";// ��ƴ�Ӻ�����ݰ���ǰ��Ϊ34
						char cds[2] = ",";
						//��ʼƴ��
						strcat(cjh, connectdata[ICAO]);
						strcat(cjh, cds);
						strcat(cjh, threadonedata[ithreadtwo].data);
						//����rawsenddata
						memcpy(&rawsenddata[irawsenddata].data, cjh, sizeof(cjh));
						//����map�������ʹ���´��ܹ�ƴ��
						connectdata.erase(ICAO);
						++irawsenddata;
					}
				}
			}
			++ithreadtwo;
		}
	}
	Sleep(10);//�ȴ�10S���߳�3��ʱ�����
	closethread2 = 1;
	_endthread();//�����߳�2
	return 0;
}

