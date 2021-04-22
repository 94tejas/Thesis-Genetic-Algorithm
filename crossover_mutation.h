
void Crossover(char** population,int curr_pop_size) //Two-point crossover. Since 3 variables of 10-bytes each are involved, the cross-over points are at 4 bytes and 6 bytes for each variable.
{
	int k=0,count=0;
	cout<<"Crossover()"<<endl;
	while(k<curr_pop_size-1)
	{
		char tmp[7];
		for(int i=0;i<4;i++)
		{
			tmp[i]=population[k][i];
			population[k][i]=population[k+1][i];
			population[k+1][i]=tmp[i];
		}
		for(int i=7;i<10;i++)
		{
			tmp[i-3]=population[k][i];
			population[k][i]=population[k+1][i];
			population[k+1][i]=tmp[i-3];
		}
		for(int i=0;i<4;i++)
		{
			tmp[i]=population[k][i+10];
			population[k][i+10]=population[k+1][i+10];
			population[k+1][i+10]=tmp[i];
		}
		for(int i=7;i<10;i++)
		{
			tmp[i-3]=population[k][i+10];
			population[k][i+10]=population[k+1][i+10];
			population[k+1][i+10]=tmp[i-3];
		}
		for(int i=0;i<4;i++)
		{
			tmp[i]=population[k][i+20];
			population[k][i+20]=population[k+1][i+20];
			population[k+1][i+20]=tmp[i];
		}
		for(int i=7;i<10;i++)
		{
			tmp[i-3]=population[k][i+20];
			population[k][i+20]=population[k+1][i+20];
			population[k+1][i+20]=tmp[i-3];
		}
		k+=2;
	}
}

void Mutation(char** population,int curr_pop_size) //Mutation has 5% probability of happening for each generation
{
	srand(clock());
	if(rand()%100<=5)
	{
		cout<<"Mutation()"<<endl;
		for(int i=0;i<curr_pop_size/50;i++)
		{
			if(population[rand()%curr_pop_size][rand()%30]=='0')
				population[rand()%curr_pop_size][rand()%30]='1';
			else
				population[rand()%curr_pop_size][rand()%30]='0';
		}
	}	
}