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
	cout << "Choose players, then bots. Use buttons " << char(24) << " or " << char(25) << ".\nCould be 7 players and 2 - minimum." << "\nAfter choose press ENTER." << endl;
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
	int first_money = 1200;
	PLAYER* player_arr = new PLAYER[count_players];
	for (int i = 0; i < count_players; i++) {
		player_arr[i].money = first_money;
		player_arr[i].prison = false;
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
	c.X = 28, c.Y += 2;
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

void PrintBar(COORD& c, HANDLE h, int temp, STREET*& street_arr) {
	c.Y += 5;
	SetConsoleCursorPosition(h, c);
	if (_strcmpi(street_arr[temp].master, "Anyone has") == 0)
		SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
	else
		SetConsoleTextAttribute(h, 1);
	cout << "Buy";
	c.X = 28, c.Y++;
	SetConsoleCursorPosition(h, c);
	if (_strcmpi(street_arr[temp].master, "Anyone has") == 0)
		SetConsoleTextAttribute(h, 1);
	else if (_strcmpi(street_arr[temp].master, "Anyone has") != 0
		&& street_arr[temp].property > 0)
		SetConsoleTextAttribute(h, 1);
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
	c.X = 28, c.Y--;
	SetConsoleCursorPosition(h, c);
	if (_strcmpi(street_arr[temp].master, "Anyone has") != 0 &&
		_strcmpi(street_arr[temp].call, "1# Railway st.") != 0 &&
		_strcmpi(street_arr[temp].call, "2# Railway st.") != 0 &&
		_strcmpi(street_arr[temp].call, "3# Railway st.") != 0 &&
		_strcmpi(street_arr[temp].call, "4# Railway st.") != 0) {
		if (street_arr[temp].property > 0)
			SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
		else
			SetConsoleTextAttribute(h, 1);
		cout << "Lay house";
		c.X = 28, c.Y++;
		if (street_arr[temp].property >= 0)
			SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
		else
			SetConsoleTextAttribute(h, 1);
		SetConsoleCursorPosition(h, c);
		cout << "Build house";
		c.X = 28, c.Y = 2;
	}
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

void Choose(HANDLE h, int& code, int num, int temp, STREET*& street_arr, int result, COORD& c, PLAYER*& player_arr) {
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
			if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				if (mouse.X > 27 && mouse.X < 31 && mouse.Y == 7 
					&& _strcmpi(street_arr[temp].master, "Anyone has") == 0) {
					char* str = new char[5];
					strcpy_s(street_arr[temp].master, 49, "Player #");
					_itoa_s(num + 1, str, 5, 10);
					strcat_s(street_arr[temp].master, 49, str);
					Bought(temp, street_arr, player_arr, num);
					PrintPlayer(c, h, player_arr, num);
					PrintBar(c, h, temp, street_arr);
					delete[] str;
				}
				else if (mouse.X > 27 && mouse.X < 31 && mouse.Y == 8
					&& _strcmpi(street_arr[temp].master, "Anyone has") != 0
					&& street_arr[temp].property == 0) {
					strcpy_s(street_arr[temp].master, 49, "Anyone has");
					Lay(temp, street_arr, player_arr, num);
					PrintPlayer(c, h, player_arr, num);
					PrintBar(c, h, temp, street_arr);
				}
				else if (mouse.X > 27 && mouse.X < 37 && mouse.Y == 9
					&& street_arr[temp].property > 0) {
					LayHouse(temp, street_arr, player_arr, num);
					PrintPlayer(c, h, player_arr, num);
					PrintBar(c, h, temp, street_arr);
				}
				else if (mouse.X > 27 && mouse.X < 39 && mouse.Y == 10
					&& _strcmpi(street_arr[temp].master, "Anyone has") != 0 &&
					_strcmpi(street_arr[temp].call, "1# Railway st.") != 0 &&
					_strcmpi(street_arr[temp].call, "2# Railway st.") != 0 &&
					_strcmpi(street_arr[temp].call, "3# Railway st.") != 0 &&
					_strcmpi(street_arr[temp].call, "4# Railway st.") != 0 && 
					street_arr[temp].property < 5) {
					BuildHouse(temp, street_arr, player_arr, num);
					PrintPlayer(c, h, player_arr, num);
					PrintBar(c, h, temp, street_arr);
				}
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
			}
		}
		if (code == 13)
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
	COORD c{ 28,2 };
	while (true) {
		for (int i = 0; i < count_players; i++) {
			Salary(player_arr, i, salary);
			PrintPlayer(c, h, player_arr, i);
			Stone(h, 11, 17, result); // first stone
			Stone(h, 13, 17, result); // seconsd stone
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
			PrintBar(c, h, temp, street_arr);
			OtherVatiant(c, h, code);
			if (code == 224 || code == 0)
				code = _getch();
			if (code != 13) {
				UCanBuy(c, h);
				Choose(h, code, i, temp, street_arr, result, c, player_arr);
			}
			ClearField(h);
			result = 0;
			code = 0;
			c.X = 28, c.Y = 2;
		}
	}
}