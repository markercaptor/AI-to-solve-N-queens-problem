#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include<chrono>

using namespace std;
using namespace chrono;



#define SIZE 10
vector<vector<int>> arr[SIZE];
vector<vector<int>> replacment[SIZE];
int holder;
int count;
int iteration_count;
int fact(int n); 
  
int nCr(int n) 
{ 
    return fact(n) / (fact(2) * fact(n - 2)); 
} 
  
// Returns factorial of n 
int fact(int n) 
{ 
    int res = 1; 
    for (int i = 2; i <= n; i++) 
        res = res * i; 
    return res; 
} 



int fitness(vector<vector<int>> arr)
{
	int value = 0;
	for (int j = 0; j < arr.size(); j++)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i][j] == 1)
			{
				
				for (int x = j+1; x < arr.size(); x++)
				{
					if (arr[i][x] == 1)
					{
						value++;
					}
				}
				
				
				for (int x = 1; x < arr.size(); x++)
				{
					
					if ( (i-x) >= 0 && (j+x) < arr.size() )
					{
						if (arr[i-x][j+x] == 1)
						{
							value++;
						}
						
					}
					
					
					if ( (i+x) < arr.size() && (j+x) < arr.size() )
					{
						if (arr[i+x][j+x] == 1)
						{
							value++;
						}
					}
					
				}
				
			}
		}
		
	}
	
	return holder - value;
}

void repo(int x, int y, int n)
{
	int repo = arr[0].size();
	int mid = rand() % repo;
	vector<vector<int>> temp(repo, vector<int> (repo,0));
	
	for (int i = 0; i < repo; i++)
	{
		for (int j = 0; j < repo; j++)
		{
			if (i < mid)
			{
				temp[j][i] = arr[x][j][i];
			}
			else
			{
				temp[j][i] = arr[y][j][i];
			}
			
		}
	}
	
	if ((rand() % 5) == 1) 
	{
		
		int mutation = rand() % repo;
		for (int i = 0; i < repo; i++)
		{
			if (temp[i][mutation] == 1)
			{
				temp[i][mutation] = 0;
				temp[rand() % repo][mutation] = 1;
				
				break;
			}
		}
		
		
	}
	
	replacment[n] = temp;
}

int makerand()
{
	
	int sum = 0;
	int prob[SIZE];
	
	for (int i = 0; i < SIZE; i++)
	{
		sum += fitness(arr[i]);
		prob[i] = fitness(arr[i]);
	}
	
	int r = 0;
	
	if (sum != 0)
	{
		int r = rand() % sum;
	}
	
	for (int i = 0; i < SIZE; i++)
	{
		
		if (r<= prob[i])
		{
			return i;
		}
		r -= prob[i];
		
	}
	
	return 0;
	
}

void display(vector<vector<int>> arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		cout << "| ";
		for (int j = 0; j < arr.size(); j++)
		{
			cout << arr[i][j] << " | ";
		}
		cout << endl;
	}
	return;
}

void gA()
{
	int x = 0, y = 1;
	int found = 0, iterations = 0;
	int max = 0;
	
	for (int i = 0; i < arr[0].size(); i++)
	{
		max += i;
		
	}
	
	while (!found)
	{
		
		for (int i = 0; i < SIZE; i++)
		{
			x = makerand();
			y = makerand();
			
			if (y == x)
			{
				if (y == SIZE-1)
				{
					y--;
				}
				else
				{
					y++;
				}
				
				
			}
			
			for (int i = 0; i < SIZE; i++)
			{
				repo(x, y, i);
				
			}
		}
		
		
		for (int i = 0; i < SIZE; i++)
		{
			if (fitness(replacment[i]) >= fitness(arr[i]))
			{
				arr[i] = replacment[i];
				
			}
			
			
			if (fitness(arr[i]) == max)
			{
				cout << "Number of iterrations: " << iterations << endl;
				cout<<"Solution: "<<endl;
				display(arr[i]);
				found = 1;
				
			}
			
		}
		iterations++;
	}
	
}



int main()
{

	cout << "How many queens do you want: ";
	int n;
	cin >> n;
    holder = nCr(n);
	
	if(n ==2 || n == 3)
	{
		cout<< "There is no solution."<<endl;
		return 0;
	}
	

	vector<vector<int>> populate(n, vector<int> (n,0));
	

	srand (time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < populate.size(); j++)
		{
			populate[rand() % populate.size()][j] = 1;
		}
		arr[i] = populate;
		for (int j = 0; j < populate.size(); j++)
		{
			for (int t = 0; t < populate.size(); t++)
			{
				populate[j][t] = 0;
			}
		}
	}
	 auto start = high_resolution_clock::now();
	gA();
	 auto stop = high_resolution_clock::now();
	 
	  auto duration = duration_cast<milliseconds>(stop-start);
	 
	cout << "Execution Time: " << duration.count() << " milliseconds" << endl;
	
	return 0;
}