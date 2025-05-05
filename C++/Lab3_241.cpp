// Brian Stortzum
// 3/4/2025
// This program is a search and sort function for lab 3
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


// This is the structure for the function
struct items
{
	string name = "name";
	double sales = 0;
};

// Declare Constants
const int SORT = 1; // These valuse works with the menu
const int SEARCH = 2;
const int DISPLAY = 3;
const int WRITE = 4;
const int END = 5;
const int NUMBER = 2;
const int NAME = 1;

//Prototype functions
ifstream openInFile(); //Function to read file
ofstream openOutFile(); // Function to write file
void inputData(vector<items>& iteVec);
void outputData(vector<items>iteVec);
void selectionSortAlphabet(vector<items>& iteVec, int size);
void selectionSortSales(vector<items>& iteVec, int size);
void swap(items& a, items& b);
void searchItem(vector<items>& iteVec);
string toLower(string str);
int main();

int main()
{
	
    //declare varables
    int value = 0;
    
    // Makes an empty vector to get data and send it
    vector<items>itemData;
   
    // Read Data from File
    inputData(itemData);
    
    // Incase there is no data
    if (itemData.empty())
    {
        cout << "There was no data Given" << endl;
        system("pause");
        return 0;
    }


    do //Display the menu to the customer
    {
        cout << "\nWelcome to the IS-241 Search and Sort Program\n";
        cout << "Please select from the menu below:\n";
        cout << "1. Sort the data\n";
        cout << "2. Search for an Item\n";
        cout << "3. Display the data in sorted order\n";
        cout << "4. Write the data in sorted order\n";
        cout << "5. End the Program\n";
        cout << "\nEnter selection here: ";
        cin >> value;
   

        switch (value)
        {
        case SORT: //The user is sort the data
        {
            int sortStyle;
            cout << "Sort Menu\n";  //Determine paper size
            cout << "Please select from the menu below:\n";
            cout << "1. Sort the data alphabetically\n";
            cout << "2. Sort the data by the highest sales\n";
            cout << "Enter selection here: ";
            cin >> sortStyle;
            while (sortStyle < NAME || sortStyle > NUMBER) //Loop until valid value is entered
            {
                cout << "Sort Menu\n";
                cout << "Please select from the menu below:\n";
                cout << "1. Sort the data alphabetically\n";
                cout << "2. Sort the data by the highest sales\n";
                cout << "Enter selection here: ";
                cin >> sortStyle;
            }
            if (sortStyle == NAME)  //Specify the sort style
            {
                selectionSortAlphabet(itemData, itemData.size());
            }
            else
            {
                selectionSortSales(itemData, itemData.size());
            }
            break;
        }
        case SEARCH: //The user is searching for items
        {
            selectionSortAlphabet(itemData, itemData.size());
            searchItem(itemData);
            break;
        }
        case DISPLAY: //The user is displaying the vector
        {
            cout << right << setw(18) << "Sales List:" << endl;
            cout << setw(20) << left << "Item:" << setw(15) << "Units Sold:" << endl;
            cout << setw(20) << left << "-----" << "-----------" << endl;

            for (const items& item : itemData)
            {
                cout << setw(20) << left << item.name << right << setw(6) << item.sales << endl;
            }

            break;
        }
        case WRITE: //The user is writing a file
        {
            cin.ignore();

            outputData(itemData);

            cout << "\nData written to file successfully!" << endl;
            break;
        }
        }
    } while (value != END);


	cout << "Thank you for using my program!\n";
	system("pause");
	return 0;
}

// This Fuction finds the file you are looking for and opens it
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

// This Fuction finds the file you are looking to change and opens it
ofstream openOutFile()
{
    string fName;
    ofstream fHandle;
    do
    {
        cout << "Enter output file name and path: ";
        getline(cin, fName);
        fHandle.open(fName);
        if (!fHandle)
        {
            cout << "Error - File could not be found. Please Reenter!\n\n";
        }
    } while (!fHandle);
    return fHandle;
}

// This function puts the data from the input file and puts into a vector
void inputData(vector<items>& iteVec)
{
    string tempName;
    string tempSales;
    items tempItems;
    ifstream fHandle;
    fHandle = openInFile();

    while (getline(fHandle, tempName))
    {
        getline(fHandle, tempSales);
        tempItems.name = tempName;
        tempItems.sales = stod(tempSales);
        iteVec.push_back(tempItems);
    }

    fHandle.close();

}

// This function puts the change data from the program and puts into a the desired output file
void outputData(vector<items>iteVec)
{
    string tempName;
    string tempSales;
    items tempItems;
    ofstream fHandle;
    fHandle = openOutFile();

    for (items tempItems : iteVec)
    {
        fHandle << tempItems.name << endl;
        fHandle << tempItems.sales << endl;
    }

    fHandle.close();
}

// This function assist the sort function
void swap(items& a, items& b)
{
    items temp = a;
    a = b;
    b = temp;
}

// This Function sorts the vector by Alphabetical order
void selectionSortAlphabet(vector<items>& iteVec, int size)
{
    int minIndex;
    items minValue;

    for (int start = 0; start < (size - 1); start++)
    {
        minIndex = start;
        minValue = iteVec[start];  // Get the actual value at 'start'

        for (int index = start + 1; index < size; index++)
        {
            if (iteVec[index].name < minValue.name)  // Alphabetical order
            {
                minValue = iteVec[index];
                minIndex = index;
            }
        }
        swap(iteVec[start], iteVec[minIndex]);  // Swap within the same vector
    }
}

// This Function sorts the vector to highest sales
void selectionSortSales(vector<items>& iteVec, int size)
{
    int maxIndex;
    items maxValue;

    for (int start = 0; start < size - 1; start++)
    {
        maxIndex = start;
        maxValue = iteVec[start];

        for (int index = start + 1; index < size; index++)
        {
            if (iteVec[index].sales > maxValue.sales)  // Highest first
            {
                maxValue = iteVec[index];
                maxIndex = index;
            }
        }
        swap(iteVec[start], iteVec[maxIndex]);
    }
}

// This lowercase all the value from the data and the input so its not case senitive
string toLower(string str)
{
    for (char& c : str)
    {
        c = tolower(c);
    }
    return str;
}

// This function searches for the item on the data table
void searchItem(vector<items>& iteVec)
{
    string searchName;
    cout << "Please enter the name of the item you are looking for: ";
    cin.ignore();  // Clear leftover newline
    getline(cin, searchName);
    searchName = toLower(searchName);  // Case-insensitive search

    int downItem = 0;
    int upItem = iteVec.size() - 1;
    bool foundItem = false;

    while (downItem <= upItem)
    {
        int Item = (downItem + upItem) / 2;

        string currentItemName = toLower(iteVec[Item].name);  // Also lowercase the item name

        if (currentItemName == searchName)
        {
            cout << "Item found: " << iteVec[Item].name << " - Sold Units: " << iteVec[Item].sales << endl;
            foundItem = true;
            break;
        }
        else if (currentItemName > searchName)
        {
            upItem = Item - 1;
        }
        else
        {
            downItem = Item + 1;
        }
    }

    if (!foundItem)
    {
        cout << "Error: Item '" << searchName << "' was not found in inventory.\n";
    }
}

