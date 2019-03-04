#include "Room.h"

Room::Room(): id(-1), name("NAME"), list (*new vector<int>)
{}

Room::Room(const Room& cpy): id(cpy.id), name(cpy.name), list(cpy.list)
{}

Room& Room::operator=(const Room& cpy)
{
    id = cpy.id;
    name = cpy.name;
    list = cpy.list;
}

Room::Room(int _id, string _name, vector<int>& _list): id (_id), name (_name), list (_list)
{}
