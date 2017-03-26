#ifndef CELLPHONE_H
#define CELLPHONE_H

#include <iostream>
using namespace std;

class CellPhone
{
private:
	string id;
	string name;
	string model;
	double memory;
	int apps;
	int songs;

public:
	//Constructors
	CellPhone();
	CellPhone(string id, string name, string model, double memory, int apps, int songs);

	//Accesors

	string getID(){ return id; }
	string getName(){ return name; }
	string getModel() { return model; }
	double getMemory() { return memory; }
	int getApps() { return apps; }
	int getSongs() { return songs; }

	//Mutators

	void setID(string id) { this->id = id; }
	void setName(string name){ this->name = name; }
	void setModel(string model){ this->model = model; }
	void setMemory(double memory){ this->memory = memory; }
	void setApps(int apps){ this->apps = apps; }
	void setSongs(int songs){ this->songs = songs; }

	friend int compareString(string string1, string string2, int flag);
	//Overloaded operators
	bool operator<=(const CellPhone &right){ return (name.compare(right.name) <= 0); }
	bool operator!= (const CellPhone &right){ return (name.compare(right.name) != 0); }


	//bool operator+= (const CellPhone &right){ return (name.compare(right.name) == 0); }

	bool operator> (const CellPhone &right){ return (id.compare(right.id) > 0); }
	bool operator==(const CellPhone &right){ return (id.compare(right.id) == 0); }
	bool operator< (const CellPhone &right){ return (id.compare(right.id) < 0); }
	//bool operator<=(const CellPhone &right){ return (id.compare(right.id) <= 0); }
	bool operator>=(const CellPhone &right){ return (name.compare(right.name) >= 0); }


	//Destructor
	~CellPhone(){};

};


#endif