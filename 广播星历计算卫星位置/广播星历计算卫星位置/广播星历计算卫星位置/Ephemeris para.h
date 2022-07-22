#pragma once
#include<iostream>
using namespace std;
class Para
{
public:
	Para(){}

	int PRN;
	int year, month, day, hour, min, sec;
	double a0, a1, a2;//钟偏、钟速、钟漂
	double IODE, Crs, DeltaN, M0;//ORBIT1，星历发布时间，
	double Cuc, e, Cus, SqrtA;//ORBIT2
	double TOE, Cic, OMEGA, Cis;//ORBIT3
	double i0, Crc, omega, OMEGAdot;//ORBIT4
	double IDOT, L2C, GpsWeekNum, L2P;//ORBIT5
	double SatAccuracy, SatHealth, TGD, IODC;//ORBIT6
};

Para& Readfile();
double GetMJD(Para p);
double* Get_position(Para p);

