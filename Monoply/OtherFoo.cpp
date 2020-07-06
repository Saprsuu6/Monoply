#include"Header.h"

void Setings(HANDLE h) {
	system("mode con cols=51 lines=21");
	system("title Monopoly");
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100;
	SetConsoleCursorInfo(h, &info);
	SetConsoleTextAttribute(h, (int)COLOURS::GREEN);
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
	COORD c{ 0,0 };
	bool temp = false;
	int count = 0;
	while (true) {
		SetConsoleCursorPosition(h, c);
		cout << "Choose players, then bots. Use buttons " << char(24) << " or " << char(25) << ".\nCould be\
 7 players and 2 - minimum." << "\nAfter choose press ENTER.\n" << endl;
		c.Y += 3;
		SetConsoleCursorPosition(h, c);
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
		system("cls");
		c.X = 0, c.Y = 0;
		temp = false;
		if (count_players >= 2)
			break;
	}
}

PLAYER* PayersArr(int count_players) {
	int first_money = 1000;
	PLAYER* player_arr = new PLAYER[count_players];
	for (int i = 0; i < count_players; i++) {
		player_arr[i].rl = 0;
		player_arr[i].money = first_money;
		player_arr[i].prison = false;
		player_arr[i].bankrupt = false;
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
	street_arr[0] = CreateStreet(street, (int)COLOURS::BROWN, 60, rent.brown, "Los Venturos Mafia", "Anyone has", 0);
	street_arr[1] = CreateStreet(street, (int)COLOURS::CYAN, 120, rent.cyan, "Varrios Los Aztecas", "Anyone has", 0);
	street_arr[2] = CreateStreet(street, (int)COLOURS::PINK, 160, rent.pink, "Ballas", "Anyone has", 0);
	street_arr[3] = CreateStreet(street, (int)COLOURS::ORANGE, 200, rent.orange, "Da Nang Boys", "Anyone has", 0);
	street_arr[4] = CreateStreet(street, (int)COLOURS::RED, 240, rent.red, "San Fierro Triads", "Anyone has", 0);
	street_arr[5] = CreateStreet(street, (int)COLOURS::YELLOW, 280, rent.yellow, "Los Santos Vagos", "Anyone has", 0);
	street_arr[6] = CreateStreet(street, (int)COLOURS::GREEN, 320, rent.green, "Grove Street Familes", "Anyone has", 0);
	street_arr[7] = CreateStreet(street, (int)COLOURS::BLUE, 400, rent.blue, "San Fierro Rifa", "Anyone has", 0);
	street_arr[8] = CreateStreet(street, (int)COLOURS::WHITE, 200, rent.railway, "1# Railway st.", "Anyone has", 0);
	street_arr[9] = CreateStreet(street, (int)COLOURS::WHITE, 200, rent.railway, "2# Railway st.", "Anyone has", 0);
	street_arr[10] = CreateStreet(street, (int)COLOURS::WHITE, 200, rent.railway, "3# Railway st.", "Anyone has", 0);
	street_arr[11] = CreateStreet(street, (int)COLOURS::WHITE, 200, rent.railway, "4# Railway st.", "Anyone has", 0);
	return street_arr;
}

STREET CreateStreet(STREET& street, int colour, int price, int rent[], const char* call, const char* master, int property) {
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
	street.property = 0;
	street.call = new char[50];
	street.master = new char[50];
	street.colour = colour;
	street.price = price;
	strcpy_s(street.call, 49, call);
	strcpy_s(street.master, 49, master);
	return street;
}

int Stone(HANDLE h, int x, int y) {
	int random = rand() % 6 + 1;
	rand();
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j < 7; j++) {
			PrintStone(h, j, x, y);
			if (i == 4 && j == random) {
				PrintStone(h, j, x, y);
				return j;
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

void ShowProperty(HANDLE h, int colour, int price, int ar_rent[], const char* call, const char* master, int property) {
	COORD c{ 3,3 };
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, colour);
	cout << call;
	c.X = 3, c.Y += 2;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, (int)COLOURS::WHITE);
	cout << "Price - " << price << "$";
	c.X = 3, c.Y++;
	if (colour == (int)COLOURS::WHITE) {
		for (int i = 0; i < 4; i++) {
			SetConsoleCursorPosition(h, c);
			cout << i + 1 << " station - " << ar_rent[i] << "$";
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
	SetConsoleTextAttribute(h, colour);
	SetConsoleCursorPosition(h, c);
	cout << "Property - " << property;
	c.X = 3, c.Y += 2;
	SetConsoleTextAttribute(h, (int)COLOURS::WHITE);
	SetConsoleCursorPosition(h, c);
	cout << master;
}

void ClearField(HANDLE h) { 
	COORD c{ 3,3 };
	for (int i = 0; i < 12; i++) {
		SetConsoleCursorPosition(h, c);
		for (int j = 0; j < 20; j++) 
			cout << " ";
		c.X = 3, c.Y++;
	}
}

void PrintPlayer(COORD& c, HANDLE h, PLAYER*& player_arr, int i) {
	c.X = 28, c.Y = 2;
	SetConsoleTextAttribute(h, (int)COLOURS::WHITE);
	SetConsoleCursorPosition(h, c);
	cout << "Player #" << i + 1;
	c.X = 28, c.Y++;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, (int)COLOURS::PINK);
	if (player_arr[i].bankrupt == false)
		cout << "Not bankrupt";
	else
		cout << "Bankrupt    ";
	SetConsoleTextAttribute(h, (int)COLOURS::WHITE);
	c.X = 28, c.Y++;
	SetConsoleCursorPosition(h, c);
	cout << "Money - " << player_arr[i].money << "$   ";
	c.X = 28, c.Y++;
	SetConsoleCursorPosition(h, c);
	if (player_arr[i].prison == false) 
		cout << "Not in prison";
	else
		cout << "In prison";
	c.X = 28, c.Y = 2;
}

void PrintBar(COORD& c, HANDLE h, int temp, STREET*& street_arr, int num, bool pay_rent, PLAYER*& player_arr) {
	char* str = new char[5];
	char* temp_str = new char[20];
	_itoa_s(num + 1, str, 5, 10);
	strcpy_s(temp_str, 19, "Player #");
	strcat_s(temp_str, 19, str);
	c.Y += 5;
	SetConsoleCursorPosition(h, c);
	if (_strcmpi(street_arr[temp].master, "Anyone has") == 0 &&
		player_arr[num].prison != true && player_arr[num].bankrupt == false)
		SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
	else
		SetConsoleTextAttribute(h, (int)COLOURS::DARKBLUE);
	cout << "Buy";
	c.X = 28, c.Y++;
	SetConsoleCursorPosition(h, c);
	if (_strcmpi(street_arr[temp].master, temp_str) == 0 && 
		street_arr[temp].colour == (int)COLOURS::WHITE &&
		street_arr[temp].property > 0 && player_arr[num].prison != true && 
		player_arr[num].bankrupt == false)
		SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
	else if (_strcmpi(street_arr[temp].master, temp_str) != 0 || 
		_strcmpi(street_arr[temp].master, "Anyone has") == 0 ||
		_strcmpi(street_arr[temp].master, "Anyone has") != 0 &&
		street_arr[temp].property > 0 || player_arr[num].prison == true && 
		player_arr[num].bankrupt == true)
		SetConsoleTextAttribute(h, (int)COLOURS::DARKBLUE);
	else
		SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
	cout << "Lay";
	c.X = 28, c.Y++;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 1);
	cout << "Lay house";
	c.X = 28, c.Y++;
	SetConsoleCursorPosition(h, c);
	cout << "Build house";
	if (_strcmpi(street_arr[temp].master, "Anyone has") != 0 &&
		street_arr[temp].colour != (int)COLOURS::WHITE) {
		c.X = 28, c.Y--;
		SetConsoleCursorPosition(h, c);
		if (_strcmpi(street_arr[temp].master, temp_str) == 0 && 
			street_arr[temp].property > 0 && player_arr[num].prison != true && 
			player_arr[num].bankrupt == false)
			SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
		else
			SetConsoleTextAttribute(h, (int)COLOURS::DARKBLUE);
		cout << "Lay house";
		c.X = 28, c.Y++;
		if (_strcmpi(street_arr[temp].master, temp_str) == 0 &&
			street_arr[temp].property >= 0 && player_arr[num].prison != true && 
			player_arr[num].bankrupt == false)
			SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
		else
			SetConsoleTextAttribute(h, (int)COLOURS::DARKBLUE);
		SetConsoleCursorPosition(h, c);
		cout << "Build house";
	}
	c.X = 28, c.Y += 2;
	SetConsoleCursorPosition(h, c);
	if (_strcmpi(street_arr[temp].master, "Anyone has") != 0 &&
		_strcmpi(street_arr[temp].master, temp_str) != 0 &&
		pay_rent == false && player_arr[num].prison != true && 
		player_arr[num].bankrupt == false)
		SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
	else
		SetConsoleTextAttribute(h, (int)COLOURS::DARKBLUE);
	cout << "Pay Rent";
	c.X = 28, c.Y++;
	SetConsoleCursorPosition(h, c);
	if (player_arr[num].bankrupt != true)
		SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
	else
		SetConsoleTextAttribute(h, (int)COLOURS::DARKBLUE);
	cout << "Bankrupt!!!";
	c.X = 28, c.Y = 2;
	delete[] str;
	delete[] temp_str;
}

void Salary(PLAYER*& player_arr, int i, int salary) {
	player_arr[i].money += salary;
}

void OtherVatiant(COORD& c, HANDLE h, int& code) {
	c.X = 28, c.Y = 15;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, (int)COLOURS::WHITE);
	cout << "Press ENTER for next";
	c.X = 28, c.Y++;
	SetConsoleCursorPosition(h, c);
	cout << "Or ANY KEYS";
	code = _getch();
}

void UCanBuy(COORD& c, HANDLE h) {
	c.X = 28, c.Y++;
	SetConsoleCursorPosition(h, c);
	cout << "You can buy!";
	Sleep(500);
	ClearText(c, h);
}

void ClearText(COORD& c, HANDLE h) {
	c.X = 28, c.Y -= 2;
	for (int i = 0; i < 3; i++) {
		SetConsoleCursorPosition(h, c);
		cout << "                    ";
		c.X = 28, c.Y++;
	}
}

void Bought(int temp, STREET*& street_arr, PLAYER*& player_arr, int num) {
	player_arr[num].money -= street_arr[temp].price;
}

void Lay(int temp, STREET*& street_arr, PLAYER*& player_arr, int num) {
	player_arr[num].money += street_arr[temp].price / 2;
}

void BuildHouse(int temp, STREET*& street_arr, PLAYER*& player_arr, int num) {
	street_arr[temp].property++;
	player_arr[num].money -= street_arr[temp].price / 2;
}

void LayHouse(int temp, STREET*& street_arr, PLAYER*& player_arr, int num) {
	street_arr[temp].property--;
    player_arr[num].money += street_arr[temp].price / 4;
}

void PayRent(int temp, STREET*& street_arr, PLAYER*& player_arr, int num) {
	if (street_arr[temp].colour != (int)COLOURS::WHITE) {
		switch (street_arr[temp].property) {
		case (0):
			player_arr[num].money -= street_arr[temp].rent[0];
			street_arr[temp].box = player_arr[num].money - street_arr[temp].rent[0];
			break;
		case (1):
			player_arr[num].money -= street_arr[temp].rent[1];
			street_arr[temp].box = player_arr[num].money - street_arr[temp].rent[1];
			break;
		case (2):
			player_arr[num].money -= street_arr[temp].rent[2];
			street_arr[temp].box = player_arr[num].money - street_arr[temp].rent[2];
			break;
		case (3):
			player_arr[num].money -= street_arr[temp].rent[3];
			street_arr[temp].box = player_arr[num].money - street_arr[temp].rent[3];
			break;
		case (4):
			player_arr[num].money -= street_arr[temp].rent[4];
			street_arr[temp].box = player_arr[num].money - street_arr[temp].rent[4];
			break;
		case (5):
			player_arr[num].money -= street_arr[temp].rent[5];
			street_arr[temp].box = player_arr[num].money - street_arr[temp].rent[5];
			break;
		}
	}
	else {
		switch (street_arr[temp].property) {
		case (1):
			player_arr[num].money -= street_arr[temp].rent[0];
			street_arr[temp].box = player_arr[num].money - street_arr[temp].rent[0];
			break;
		case (2):
			player_arr[num].money -= street_arr[temp].rent[1];
			street_arr[temp].box = player_arr[num].money - street_arr[temp].rent[1];
			break;
		case (3):
			player_arr[num].money -= street_arr[temp].rent[2];
			street_arr[temp].box = player_arr[num].money - street_arr[temp].rent[2];
			break;
		case (4):
			player_arr[num].money -= street_arr[temp].rent[3];
			street_arr[temp].box = player_arr[num].money - street_arr[temp].rent[3];
			break;
		}
		player_arr[num].rl++;
	}
}

void TakeFromBox(int temp, STREET*& street_arr, PLAYER*& player_arr, int num) {
	player_arr[num].money += street_arr[temp].box;
	street_arr[temp].box = 0;
}

void RlForProperty(int temp, STREET*& street_arr, PLAYER*& player_arr, int num) {
	street_arr[temp].property = player_arr[num].rl;
}

void RlPlus(PLAYER*& player_arr, int num) {
	player_arr[num].rl++;
}

void RlMinus(PLAYER*& player_arr, int num) {
	player_arr[num].rl--;
}

void CreateNewFile() {
	_mkdir("Saves");
}

void IfBancrupt(PLAYER*& player_arr, int num) {
	player_arr[num].rl = 0;
	player_arr[num].prison = false;
	player_arr[num].money = 0;
}

void Knockout(int temp, STREET*& street_arr, PLAYER*& player_arr, int num) {
	char* str = new char[5];
	char* temp_str = new char[20];
	_itoa_s(num + 1, str, 5, 10);
	strcpy_s(temp_str, 19, "Player #");
	strcat_s(temp_str, 19, str);
	street_arr[temp].box = 0;
	strcpy_s(street_arr[temp].master, 19, "Anyone has");
	street_arr[temp].property = 0;
	delete[] str;
	delete[] temp_str;
}

void Choose(HANDLE h, int& code, int num, int temp, STREET*& street_arr, int result, COORD& c, PLAYER*& player_arr,
	int count_players) {
	bool pay_rent = false;
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
			char* str = new char[5];
			char* temp_str = new char[20];
			if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				_itoa_s(num + 1, str, 5, 10);
				strcpy_s(temp_str, 19, "Player #");
				strcat_s(temp_str, 19, str);
				if (player_arr[num].prison == false && player_arr[num].bankrupt == false) {
					if (mouse.X > 27 && mouse.X < 31 && mouse.Y == 7
						&& _strcmpi(street_arr[temp].master, "Anyone has") == 0) {
						strcpy_s(street_arr[temp].master, 49, "Player #");
						strcat_s(street_arr[temp].master, 49, str);
						Bought(temp, street_arr, player_arr, num);
						if (street_arr[temp].colour == (int)COLOURS::WHITE)
							RlPlus(player_arr, num);
						if (_strcmpi(street_arr[temp].master, temp_str) == 0 &&
							street_arr[temp].colour == (int)COLOURS::WHITE)
							RlForProperty(temp, street_arr, player_arr, num);
					}
					if (_strcmpi(street_arr[temp].master, temp_str) == 0) {
						if (mouse.X > 27 && mouse.X < 31 && mouse.Y == 8
							&& _strcmpi(street_arr[temp].master, "Anyone has") != 0
							&& street_arr[temp].property == 0) {
							strcpy_s(street_arr[temp].master, 49, "Anyone has");
							Lay(temp, street_arr, player_arr, num);
						}
						else if (mouse.X > 27 && mouse.X < 31 && mouse.Y == 8 &&
							street_arr[temp].colour == (int)COLOURS::WHITE &&
							street_arr[temp].property > 0) {
							RlMinus(player_arr, num);
							if (_strcmpi(street_arr[temp].master, temp_str) == 0 &&
								street_arr[temp].colour == (int)COLOURS::WHITE)
								RlForProperty(temp, street_arr, player_arr, num);
							strcpy_s(street_arr[temp].master, 49, "Anyone has");
							Lay(temp, street_arr, player_arr, num);
						}
						else if (mouse.X > 27 && mouse.X < 37 && mouse.Y == 9 &&
							street_arr[temp].colour != (int)COLOURS::WHITE &&
							street_arr[temp].property > 0) {
							LayHouse(temp, street_arr, player_arr, num);
						}
						else if (mouse.X > 27 && mouse.X < 39 && mouse.Y == 10 &&
							_strcmpi(street_arr[temp].master, "Anyone has") != 0 &&
							street_arr[temp].colour != (int)COLOURS::WHITE &&
							street_arr[temp].property < 5) {
							BuildHouse(temp, street_arr, player_arr, num);
						}
					}
					if (_strcmpi(street_arr[temp].master, temp_str) != 0 &&
						_strcmpi(street_arr[temp].master, "Anyone has") != 0 &&
						mouse.X > 27 && mouse.X < 36 && mouse.Y == 12 &&
						pay_rent == false) {
						PayRent(temp, street_arr, player_arr, num);
						pay_rent = true;
					}
				}
				if ((mouse.X > 27 && mouse.X < 39 && mouse.Y == 13 || player_arr[num].money < 0) &&
					player_arr[num].bankrupt == false)
					player_arr[num].bankrupt = true;
				if (_strcmpi(street_arr[temp].master, temp_str) == 0)
					TakeFromBox(temp, street_arr, player_arr, num);
				if (player_arr[num].bankrupt == true && _strcmpi(street_arr[temp].master, temp_str) == 0)
					Knockout(temp, street_arr, player_arr, num);
				if (player_arr[num].bankrupt == true) 
					IfBancrupt(player_arr, num);
				PrintPlayer(c, h, player_arr, num);
				PrintBar(c, h, temp, street_arr, num, pay_rent, player_arr);
				ClearField(h);
				switch (result) {
				case(1):
					temp = 0;
					ShowProperty(h, street_arr[0].colour, street_arr[0].price, street_arr[0].rent, street_arr[0].call, street_arr[0].master, street_arr[0].property);
					break;
				case(2):
					temp = 1;
					ShowProperty(h, street_arr[1].colour, street_arr[1].price, street_arr[1].rent, street_arr[1].call, street_arr[1].master, street_arr[1].property);
					break;
				case(3):
					temp = 2;
					ShowProperty(h, street_arr[2].colour, street_arr[2].price, street_arr[2].rent, street_arr[2].call, street_arr[2].master, street_arr[2].property);
					break;
				case(4):
					temp = 3;
					ShowProperty(h, street_arr[3].colour, street_arr[3].price, street_arr[3].rent, street_arr[3].call, street_arr[3].master, street_arr[3].property);
					break;
				case(5):
					temp = 4;
					ShowProperty(h, street_arr[4].colour, street_arr[4].price, street_arr[4].rent, street_arr[4].call, street_arr[4].master, street_arr[4].property);
					break;
				case(6):
					temp = 5;
					ShowProperty(h, street_arr[5].colour, street_arr[5].price, street_arr[5].rent, street_arr[5].call, street_arr[5].master, street_arr[5].property);
					break;
				case(7):
					temp = 6;
					ShowProperty(h, street_arr[6].colour, street_arr[6].price, street_arr[6].rent, street_arr[6].call, street_arr[6].master, street_arr[6].property);
					break;
				case(8):
					temp = 7;
					ShowProperty(h, street_arr[7].colour, street_arr[7].price, street_arr[7].rent, street_arr[7].call, street_arr[7].master, street_arr[7].property);
					break;
				case(9):
					temp = 8;
					ShowProperty(h, street_arr[8].colour, street_arr[8].price, street_arr[8].rent, street_arr[8].call, street_arr[8].master, street_arr[8].property);
					break;
				case(10):
					temp = 9;
					ShowProperty(h, street_arr[9].colour, street_arr[9].price, street_arr[9].rent, street_arr[9].call, street_arr[9].master, street_arr[9].property);
					break;
				case(11):
					temp = 10;
					ShowProperty(h, street_arr[10].colour, street_arr[10].price, street_arr[10].rent, street_arr[10].call, street_arr[10].master, street_arr[10].property);
					break;
				case(12):
					temp = 11;
					ShowProperty(h, street_arr[11].colour, street_arr[11].price, street_arr[11].rent, street_arr[11].call, street_arr[11].master, street_arr[11].property);
					break;
				}
				OtherVatiant(c, h, code);
				ClearText(c, h);
				if (code == 224 || code == 0)
					code = _getch();
				if (code == 13)
					break;
				else if (code == 67) {
					Save(street_arr, player_arr, count_players);
					break;
				}
				else if (code == 68) {
					Loading(street_arr, player_arr, count_players);
					break;
				}
				else if (code == 59)
					Instruction(h);
			}
			delete[] str;
			delete[] temp_str;
		}
		if (code == 13 || code == 67 || code == 68)
			break;
	}
}

void GameEngine(HANDLE h, STREET& street, int count_players) {
	int temp;
	int salary = 50;
	int code = 0;
	STREET* street_arr = new STREET[12];
    street_arr = ArrOfTheProperty(street);
	PLAYER* player_arr = new PLAYER[count_players];
	player_arr = PayersArr(count_players);
	int result = 0;
	int first_stone;
	int second_stone;
	int for_prison = 0;
	int counter_for_escape_from_prison = 0;
	COORD c{ 28,2 };
	SetConsoleCursorPosition(h, c);
	while (true) {
		for (int i = 0; i < count_players; i++) {
			if (player_arr[i].bankrupt == false)
				Salary(player_arr, i, salary);
			PrintPlayer(c, h, player_arr, i);
			first_stone = Stone(h, 11, 17); // first stone
			second_stone = Stone(h, 13, 17); // seconsd stone
			result = first_stone + second_stone;
			Sleep(200); 
			switch (result) {
			case(1):
				temp = 0;
				ShowProperty(h, street_arr[0].colour, street_arr[0].price, street_arr[0].rent, street_arr[0].call, street_arr[0].master, street_arr[0].property);
				break;																												   
			case(2):
				temp = 1;
				ShowProperty(h, street_arr[1].colour, street_arr[1].price, street_arr[1].rent, street_arr[1].call, street_arr[1].master, street_arr[1].property);
				break;																												   
			case(3):
				temp = 2;
				ShowProperty(h, street_arr[2].colour, street_arr[2].price, street_arr[2].rent, street_arr[2].call, street_arr[2].master, street_arr[2].property);
				break;																												   
			case(4):	
				temp = 3;
				ShowProperty(h, street_arr[3].colour, street_arr[3].price, street_arr[3].rent, street_arr[3].call, street_arr[3].master, street_arr[3].property);
				break;																												   
			case(5):	
				temp = 4;
				ShowProperty(h, street_arr[4].colour, street_arr[4].price, street_arr[4].rent, street_arr[4].call, street_arr[4].master, street_arr[4].property);
				break;																												   
			case(6):	
				temp = 5;
				ShowProperty(h, street_arr[5].colour, street_arr[5].price, street_arr[5].rent, street_arr[5].call, street_arr[5].master, street_arr[5].property);
				break;																												   
			case(7):	
				temp = 6;
				ShowProperty(h, street_arr[6].colour, street_arr[6].price, street_arr[6].rent, street_arr[6].call, street_arr[6].master, street_arr[6].property);
				break;																												   
			case(8):	
				temp = 7;
				ShowProperty(h, street_arr[7].colour, street_arr[7].price, street_arr[7].rent, street_arr[7].call, street_arr[7].master, street_arr[7].property);
				break;																												   
			case(9):	
				temp = 8;
				ShowProperty(h, street_arr[8].colour, street_arr[8].price, street_arr[8].rent, street_arr[8].call, street_arr[8].master, street_arr[8].property);
				break;																												   
			case(10):	
				temp = 9;
				ShowProperty(h, street_arr[9].colour, street_arr[9].price, street_arr[9].rent, street_arr[9].call, street_arr[9].master, street_arr[9].property);
				break;
			case(11):
				temp = 10;
				ShowProperty(h, street_arr[10].colour, street_arr[10].price, street_arr[10].rent, street_arr[10].call, street_arr[10].master, street_arr[10].property);
				break;
			case(12):
				temp = 11;
				ShowProperty(h, street_arr[11].colour, street_arr[11].price, street_arr[11].rent, street_arr[11].call, street_arr[11].master, street_arr[11].property);
				break;
			}
			PrintBar(c, h, temp, street_arr, i, false, player_arr);
			OtherVatiant(c, h, code);
			if (code == 224 || code == 0)
				code = _getch();
			if (code != 13 && code != 67 && code != 68 && code != 59) {
				UCanBuy(c, h);
				Choose(h, code, i, temp, street_arr, result, c, player_arr, count_players);
			}
			else if (code == 59)
				Instruction(h);
			SaveOrLoad(code, street_arr, player_arr, i, count_players);
			ClearField(h);
			result = 0;
			code = 0;
			c.X = 28, c.Y = 2;
			if (first_stone == second_stone && player_arr[i].prison == false) {
				i--;
				for_prison++;
			}
			if (for_prison == 3)
				player_arr[i].prison = true;
			if (player_arr[i].prison == true)
				counter_for_escape_from_prison++;
			if (counter_for_escape_from_prison == 3) {
				player_arr[i].money -= 50;
				player_arr[i].prison = false;
			}
			if (first_stone == second_stone && player_arr[i].prison == true)
				player_arr[i].prison = false;
		}
	}
}

void Save(STREET*& street_arr, PLAYER*& player_arr, int count_players) {
	int all_street = 12;
	FILE* fl;
	fopen_s(&fl, "Saves\\save.txt", "wb");
	fwrite(&count_players, sizeof(int), 1, fl);
	for (int i = 0; i < count_players; i++)
		fwrite(&player_arr[i], sizeof(PLAYER), 1, fl);
	for (int i = 0; i < all_street; i++) {
		fwrite(&street_arr[i].box, sizeof(int), 1, fl);
		fwrite(&street_arr[i].property, sizeof(int), 1, fl);
		fwrite(&street_arr[i].colour, sizeof(int), 1, fl);
		fwrite(&street_arr[i].price, sizeof(int), 1, fl);
		if (street_arr[i].colour != (int)COLOURS::WHITE) {
			for (int j = 0; j < 6; j++) 
				fwrite(&street_arr[i].rent[j], sizeof(int), 1, fl);
		}
		else {
			for (int j = 0; j < 4; j++)
				fwrite(&street_arr[j].rent[j], sizeof(int), 1, fl);
		}
		for (int j = 0; j < 49; j++)
			fwrite(&street_arr[i].call[j], sizeof(char), 1, fl);
		for (int j = 0; j < 49; j++)
			fwrite(&street_arr[i].master[j], sizeof(char), 1, fl);
	}
	fclose(fl);
}

void Loading(STREET*& street_arr, PLAYER*& player_arr, int count_players) {
	int all_street = 12;
	FILE* fl;
	fopen_s(&fl, "Saves\\save.txt", "rb");
	fread(&count_players, sizeof(int), 1, fl);
	for (int i = 0; i < count_players; i++)
		fread(&player_arr[i], sizeof(PLAYER), 1, fl);
	for (int i = 0; i < all_street; i++) {
		fread(&street_arr[i].box, sizeof(int), 1, fl);
		fread(&street_arr[i].property, sizeof(int), 1, fl);
		fread(&street_arr[i].colour, sizeof(int), 1, fl);
		fread(&street_arr[i].price, sizeof(int), 1, fl);
		if (street_arr[i].colour != (int)COLOURS::WHITE) {
			for (int j = 0; j < 6; j++)
				fread(&street_arr[i].rent[j], sizeof(int), 1, fl);
		}
		else {
			for (int j = 0; j < 4; j++)
				fread(&street_arr[j].rent[j], sizeof(int), 1, fl);
		}
		for (int j = 0; j < 49; j++)
			fread(&street_arr[i].call[j], sizeof(char), 1, fl);
		for (int j = 0; j < 49; j++)
			fread(&street_arr[i].master[j], sizeof(char), 1, fl);
	}
	fclose(fl);
}

void SaveOrLoad(int code, STREET*& street_arr, PLAYER*& player_arr, int i, int count_players) {
	if (code == 67)
		Save(street_arr, player_arr, count_players);
	else if (code == 68)
		Loading(street_arr, player_arr, count_players);
}

void Instruction(HANDLE h) {
	COORD c{ 0,0 };
	SetConsoleTextAttribute(h, (int)COLOURS::GREEN);
	while (true){
		system("cls");
		SetConsoleCursorPosition(h, c);
		cout << "For begin you may press ENTER to next player \nor ANY keys to make events.\
 After your choose you \nmay also press ENTER to next player or ANY keys to contine your events.\
 You may press F1 to read \ninstruction. You may press keys F9 to make a save \nor F10 to make a load.\n\n\
 GAMEPLAY:\nFor begin all players can buy streets, what will\nhelp them go bunkrupt other players. Also players\n\
can buy houses, lay it, lay streets. When player \ncome to someone else's street, player should \nto pay a rent.\n\n\
You should remember, if you will have money\nfew then 0, you will became bancrupt!\n\n\n\nPress ESC to return the game";
		if (Events() == 27) {
			system("cls");
			break;
		}
	}
}

int Events() {
	int code = _getch();
	if (code == 224 || code == 0)
		code = _getch();
	return code;
}