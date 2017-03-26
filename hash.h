//**************************************************************
//  
//**************************************************************
#ifndef HASH_H
#define HASH_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

const int BUCKET_SIZE = 3;

template <class ItemType, class KeyType>
class Hash
{
private:
	//vector<vector<ItemType>> list;	                        // Vector of vectors to represent buckets.
	vector<ItemType*> *list;
	int tableSize;
	int itemCount;       	    								// Number of items in the hash table.
	int collision;
	vector<ItemType*> overflow_Area;
	//CellPhone Temp;
public:
	//HashTable(int size) { list.resize(size); }
	Hash(int size) { list = new vector<ItemType*>[size]; tableSize = size; itemCount = 0; collision = 0; }
	int getCount() { return itemCount; }
	void printTable(void print(ItemType &anItem));
	void printHashT(void print(ItemType &anItem));
	bool hash_insert(int getHash(const KeyType &id, const int &size), ItemType *&item);
	bool hash_search(int getHash(const KeyType &id, const int &size), ItemType targetItem, ItemType &returnItem);
	bool hash_delete(int getHash(const KeyType &id, const int &size), ItemType *item, ItemType &returnedItem);
	bool writeTofile();
	void reHash(int getHash(const KeyType &id, const int &size));
	void statistics();
	void destroyTable();

	//getters
	int getItemCount(){ return itemCount; }
	int getCollision(){ return collision; }

	//Destructor
	~Hash();
};

template<class ItemType, class KeyType>
void Hash <ItemType, KeyType>::statistics()
{
	int loadedbuckets = 0;
	int fullbuckets = 0;
	int item_in_bucket = 0;

	// load factor
	for (int x = 0; x < tableSize; x++)
	{
		if (!list[x].empty()){
			item_in_bucket += (list[x].size() - 1);
			loadedbuckets++;
		}
		else if (list[x].size() == BUCKET_SIZE)
		{
			fullbuckets++;
		}
	}
	cout << setprecision(2) << fixed;
	cout << "Load Factor  : " << (double)loadedbuckets / tableSize * 100 << "%\n";
	cout << "Full Buckets : " << fullbuckets << "\n";
	cout << "Total indexes with items: " << loadedbuckets << "\n";
	cout << "Average items per bucket: " << (double)item_in_bucket / tableSize << "\n";
	cout << "Average items per index: " << (double)itemCount / tableSize << "\n";
}
//**************************************************************
//  
//**************************************************************
template<class ItemType, class KeyType>
bool Hash <ItemType, KeyType>::writeTofile()
{
	ofstream outfile;
	outfile.open("Outfile.txt");
	if (!outfile)
	{
		cout << "=========================================\n"
			<< "== F I L E  C A N T  B E  O P E N E D  ==\n"
			<< "=========================================\n";
		return false;
	}
	outfile << left << setw(9) << "FCC ID" << left << setw(12) << "Make" << left << setw(17) << "Model" << left << setw(9) << "Memory" << left << setw(6) << "Apps" << left << setw(5) << "Songs \n";
	for (int i = 0; i < tableSize; i++)
	if (!list[i].empty())
	for (unsigned int j = 0; j < list[i].size(); j++)
	{
		outfile << left << setw(8) << list[i][j]->getID() << " " << left << setw(11) << list[i][j]->getName() << " " << left << setw(16) << list[i][j]->getModel() << " ";
		outfile << left << setw(8) << list[i][j]->getMemory() << " " << left << setw(6) << list[i][j]->getApps() << left << setw(5) << list[i][j]->getSongs() << " " << endl;
	}
	if (overflow_Area.size() > 0)
	{
		outfile << "============================================\n"
				<< "=== O  V  E  R  F  L  O  W    A  R  E  A ===\n"
				<< "============================================\n";
		for (int i = 0; i < tableSize; i++)
		if (!list[i].empty())
		for (unsigned int j = 0; j < overflow_Area.size(); j++)
		{
			outfile << left << setw(8) << list[i][j]->getID() << " " << left << setw(11) << list[i][j]->getName() << " " << left << setw(16) << list[i][j]->getModel() << " ";
			outfile << left << setw(8) << list[i][j]->getMemory() << " " << left << setw(6) << list[i][j]->getApps() << left << setw(5) << list[i][j]->getSongs() << " " << endl;
		}
	}
	else
	{
		outfile << "=================================================\n"
			    << "=== N O  I T E M  I N  T H E  O V E R F L O W ===\n"
			    << "=================================================\n";
	}	
	return true;
}
//**************************************************************
//  
//**************************************************************
template<class ItemType, class KeyType>
bool Hash<ItemType, KeyType>::hash_insert(int getHash(const KeyType &id, const int &size), ItemType *& item)
{
	int index = getHash(item->getID(), tableSize);
	if (list[index].empty()){
		list[index].push_back(item);
		itemCount++;
	}
	else if (list[index].size() < BUCKET_SIZE)
	{
		list[index].push_back(item);

		collision++;
		itemCount++;

		// Keep buckets sorted.	Doesn't work.
		/*int swap_iter = 1;
		if (list[index].size() > 2 && *list[index][BUCKET_SIZE - swap_iter] < *list[index][BUCKET_SIZE - (swap_iter + 1)])
		{
			ItemType* temp = list[index][BUCKET_SIZE - swap_iter];
			list[index][BUCKET_SIZE - swap_iter] = list[index][BUCKET_SIZE - (swap_iter + 1)];
			list[index][BUCKET_SIZE - (swap_iter + 1)] = temp;
		}*/
	}
	else if (list[index].size() == BUCKET_SIZE)
	{
		overflow_Area.push_back(item);
		//int size = overflow_Area.size();

		//// Keep overflow area sorted.
		//while ( size > 2 && *overflow_Area[size - 1] < *list[index][size - 2])
		//{
		//	ItemType* temp = overflow_Area[size - 1];
		//	overflow_Area[size - 1] = list[index][size - 2];
		//	overflow_Area[size - 2] = temp;
		//}

		collision++;
		itemCount++;
	}
	return true;
}

//**************************************************************
//  
//**************************************************************
template<class ItemType, class KeyType>
bool Hash<ItemType, KeyType>::hash_search(int getHash(const KeyType &id, const int &size), ItemType targetItem, ItemType &returnItem)
{
	int index = getHash(targetItem.getID(), tableSize);
	if (list[index].empty())
		return false;
	for (unsigned int num = 0; num < list[index].size(); num++)
	{
		if (list[index][num]->getID() == targetItem.getID())
		{
			returnItem = *list[index][num];
			return true;
		}
	}
	for (unsigned int x = 0; x < overflow_Area.size(); x++)
	{
		if (overflow_Area[x]->getID() == targetItem.getID())
		{
			returnItem = *overflow_Area[x];
			return true;
		}
	}
	return false;


}

//**************************************************************
// This function prints every item in the table
//**************************************************************
template<class ItemType, class KeyType>
void Hash<ItemType, KeyType>::printTable(void print(ItemType &anItem))
{
	for (int i = 0; i < tableSize; i++)
	if (!list[i].empty())
	for (unsigned int j = 0; j < list[i].size(); j++)
		print(*list[i][j]);
	if (overflow_Area.size() > 0)
	{
		cout << "============================================\n"
			<< "=== O  V  E  R  F  L  O  W    A  R  E  A ===\n"
			<< "============================================\n";
		for (unsigned int z = 0; z < overflow_Area.size(); z++)
			print(*overflow_Area[z]);
	}
	else
	{
		cout << "=================================================\n"
			 << "=== N O  I T E M  I N  T H E  O V E R F L O W ===\n"
			 << "=================================================\n";
	}
}

//**************************************************************
// this function prints the table and shows which are synonyms
//**************************************************************
template<class ItemType, class KeyType>
void Hash<ItemType, KeyType>::printHashT(void print(ItemType &anItem))
{
	for (int i = 0; i < tableSize; i++)
	{
		cout << endl;
		if (list[i].empty())
		{
			cout << "Index: " << i << endl;
			cout << "     -This index is empty\n";
		}
		else
		{
			cout << "Index: " << i << endl;
			print(*list[i][0]);
		}
		for (unsigned int j = 1; j < list[i].size(); j++)
		{
			cout << endl;
			cout << "         ";
			print(*list[i][j]);
		}
	}

	if (overflow_Area.size() > 0)
	{
		cout << "============================================\n"
			<< "=== O  V  E  R  F  L  O  W    A  R  E  A ===\n"
			<< "============================================\n";
		for (unsigned int z = 0; z < overflow_Area.size(); z++)
			print(*overflow_Area[z]);
	}
	else
	{
		cout << "=================================================\n"
			    << "=== N O  I T E M  I N  T H E  O V E R F L O W ===\n"
			    << "=================================================\n";
	}

	cout << "============================\n"
		<< "==Number of collisions: " << setw(2) << collision << "==\n"
		<< "============================\n";
}

//**************************************************************
//  
//**************************************************************
template<class ItemType, class KeyType>
bool Hash<ItemType, KeyType>::hash_delete(int getHash(const KeyType &id, const int &size), ItemType *item, ItemType &returnedItem)
{
	int index = getHash(item->getID(), tableSize);
	for (unsigned int x = 0; x < list[index].size(); x++)
	{
		if (list[index][x]->getID() == item->getID())
		{
			returnedItem = *list[index][x];
			list[index].erase(list[index].begin() + x);
			itemCount--;
			return true;
		}
	}
	for (unsigned int z = 0; z < overflow_Area.size(); z++)
	{
		returnedItem = (*overflow_Area[z]);
		itemCount--;
		return true;
	}
	return false;
}
template<class ItemType, class KeyType>
void Hash<ItemType, KeyType>::destroyTable()
{
	for (unsigned int count = 0; count < list->size(); count++)
	{
		for (unsigned int element = 0; element < list[count].size(); count++)
		{
			list[count][element] = NULL;
			delete list[count][element];
		}
	}
	for (unsigned int count = 0; count < overflow_Area.size(); count++)
	{
		overflow_Area[count] = NULL;
		delete overflow_Area[count];
	}
}

template<class ItemType, class KeyType>
void Hash<ItemType, KeyType>::reHash(int getHash(const KeyType &id, const int &size))
{
	//int	newArraySize = determineHashSize();

	//vector<ItemNode*> temp;
	//temp.resize(newArraySize);
	//cout << "OMG 75%, let me re-hash this table...\n";
	//cout << "Now...re-hashing this table.\n";
	//int xCount = 0;	 //How many items are.
	//for (int i = 0; i < arraySize; i++)
	//{
	//	ItemNode** headPtr = &hashTable[i];
	//	ItemNode* currPtr = hashTable[i];
	//	if (*headPtr != NULL)
	//	{
	//		*headPtr = currPtr;
	//		while (currPtr != NULL)
	//		{
	//			//*headPtr = currPtr;
	//			temp[xCount] = currPtr;
	//			xCount++;
	//			currPtr = currPtr->nextPtr;
	//		}
	//	}
	//}
	//hashTable.clear();
	//itemPerIndex.clear();
	//arraySize = newArraySize;
	//hashTable.resize(arraySize);
	//itemPerIndex.resize(arraySize);
	//itemCount = 0;
	//for (int i = 0; i < xCount; i++)
	//{
	//	insert(temp[i]->item);
	//}
	//cout << "New Hash Table Size: " << arraySize << endl;

}

template<class ItemType, class KeyType>
Hash<ItemType, KeyType>::~Hash()
{
	destroyTable();
	delete list;

}
#endif 