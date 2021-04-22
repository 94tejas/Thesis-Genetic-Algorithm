
int findMax(vector<double>& fitness,int curr_pop_size)
{
	int imax=0;
	double max=-999999999;
	for(int i=0;i<curr_pop_size;i++)
	{
		if(fitness[i]>max)
		{
			max=fitness[i];
			imax=i;
		}
	}
	//cout<<"MAX= "<<fitness[imax]<<" ";
	fitness[imax]=-99999999.00;
	//cout<<imax<<" ";
	return imax;
}

int findMin(vector<double>& fitness,int curr_pop_size)
{
	int imin=0,min=999999999;
	for(int i=0;i<curr_pop_size;i++)
	{
		if(fitness[i]<min && fitness[i]>0)
		{
			min=fitness[i];
			imin=i;
		}
	}
	//cout<<"MIN= "<<fitness[imin]<<" ";
	fitness[imin]=999999999;
	return imin;
}

void SurvivorSelection(char** old_population, char** new_population, vector<double> fitness,int curr_pop_size)
{
	vector<int> mating_pool;
	int count=0;
	while(count<2*curr_pop_size*4/10)
	{
		mating_pool.push_back(findMax(fitness,2*curr_pop_size));
		count++;
	}
	//cout<<endl;

	count=0;
	while(count<2*curr_pop_size/10)
	{
		mating_pool.push_back(findMin(fitness,2*curr_pop_size));
		count++;
	}
	//cout<<endl;

	//cout<<"sizeof mating_pool="<<mating_pool.size()<<endl;
	count=0;
	while(count<mating_pool.size())
	{
		for(int i=0;i<30;i++)
		{
			new_population[count][i]=old_population[mating_pool[count]][i];
		}
		count++;
	}
}