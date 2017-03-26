//**************************************************************
//  
//**************************************************************
#include <iostream>
#include "StructManager.h"
#include <iomanip>

using namespace std;

void welcome();
int fileCount(ifstream &inFile);
void readFile(StructManager* structManager, ifstream &inFile);
int hashGenerator(const string& key, const int &arraySize);
void displayPhone(CellPhone & anItem);
void simpDisplay(CellPhone & anItem);
int compareString(void* tLeft, void* tRight, void* mode);
void farewell();

const unsigned int HASH_TABLE_SIZE = 100;	  // For testing purposes; must write function to determine hash table size.
const string fileName = "cellphones.txt";

int main()
{
	welcome();
	ifstream inFile;		     // ifstream object to input.
	inFile.open(fileName);	     //	open input file.

	if (!inFile)
	{
		cout << "=================================\n"
			 << "== F I L E   N O T   F O U N D ==\n"
			 << "=================================\n";
			system("pause");
			return 0;
	}
	else
	{
		StructManager *driver = new StructManager(fileCount(inFile), displayPhone, simpDisplay, hashGenerator, compareString);
		readFile(driver, inFile);
		driver->menuManager();
	}
	inFile.close();
	farewell();
	system("pause");
	return 0;
}

//**************************************************************
//	Prints welcome message.
//**************************************************************
void welcome()
{
	cout << "==========================================\n" 
	     << "======      W  E  L  C  O M  E      ======\n" 
	     << "==========================================\n";
	
	/*
	cout << "Welcome!\n";
	cout << "This is Team 6's project for the Spring 2015 CIS 22C class.\n";
	cout << "This program maintains a list of cell phones available in the market\n";
	cout << "utilizing a Hash Table for searching and a Binary Search Tree for sorting\n";
	cout << "by primary search key (FCC ID) or secondary search key (manufacturer).\n";
	cout << "Collisions are resolved buckets.\n\n";
	cout << "INPUT FILE NAME IS: cellphones.txt\n\n";
	cout << "Developed by: Sam Singh, Eric Du, Gideon Ubaldo and Denny Hung.\n\n";
*/
}

//**************************************************************
//	Gets amount of items in the input file.
//**************************************************************
int fileCount(ifstream &inFile) {
	string lineCount;
	int count = 0;
	while (getline(inFile, lineCount)){
		count++;
	}
	inFile.close();
	inFile.open(fileName);
	return count;
}

//**************************************************************
//	Function that reads input from file.
//**************************************************************
void readFile(StructManager *structManager, ifstream &inFile)
{
	// local variables to store input from file.
	string id = "";
	string name = "";
	string model = "";
	double memory = 0;
	int apps = 0;
	int songs = 0;

	while (getline(inFile, id, ';'))
	{
		getline(inFile, name, ';');
		getline(inFile, model, ';');
		inFile >> memory >> apps >> songs;
		inFile.get();
		CellPhone *newCellPhone = new CellPhone(id, name, model, memory, apps, songs);
		structManager->buildList(newCellPhone);
	}
}

//**************************************************************
//	Displays an item. //Under construction
//**************************************************************
void displayPhone(CellPhone & anItem)
{
    //cout << fixed << setprecision(1);
    cout << left << setw(8) << anItem.getID() << " " << left << setw(11) << anItem.getName() << " " << left << setw(16) << anItem.getModel()  << " ";
    cout << left << setw(8) << anItem.getMemory() << " " << left << setw(6) << anItem.getApps() << left << setw(5) << anItem.getSongs() << " " << endl;
}


//**************************************************************
//	Displays an item PART 2. //Under construction
//**************************************************************
void simpDisplay(CellPhone &anItem)
{
	cout << anItem.getID() << " " << anItem.getName() << endl;
}
//**************************************************************
//  Hash Generator
//**************************************************************
int hashGenerator(const string& key, const int &arraySize)
{
	unsigned int h = 5381;
	int index;

	for (unsigned int i = 0; i < key.size(); i++)
	{
		h = (h << 5) + h + key[i];
	}

	index = h % arraySize;
	//cout << "the hashed index is " << index<< endl;
	return index;
}

//**************************************************************
//	Prints farewell message.
//**************************************************************
void farewell()
{
	cout << "==========================================\n" 
	     << "=======    G  O  O  D  B  Y  E    ========\n" 
	     << "==========================================\n";
}

//TESTING 

// tLeft and tRight would be CellPhone objects, and mode would be an integer flag (1 if tree is sorted by primary key
// or 2 if sorted by secondary key).

int compareString(void* tLeft, void* tRight, void* mode)
{
	CellPhone left = *((CellPhone*)tLeft); /// you cannot dereference a void pointer:
	CellPhone right = *((CellPhone*)tRight); /// cast it first, then dereference it!
	int flag = *((int*)mode); /// you cannot dereference a void pointer:

	if (flag == 1)
	{
		if (left.getID().compare(right.getID()) < 0)
			return -1;
		if (left.getID().compare(right.getID()) == 0)
			return 0;
		return 1;
	}
	else
	{
		if (left.getName().compare(right.getName()) < 0)
			return -1;
		if (left.getName().compare(right.getName()) == 0)
			return 0;
		return 1;
	}
}