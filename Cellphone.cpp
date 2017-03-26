//**************************************************************
//  
//**************************************************************

#include "CellPhone.h"

CellPhone::CellPhone()
{
	id = "";
	name = "";
	model = "";
	memory = 0;
	apps = 0;
	songs = 0;
}

CellPhone::CellPhone(string id, string name, string model, double memory, int apps, int songs)
{
	setID(id);
	setName(name);
	setModel(model);
	setMemory(memory);
	setApps(apps);
	setSongs(songs);

}
//**************************************************************
//  
//**************************************************************
//CellPhone::~CellPhone()
//{
//
//}