#include<iostream>
#include<windows.h>
#include<ctime>
#include<conio.h>
#include<direct.h>
using namespace std;

enum class COLOURS { WHITE = 15, BROWN = 12, CYAN = 11, PINK = 13, ORANGE = 6, RED = 4,
	YELLOW = 14, GREEN = 10, BLUE = 9, DARKBLUE = 1 };

struct STREET {
	int box;
	int property;
	int colour;
	int price;
	int* rent = nullptr;
	char* call = nullptr;
	char* master = nullptr;
};

struct PLAYER {
	int rl;
	int money;
	bool prison;
	bool bankrupt;
};

struct RENT {
	static const int size = 6;
	int brown[size] = { 4, 20, 60, 180, 320, 450 };
	int cyan[size] = { 8, 40, 100, 300, 450, 600 };
	int pink[size] = { 10, 50, 150, 450, 625, 750 };
	int orange[size] = { 16, 80, 220, 600, 800, 1000 };
	int red[size] = { 20, 100, 300, 750, 925, 1100 };
	int yellow[size] = { 24, 120, 360, 850, 1025, 1200 };
	int green[size] = { 28, 150, 450, 1000, 1200, 1400 };
	int blue[size] = { 50, 200, 600, 1400, 1700, 2000 };
	int railway[size - 2] = { 25, 50, 100, 200 };
};

int main();
void ChoosePlayers(HANDLE h, int& count_all);
void Getch(int& count, bool& temp, int& count_players);
void PrintCount(COORD& c, HANDLE& h, int& count, const char* word);
void Setings(HANDLE h);
void CountOfPlayers(int& count, int& count_all);
PLAYER* PayersArr(int count_players);
void GameField();
STREET* ArrOfTheProperty(STREET& street);
STREET CreateStreet(STREET& street, int colour, int price, int rent[], const char* call, const char* master, int property);
int Stone(HANDLE h, int x, int y);
void PrintStone(HANDLE h, int num, int x, int y);
void GameEngine(HANDLE h, STREET& street, int count_players);
void ShowProperty(HANDLE h, int colour, int price, int ar_rent[], const char* call, const char* master, int property);
void ClearField(HANDLE h);
void PrintBar(COORD& c, HANDLE h, int temp, STREET*& street_arr, int num, bool pay_rent, PLAYER*& player_arr);
void Salary(PLAYER*& player_arr, int i, int salary);
void PrintPlayer(COORD& c, HANDLE h, PLAYER*& player_arr, int i);
void Choose(HANDLE h, int& code, int num, int temp, STREET*& street_arr, int result, COORD& c, PLAYER*& player_arr,
	int count_players);
void OtherVatiant(COORD& c, HANDLE h, int& code);
void UCanBuy(COORD& c, HANDLE h);
void ClearText(COORD& c, HANDLE h);
void Bought(int temp, STREET*& street_arr, PLAYER*& player_arr, int num);
void Lay(int temp, STREET*& street_arr, PLAYER*& player_arr, int num);
void BuildHouse(int temp, STREET*& street_arr, PLAYER*& player_arr, int num);
void LayHouse(int temp, STREET*& street_arr, PLAYER*& player_arr, int num);
void PayRent(int temp, STREET*& street_arr, PLAYER*& player_arr, int num);
void RlForProperty(int temp, STREET*& street_arr, PLAYER*& player_arr, int num);
void CreateNewFile();
void Save(STREET*& street_arr, PLAYER*& player_arr, int count_players);
void Loading(STREET*& street_arr, PLAYER*& player_arr, int count_players);
void SaveOrLoad(int code, STREET*& street_arr, PLAYER*& player_arr, int i, int count_players);
void Instruction(HANDLE h);
void IfBancrupt(PLAYER*& player_arr, int num);
void Knockout(int temp, STREET*& street_arr, PLAYER*& player_arr, int num);
int Events();