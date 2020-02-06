//============================================================================
// Name        : optimal.cpp
// Author      : vivek
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class job
{
public:
	int size;
	string name;
};

class tape
{
public:
	int size;
	int job[10];
};

bool compare(job j1,job j2)
{
	return j1.size <= j2.size;
}

int optimal(job j[],tape t[],int n,int m,int size)
{

	double MRT=0;

	int i=0;
	int loop=0;
	int k=0;
	for( i=0;i<n;i++)
	{





		int sum=0;
		if(t[k].size >= j[i].size)
		{
			t[k].size = t[k].size - j[i].size;
			t[k].job[loop]=i;
		}
		else
		{
			cout<<endl<<"Space not available for job-";
			for(int v=i;v<n;v++)
			{
				cout<<j[v].name<<" ";
			}
			return -1;
		}

		cout<<endl<<"Job-"<<j[i].name<<" Allocated at tape"<<k;
		/*for(int jj=0;jj<=i;jj++)
		{
			sum+=j[jj].size;
		}
		cout<<sum<<endl<<endl;
		MRT+=sum;*/


		if(i == m-1)
		{
			loop++;
		}


		k = (k+1)%m;


	}

	for(int i=0;i<m;i++)
	{
		cout<<endl<<"Tape-"<<i<<"--";
		for(int jj=0;jj<=loop;jj++)
		{
			cout<<j[t[i].job[jj]].name<<" ";
		}
		cout<<endl;
	}

}

int main()
{
	int n;
	int m;
	int size;

	cout<<"Enter number of Tapes"<<endl;
	cin>>m;

	cout<<"Enter number of Jobs"<<endl;
	cin>>n;

	cout<<"Enter size of Tape"<<endl;
	cin>>size;



	job j[10];
	tape t[10];

	for(int z=0;z<m;z++)
		{
			t[z].size = size;
		}


	cout<<"Enter Size of Jobs"<<endl;

	for(int i=0;i<n;i++)
	{
		cout<<endl<<"Enter name"<<endl;
		cin>>j[i].name;
		cout<<endl<<"Enter Size"<<endl;
		cin>>j[i].size;

	}

	sort(j,j+n,compare);

	for(int i=0;i<n;i++)
		{
			//cout<<endl<<"Enter name"<<endl;
			cout<<endl<<j[i].name<<"-"<<j[i].size;

			//cin>>j[i].size;

		}

	optimal(j,t,n,m,size);

	/*for(int i=0;i<m;i++)
		{
			cout<<endl<<t[i].size<<endl;
		}*/






}


