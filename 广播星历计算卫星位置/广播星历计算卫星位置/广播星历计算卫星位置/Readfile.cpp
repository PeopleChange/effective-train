#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include "Ephemeris para.h"
using namespace std;

template<class Type>
Type stringToDouble(string sstr)
{
	istringstream ist(sstr);
	double num;
	ist >> num;
	return num;
}

Para& Readfile()
{
	string filepath = "E:\\QQ文件\\导航课程\\GNSS\\第一次作业要求及数据\\brdc2530.18n";
	ifstream infile;
	infile.open(filepath);

	if (!infile)
	{
		cout << "文件打开失败" << endl;
	}

	vector<string> line;
	string strline;
	while (getline(infile, strline))
	{
		replace(strline.begin(), strline.end(), 'D', 'E');
	
		line.push_back(strline);
	}
	/*for (size_t i = 0; i < line.size(); i++)
	{
		cout << line[i] << endl;
	}*/

	Para p;
	stringstream word0(line[0]);
	word0 >> p.PRN>>p.year>>p.month>>p.day>>p.hour>>p.min>>
		p.sec>>p.a0>>p.a1>>p.a2;
	stringstream word1(line[1]);
	word1 >> p.IODE >> p.Crs >> p.DeltaN >> p.M0;
	stringstream word2(line[2]);
	word2 >> p.Cuc >> p.e >> p.Cus >> p.SqrtA;
	stringstream word3(line[3]);
	word3 >> p.TOE >> p.Cic >> p.OMEGA >> p.Cis;
	stringstream word4(line[4]);
	word4 >> p.i0 >> p.Crc >> p.omega >> p.OMEGAdot;
	stringstream word5(line[5]);
	word5 >> p.IDOT >> p.L2C >> p.GpsWeekNum >> p.L2P;
	stringstream word6(line[6]);
	word6 >> p.SatAccuracy >> p.SatHealth >> p.TGD >> p.IODC;

	infile.close();
	return p;
}

int GetRow(string file)
{
	ifstream infile;
	infile.open(file);
	string line;
	int n = 0;
	while (getline(infile, line))
	{
		n++;
	}
	infile.close();
	return n;
}
