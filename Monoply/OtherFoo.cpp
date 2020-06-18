#include"Header.h"

void Setings(HANDLE& h) {
	system("mode con cols=51 lines=21");
	system("title Monopoly");
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100;
	SetConsoleCursorInfo(h, &info);
	srand(time(0));
}

void Getch(int& count, bool& temp, int& count_players) {
	int code;
	code = _getch();
	if (code == 224)
		code = _getch();
	if (code == 72 && count != 7 && count_players + count < 7)
		count++;
	else if (code == 80 && count != 0)
		count--;
	else if (code == 13)
		temp = true;
}

void PrintCount(COORD& c, HANDLE& h, int& count, const char* word) {
	SetConsoleCursorPosition(h, c);
	cout << word;
	if (count != 13) 
		printf(":%1d", count);
}

void CountOfPlayers(int& count, int& count_players) {
	count_players += count;
}

void ChoosePlayers(HANDLE& h, int& count_players) {
	cout << "Choose players, then bots. Use buttons " << char(24) << " or " << char(25) << ".\nCould be 7 players" << endl;
	COORD c{ 0,2 };
	bool temp = false;
	int count = 0;
	while (true) {
		if (temp == true)
			break;
		PrintCount(c, h, count, "Players");
		Getch(count, temp, count_players);
 	}
	CountOfPlayers(count, count_players);
	c.Y++;
	count = 0;
	temp = false;
	while (true) {
		if (temp == true)
			break;
		PrintCount(c, h, count, "Bots");
		Getch(count, temp, count_players);
	}
	CountOfPlayers(count, count_players);
}

void PayersArr(int& count_players) {
	int first_money = 1500;
	PLAYER* player_arr = new PLAYER[count_players];
	for (int i = 0; i < count_players; i++) {
		player_arr->money = first_money;
		player_arr->prison = false;
	}
}

void GameField() {
	int width = 50;
	int hight = 20;
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 || j == 0 || i == hight - 1 || j == width - 1 || j == width / 2)
				cout << char(219);
			else
				cout << " ";
		}
		cout << endl;
	}
}

void ArrOfTheProperty() {
	RENT rent;
	int all_street = 12;
	STREET* street_arr = new STREET[all_street];
	street_arr[0] = CreateStreet((int)COLOURS::BROWN, 60, rent.brown, "Gangsta street", "Anyone has");
	street_arr[1] = CreateStreet((int)COLOURS::CYAN, 120, rent.cyan, "White treet", "Anyone has");
	street_arr[2] = CreateStreet((int)COLOURS::PINK, 160, rent.pink, "Magic street", "Anyone has");
	street_arr[3] = CreateStreet((int)COLOURS::ORANGE, 240, rent.orange, "Tropic street", "Anyone has");
	street_arr[4] = CreateStreet((int)COLOURS::RED, 280, rent.red, "Sun street", "Anyone has");
	street_arr[5] = CreateStreet((int)COLOURS::YELLOW, 320, rent.yellow, "Banana street", "Anyone has");
	street_arr[6] = CreateStreet((int)COLOURS::GREEN, 400, rent.green, "Growl street", "Anyone has");
	street_arr[7] = CreateStreet((int)COLOURS::BLUE, 4, rent.blue, "Sky street", "Anyone has");
}

STREET CreateStreet(int colour, int price, int rent[], const char* call, const char* master) {
	STREET street;
	street.colour = colour;
	street.price = price;
	for (int i = 0; i < 5; i++) 
		street.rent[i] = rent[i];
	strcpy_s(street.call, 50, call);
	strcpy_s(street.master, 5, master);
	return street;
}