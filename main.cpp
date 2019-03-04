#include <iostream>
#include "Interface.h"

using namespace std;
Interface* Ani = new Interface();
int main()
{
    Ani ->addRoom("MJ1 ze spacja");

    Ani ->addItem("Name1 ze spacjami", "Opis xD");
    Ani ->addItem("Name2", "Opis xD");
    Ani ->addItem("Name3", "Opis xD");
    Ani ->addItem("Name4", "Opis xD");
    Ani ->addItem("Name5", "Opis xD");

    Ani ->itemOut(1,1);
    Ani ->itemOut(2,1);

    Ani -> saveState();

    //Ani -> loadState();

    cout << Ani->roomState(1).list [1];

    return 0;
}
