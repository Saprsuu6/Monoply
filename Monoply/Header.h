#include<iostream>
#include<windows.h>
#include<ctime>
#include<conio.h>
using namespace std;

enum class COLOURS { BROWN = 12, CYAN = 11, PINK = 13, ORANGE = 6, RED = 4, YELLOW = 14, GREEN = 10, BLUE = 9 };

struct STREET {
	int colour;
	int price;
	int* rent;
	char* name;
};

struct PLAYER {
	int money;
	bool prison;
};

void ChoosePlayers(HANDLE& h, int& count_all);
void Getch(int& count, bool& temp);
void PrintCount(COORD& c, HANDLE& h, int& count, const char* word);
void Setings(HANDLE& h);
void CountOfPlayers(int& count, int& count_all);
void PayersArr(int& count_players);
void GameField();