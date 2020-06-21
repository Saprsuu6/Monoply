#include"Header.h"

int main() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int count_players = 0;
	STREET street{};
	PLAYER player{};
	Setings(h);
	ChoosePlayers(h, count_players);
	PayersArr(count_players);
	system("cls");
	GameField();
	Sleep(300);
	GameEngine(h);
	system("pause > NULL");
}