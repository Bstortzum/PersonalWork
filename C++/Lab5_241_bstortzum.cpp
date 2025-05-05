// Brian Stortzum
// 4/1/2025
// This is for lab 5 and its a employee data reader that uses C strings
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <cstring>
#include <cstdlib>
using namespace std;

//Define Constants
const int EMP_NAME_SIZE = 24;

struct EmpName {
    char nameFirst[EMP_NAME_SIZE];
    char nameLast[EMP_NAME_SIZE];
};

struct Employees {
    EmpName name;
    int days = 0;
    int sold = 0;
};


//Protoype functions
ifstream openInFile(); //Function to read file
void inputData(vector<Employees>& empVec);
void displayTitle();
void displayEmployees(const vector<Employees>& empVec);
void sortByLastName(vector<Employees>& empVec);

int main()
{
    // Set the iomanip values for double numbers
    cout << fixed << setprecision(2) << showpoint;

    // 
    displayTitle();

    // Makes an empty vector to get data and send it
    vector<Employees>empData;

    // Read Data from File
    inputData(empData);

    sortByLastName(empData);
    displayEmployees(empData);

    cout << "\nThank you for using the program\n";
    system("pause");
    return 0;
}

// This function find and input the data into the program
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

// This function puts the data into the embedded struct
void inputData(vector<Employees>& empVec) 
{
    ifstream fHandle;
    char tempFirst[EMP_NAME_SIZE];
    char tempLast[EMP_NAME_SIZE];
    char numDaySold[EMP_NAME_SIZE];
    Employees tempEmp;

    fHandle = openInFile();

    while (fHandle.getline(tempFirst, EMP_NAME_SIZE)) 
    {
        fHandle.getline(tempLast, EMP_NAME_SIZE);
        fHandle.getline(numDaySold, EMP_NAME_SIZE);
        tempEmp.days = atoi(numDaySold);
        fHandle.getline(numDaySold, EMP_NAME_SIZE);
        tempEmp.sold = atoi(numDaySold);

        strncpy_s(tempEmp.name.nameFirst, EMP_NAME_SIZE, tempFirst, EMP_NAME_SIZE);
        strncpy_s(tempEmp.name.nameLast, EMP_NAME_SIZE, tempLast, EMP_NAME_SIZE);
        empVec.push_back(tempEmp);
    }

    fHandle.close();
    cout << "\nThe number of Employees read is: " << empVec.size() << "\n\n";
}

// This function display the title
void displayTitle()
{
    cout << "IS-241 Lab 5 – C-Strings and Embedded Structures\n";
    cout << "This program reads in an employee file and displays the file in sorted order by last name.\n\n";
}

// This function display the data and sorts it by last name
void displayEmployees(const vector<Employees>& empVec)
{
    for (const Employees& emp : empVec)
    {
        double avg = emp.days == 0 ? 0 : static_cast<double>(emp.sold) / emp.days;
        cout << "Employee: " << emp.name.nameFirst << " " << emp.name.nameLast << " worked " << emp.days << " days and sold " << emp.sold << " units for an average of " << avg << " units per day.\n";
    }
}

// This function sorts the dat by last name
void sortByLastName(vector<Employees>& empVec)
{
    for (size_t i = 0; i < empVec.size() - 1; i++) 
    {
        size_t minIndex = i;
        for (size_t j = i + 1; j < empVec.size(); j++) 
        {
            if (strcmp(empVec[j].name.nameLast, empVec[minIndex].name.nameLast) < 0) 
            {
                minIndex = j;
            }
        }
        if (minIndex != i) 
        {
            swap(empVec[i], empVec[minIndex]);
        }
    }
}

