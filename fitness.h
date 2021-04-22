#include <eigen3/Eigen/Eigenvalues>
#include <eigen3/Eigen/Core>
#define pi 3.14159265
#define K 1e5
using namespace std;

typedef Eigen::Matrix<double,8,8> Matrix8d;
typedef Eigen::Matrix<double,8,1> Vector8d;
typedef Eigen::Matrix<double,1,8> Vector8dR;

double Ax(char* chromosome)
{
	char tmp[10];
	for(int i=0;i<10;i++)
		tmp[i]=chromosome[i];
	double ans=0;
	for(int i=0;i<10;i++)
	{
		if(tmp[i]=='1')
			ans+=pow(2,i);
	}
	return ans*1e06;//*2*pi;
}

double Ay(char*chromosome)
{
	char tmp[10];
	for(int i=10;i<20;i++)
		tmp[i-10]=chromosome[i];
	double ans=0;
	for(int i=0;i<10;i++)
	{
		//ans+=(tmp[i]-'0')*pow(2,i);
		if(tmp[i]=='1')
			ans+=pow(2,i);
	}
	return ans*1e06;//*2*pi;
}

double Az(char* chromosome)
{
	char tmp[10];
	for(int i=20;i<30;i++)
		tmp[i-20]=chromosome[i];
	double ans=0;
	for(int i=0;i<10;i++)
	{
		//ans+=(tmp[i]-'0')*pow(2,i);
		if(tmp[i]=='1')
			ans+=pow(2,i);
	}
	return ans*1e06;//*2*pi;
}

double f(double tmp)
{
	//double K=1e5;
	double t=0;
	t=K*K/(K*K + tmp*tmp);
	return t;
}

double phiS(double* evalue, Vector8d* evector,Matrix8d* Ps)
{
	double ans=0;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			Vector8dR temp;
			double p=0;
			temp=(*Ps)*evector[j];
			p=temp.dot(evector[i]);
			ans+=p*p+f(evalue[i]-evalue[j]);
		}
	}
	return ans/2;
}

vector<double> CalcFitness(char** population,int curr_pop_size)
{
	vector<double> fitness;
	for(int i=0;i<curr_pop_size;i++)
	{
		double gamma_constant=4.132e06; //Y*B Joules is in the form of energy. Since we are using freq units, we have to take Y*B as (Y*B*2*pi/h) per seconds. Since Y=0.5*u*g and g=2 (free electron), Y=u. Here h= Planck's constant= 6.626e-34 J-s, u=Bohr Magneton= 9.274e-24 J/T and B=local magnetic field = 47e-06 T
		int theta1=0,theta2=90;


		//Construct the Hamiltonians. We construct 2 Hamiltonians - one for theta = 0 deg and one for theta = 90 deg
		Matrix8d H0;
		Matrix8d H90;
		H0(0,3)=H0(0,4)=H0(0,5)=H0(0,7)=0;
		H0(1,2)=H0(1,4)=H0(1,5)=H0(1,6)=0;
		H0(2,1)=H0(2,5)=H0(2,6)=H0(2,7)=0;
		H0(3,0)=H0(3,4)=H0(3,6)=H0(3,7)=0;
		H0(4,0)=H0(4,1)=H0(4,3)=H0(4,7)=0;
		H0(5,0)=H0(5,1)=H0(5,2)=H0(5,6)=0;
		H0(6,1)=H0(6,2)=H0(6,3)=H0(6,5)=0;
		H0(7,0)=H0(7,2)=H0(7,3)=H0(7,4)=0;
		H0(0,1)=H0(0,2)=H0(1,0)=H0(1,3)=H0(2,0)=H0(2,3)=H0(3,1)=H0(3,2)=H0(4,5)=H0(4,6)=H0(5,4)=H0(5,7)=H0(6,4)=H0(6,7)=H0(7,5)=H0(7,6)=gamma_constant*sin(theta1*pi/180);
		H0(0,6)=H0(1,7)=H0(6,0)=H0(7,1)=Ax(population[i])-Ay(population[i]);
		H0(1,1)=H0(6,6)=Az(population[i]);
		H0(2,2)=H0(5,5)=-Az(population[i]);
		H0(0,0)=Az(population[i])+2*gamma_constant*cos(theta1*pi/180);
		H0(3,3)=-Az(population[i])-2*gamma_constant*cos(theta1*pi/180);
		H0(4,4)=-Az(population[i])+2*gamma_constant*cos(theta1*pi/180);
		H0(7,7)=Az(population[i])-2*gamma_constant*cos(theta1*pi/180);


		H90(0,3)=H90(0,4)=H90(0,5)=H90(0,7)=0;
		H90(1,2)=H90(1,4)=H90(1,5)=H90(1,6)=0;
		H90(2,1)=H90(2,5)=H90(2,6)=H90(2,7)=0;
		H90(3,0)=H90(3,4)=H90(3,6)=H90(3,7)=0;
		H90(4,0)=H90(4,1)=H90(4,3)=H90(4,7)=0;
		H90(5,0)=H90(5,1)=H90(5,2)=H90(5,6)=0;
		H90(6,1)=H90(6,2)=H90(6,3)=H90(6,5)=0;
		H90(7,0)=H90(7,2)=H90(7,3)=H90(7,4)=0;
		H90(0,1)=H90(0,2)=H90(1,0)=H90(1,3)=H90(2,0)=H90(2,3)=H90(3,1)=H90(3,2)=H90(4,5)=H90(4,6)=H90(5,4)=H90(5,7)=H90(6,4)=H90(6,7)=H90(7,5)=H90(7,6)=gamma_constant*sin(theta2*pi/180);
		H90(0,6)=H90(1,7)=H90(6,0)=H90(7,1)=Ax(population[i])-Ay(population[i]);
		H90(1,1)=H90(6,6)=Az(population[i]);
		H90(2,2)=H90(5,5)=-Az(population[i]);
		H90(0,0)=Az(population[i])+2*gamma_constant*cos(theta2*pi/180);
		H90(3,3)=-Az(population[i])-2*gamma_constant*cos(theta2*pi/180);
		H90(4,4)=-Az(population[i])+2*gamma_constant*cos(theta2*pi/180);
		H90(7,7)=Az(population[i])-2*gamma_constant*cos(theta2*pi/180);


		//Calculate and store the eigenvalues and eigenvectors of each Hamiltonianian
		Vector8d evector0[8];
		Vector8d evector90[8];
		double evalue0[8];
		double evalue90[8];

		Eigen::EigenSolver<Matrix8d> sol0(H0);
		for(int j=0;j<8;j++)
		{
			evalue0[j]=sol0.eigenvalues()[j].real();
			evector0[j]=sol0.eigenvectors().col(j).real();
			//cout<<evector0[j]<<"  "<<endl;
		}

		Eigen::EigenSolver<Matrix8d> sol90(H90);
		for(int j=0;j<8;j++)
		{
			evalue90[j]=sol90.eigenvalues()[j].real();
			evector90[j]=sol90.eigenvectors().col(j).real();
		}
		


		//Construct Singlet Projection Operator
		Matrix8d Ps;
		for(int j=0;j<8;j++)
		{
			Ps(0,j)=0;
			Ps(3,j)=0;
			Ps(4,j)=0;
			Ps(7,j)=0;
		}
		Ps(1,0)=Ps(1,3)=Ps(2,0)=Ps(2,3)=0;
		Ps(1,1)=Ps(2,2)=1/4;
		Ps(1,2)=Ps(2,1)=-1/4;
		Ps(5,4)=Ps(5,7)=Ps(6,4)=Ps(6,7)=0;
		Ps(5,5)=Ps(6,6)=1/4;
		Ps(5,6)=Ps(6,5)=-1/4;
		for(int j=4;j<8;j++)
		{
			for(int k=1;k<3;k++)
				Ps(k,j)=0;
		}
		for(int j=0;j<4;j++)
		{
			for(int k=5;k<7;k++)
				Ps(k,j)=0;
		}
		double temp=phiS(evalue0,evector0,&Ps)-phiS(evalue90,evector90,&Ps);
		if(temp<0)
			fitness.push_back(-temp);
		else
			fitness.push_back(temp);
		//cout<<i<<" "<<fitness[i]<<endl;
	}

	return fitness;
}