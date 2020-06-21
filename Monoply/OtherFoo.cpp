#include"Header.h"

void Setings(HANDLE h) {
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

void ChoosePlayers(HANDLE h, int& count_players) {
	cout << "Choose players, then bots. Use buttons " << char(24) << " or " << char(25) << ".\nCould be 7 players." << "\nAfter choose press ENTER." << endl;
	COORD c{ 0,3 };
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

void PayersArr(int count_players) {
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
			else if ((i == hight - 5 || i == 2) && j > 1 && j < width - 26)
				cout << char(196);
			else if ((j == width - 27 || j == 2) && i > 2 && i < hight - 5)
				cout << char(179);
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
	street_arr[0] = CreateStreet((int)COLOURS::BROWN, 60, rent.brown, "Los Venturos Mafia", "Anyone has");
	street_arr[1] = CreateStreet((int)COLOURS::CYAN, 120, rent.cyan, "Varrios Los Aztecas", "Anyone has");
	street_arr[2] = CreateStreet((int)COLOURS::PINK, 160, rent.pink, "Ballas", "Anyone has");
	street_arr[3] = CreateStreet((int)COLOURS::ORANGE, 240, rent.orange, "Da Nang Boys", "Anyone has");
	street_arr[4] = CreateStreet((int)COLOURS::RED, 280, rent.red, "San Fierro Triads", "Anyone has");
	street_arr[5] = CreateStreet((int)COLOURS::YELLOW, 320, rent.yellow, "Los Santos Vagos", "Anyone has");
	street_arr[6] = CreateStreet((int)COLOURS::GREEN, 400, rent.green, "Grove Street Familes", "Anyone has");
	street_arr[7] = CreateStreet((int)COLOURS::BLUE, 4, rent.blue, "San Fierro Rifa", "Anyone has");
}

STREET CreateStreet(int colour, int price, int rent[], const char* call, const char* master) {
	STREET street{};
	street.colour = colour;
	street.price = price;
	for (int i = 0; i < 5; i++) 
		street.rent[i] = rent[i];
	strcpy_s(street.call, 50, call);
	strcpy_s(street.master, 5, master);
	return street;
}

void Stone(HANDLE h, int x, int y, int& result) {
	int random = rand() % 6 + 1;
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j < 7; j++) {
			PrintStone(h, j, x, y);
			if (i == 4 && j == random) {
				result += j;
				PrintStone(h, j, x, y);
				break;
			}
			Sleep(30);
		}
	}
}

void PrintStone(HANDLE& h, int num, int x, int y) {
	COORD c{ x,y };
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 4);
	cout << num;
}

void ShowProperty(HANDLE& h, int colour, int price, int ar_rent[], const char* call, const char* master) {
	RENT rent;
	COORD c{ 3,3 };
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, colour);
	cout << call;
	c.X = 3, c.Y++;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, (int)COLOURS::WHITE);
	cout << price;
	c.X = 3, c.Y++;
	for (int i = 1; i < 6; i++) {
		SetConsoleCursorPosition(h, c);
		if (i == 5) {
			cout << "HOTEL - " << ar_rent[i] << "$";
			break;
		}
		cout << i << " house - " << ar_rent[i] << "$";
		c.X = 3, c.Y++;
	}
	c.X = 3, c.Y += 2;
	cout << master;
}

void GameEngine(HANDLE& h) {
	RENT rent;
	int result = 0;
	Stone(h, 11, 17, result); // first stone
	Stone(h, 13, 17, result); // seconsd stone
	ShowProperty(h, (int)COLOURS::BROWN, rent.brown)
}