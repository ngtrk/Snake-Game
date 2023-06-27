#pragma once
#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <vector>



#define esc 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void cls()
{

	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };
	std::cout.flush();

	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);
	SetConsoleCursorPosition(hOut, topLeft);
}


void ClearScreen() {
	COORD cursorPosition;	
	cursorPosition.X = 0;	
	cursorPosition.Y = 0;	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}


class SnakeGame {
private:
	enum Direction {
		STOP = 0,
		LEFT, RIGHT, UP, DOWN

	};

	Direction SnakeDirection;
	const int Height, Width;
	int Snake_x[100], Snake_y[100];
	int SnakeHead_x, SnakeHead_y, Fruit_x, Fruit_y;
	int SnakeBodyCount, SnakeMaxLen, speeed;
	bool GameOver;
	bool BodyPrintFlag;
	std::vector<std::pair<int, int>> pos;


	void Controller();
	void SetUp();
	void DisplayMenu();
	void Prepare();
	void DisplayGameOver();
	void DisplayInstructions();
	void Stage();
	void Playing();


public:
	SnakeGame();
	void Start();

};


SnakeGame::SnakeGame() : Height(22), Width(80) {
	SnakeDirection = STOP;
	SnakeBodyCount = 0;
	SnakeMaxLen = 100;
	speeed = 600;
	GameOver = false;
	BodyPrintFlag = false;
	SnakeHead_x = 0;
	SnakeHead_y = 0;
	Fruit_x = 0;
	Fruit_y = 0;

	for (int i = 0; i < SnakeMaxLen; i++) {
		Snake_x[i] = 0;
		Snake_y[i] = 0;
	}
}


void SnakeGame::Prepare(){

	SetUp();

	while (!GameOver) {
		Stage();
		Controller();
		Playing();
		std::this_thread::sleep_for(std::chrono::milliseconds(speeed));

	}
}



void SnakeGame::SetUp() {
	GameOver = false;
	SnakeDirection = STOP;
	SnakeBodyCount = 0;
	speeed = 600;
	SnakeHead_x = Width / 2;
	SnakeHead_y = Height / 2;
	Fruit_x = rand() % (Width - 1) + 1;
	Fruit_y = rand() % (Height - 1) + 1;
}



void SnakeGame::DisplayGameOver() {
	std::cout << " ===========================================================================\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||           ____    _    __  __ _____ _____     _______ ____            ||\n";
	std::cout << " ||          / ___|  / \\  |  \\/  | ____/ _ \\ \\   / / ____|  _ \\           ||\n";
	std::cout << " ||         | |  _  / _ \\ | |\\/| |  _|| | | \\ \\ / /|  _| | |_) |          ||\n";
	std::cout << " ||         | |_| |/ ___ \\| |  | | |__| |_| |\\ V / | |___|  _ <           ||\n";
	std::cout << " ||          \\____/_/   \\_\\_|  |_|_____\\___/  \\_/  |_____|_| \\_\\          ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                  PRESS ANY KEY TO RETURN TO MENU                      ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ===========================================================================\n";

}

void SnakeGame::DisplayInstructions() {}



void SnakeGame::Controller() {
	if (_kbhit()) { //conio.h
		switch (_getch()) //conio.h
		{
		case KEY_LEFT:
			SnakeDirection = LEFT;
			break;

		case KEY_RIGHT:
			SnakeDirection = RIGHT;
			break;

		case KEY_UP:
			SnakeDirection = UP;
			break;

		case KEY_DOWN:
			SnakeDirection = DOWN;
			break;

		case esc:
			system("pause > nul");
			break;

		default:
			break;
		}

	}
}



void SnakeGame::DisplayMenu() {
	std::cout << " ===========================================================================\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                           *SNAKE GAME*                                ||\n";
	std::cout << " ||                              *Menu*                                   ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                         -> 1. Play Game                               ||\n";
	std::cout << " ||                         -> 2. Instructions                            ||\n";
	std::cout << " ||                         -> 3. Credits                                 ||\n";
	std::cout << " ||                         -> 4. Exit                                    ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ||                                                                       ||\n";
	std::cout << " ===========================================================================\n";

}

void SnakeGame::Start() {
	char opt = '\0';

	while (true) {
		cls();
		SnakeGame::DisplayMenu();
		opt = _getch();
		cls();
		switch (opt) {
		case '1':
			Prepare();
			cls();
			DisplayGameOver();
			_getch();
			break;

		case '2':
			DisplayInstructions();
			_getch();
			break;

		case '3':
			_getch();
			break;

		case '4':
			for (int i = 0; i < 4; i++) {
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				std::cout << ".";
				exit(-1);
			}
			break;

		default:
			break;
		}
	}
}


void SnakeGame::Stage() {
	std::cout << std::flush;
	ClearScreen();
	for (int i = 0; i < Width + 4; i++) {
		std::cout << "=";
	}
	std::cout << "\n";

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			if (j == 0) std::cout << "||";
			if (i == SnakeHead_y && j == SnakeHead_x) std::cout << "X";

			else if (i == Fruit_y && j == Fruit_x) std::cout << "#";

			else {
				BodyPrintFlag = false;
				for (int k = 0; k < SnakeBodyCount; k++) {
					if (pos[k].first == j && pos[k].second == i) {
						std::cout << "O";
						BodyPrintFlag = true;
					}
				}
				if (!BodyPrintFlag) std::cout << " ";
			}
			if (j == Width - 1) {
				std::cout << "||";
			}
		}
		std::cout << "\n";

	}
	for (int i = 0; i < Width + 4; i++) {
		std::cout << "=";
	}
}


void SnakeGame::Playing() {

	pos.insert(pos.begin(), std::make_pair(SnakeHead_x, SnakeHead_y));

	switch (SnakeDirection) {
	case 1:
		SnakeHead_x--;
		break;
	case 2:
		SnakeHead_x++;
		break;
	case 3:
		SnakeHead_y--;
		break;
	case 4:
		SnakeHead_y++;
		break;
	default:
		break;

	}


	if (SnakeHead_x >= Width) SnakeHead_x = 0;
	else if (SnakeHead_x < 0) SnakeHead_x = Width - 1;

	if (SnakeHead_y >= Height) SnakeHead_y = 0;
	else if (SnakeHead_y < 0) SnakeHead_y = Height - 1;


	for (int i = 0; i < SnakeBodyCount; i++) {

		if (pos[i].first == SnakeHead_x && pos[i].second == SnakeHead_y) GameOver = true;

	}


	if (SnakeBodyCount > SnakeMaxLen) {
		GameOver = true;
	}


	if (SnakeHead_x == Fruit_x && SnakeHead_y == Fruit_y) {
		Fruit_x = rand() % (Width - 1) + 1;
		Fruit_y = rand() % (Height - 1) + 1;
		SnakeBodyCount += 1;
		speeed -= 10;
	}


}


