#include"Header.h"

int main() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int count_players = 0;
	STREET street{};
	PLAYER player{};
	Setings(h);
	PayersArr(count_players);
	ChoosePlayers(h, count_players);
	system("cls");
	GameField();
	system("pause > NULL");
}