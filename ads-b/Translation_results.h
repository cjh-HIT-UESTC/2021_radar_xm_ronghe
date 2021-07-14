#pragma once
#include <string.h>
#include <iostream>
#define _USE_MATH_DEFINES //定义pi为M_PI
#include <math.h>
#include <mat.h>
#include"global_variable.h"
#include"translation_struct.h"
using namespace std;
/***翻译数据***/

//已知参数(下面的参数为假设值)：雷达经纬度，雷达ecef坐标
#define radar_lon 100;
#define radar_lat 100;
#define radar_ecef_x 10000;
#define radar_ecef_y 10000;
#define radar_ecef_z 10000;
#define RadarAntenAzi 45;
#define RadarAntenElv 25;

////导入M矩阵（M矩阵由已知的雷达参数唯一确定（具体产生方法根据MATLAB进行））
//MATFile* pmatFile = matOpen("C:/Users/Administrator.DESKTOP-D4RD60B/Desktop/项目相关/M.mat", "r");
//mxArray* pMxArray = matGetVariable(pmatFile, "M");
//double* MxArray_M = (double*)mxGetData(pMxArray);
//int M = mxGetM(pMxArray);
//int N = mxGetN(pMxArray);

/****计算ECEF坐标*****/
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
    //大地坐标系(WGS84坐标系)->ecef坐标系//
    //利用目标经纬度高度计算其ecef坐标系下坐标
    Data_ECEF dataecef_tar;
    dataecef_tar = WGS84toECEF(latitude, longitude, height);

    /************计算载机笛卡尔坐标系*********/
    //矩阵乘法 计算P_temp=M*[x_tar,y_tar,z_tar,1]  P_xyz=P_temp(1:3)'
    double P_x = MxArray_M[0] * dataecef_tar.x_tar + MxArray_M[1] * dataecef_tar.y_tar + MxArray_M[2] * dataecef_tar.z_tar + MxArray_M[3];
    double P_y = MxArray_M[4] * dataecef_tar.x_tar + MxArray_M[5] * dataecef_tar.y_tar + MxArray_M[6] * dataecef_tar.z_tar + MxArray_M[7];
    double P_z = MxArray_M[8] * dataecef_tar.x_tar + MxArray_M[9] * dataecef_tar.y_tar + MxArray_M[10] * dataecef_tar.z_tar + MxArray_M[11];

    //输出结果
    //%% -- - 径向距离：r = sqrt(x ^ 2 + y ^ 2 + z ^ 2)
    //% %-- - 方位角：theta = arctan(x / z)
    //% %-- - 俯仰角：phi = arcsin(y / r)
    //% %-- - 目标径向速度由载机航速 * 俯仰角得到
    double r = sqrt(pow(P_x, 2) + pow(P_y, 2) + pow(P_z, 2));
    double theta = atan(P_x / P_z);
    double phi = asin(P_y / r);
    result.tgt_rng = (int)(r);//目标距离
    result.rdr_vel = (float)(velocity * cos(phi));//径向速度
    result.tgt_az = (float)theta;//目标方位
    result.cruise_velocity = (float)velocity;//载机航速
    result.cruise_heading = (float)heading;//载机航向 

    return result;
}

