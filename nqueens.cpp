//============================================================================
// Name        : nqueens.cpp
// Author      : vivek darak
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void print(int ** b,int n,int *a){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << b[i][j] << " ";
        }
        cout << "\n";
    }

    cout<<endl<<endl<<"1-D Array is:[ ";

    for(int i=0;i<n;i++)
    {
    	cout<<a[i]<<" ";
    }
    cout<<"]";

}

void conv(int **b,int* a,int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(b[i][j] == 1)
			{
				a[j] = i;
			}
		}
	}
}


bool place(int** b,int r,int c,int n)
{
	for(int i=0;i<c;i++)
	{
		if(b[r][i])
		{
			return false;
		}
	}

	for(int i=r,j=c ; i >= 0 && j >= 0 ; i--,j-- )//upper diagonal
	{
		if(b[i][j])
		{
			return false;
		}
	}

	for(int i=r,j=c ; i < n && j >= 0 ; i++,j-- )//lower diagonal
		{
			if(b[i][j])
			{
				return false;
			}
		}

	return true;
}


bool solve(int **b,int q,int k)
{
	if(q >= k)
	{
		return true;
	}

	for(int i=0;i<k;i++)
	{
		if(place(b,i,q,k))
		{
			b[i][q]=1;
			if(solve(b,q+1,k))
			{
				return true;
			}
			b[i][q]= 0;
		}
	}
	return false;
}

int main()
{
	int n;
	int *a = new int[n];
	cout<<"Enter number of queens"<<endl;
	cin>>n;

	int** b = new int*[n];


	for(int i=0;i<n;i++)
	{
		b[i] = new int[n];
	}

	if(solve(b,0,n))
	{
		conv(b,a,n);
		print(b,n,a);
	}
	else
	{
		cout<<"solution not found";
	}

	delete(b);
	return 0;
}
