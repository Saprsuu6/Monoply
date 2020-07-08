#include"Header.h"

int main() {
	CreateNewFile();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int count_players = 0;
	STREET street{};
	PLAYER player{};
	Setings(h);
	ChoosePlayers(h, count_players);
	system("cls");
	Instruction(h);
	GameField();
	Sleep(300);
	GameEngine(h, street, count_players);
	system("pause > NULL");
}