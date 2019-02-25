#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;
struct Item
{
	Item();
	Item(int,string,string);
		
	int ID;
	string name;
	string description;
};

#endif