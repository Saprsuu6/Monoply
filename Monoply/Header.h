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
	char* call;
	char* master;
};

struct PLAYER {
	int money;
	bool prison;
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

void ChoosePlayers(HANDLE h, int& count_all);
void Getch(int& count, bool& temp, int& count_players);
void PrintCount(COORD& c, HANDLE& h, int& count, const char* word);
void Setings(HANDLE h);
void CountOfPlayers(int& count, int& count_all);
void PayersArr(int count_players);
void GameField();
void ArrOfTheProperty();
STREET CreateStreet(int colour, int price, int rent[], const char* call, const char* master);
void Stone(HANDLE h, int x, int y);
void PrintStone(HANDLE& h, int num, int x, int y);
void GameEngine(HANDLE& h);