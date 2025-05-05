// Brian Stortzum
// 03/11/25
// This program is for lab 4, it's a washing/drying machine tracker that uses Pointers and dynamic Allocation memory
#include<iostream>
#include<iomanip>
using namespace std;

// Delcare Constants
const double WASH_COST = 3.56;
const double DRY_COST = 2.99;
const double DAILY_COST = 97.00;


//Prototype Functions
double washAvg(int* loads, int days);
int howManyDryerLoads(int* loads, int days);
double calcRev(int* loads, int days);
bool profit(int loads);
int findMaxLoadDay(int* loads, int days, int& maxLoads);
int totalLoadsWashed(int* loads, int days);
int main();


int main()
{
	//Set up my iomanip statment
	cout << fixed << setprecision(1) << showpoint;

	// Declare Varables
	int days;
	int profitableDays = 0;
	int maxLoads;
	int maxDay;
	//Display menu
	cout << "IS-241 Lab 4 - Pointers" << endl;
	cout << right << setw(57) << "Welcome to the IS-241 Laundromat Profit Calulator" << endl;
	cout << endl;
	do 
{
		cout << "Enter the number of days: ";
		cin >> days;
		if (days < 0)
		{
			cout << "The number of days must be greater than 0; Please reenter: ";
			cin >> days;
		}
	} while (days < 0);
	
	// To get a value of days and put it in a dynamic array
	int* loads = new int[days];
	
	for (int i = 0; i < days; i++) 
	{
		cout << "Enter the number of loads washed for day " << (i + 1) << ": ";
		cin >> *(loads + i);

		while (*(loads + i) < 0 || *(loads + i) > 35) 
		{
			if (*(loads + i) < 0) 
			{
				cout << "Negative number entered. Please reenter: ";
			}
			else 
			{
				cout << "Number can't be greater than 35, Please reenter: ";
			}
			cin >> *(loads + i);
		}
	}

	// Prints the total loads washed of the the number of days
	int totalLoads = totalLoadsWashed(loads, days);
	cout << "\nThe total number of loads washed is " << totalLoads << endl;

	// Prints the avg amount of loads per day
	double avgLoads = washAvg(loads, days);
	cout << "The average loads per day is " << avgLoads << endl;

	// Print the total Dryer loads
	int totalDryerLoads = howManyDryerLoads(loads, days);
	cout << "\nThe total number of dryer loads is " << totalDryerLoads << endl;
	cout << "The average dryer loads per day is " << (double)totalDryerLoads / days << endl;

	// Prints the Revuenue out of all of the days
	double revenue = calcRev(loads, days);
	cout << "\nThe total revenue generated is $" << setprecision(2) << revenue << endl;
	
	// Finds the most profitable days
	for (int i = 0; i < days; i++) 
	{
		if (profit(*(loads + i))) 
		{
			profitableDays++;
		}
	}
	cout << "\nThere were " << profitableDays << " days in which the laundromat made a profit!" << endl;

	// Prints out the Most loads in one day
	maxDay = findMaxLoadDay(loads, days, maxLoads);
	cout << "\nThe day with the highest washer loads was day " << maxDay << " with " << maxLoads << " loads." << endl;

	delete[] loads;
	
	system("pause");
	return 0;
}

// This Function
double washAvg(int* loads, int days)
{
	int total = 0;
	for (int i = 0; i < days; i++)
	{
		total += *(loads + i);
	}
	return (double)total / days;
}

// This Function 
int howManyDryerLoads(int* loads, int days)
{
	int totalDryerLoads = 0;
	for (int i = 0; i < days; i++)
	{
		totalDryerLoads += (*(loads + i) + 2) / 3;
	}
	return totalDryerLoads;
}

// This Function Calcuates the Rev of the 14 days
double calcRev(int* loads, int days)
{
	double revenue = 0;
	for (int i = 0; i < days; i++) 
	{
		revenue += *(loads + i) * WASH_COST;
		revenue += ((*(loads + i) + 2) / 3) * DRY_COST;
	}
	return revenue;
}

//This Function calcuates if there was profit or not
bool profit(int loads)
{
	double dailyRevenue = (loads * WASH_COST) + (((loads + 2) / 3) * DRY_COST);
	return dailyRevenue >= DAILY_COST;
}

//This function finds the day that had the most loads
int findMaxLoadDay(int* loads, int days, int& maxLoads) 
{
	int maxDay = 1;
	maxLoads = *loads;
	for (int i = 1; i < days; i++)
	{
		if (*(loads + i) > maxLoads)
		{
			maxLoads = *(loads + i);
			maxDay = i + 1;
		}
	}
	return maxDay;
}

// This function gives me the total loads washed
int totalLoadsWashed(int* loads, int days) 
{
	int total = 0;
	for (int i = 0; i < days; i++) 
	{
		total += *(loads + i);
	}
	return total;
}