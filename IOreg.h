#include <string>
using namespace std;
struct IOreg
{
	IOreg();
	IOreg(int,int,bool,string);
	
	
	int roomID, itemID;
	bool out; //true - wydanie, false - zdeponowanie
	string person;
};