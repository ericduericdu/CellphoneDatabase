#include "StructManager.h"
#include <fstream>

StructManager::StructManager(int itemCount, void(*display)(CellPhone & item), void(*display2)(CellPhone & item), int(*hashFunction)(const string& key, const int &arraySize), int(*cmp) (void* argu1, void* argu2, void* argu3))
{
	// hash table
	hash_Table = new Hash<CellPhone, string>(determineHashSize(itemCount));

	// BST's
	main_BST = new BinarySearchTree<CellPhone>(cmp);
	secondary_BST = new BinarySearchTree<CellPhone>(cmp);

	printItem = display;

	simpDisplay = display2;

	hashGenerator = hashFunction;
}

//**************************************************************
//  This function builds the hash table and the BSTs.
//
//**************************************************************

void StructManager::buildList(CellPhone *&phone)
{
	main_BST->insert(phone);

	hash_Table->hash_insert(hashGenerator, phone);

	secondary_BST->insert2(phone);

}

//**************************************************************
//  This function displays the main menu
//
//**************************************************************

void StructManager::displayMenu()
{

	cout << "==========================================\n"
		<< "=========        M  E  N  U       ========\n"
		<< "==========================================\n"
		<< "==         A -- Add a new Data          ==\n"
		<< "==         D -- Delete Data             ==\n"
		<< "==         S -- Search a Data           ==\n"
		<< "==         L -- Data Lists              ==\n"
		<< "==         R -- Write to file           ==\n"
		<< "==         T -- Show Statistics         ==\n"
		<< "==         M -- Show Menu               ==\n"
		<< "==         Q -- Quit                    ==\n"
		<< "==========================================\n";

}
//**************************************************************
// Delete Manager
//
//**************************************************************
void StructManager::deleteManager()
{
	string tMake;
	string tID;
	CellPhone returnedItem;

	cout << "Enter the company of the phone you want to delete: ";
	cin >> tMake;

	cout << "Enter the ID of the phone you want to delete: ";
	cin >> tID;

	CellPhone *delPhone = new CellPhone(tID, tMake, "", 0, 0, 0);

	if (hash_Table->hash_delete(hashGenerator, delPhone, returnedItem))
	{
		main_BST->remove(delPhone);
		secondary_BST->remove2(delPhone);

		cout << "Item successfully deleted:";
		printItem(returnedItem);

	}
	else
		cout << "\nPhone was not in list\n\n";

}

//**************************************************************
//
//**************************************************************
void StructManager::writeTofile()
{
	if (hash_Table->writeTofile())
		cout << "Data Successfully Written to file" << endl;
	else
		cout << "Data failed to write to file" << endl;
}

//**************************************************************
// Add Manager
//
//**************************************************************
void StructManager::addManager()
{
	string tId;
	string tName;
	string tModel;
	double tMemory;
	int tApps;
	int tSongs;

	cout << "Enter FCC code: ";
	cin >> tId;
	cin.get();
	CellPhone *tPhone = new CellPhone(tId, "", "", 0, 0, 0);
	CellPhone searchResult;
	if (hash_Table->hash_search(hashGenerator, *tPhone, searchResult))
	{
		cout << "\nItem already exists.\n\n";
		cout << "FCC ID: " << searchResult.getID() << "\n";
		cout << "Manufacturer: " << searchResult.getName() << "\n";
		cout << "Model: " << searchResult.getModel() << "\n";
	}
	else
	{
		cout << "Enter phone make: ";
		cin >> tName;
		cin.get();
		cout << "Enter phone model: ";
		getline(cin, tModel);
		cout << "Enter memory amount: ";
		cin >> tMemory;
		cout << "Enter number of apps: ";
		cin >> tApps;
		cout << "Enter number of songs: ";
		cin >> tSongs;

		
		tPhone->setName(tName);
		tPhone->setModel(tModel);
		tPhone->setMemory(tMemory);
		tPhone->setApps(tApps);
		tPhone->setSongs(tSongs);

		main_BST->insert(tPhone);

		secondary_BST->insert2(tPhone);

		hash_Table->hash_insert(hashGenerator, tPhone);

		cout << "\nYour desired phone has been added.\n\n";
	}

}

void StructManager::outputExtraCredit()
{
	ifstream infile;
	infile.open("extraCredit.txt");

	string awesome;
	while(infile)
	{
		getline(infile,awesome);
		cout << awesome << endl;
	}
	
}

//**************************************************************
// This function manages the Main Menu
//
//**************************************************************

void StructManager::menuManager()
{
	displayMenu();

	// for hash
	string option;
	string returnedObject;

	char choice;
	bool repeatMenu = true;


	while (repeatMenu == true)
	{
		switch (choice = getLetter())
		{
		case 'A':
			addManager();
			break;

		case 'D':
			deleteManager();
			break;

		case 'S':
			searchSubMenu();
			break;

		case 'L':
			listSubMenu();
			break;

		case 'R': 
			writeTofile();
			break;

		case 'M':
			displayMenu();
			cout << endl;
			break;

		case 'T':
			hash_Table->statistics();
			break;

		case 'W':
			cout << " ====================================" << endl;
			cout << " ----WARRIORS: 2015 NBA CHAMPIONS----" << endl;
			cout << " ====================================" << endl;
			cout << "              ,--'''|'''--.        " << endl;
			cout << "            .'      |      `,      " << endl;
			cout << "        __/_ `.     |     ,' '|    " << endl;
			cout << "       |    |  `.   |   ,'     |   " << endl;
			cout << "       .    |    `--|--'        |  " << endl;
			cout << "       |    `.______|___________|  " << endl;
			cout << "        .     `-.   |           |  " << endl;
			cout << "         |       `-.|-._       |   " << endl;
			cout << "         '| -._     `.  '.   ,/    " << endl;
			cout << "           '   '-.___/    ' /      " << endl;
			cout << "             `---.__|__.--''       " << endl;

			break;

		case 'Q':

			writeTofile();
			repeatMenu = false;
			break;

		case 'E':outputExtraCredit();

		default:
			cout << endl;
			cout << "--- error: invalid input ---" << endl;
			cout << "Push M to see the menu" << endl;
			cout << endl;
			break;
		}
	}
}

//**************************************************************
// This function retrieves a letter to use for the submenu's
//
//**************************************************************
int StructManager::getNum()
{
	string entry;
	int num = 3;
	bool isNum = false;

	while (isNum == false)
	{

		cout << "Please enter a [number]: ";
		cin >> entry;
		cin.ignore();


		if (isdigit(entry[0]))
		{
			num = entry[0] - 48;
			isNum = true;
		}
		else
		{
			cout << "-- error: invalid entry --" << endl << endl;
		}
	}

	return num;
}

//**************************************************************
// This function retrieves a letter for main menu
//
//**************************************************************
char StructManager::getLetter()
{
	string choice;
	char letter;

	cout << "Please enter a [character]:";

	cin >> choice;
	cin.ignore();

	letter = toupper(choice[0]);
	cout << endl;

	return letter;

}

//**************************************************************
// This function retrieves a string to search for the primary
// key
//**************************************************************
void StructManager::getPrimaryKey()
{
	string search_ID = "";
	CellPhone tempTarget;
	tempTarget.setID("empty");
	CellPhone temp;
	CellPhone *returnedItem = &temp;

	cout << "Please enter a FCC-ID to search for: ";

	cin >> search_ID;
	cin.ignore();

	for (unsigned int i = 0; i < search_ID.length(); i++)
	{
		search_ID[i] = toupper(search_ID[i]);
	}

	tempTarget.setID(search_ID);


	if (hash_Table->hash_search(hashGenerator, tempTarget, *returnedItem))
	{
		cout << "Item Found: \n";
		printItem(*returnedItem);
	}
	else
		cout << "Item not found.\n";
}

//**************************************************************
// This function retrieves a string to search for
//
//**************************************************************
void StructManager::getSecondaryKey()
{
	string secKey;

	cout << "Please enter a Company Name to search for: ";

	cin >> secKey;
	cin.ignore();

	CellPhone *tempCell = new CellPhone("", secKey, "", 0, 0, 0);

	secondary_BST->printKey(printItem, *tempCell);
}
//**************************************************************
// this function manages the search sub menu
//
//**************************************************************

void StructManager::searchMenuTable()
{
	cout << "-----------------------------\n"
		<< "----  S  E  A  R  C  H   ----\n"
		<< "-----------------------------\n"
		<< "---   1 : FCC ID          ---\n"
		<< "---   2 : Company Name    ---\n"
		<< "---   3 : Show Menu       ---\n"
		<< "---   0 : Quit Search     ---\n"
		<< "-----------------------------\n";
}


//**************************************************************
// this function manages the search sub menu
//
//**************************************************************
void StructManager::searchSubMenu()
{
	int choice;
	bool repeatMenu = true;
	string temp;

	searchMenuTable();

	while (repeatMenu == true)
	{

		string search_ID = "";
		CellPhone tempTarget;
		tempTarget.setID("empty");
		CellPhone temp;
		CellPhone *returnedItem = &temp;
		string entry;

		switch (choice = getNum())
		{
		case 1:

			getPrimaryKey();
			break;

		case 2:
			getSecondaryKey();
			break;

		case 3:
			searchMenuTable();
			break;

		case 0:
			cout << "Now quitting search" << endl << endl;
			repeatMenu = false;
			break;

		default:
			cout << "-- error: invalid input--" << endl;
			cout << " enter 3 to see submenu again" << endl;
			break;
		}
	}

}
//**************************************************************
// This function manages the list sub menu
//
//**************************************************************
void StructManager::listSubMenu()
{
	int choice;
	bool repeatMenu = true;
	int temp = 0;

	cout << "   List Submenu" << endl;
	cout << "   ---------------------------" << endl;
	cout << "   1 : List Unsorted" << endl;
	cout << "   2 : List Sorted by Primary key" << endl;
	cout << "   3 : List Sorted by Secondary key" << endl;
	cout << "   4 : special print: indented list" << endl;
	cout << "   5 : Print submenu again" << endl;
	cout << "   6 : Print indented Primary BST" << endl;
	cout << "   7 : Print indented Secondary BST" << endl;
	cout << "   0 : quit" << endl << endl;

	while (repeatMenu == true)
	{

		switch (choice = getNum())
		{
		case 1:
			cout << "Cell Phones sorted by Primary Key" << endl << endl;
			cout << "FCC ID   Make        Model            Memory   Apps  Songs\n";
			cout << "-------  ----------- ---------------- -------- ----- -----\n";
			hash_Table->printTable(printItem);
			break;

		case 2:
			cout << "Cell Phones sorted by Primary Key" << endl << endl;
			cout << "FCC ID   Make        Model            Memory   Apps  Songs\n";
			cout << "-------  ----------- ---------------- -------- ----- -----\n";
			main_BST->inOrder(printItem);
			break;

		case 3:
			cout << "sorted secondary key" << endl << endl;
			cout << "FCC ID   Make        Model            Memory   Apps  Songs\n";
			cout << "-------  ----------- ---------------- -------- ----- -----\n";
			secondary_BST->inOrder(printItem);
			break;

		case 4:
			cout << "Hash Table indented list" << endl << endl;
			hash_Table->printHashT(simpDisplay);
			break;

		case 5:

			cout << "   List Submenu" << endl;
			cout << "   ---------------------------" << endl;
			cout << "   1 : List Unsorted" << endl;
			cout << "   2 : List Sorted by Primary key" << endl;
			cout << "   3 : List Sorted by Seconday key" << endl;
			cout << "   4 : special print: indented list" << endl;
			cout << "   5 : Print submenu again" << endl;
			cout << "   6 : Print indented Primary BST" << endl;
			cout << "   7 : Print indented Secondary BST" << endl;
			cout << "   0 : quit" << endl << endl;
			break;

		case 6:
			main_BST->printTree(simpDisplay);
			break;

		case 7:
			secondary_BST->printTree(simpDisplay);
			break;

		case 0:

			cout << "now quitting list" << endl << endl;
			repeatMenu = false;
			break;

		default:
			cout << "-- error: invalid input--" << endl;
			cout << " enter 5 to see submenu again" << endl << endl;
			break;
		}
	}

}

//**************************************************************
//
//
//**************************************************************

int StructManager::determineHashSize(int fileCount)
{
	return nextPrime((fileCount / DEFAULT_LOAD_FACTOR));
}
//**************************************************************
//
//
//**************************************************************
int StructManager::nextPrime(int fileCount)
{
	while (!isPrime(fileCount))
		fileCount++;
	return fileCount;
}
//**************************************************************
//
//
//**************************************************************
bool StructManager::isPrime(int num)
{
	for (int i = 2; i < num; i++)
	{
		if (num % i == 0)
			return false;
	}
	return true;
}
//**************************************************************
//
//
//**************************************************************
StructManager::~StructManager()
{
	delete hash_Table;
	delete main_BST;
	delete secondary_BST;
}
