#include<iostream>
#include<iomanip>
#include "Ephemeris para.h"
#include<math.h>
using namespace std;

#define GM 3.986005E14
#define we 7.292115e-5

int main()
{
	Para p;
	p=Readfile();

	double *p1;
	p1 = Get_position(p);
	double X = p1[0] * cos(p1[2]) - p1[1] * cos(p1[3])*sin(p1[2]);
	double Y = p1[0] * sin(p1[2]) + p1[1] * cos(p1[3])*cos(p1[2]);
	double Z = p1[1] * sin(p1[3]);

	cout << setiosflags(ios_base::left) << setw(10);
	cout << "卫星平面位置：" << endl;
	cout << "x=" << setiosflags(ios_base::left) 
		<<setiosflags(ios_base::fixed)<< setw(10) << p1[0] << endl;
	cout << "y=" << setiosflags(ios_base::left) <<
		setiosflags(ios_base::fixed)<<setw(10) << p1[1] << endl;
	cout << "卫星地球坐标系坐标：" << endl;
	cout << "X=" << setiosflags(ios_base::left) <<
		setiosflags(ios_base::fixed)<<setw(10) << X << endl;
	cout << "Y=" << setiosflags(ios_base::left) <<
		setiosflags(ios_base::fixed)<<setw(10) << Y << endl;
	cout << "Z=" << setiosflags(ios_base::left) <<
		setiosflags(ios_base::fixed) << setw(10) << Z << endl;

	system("pause");
	return 0;
}



double* Get_position(Para p)
{
	double *position;
	position = new double[4];

	//计算平均角速度n
	double n0 = sqrt(GM) / pow(p.SqrtA, 3);
	double n = n0 + p.DeltaN;
	//计算平近点角
	double t_MJD = GetMJD(p);
	double delta_t = t_MJD - 44244;
	double week = floor(delta_t / 7.0);
	delta_t = delta_t - week * 7;	// 周内天数
	double t = round(delta_t * 86400);//GPS周内秒
	double tk = t - p.TOE;
	if (tk > 302400)
	{
		tk = tk - 604800;
	}
	else if (tk < -302400)
	{
		tk = tk + 604800;
	}
	double M = p.M0 + n * tk;
	//计算偏近点角
	double E = 1;
	double delta;
	do
	{
		double tempE = M + p.e*sin(E);
		delta = abs(E - tempE);
		E = tempE;
	} while (delta > 1e-5);
	//计算真近点角
	double f = atan(sqrt(1 - p.e*p.e)*sin(E) / (cos(E) - p.e));
	//计算升交角距
	double _u = p.omega + f;
	//计算卫星向径
	double _r = p.SqrtA*p.SqrtA*(1 - p.e*cos(E));
	//计算摄动改正项
	double th_u = p.Cuc*cos(2 * _u) + p.Cus*sin(2 * _u);
	double th_r = p.Crc*cos(2 * _u) + p.Crs*sin(2 * _u);
	double th_i = p.Cic*cos(2 * _u) + p.Cis*sin(2 * _u);
	//计算摄动改正
	double u = _u + th_u;
	double r = _r + th_r;
	double i = p.i0 + p.IDOT*tk + th_i;
	//计算卫星平面位置
	double x = r * cos(u);
	double y = r * sin(u);
	//计算升交点精度
	double L = p.OMEGA + (p.OMEGAdot - we)*t - p.OMEGAdot*p.TOE;

	position[0] = x; position[1] = y; position[2] = L; position[3] = i;
	return position;
}

double GetMJD(Para p)
{
	double JD = 1721013.5 + 367 * p.year - floor((p.year + floor((p.month + 9) / 12))*7.0 / 4.0) + p.day + p.hour / 24.0 + floor(275 * p.month / 9.0);
	double MJD = JD - 2400000.5;
	return MJD;
}