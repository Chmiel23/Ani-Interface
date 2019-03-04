#include <vector>
#include "Item.h"

using namespace std;
struct Room
{
	Room();
	Room(const Room&);
	Room(int,string,vector<int>&);
    Room& operator=(const Room&);

	int id;
	string name;
	vector<int>& list;
};
