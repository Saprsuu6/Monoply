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
	cout << "Choose players, then bots. Use buttons " << char(24) << " or " << char(25) << ".\nCould be 7 players and 2 for minimal." << "\nAfter choose press ENTER." << endl;
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
	if (count_players < 2)
		main();
	return;
}

PLAYER* PayersArr(int count_players) {
	int first_money = 1500;
	PLAYER* player_arr = new PLAYER[count_players];
	for (int i = 0; i < count_players; i++) {
		player_arr->money = first_money;
		player_arr->prison = false;
	}
	return player_arr;
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

STREET* ArrOfTheProperty(STREET& street) {
	RENT rent;
	int all_street = 12;
	STREET* street_arr = new STREET[all_street];
	street_arr[0] = CreateStreet(street, (int)COLOURS::BROWN, 60, rent.brown, "Los Venturos Mafia", "Anyone has");
	street_arr[1] = CreateStreet(street, (int)COLOURS::CYAN, 120, rent.cyan, "Varrios Los Aztecas", "Anyone has");
	street_arr[2] = CreateStreet(street, (int)COLOURS::PINK, 160, rent.pink, "Ballas", "Anyone has");
	street_arr[3] = CreateStreet(street, (int)COLOURS::ORANGE, 200, rent.orange, "Da Nang Boys", "Anyone has");
	street_arr[4] = CreateStreet(street, (int)COLOURS::RED, 240, rent.red, "San Fierro Triads", "Anyone has");
	street_arr[5] = CreateStreet(street, (int)COLOURS::YELLOW, 280, rent.yellow, "Los Santos Vagos", "Anyone has");
	street_arr[6] = CreateStreet(street, (int)COLOURS::GREEN, 320, rent.green, "Grove Street Familes", "Anyone has");
	street_arr[7] = CreateStreet(street, (int)COLOURS::BLUE, 400, rent.blue, "San Fierro Rifa", "Anyone has");
	street_arr[8] = CreateStreet(street, (int)COLOURS::WHITE, 200, rent.railway, "1# Railway st.", "Anyone has");
	street_arr[9] = CreateStreet(street, (int)COLOURS::WHITE, 200, rent.railway, "2# Railway st.", "Anyone has");
	street_arr[10] = CreateStreet(street, (int)COLOURS::WHITE, 200, rent.railway, "3# Railway st.", "Anyone has");
	street_arr[11] = CreateStreet(street, (int)COLOURS::WHITE, 200, rent.railway, "4# Railway st.", "Anyone has");
	return street_arr;
}

STREET CreateStreet(STREET& street, int colour, int price, int rent[], const char* call, const char* master) {
	if (colour == (int)COLOURS::WHITE) {
		street.rent = new int[4];
		for (int i = 0; i < 4; i++)
			street.rent[i] = rent[i];
	}
	else {
		street.rent = new int[6];
		for (int i = 0; i < 6; i++)
			street.rent[i] = rent[i];
	}
	street.call = new char[50];
	street.master = new char[50];
	street.colour = colour;
	street.price = price;
	strcpy_s(street.call, 49, call);
	strcpy_s(street.master, 49, master);
	return street;
}

void Stone(HANDLE h, int x, int y, int& result) {
	int random = rand() % 6 + 1;
	rand();
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

void PrintStone(HANDLE h, int num, int x, int y) {
	COORD c{ x,y };
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 4);
	cout << num;
}

void ShowProperty(HANDLE h, int colour, int price, int ar_rent[], const char* call, const char* master) {
	COORD c{ 3,3 };
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, colour);
	cout << call;
	c.X = 3, c.Y += 2;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, (int)COLOURS::WHITE);
	cout << "Price - " << price;
	c.X = 3, c.Y++;
	if (colour == (int)COLOURS::WHITE) {
		for (int i = 0; i < 4; i++) {
			SetConsoleCursorPosition(h, c);
			cout << i + 1 << "# station - " << ar_rent[i] << "$";
			c.X = 3, c.Y++;
		}
	}
	else {
		for (int i = 0; i < 6; i++) {
			SetConsoleCursorPosition(h, c);
			if (i == 0)
				cout << "Without houses - " << ar_rent[i] << "$";
			else if (i == 5) 
				cout << "HOTEL - " << ar_rent[i] << "$";
			else
				cout << i << " House - " << ar_rent[i] << "$";
			c.X = 3, c.Y++;
		}
	}
	c.X = 3, c.Y++;
	SetConsoleCursorPosition(h, c);
	cout << master;
}

void ClearField(HANDLE h) { 
	COORD c{ 3,3 };
	for (int i = 0; i < 12; i++) {
		SetConsoleCursorPosition(h, c);
		for (int j = 0; j < 20; j++) 
			cout << " ";
		c.X =3, c.Y++;
	}
}

void Choose() {
	COORD mouse;
	HANDLE h_m = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(h_m, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	const int events = 256;
	INPUT_RECORD all_events[events];
	DWORD read_events;
	while (true) {
		ReadConsoleInput(h_m, all_events, events, &read_events);
		for (int i = 0; i < read_events; i++) {
			mouse.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
			mouse.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;

		}
	}
}

void PrintBar(COORD& c, HANDLE h, int i) {
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, (int)COLOURS::WHITE);
	cout << "Player #" << i + 1;
}

void GameEngine(HANDLE h, STREET& street, int count_players) {
	int salary = 20;
	STREET* street_arr = new STREET[12];
    street_arr = ArrOfTheProperty(street);
	PLAYER* player_arr = new PLAYER[count_players];
	player_arr = PayersArr(count_players);
	PayersArr(count_players);
	int result = 0;
	COORD c{ 28,2 };
	while (true) {
		for (int i = 0; i < count_players; i++) {
			PrintBar(c, h, i);
			Stone(h, 11, 17, result); // first stone
			Stone(h, 13, 17, result); // seconsd stone
			Sleep(200);
			switch (result) {
			case(1):
				ShowProperty(h, street_arr[0].colour, street_arr[0].price, street_arr[0].rent, street_arr[0].call, street_arr[0].master);
				break;
			case(2):
				ShowProperty(h, street_arr[1].colour, street_arr[1].price, street_arr[1].rent, street_arr[1].call, street_arr[1].master);
				break;
			case(3):
				ShowProperty(h, street_arr[2].colour, street_arr[2].price, street_arr[2].rent, street_arr[2].call, street_arr[2].master);
				break;
			case(4):
				ShowProperty(h, street_arr[3].colour, street_arr[3].price, street_arr[3].rent, street_arr[3].call, street_arr[3].master);
				break;
			case(5):
				ShowProperty(h, street_arr[4].colour, street_arr[4].price, street_arr[4].rent, street_arr[4].call, street_arr[4].master);
				break;
			case(6):
				ShowProperty(h, street_arr[5].colour, street_arr[5].price, street_arr[5].rent, street_arr[5].call, street_arr[5].master);
				break;
			case(7):
				ShowProperty(h, street_arr[6].colour, street_arr[6].price, street_arr[6].rent, street_arr[6].call, street_arr[6].master);
				break;
			case(8):
				ShowProperty(h, street_arr[7].colour, street_arr[7].price, street_arr[7].rent, street_arr[7].call, street_arr[7].master);
				break;
			case(9):
				ShowProperty(h, street_arr[8].colour, street_arr[8].price, street_arr[8].rent, street_arr[8].call, street_arr[8].master);
				break;
			case(10):
				ShowProperty(h, street_arr[9].colour, street_arr[9].price, street_arr[9].rent, street_arr[9].call, street_arr[9].master);
				break;
			case(11):
				ShowProperty(h, street_arr[10].colour, street_arr[10].price, street_arr[10].rent, street_arr[10].call, street_arr[10].master);
				break;
			case(12):
				ShowProperty(h, street_arr[11].colour, street_arr[11].price, street_arr[11].rent, street_arr[11].call, street_arr[11].master);
				break;
			}
			result = 0;
			_getch();
			ClearField(h);
			player_arr[i].money += salary;
		}
	}
}