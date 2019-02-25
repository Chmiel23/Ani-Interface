#include "Item.h"
#include "IOreg.h"
#include <vector>
#include <map>
struct Depo
{
	map <int,Item*> list;
	vector <IOreg*> IOregister;
};