#include "Room.h"

Room::Room(): id(0), name("NAME")
{}

Room::Room(int _id, string _name): id (_id), name (_name), list (NULL)
{}
