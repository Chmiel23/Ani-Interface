#include "Item.h"

Item::Item(): ID(-1), name("NAME"), description ("DESC")
{}

Item::Item(int _ID, string _name, string _description):
        ID (_ID), name (_name), description (_description)
{}
