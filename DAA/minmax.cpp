//============================================================================
// Name        : minmax.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<climits>
using namespace std;

void minmax(int *a,int low,int high,int* min,int* max)
{

	if(low == high)
	{
		if(*min > a[low])
		{
			*min = a[low];
		}
		if(*max < a[low])
		{
			*max = a[low];
		}


		return;
	}

	if((high - low) == 1 )
	{
		if(a[low] < a[high])
		{
			if(*min > a[low])
			{
				*min = a[low];
			}

			if(*max < a[high])
			{
				*max = a[high];
			}


		}
		else
		{
			if(*min > a[high])
			{
				*min = a[high];
			}

			if(*max < a[low])
			{
				*max = a[low];
			}


		}

		return;
	}

	int mid = (low + high)/2;
	cout<<"Elements- ";
	for(int i=low;i<=mid;i++)
				{
					cout<<a[i]<<" ";


				}





			cout<<"    ";
			cout<<"min- "<<*min<<"   ";
			cout<<"max- "<<*max<<endl<<endl;

			cout<<"Elements- ";

			for(int i=mid+1;i<=high;i++)
							{
								cout<<a[i]<<" ";


							}




						cout<<"    ";
						cout<<"min- "<<*min<<"   ";
						cout<<"max- "<<*max<<endl<<endl;


	minmax(a,low,mid,min,max);

	cout<<"Elements- ";
		for(int i=low;i<=mid;i++)
			{
				cout<<a[i]<<" ";


			}





		cout<<"    ";
		cout<<"min- "<<*min<<"   ";
		cout<<"max- "<<*max<<endl<<endl;



	minmax(a,mid+1,high,min,max);

	cout<<"Elements- ";

	for(int i=mid+1;i<=high;i++)
				{
					cout<<a[i]<<" ";


				}




			cout<<"    ";
			cout<<"min- "<<*min<<"   ";
			cout<<"max- "<<*max<<endl<<endl;

}

int main()
{
	int n;
	int *a=NULL;
	int min = INT_MAX;
	int max = INT_MIN;


	cout<<"Enter Number of Elements"<<endl;
	cin>>n;

	a = new int[n];

	cout<<"Enter the Elements"<<endl;

	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}

	cout<<"Elements are: ";
	for(int i=0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;


	minmax(a,0,n-1,&min,&max);

	cout<<"max-"<<max<<endl;
	cout<<"min-"<<min<<endl;


	return 0;
}


