#include "IOreg.h"
#include "Item.h"
#include "Room.h"
#include <map>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Interface
{
	public:
		Interface();

		int addRoom(string);
		int addItem(string,string);

		bool itemOut(int,int);
		bool itemReturn(int);

		Item* itemState(int);
		Room* roomState(int);

		bool saveState();
		bool loadState();

	private:
		map<int,Room*>			RoomID_Room_rel;
		map<int,Item*>			ItemID_Item_rel;
		map<int,int>			ItemID_RoomID_rel;
		map<int,vector<int>*>   RoomID_ItemID_rel;

		int last_room_id;
		int last_item_id;

		void addReg();
		queue<IOreg*> rejest;

};
