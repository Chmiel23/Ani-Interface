# Ani Interface
Ani Interface to kod będący owocem prac jakiegoś typa z polandii który postanowił zrobic cos co ma jakieś zastosowanie. Klasa ta pozwala na wykonywanie podstawowych operacji na zbiorze zbiorze przedmiotów które znajdują się w odpowiednich pokojach. Czyli generalnie obsługę kwatermistrzostwa na konwentach (bo taki był pierwotny zamysł).

## Pokoje
Dane o pokoju składowane sa w strukturze `Room` gdzie znajdują się informacje o nazwie pokoju, jego ID oraz zbiorze liczb będących ID przedmiotów znajdujących się w pokoju.
```cpp
struct Room
{
	Room();
	Room(int,string);
		
	int id;
	string name;
	vector<int>* list;
};
```
Przy tworzeniu (wywołaniu konstruktora klasy) obiektu klasy Interface automatycznie tworzy się pokój o ID = 0 i nazwie "DEPO".

## Przedmioty
Dane o przedmiocie równierz przechowywane sa w strukturze przechowujacej trzy wartości: ID, nazwę i opis przedmiotu.
```cpp
struct Item
{
	Item();
	Item(int,string,string);
		
	int ID;
	string name;
	string description;
};
```

## Relacje
Klasa opiera swoje działanie o ideę podobną do baz danych SQL, czyli kazdy obiekt ma przypisany numer identyfikacyjny, a te numery łączymy ze soba w odpowiednie relacje. W tym celu klasa zawiera cztery struktury `map` z których każda odpowiada za odpowiednia relację. Pierwsze dwie: `RoomID_Room_rel` i `ItemID_Item_rel`przypisują danemu ID wskaźnik odpowiednio do struktury pokoju i przedmiotu. Pozostałe dwie: `ItemID_RoomID_rel` i `RoomID_ItemID_rel` to relacje ID przedmiotu -> ID pokoju (w jakim pokoju jest dany przedmiot) i na odwrót (jakie przedmioty są w danym pokoju). Wszystkie te relacje są polami prywatnymi klasy więc nie mamy do nich bezpośredniego dostępu. Pomagają one jedynie realizować procesy zachodzące podczas uzywania klasy.

**Items**

|ID|Name|Description|
|---|---|---| 
|0|Kabel VGA  |Uszkodzony kolor czerwony|
|1|Kabel ATX  ||
|2|Rozg. 5gn. |Potrzeba bezpiecznika|
|3|Rozg. 5gn. ||
|4|Przedł. 15m||

**Rooms**

|ID|Name|list|
|---|---|---|
|0|DEPO|2,3|
|1|Planszówki|4|
|2|Mangowo Japońska 1|0,1|

**Item -> Room**

|Item ID|Room ID|
|---|---|
|0|2|
|1|2|
|2|0|
|3|0|
|4|1|

**Room -> Items**

|Room ID | Item IDs|
|---|---|
|0|2,3|
|1|4|
|2|0,1|

Zauważmy że tabele **Rooms** i relacja **Room -> Items** są niemalże identyczne ze względu na zawartość listy przedmiotów która jest oczywiście taka sama w obu przypadkach (zaznaczmy że oczywiście w relacji ID - Room przechowywane są wskaźniki na pokoje). Dlatego też wskaźniki na wektor zapisane w relacji **Room -> Items** oraz w **obiekcie** danego pokoju wskazują na **tą samą listę**.
## Metody klasy Interface
To chyba najważniejsza część tej "dokumentacji". Jakie interakcje mogę wykonać w ramach tej klasy? O tym najprędzej powie deklaracja klasy:
```cpp
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
		[...]

};
```
### addRoom
Metoda ta dodaje nowy pokój do listy pokoi. Nowy pokój uwzględniony jest w każdej z czterech relacji. Metoda przyjmuje jako argument nazwę nowego pokoju, a zwraca ID nowo utworzonego pokoju.
### addItem
Ta metoda dodaje nowy przedmiot do listy wszystkich przedmiotów i analogicznie do poprzedniej metody, uwzględnia się obecność nowego przedmiotu we wszystkich relacjach. Metoda przyjmuje jako argumenty nazwę nowego przedmiotu oraz opis tego przedmiotu. Automatycznie przedmiot lokowany jest w DEPO.
### itemOut
Ta metoda służy do wydawania przedmiotu z depozytu. Jako argument przyjmuje ID przedmiotu oraz ID pokoju do którego przedmiot ma być wydany. Istnieje możliwość próby wydania przedmiotu którego w DEPO nie ma, wówczas metoda zwraca wartość `false`. Jednak kiedy akcja zakończy się powodzeniem, zwraca `true`.
### itemReturn
Tą metodą sprowadzamy dany przedmiot z powrotem do depozytu. Jako argument przyjmuje ID przedmiotu który do depo wraca. Jeżeli spróbujemy zwrócić przedmiot który już jest w depo, metoda zwraca wartość `false` , jeżeli nie to `true`.
### itemState
Jest to metoda zwracająca wskaźnik na przedmiot o danym ID, a to ID przyjmuje jako argument. Wskaźnik brany jest wprost z jednej z relacji w klasie.
### roomState
_Analogicznie do `itemState`_
### saveState
Jest to metoda zapisująca stan czterech relacji do czterech plików. Pliki te mają format **.ini** i zapisują się w folderze z programem. Jest to moment w którym możemy łatwo uprzykrzyć sobie prace z klasą ponieważ zmieniając wartości w jednym z plików, należałoby pozmieniać odpowiednie wartości w pozostałych plikach, tak jak dodając na przykład przedmiot do relacji z ID należy dodać go również do pozostałych. Zalecam więc **nie ruszać** zapisanych plików!
### loadState
Metoda działająca na odwrót do poprzedniej. Ta ładuje zawartość relacji z plików.

## Na koniec słów kilka
Projekt ten nie jest niczym zobowiązującym i nadal zapewne posiada wiele wad i może być trudna w obsłudze. Może zawierać dziwne rozwiązania które doświadczonym programistom zapewne nie przyszłoby do głowy zastosować. Program ten nie jest również jakoś specjalnie optymalizowany pod obsługę wielkich ilości informacji. Jest to tylko owoc pracy pewnego młodego człowieka który zamarzył zostać kimś w świecie IT. W razie uwag, piszcie  na discorda czy gdziekolwiek bo i tak roześlę to niewielkiej grupie osób.

## Todo
+ Implementacja kolejki rejestrów wydań i zdań przedmiotów.
+ Do każdego wydania i zdania przedmiotu należy podać kto przedmiot bierze lub zwraca.
+ Możliwość przenoszenia przedmiotów między pokojami.

