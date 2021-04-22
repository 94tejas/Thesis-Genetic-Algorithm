#include <iostream>	
#include <vector>
#include <ctime>
#include <fstream>
#include "fitness.h"
#include "crossover_mutation.h"
#include "survivor_selection.h"

using namespace std;

vector<double> CalcFitness(char** population);
void  Crossover(char** population,vector<int> mating_pool);
void Mutation(char** population);

double total_fitness(vector<double>& fitness,int curr_pop_size)
{
	double t=0;
	for(int i=0;i<curr_pop_size;i++)
		t+=fitness[i];
	return t;
}

int MaxFitness(char** population,vector<double>& fitness,int curr_pop_size)
{
	double max=0;
	int imax=0;
	for(int i=0;i<curr_pop_size;i++)
	{
		if(fitness[i]>max)
		{
			max=fitness[i];
			imax=i;
		}
	}
	/*cout<<"Max fitness="<<max<<" ";
	cout<<"Ax="<<Ax(population[imax])<<" Ay="<<Ay(population[imax])<<" Az="<<Az(population[imax])<<endl;
	cout<<"Ax=";
	for(int i=0;i<10;i++)
		cout<<population[imax][i];
	cout<<" Ay=";
	for(int i=0;i<10;i++)
		cout<<population[imax][i+10];
	cout<<" Az=";
	for(int i=0;i<10;i++)
		cout<<population[imax][i+20];
	cout<<endl;
	cout<<imax<<"  "<<population[imax]<<endl;*/
	return imax;
}

double avg_fitness(vector<double>& fitness,int curr_pop_size)
{
	return total_fitness(fitness,curr_pop_size)/(double)curr_pop_size;
}

void PrintCurrentPop(char** population,int curr_pop_size)
{
	for(int i=0;i<curr_pop_size;i++)
		cout<<population[i]<<endl;
}

int main()
{
	//Allocate memory for the population at its initialize size MAX_POPULATION
	int MAX_POPULATION;
	cin>>MAX_POPULATION;
	int p=0,m=MAX_POPULATION;
	while(m>10)
	{
		m/=2;
		p++;
	}
	char** population[p+1];
	population[0]=(char**)malloc((MAX_POPULATION)*sizeof(char*));
	for(int i=0;i<MAX_POPULATION;i++)
		population[0][i]=(char*)malloc(31*sizeof(char));
	int curr_pop_size=MAX_POPULATION;

	//Create a filetream for storing output
	fstream ofile{"output.txt",ios::out};
	ofile<<"Initial population size="<<curr_pop_size<<endl<<"Gen   "<<"Avg F     "<<"Max F        "<<"Ax          Ay          Az        A"<<endl;;

	//Seed the random number generator to the system time
	srand(clock());

	//Initialize the population space with 1s and 0s randomly
	for(int i=0;i<curr_pop_size;i++)
	{
		for(int j=0;j<30;j++)
		{
			population[0][i][j]=(char)(rand()%2+48);
		}
		population[0][i][30]='\0';
	}

	vector<double> fitness;
	fitness=CalcFitness(population[0],curr_pop_size);
	double curr_fitness=avg_fitness(fitness,curr_pop_size);

	int count=0, gen=1;
	//cout<<"Generation 1 complete. Avg Fitness="<<avg_fitness(fitness,curr_pop_size)<<endl<<endl;
	//PrintCurrentPop(population[0],curr_pop_size);

	int max=MaxFitness(population[0],fitness,curr_pop_size);
	double A = 2*pi/pow((  pow(Ax(population[gen-1][max]),2)  +  pow(Ay(population[gen-1][max]),2)  +  pow(Az(population[gen-1][max]),2) ),0.5);
	ofile<<gen<<"   "<<curr_fitness<<"   "<<fitness[max]<<"    "<<Ax(population[gen-1][max])<<"   "<<Ay(population[gen-1][max])<<"   "<<Az(population[gen-1][max])<<"   "<<A<<endl;


	while(curr_pop_size>10) //Termination condition is when the size of the population falls to less than 10
	{

		curr_pop_size/=2;
		cout<<"curr_pop_size="<<curr_pop_size<<endl;
		population[gen]=(char**)malloc((curr_pop_size)*sizeof(char*));
		for(int i=0;i<curr_pop_size;i++)
			population[gen][i]=(char*)malloc(31*sizeof(char));

		for(int i=0;i<curr_pop_size;i++)
		{
			for(int j=0;j<30;j++)
			{
				population[gen][i][j]=(char)(rand()%2+48);
			}
			population[gen][i][30]='\0';
		}

		SurvivorSelection(population[gen-1],population[gen],fitness,curr_pop_size);
		Crossover(population[gen],curr_pop_size);
		Mutation(population[gen],curr_pop_size);
		fitness=CalcFitness(population[gen],curr_pop_size);
		curr_fitness=avg_fitness(fitness,curr_pop_size);

		gen++;
		cout<<"Generation "<<gen<<" complete. Avg Fitness="<<curr_fitness<<endl;
		max=MaxFitness(population[0],fitness,curr_pop_size);
		PrintCurrentPop(population[gen-1],curr_pop_size);
		cout<<endl<<endl;
		A = 2*pi/pow((  pow(Ax(population[gen-1][max]),2)  +  pow(Ay(population[gen-1][max]),2)  +  pow(Az(population[gen-1][max]),2) ),0.5);
		ofile<<gen<<"   "<<curr_fitness<<"   "<<fitness[max]<<"    "<<Ax(population[gen-1][max])<<"   "<<Ay(population[gen-1][max])<<"   "<<Az(population[gen-1][max])<<"   "<<A<<endl;

	}

	fstream Afile{"AvsK.txt",ios::out|ios::app};
	Afile<<A<<"    "<<K<<endl;

	PrintCurrentPop(population[gen-1],curr_pop_size);
	MaxFitness(population[gen-1],fitness,curr_pop_size);
	return 0;
}	