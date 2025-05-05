//Brian Stortzum
// 02/14/2025
//This is a bookstore vendor
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Items {
    string name = "name";
    double cost = 0;
    int inv = 0;
    int pur = 0;
};

//Define Menu Constants
const int INK = 1;
const int BACK = 2;
const int PAPER = 3;
const int PEN = 4;
const int QUIT = 5;
const int REAM = 1;
const int CASE = 2;

// Define Calculation Constants
const int BACK_DISC = 3;
const int PEN_DISC_1 = 5;
const int PEN_DISC_2 = 10;
const double PEN_1 = 0.10; //Discount for 6 - 10 pens
const double PEN_2 = 0.20; //Discount for > 10 pens
const double TAX = 0.06;  //Sales Tax Rate
const double DISC = 0.10; //Discount for 3 or more itemList[1]['cost']s

//Protoype functions
ifstream openInFile(); //Function to read file
ofstream openOutFile(); // Function to write file
void inputData(vector<Items>&iteVec);
int valInt(string itemStr, int invNum);
int main();
void outputData(vector<Items>iteVec);

int main()
{
    // Set the iomanip values for double numbers
    cout << fixed << setprecision(2) << showpoint;

    //Declare varables
    int item = 0; //item selected from menu
    int totalInk = 0;  //counters for each item
    int totalBack = 0;
    int totalReam = 0;
    int totalCase = 0;
    int totalPen = 0;
    int numItem = 0;
    double penCost = 0, packCost = 0, reamsCost = 0, casesCost = 0, inkCost = 0;
    double cost = 0;
    double totalCost = 0;
    double backCost = 0;
    double discount = 0;
    double totalPenCost = 0;
    double tax = 0;

    // Create an empty vector
    vector<Items>itemData;

    // Read Data from File
    inputData(itemData);
    // Incase there is no data
    if (itemData.empty())
    {
        cout << "There was no data Given" << endl;
    }
    // Giving varablie to do the cost caluation
    for (Items tempItems : itemData)
    {
        inkCost = itemData.at(0).cost;
        packCost = itemData.at(1).cost;
        reamsCost = itemData.at(2).cost;
        casesCost = itemData.at(3).cost;
        penCost = itemData.at(4).cost;
    }

    outputData(itemData);

    do //Display the menu to the customer
    {
        cout << "\nWelcome to the IS-241 Bookstore\n";
        cout << "Please select from the menu below:\n";
        cout << "\t1. Printer Ink\n";
        cout << "\t2. Backpacks\n";
        cout << "\t3. Printer Paper\n";
        cout << "\t4. Pens\n";
        cout << "\t5. Checkout\n";
        cout << "\nEnter selection here: ";
        cin >> item;
   

        switch (item)
        {
        case INK: //The customer is buying printer ink
        {
            numItem = valInt(itemData.at(0).name, itemData.at(0).inv);
            cost = numItem * inkCost;
            totalInk += numItem;
            cout << "The subtotal is: $" << setw(2) << cost << endl;
            break;
        }
        case BACK: //The customer is buying backpacks
        {
            numItem = valInt(itemData.at(1).name, itemData.at(1).inv);
            cost = numItem * packCost;
            totalBack += numItem;
            cout << "The subtotal is: $" << setw(2) << cost << endl;
            break;
        }
        case PAPER: //The customer is buying paper
        {
            cout << "\nPaper comes in two sizes\n";  //Determine paper size
            cout << "Please select from the menu below:\n";
            cout << "\t1. Ream\n";
            cout << "\t2. Case";
            int papSize;
            cout << "\nEnter selection here: ";
            cin >> papSize;
            while (papSize < 1 or papSize > 2) //Loop until valid value is entered
            {
                cout << "\nPaper comes in two sizes\n";
                cout << "Please select from the menu below:\n";
                cout << "\t1. Ream\n";
                cout << "\t2. Case\n";
                cout << "\nEnter selection here: ";
                cin >> papSize;
            }
            if (papSize == 1)  //Specify the paper size and get how many
            {
                numItem = valInt(itemData.at(2).name, itemData.at(2).inv);
                cost = numItem * reamsCost;
                totalReam += numItem;
            }
            else
            {
                numItem = valInt(itemData.at(3).name, itemData.at(3).inv);
                cost = numItem * casesCost;
                totalCase += numItem;
            }

            cout << "The subtotal is: $" << setw(2) << cost << endl;
            break;

        }
        case PEN: //The customer is buying pens
        {
            numItem = valInt(itemData.at(4).name, itemData.at(4).inv);
            if (numItem <= 5)  //Determine the price of the pens
            {
                cost = numItem * penCost;
                totalPen += numItem;
                cout << "The subtotal is: $" << setw(2) << cost << endl;
            }
            else if (numItem > 5 and numItem <= 10)
            {
                cost = numItem * PEN_1;
                totalPen += numItem;
                cout << "The subtotal is: $" << setw(2) << cost << endl;
            }
            else
            {
                cost = numItem * PEN_2;
                totalPen += numItem;
                cout << "The subtotal is : $" << setw(2) << cost << endl;
            }
            break;
        }
        case QUIT: // The customer has selected to checkout and end the session
        {
            // Determine total cost
            totalCost = totalInk * inkCost;
            if (totalBack < 3)
            {
                totalCost += totalBack * backCost;
            }
            else
            {
                discount = totalBack * packCost * DISC;
                backCost = (totalBack * packCost) - discount;
                totalCost += backCost;
                totalCost += totalReam * reamsCost;
                totalCost += totalCase * casesCost;
            }
            if (totalPen <= 5)
            {
                totalCost += totalPen * penCost;
                totalPenCost = penCost;
            }
            else if (totalPen > 5 and totalPen <= 10)
            {
                totalCost += totalPen * PEN_1;
                totalPenCost = PEN_1;
            }
            else
            {
                totalCost += totalPen * PEN_2;
                totalPenCost = PEN_2;
            }
            break;
        }
        }
    } while (item != QUIT);

        //Display the receipt - only display an item if the cutomer purchased the item

        cout << "\nReceipt:\n";
        if (totalInk > 0)
        {
            cout << totalInk << " printer ink(s) purchased for $" << setw(2) << totalInk * inkCost << endl;
        }
        if (totalBack > 0)
        {
            if (totalBack < 3)
            {
                cout << totalBack << " backpacks(s) purchased for $" << setw(2) << totalBack * packCost << endl;
            }
            else
            {
                cout << totalBack << " backpacks(s) purchased for $" << setw(2) << backCost << endl;
            }
        }
        if (totalReam > 0)
        {
            cout << totalReam << " ream(s) of paper purchased for $" << setw(2) << totalReam * REAM << endl;
        }
        if (totalCase > 0)
        {
            cout << totalCase << " case(s)of paper purchased for $" << setw(2) << totalCase * CASE << endl;
        }
        if (totalPen > 0)
        {
            cout << totalPen << " pen(s) purchased for $" << setw(2) << (totalPen * penCost) << endl;
        }
        //Display final subtotal, calculate and display the sales tax and display the final total
        cout << "\nThe subtotal cost is: $" << setw(2) << totalCost << endl;
        tax = totalCost * TAX;
        cout << "The total tax is: $" << setw(2) << tax << endl;
        cout << "\nThe final cost is: $" << setw(2) << totalCost + tax << endl;

        system("pause");
        cout << "\nThank you for using the program\n";
        return 0;
}

int valInt(string itemStr, int invNum)
{
    int num;
    cout << "Enter the number of " << itemStr << " to be purchased: ";
    cin >> num;
    while (num <= 0)
    {
        cout << ("\nError - must be a number greater than or equal to zero. Please reenter.\n");
        cout << "Enter the number of " << itemStr << " to be purchased: ";
        cin >> num;
    }
    while (num > invNum)
    {
        cout << "Error - the store only has " << invNum << " " << itemStr << ". Please reenter \n";
        cout << "Enter the number of " << itemStr << " to be purchased: ";
        cin >> num;
    }
    return num;
}

ifstream openInFile()
{
    string fName;
    ifstream fHandle;
    do
    {
        cout << "Enter file name and path: ";
        getline(cin, fName);
        fHandle.open(fName);
        if (!fHandle)
        {
            cout << "Error - File could not be found. Please Reenter\n\n";
        }
    } while (!fHandle);
    return fHandle;
}

ofstream openOutFile()
{
    string fName;
    ofstream fHandle;
    do
    {
        cout << "Enter file name and path: ";
        getline(cin, fName);
        fHandle.open(fName);
        if (!fHandle)
        {
            cout << "Error - File could not be found. Please Reenter!\n\n";
        }
    } while (!fHandle);
    return fHandle;
}

void inputData(vector<Items>& iteVec)
{
    string tempName;
    string tempCost;
    string tempInv;
    string tempPur;
    Items tempItems;
    ifstream fHandle;
    fHandle = openInFile();

    while (getline(fHandle, tempName))
    {
        getline(fHandle, tempCost);
        getline(fHandle, tempInv);
        getline(fHandle, tempPur);
        tempItems.name = tempName;
        tempItems.cost = stod(tempCost);
        tempItems.inv = stoi(tempInv);
        tempItems.pur = stoi(tempPur);
        iteVec.push_back(tempItems);
    }

    fHandle.close();

}

void outputData(vector<Items>iteVec)
{
    string tempName;
    string tempCost;
    string tempInv;
    string tempPur;
    Items tempItems;
    ofstream fHandle;
    fHandle = openOutFile();

    for (Items tempItems : iteVec)
    {
        fHandle << tempItems.name << endl;
        fHandle << tempItems.cost << endl;
        fHandle << tempItems.inv << endl;
        fHandle << tempItems.pur << endl;
    }

    fHandle.close();
}