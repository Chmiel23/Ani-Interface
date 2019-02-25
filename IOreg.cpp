#include "IOreg.h"

IOreg::IOreg():
	roomID(0), itemID(0), out(false), person("someone")
{}

IOreg::IOreg(int _room, int _item, bool _out, string _person):
	roomID(_room), itemID(_item), out(_out), person(_person)
{}
