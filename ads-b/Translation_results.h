#pragma once
#include <string.h>
#include <iostream>
#define _USE_MATH_DEFINES //����piΪM_PI
#include <math.h>
#include <mat.h>
#include"global_variable.h"
#include"translation_struct.h"
using namespace std;
/***��������***/

//��֪����(����Ĳ���Ϊ����ֵ)���״ﾭγ�ȣ��״�ecef����
#define radar_lon 100;
#define radar_lat 100;
#define radar_ecef_x 10000;
#define radar_ecef_y 10000;
#define radar_ecef_z 10000;
#define RadarAntenAzi 45;
#define RadarAntenElv 25;

////����M����M��������֪���״����Ψһȷ�������������������MATLAB���У���
//MATFile* pmatFile = matOpen("C:/Users/Administrator.DESKTOP-D4RD60B/Desktop/��Ŀ���/M.mat", "r");
//mxArray* pMxArray = matGetVariable(pmatFile, "M");
//double* MxArray_M = (double*)mxGetData(pMxArray);
//int M = mxGetM(pMxArray);
//int N = mxGetN(pMxArray);

/****����ECEF����*****/
Data_ECEF WGS84toECEF(double latitude, double longitude, double height) {
    Data_ECEF dataecef;
    double X;
    double Y;
    double Z;
    double a = 6378137.0;
    double b = 6356752.31424518;
    double E = (a * a - b * b) / (a * a);
    double COSLAT = cos(latitude * M_PI / 180);
    double SINLAT = sin(latitude * M_PI / 180);
    double COSLONG = cos(longitude * M_PI / 180);
    double SINLONG = sin(longitude * M_PI / 180);
    double N = a / (sqrt(1 - E * SINLAT * SINLAT));
    double NH = N + height;
    X = NH * COSLAT * COSLONG;
    Y = NH * COSLAT * SINLONG;
    Z = (b * b * N / (a * a) + height) * SINLAT;
    dataecef.x_tar = X;
    dataecef.y_tar = Y;
    dataecef.z_tar = Z;
    return dataecef;
}

Data_trainslat Translation(char* Long, char* Lat, char* Altitude, char* Track, char* GroundSpeed) {
    Data_trainslat result;
    double longitude = atof(Long);
    double latitude = atof(Lat);
    double height = atof(Altitude);
    double heading = atof(Track);
    double velocity = atof(GroundSpeed);
    //�������ϵ(WGS84����ϵ)->ecef����ϵ//
    //����Ŀ�꾭γ�ȸ߶ȼ�����ecef����ϵ������
    Data_ECEF dataecef_tar;
    dataecef_tar = WGS84toECEF(latitude, longitude, height);

    /************�����ػ��ѿ�������ϵ*********/
    //����˷� ����P_temp=M*[x_tar,y_tar,z_tar,1]  P_xyz=P_temp(1:3)'
    double P_x = MxArray_M[0] * dataecef_tar.x_tar + MxArray_M[1] * dataecef_tar.y_tar + MxArray_M[2] * dataecef_tar.z_tar + MxArray_M[3];
    double P_y = MxArray_M[4] * dataecef_tar.x_tar + MxArray_M[5] * dataecef_tar.y_tar + MxArray_M[6] * dataecef_tar.z_tar + MxArray_M[7];
    double P_z = MxArray_M[8] * dataecef_tar.x_tar + MxArray_M[9] * dataecef_tar.y_tar + MxArray_M[10] * dataecef_tar.z_tar + MxArray_M[11];

    //������
    //%% -- - ������룺r = sqrt(x ^ 2 + y ^ 2 + z ^ 2)
    //% %-- - ��λ�ǣ�theta = arctan(x / z)
    //% %-- - �����ǣ�phi = arcsin(y / r)
    //% %-- - Ŀ�꾶���ٶ����ػ����� * �����ǵõ�
    double r = sqrt(pow(P_x, 2) + pow(P_y, 2) + pow(P_z, 2));
    double theta = atan(P_x / P_z);
    double phi = asin(P_y / r);
    result.tgt_rng = (int)(r);//Ŀ�����
    result.rdr_vel = (float)(velocity * cos(phi));//�����ٶ�
    result.tgt_az = (float)theta;//Ŀ�귽λ
    result.cruise_velocity = (float)velocity;//�ػ�����
    result.cruise_heading = (float)heading;//�ػ����� 

    return result;
}

