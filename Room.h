#include <vector>
#include "Item.h"

using namespace std;
struct Room
{
	Room();
	Room(int,string);
		
	int id;
	string name;
	vector<int>* list;
};