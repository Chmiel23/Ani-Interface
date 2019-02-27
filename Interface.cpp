#include "Interface.h"
#define TAB char(9)

Interface::Interface():
	last_room_id(0),
	last_item_id(0)
{
	//Room o ID = 0 - DEPO
	RoomID_Room_rel [0] = new Room(0, "DEPO");
    RoomID_ItemID_rel [0] = new vector<int>;
    RoomID_Room_rel [0] -> list = RoomID_ItemID_rel [0];
	last_room_id++;
}

int Interface::addRoom(string name)
{
	RoomID_Room_rel [last_room_id] = new Room(last_room_id, name);
	RoomID_ItemID_rel [last_room_id] = new vector<int>;
	RoomID_Room_rel [last_room_id] -> list = RoomID_ItemID_rel [last_room_id];
	last_room_id++;
	return last_room_id - 1;
}

int Interface::addItem(string name, string description)
{
	ItemID_Item_rel [last_item_id] = new Item(last_item_id, name, description);
	ItemID_RoomID_rel [last_item_id]  = 0;
	RoomID_ItemID_rel [0] -> push_back( last_item_id );

	last_item_id++;
	return last_item_id - 1;
}

bool Interface::itemOut(int itemId, int roomId)
{
	if ( ItemID_Item_rel [itemId] == NULL )
		return false; //Przedmiot nie istnieje
	if ( ItemID_RoomID_rel [itemId] != 0 )
		return false; //Jak próbujesz wydaæ przedmiot którego nie ma w depo


	unsigned int i=0;
	while (RoomID_ItemID_rel[0] -> at(i) != itemId ||
			i > ItemID_Item_rel.size()) {i++;}
	RoomID_ItemID_rel [0] -> erase (RoomID_ItemID_rel [0] -> begin()+i); //Wyjmij z depo
	RoomID_ItemID_rel [roomId] -> push_back(itemId); //Ulokuj w roomie
	ItemID_RoomID_rel [itemId] = roomId;
	return true;

}

bool Interface::itemReturn(int itemId)
{
	if ( ItemID_Item_rel [itemId] == NULL )
		return false; //Przedmiot nie istnieje


	int roomId = ItemID_RoomID_rel [itemId];
	ItemID_RoomID_rel [itemId] = 0;

	unsigned int i=0;
	while (RoomID_ItemID_rel[roomId] -> at(i) != itemId ||
			i > ItemID_Item_rel.size())
    {i++;} //(znajdx w wektorze item
	RoomID_ItemID_rel [roomId] -> erase (RoomID_ItemID_rel [roomId] -> begin()+i); //Wyjmij z rooma
	RoomID_ItemID_rel [0] -> push_back(itemId); //Ulokuj w depo
        return true;
}
Item* Interface::itemState (int index)
{
	return ItemID_Item_rel [index];
}

Room* Interface::roomState (int index)
{
	return RoomID_Room_rel [index];
}

bool Interface::saveState()
{
    fstream save;
    /**ItemID -> ITEMS ---------------------------------------*/
    save.open("IDItems.ini", fstream::out | fstream::trunc);
    if (!save.is_open())
        return false;
    save << "[ID->Items]" << endl;
    unsigned int i = 0;
    while ( i < ItemID_RoomID_rel.size() )
    {
        if (ItemID_Item_rel[i] != NULL)
        {
            save << i << TAB << ItemID_Item_rel[i] -> name << TAB << ItemID_Item_rel[i] -> description << endl;
            i++;
        }
    }
    save.close();
    save << "[ID->room]" << endl;

    /** RoomID ->ROOMS --------------------------------------*/
    save.open("IDRooms.ini", fstream::out | fstream::trunc);
    if (!save.is_open())
        return false;
    save << "[ID->Rooms]" << endl;
    i = 0;
    while ( i < RoomID_Room_rel.size() )
    {
        if (RoomID_Room_rel[i] != NULL)
        {
            save << RoomID_Room_rel[i] -> id << TAB << RoomID_Room_rel[i] -> name << TAB;
            /*for (unsigned int j=0;j<RoomID_Room_rel[i]->list->size();j++)
            {
                save << RoomID_Room_rel[i]->list->at(j)<< " ";
            } //Zapis listy itemsów, docelowo do usunięcia */
            i++;
        }
        save << endl;
    }
    save.close();

    /**Item -> Room ------------------------------------------*/
    save.open("ItemId-RoomID.ini", fstream::out | fstream::trunc);
    if (!save.is_open())
        return false;
    save << "[Item->Room]" << endl;
    i=0;
    while ( i < ItemID_RoomID_rel.size() )
    {
        if (ItemID_RoomID_rel.find(i) != ItemID_RoomID_rel.end())
        {
            save << i << " " << ItemID_RoomID_rel[i] << endl;
            i++;
        }
    }
    save.close();

    /**Room -> Items -----------------------------------------*/
    save.open("RoomId-ItemID.ini", fstream::out | fstream::trunc);
    if (!save.is_open())
        return false;
    save << "[Room->Item]" << endl;
    i=0;
    while ( i < RoomID_ItemID_rel.size() )
    {
        if (RoomID_ItemID_rel.find(i) != RoomID_ItemID_rel.end())
        {
            save << i << " ";
            for (unsigned int j=0;j<RoomID_ItemID_rel[i]->size();j++)
            {
                save << RoomID_ItemID_rel[i]->at(j)<< " ";
            }
            save << endl;
            i++;
        }
    }
    return true;
}

bool Interface::loadState()
{
    fstream load;
    string buffer, name, description;
    int room_id, item_id;
     /**Load ID -> Rooms **/
    load.open ("IDRooms.ini", fstream::in);
    if (!load.is_open())
        return false;
    getline(load,buffer);
    if (buffer.compare ("[ID->Rooms]"))
        return false;

    while(getline(load, buffer))
    {
        istringstream ss(buffer);
        ss >> room_id;       //Ładowanie ID

        getline (ss,buffer,TAB);
        getline (ss,name,TAB);

        if ( room_id != 0 ) //Jeżeli id=0 nie robić nowego depo
            RoomID_Room_rel [room_id] = new Room(room_id,name);

        /*while (!ss.eof()) //Ładowanie itemsów [do przeniesienia w ładowanie innej tabeli]
        {
            ss >> item_id;
            RoomID_Room_rel [room_id] -> list -> push_back(item_id);
        }*/
    }
    load.close();

    /**Load ID -> Items **/
    load.open ("IDItems.ini", fstream::in);
    if (!load.is_open())
        return false;
    getline(load,buffer);

    if (buffer.compare ("[ID->Items]"))
        return false;
    while (getline(load, buffer))
    {
        istringstream ss(buffer);

        ss >> item_id;
        getline(ss,buffer,TAB);
        getline(ss,name,TAB);
        getline(ss,description,TAB);

        ItemID_Item_rel [item_id] = new Item(item_id, name, description);

    }
    load.close();

    /**Load Item -> Room */
    load.open ("ItemId-RoomID.ini", fstream::in);
    if (!load.is_open())
        return false;
    getline(load,buffer);
    if (buffer.compare ("[Item->Room]"))
        return false;

    while(!load.eof())
    {
        load >> item_id;
        load >> room_id;
        ItemID_RoomID_rel [item_id] = room_id;
    }
    load.close();

    /**Load Room -> Item*/
    load.open ("RoomId-ItemID.ini", fstream::in);
    if (!load.is_open())
        return false;
    getline(load,buffer);
    if (buffer.compare ("[Room->Item]"))
        return false;
    while(getline(load, buffer))
    {
        istringstream ss(buffer);

        ss >> room_id;

        RoomID_ItemID_rel [room_id] = new vector<int>;
        RoomID_Room_rel [room_id] -> list = RoomID_ItemID_rel [room_id];

        while (!ss.eof())
        {
            ss >> item_id;
            RoomID_ItemID_rel [room_id] -> push_back(item_id);
        }
    }
    return true;
}
