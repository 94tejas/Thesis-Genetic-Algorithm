#include <iostream>
#include <cmath>
#include <fstream>
#include "phiS.h"
using namespace std;

double CalcPhi(double Ax,double Ay,double Az,double theta1);

int main()
{
	double Ax,Ay,Az;

	cout<<"Enter Ax:"<<endl;
	cin>>Ax;

	cout<<"Enter Ay:"<<endl;
	cin>>Ay;

	cout<<"Enter Az:"<<endl;
	cin>>Az;

	double theta=0;

	fstream ofile {"phi.txt", ios::out};

	while(theta<=90)
	{
		ofile<<theta<<"   "<<CalcPhi(Ax,Ay,Az,theta)<<endl;
		theta+=0.1;
	}
	return 0;
}