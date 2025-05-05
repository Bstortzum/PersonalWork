// Brian Stortzum
// 2/20/2025
// This Program is for Lab 2 and it uses 1-D arrays and 2-D arrays
#include<iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

//Declare Constants
const int DAYS = 7;
const int INVITEMS = 3;


// Prototype functions
ifstream openInFile();
void inputData(string nameArray[], int salesArray[][DAYS]);
int main();
void disp2D(const string nameArray[], const int salesArray[][DAYS]);
void avgItemSold(const string nameArray[], const int salesArray[][DAYS]);
void lowAmoSold(const string nameArray[], const int salesArray[][DAYS]);
void maxAmoSold(const string nameArray[], const int salesArray[][DAYS]);
void mostMaxAmoSold(const string nameArray[], const int salesArray[][DAYS]);

int main()
{
    //Set up my iomanip statment
    cout << fixed << setprecision(1) << showpoint;

    // Declare varables
    string nameArray[INVITEMS]; // The 1-D Array
    int salesArray[INVITEMS][DAYS]; // The 2-D Array
    
    inputData(nameArray, salesArray);
    disp2D(nameArray, salesArray);
    avgItemSold(nameArray, salesArray);
    lowAmoSold(nameArray, salesArray);
    maxAmoSold(nameArray, salesArray);
    mostMaxAmoSold(nameArray, salesArray);

    system("pause");
    return 0;
}

// Opens the file that for the data that is needed
ifstream openInFile()
{
    string fName;
    ifstream fHandle;
    do
    {
        cout << "Enter input file name and path: ";
        getline(cin, fName);
        fHandle.open(fName);
        if (!fHandle)
        {
            cout << "Error - File could not be found. Please Reenter\n\n";
        }
    } while (!fHandle);
    return fHandle;
}

// This Function gets the data from the file and puts into the array
void inputData(string nameArray[], int salesArray[][DAYS])
{
    ifstream fHandle;
    fHandle = openInFile();

    for (int i = 0; i < INVITEMS; i++)
    {
        getline(fHandle, nameArray[i]);
        for (int j = 0; j < DAYS; j++)
        {
            fHandle >> salesArray[i][j];
        }
        fHandle.ignore();
    }

    fHandle.close();

}

// This function displayes the 2D array like the assignment wants it
void disp2D(const string nameArray[], const int salesArray[][DAYS])
{
    cout << left << setw(15) << "Name";
    for (int e = 1; e <= DAYS; e++) 
    {
        cout << right << setw(9) << "Day " << e;
    }

    cout << endl;
    cout << left << setw(15) << "-----";

    for (int h = 1; h <= DAYS; h++)
    {
        cout << right << setw(10) << "-----";
    }
    cout << endl;

    for (int i = 0; i < INVITEMS; i++) //outside loop
    {
        cout << left << setw(15) << nameArray[i];
        for (int j = 0; j < DAYS; j++) //Inside the loop
        {
            cout << right << setw(10) << salesArray[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// This Function gets the Average amount of items sold out of the seven days
void avgItemSold(const string nameArray[], const int salesArray[][DAYS])
{
    int sum = 0;
    double Avg;
    cout << right << "Name";
    cout << right << setw(20) << "Average Sold" << endl;
    cout << right << "-----";
    cout << right << setw(19) << "------------" << endl;

    for (int i = 0; i < INVITEMS; i++) // outside loop
    {
        sum = 0;  // Reset sum for each item
        for (int j = 0; j < DAYS; j++)
        {
            sum += salesArray[i][j]; // Sum all of the elements in the array
        }

        Avg = static_cast<double>(sum) / DAYS;

        cout << left << setw(15) << nameArray[i];
        cout << right << setw(10) << Avg << endl;

        cout << endl;
    }
}


// This function finds the lowest amount of an item sold in one day
void lowAmoSold(const string nameArray[], const int salesArray[][DAYS])
{
    int minSales = salesArray[0][0];
    string minItem = nameArray[0];
    int minDay = 1;

    // Loop through all items and days to find the lowest sales
    for (int i = 0; i < INVITEMS; i++) 
    {
        for (int j = 0; j < DAYS; j++) 
        {
            if (salesArray[i][j] < minSales) // If a lower sale is found
            {
                minSales = salesArray[i][j];
                minItem = nameArray[i];
                minDay = j + 1;
            }
        }
    }

    // Output results
    cout << "Item " << minItem << " sold the lowest amount " << minSales << ", on Day " << minDay << "." << endl;
    cout << endl;
}
// This function finds the highest amount of an item sold in one day
void maxAmoSold(const string nameArray[], const int salesArray[][DAYS])
{
    int maxSales = salesArray[0][0];
    string maxItem = nameArray[0];
    int minDay = 1;

    // Loop through all items and days to find the highest sales
    for (int i = 0; i < INVITEMS; i++)
    {
        for (int j = 0; j < DAYS; j++)
        {
            if (salesArray[i][j] > maxSales) // If a highest sale is found
            {
                maxSales = salesArray[i][j];
                maxItem = nameArray[i];
                minDay = j + 1;
            }
        }
    }

    // Output results
    cout << "Item " << maxItem << " sold the highest amount " << maxSales << ", on Day " << minDay << "." << endl;
    cout << endl;
}

// This function finds the highest amount of an item sold in the span of 7 days
void mostMaxAmoSold(const string nameArray[], const int salesArray[][DAYS])
{
    int maxDays = 0;
    string maxItem;
    int countDays = 0;

    // Loop through all items to calculate how many days they have the highest sales
    for (int i = 0; i < INVITEMS; i++) 
    {
        countDays = 0;  // Reset the count for each item

        for (int j = 0; j < DAYS; j++) 
        {
            int highestSales = salesArray[0][j];
            for (int k = 1; k < INVITEMS; k++) 
            {
                if (salesArray[k][j] > highestSales) 
                {
                    highestSales = salesArray[k][j];
                }
            }

            if (salesArray[i][j] == highestSales) 
            {
                countDays++;
            }
        }

        if (countDays > maxDays) 
        {
            maxDays = countDays;
            maxItem = nameArray[i];
        }
    }

    // Output results
    cout << "Item " << maxItem << " had the greatest number of days with the highest sales, " << maxDays << " days." << endl;
    cout << endl;
}
