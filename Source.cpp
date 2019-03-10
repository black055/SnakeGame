#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;
bool gameOver;
const int width = 30, height = 30, scrSize = width*height + height - 1;
int x, y, pointX, pointY, score, sLength, preX, preY, sTail;
enum sMove { STOP, LEFT, RIGHT, UP, DOWN };
sMove dir;
char screen[scrSize];
int sBody[100];
int getIndex(int x, int y)
{
	return width*y + y + x;
}

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void setup()
{
	gameOver = 0;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	pointX = 1 + rand() % (width - 2);
	pointY = 1 + rand() % (height - 2);
	score = 0;
	for (int i = 0; i < scrSize; i++)
	{
		if ((i < width) || (i >= getIndex(0, height - 1))) screen[i] = 176;
		else screen[i] = 32;
	}
	for (int i = width + 1; i < scrSize; i = i + width + 1)
	{
		screen[i] = 176; screen[i + width - 1] = 176;
		screen[i - 1] = '\n';
	}
}

void draw()
{
	Nocursortype();
	int preIndex = getIndex(preX, preY);
	int sIndex = getIndex(x, y);
	int pointIndex = getIndex(pointX, pointY);
	screen[preIndex] = ' ';
	screen[pointIndex] = 'P';
	screen[sIndex] = '0';
	for (int i = 0; i < score; i++) screen[sBody[i]] = 'o';
	screen[sTail] = ' ';
	gotoxy(0, 0);
	cout << screen;
	gotoxy(width + 2, 3);
	cout << "Score: " << score;
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a': dir = LEFT;
			break;
		case 'd': dir = RIGHT;
			break;
		case 's': dir = DOWN;
			break;
		case 'w': dir = UP;
			break;
		case 'b': dir = STOP;
			break;
		}
	}
}

void Die()
{
	int sIndex = getIndex(x, y);
	if (x >= width - 1 || x <= 0 || y <= 0 || y >= height - 1) gameOver = true;
	 // kiem tra dung duoi
	for (int i = 1; i < score; i++)
		if (sIndex == sBody[i]) gameOver = true;
}
void logic()
{
	sTail = sBody[score - 1];
	preX = x; preY = y;
	switch (dir)
	{
	case LEFT: x--;
		break;
	case RIGHT: x++;
		break;
	case UP: y--;
		break;
	case DOWN: y++;
		break;
	}
	if (score)
	{
		if (getIndex(x, y) == sBody[0])
		{
			switch (dir)
			{
			case LEFT: x += 2;
				break;
			case RIGHT: x -= 2;
				break;
			case UP: y += 2;
				break;
			case DOWN: y -= 2;
				break;
			}
		}
	}
	if (getIndex(x, y) == getIndex(pointX, pointY))
	{
		score++;
		pointX = 1 + rand() % (width - 2);
		pointY = 1 + rand() % (height - 2);
	}
	for (int i = score - 1; i>=1; i--) 
		sBody[i] = sBody[i - 1];
	sBody[0] = getIndex(preX, preY);
}

void main()
{
	setup();
	while (!gameOver)
	{
		Sleep(10);
		draw();
		input();
		logic();
		Die();
	}
	gotoxy(7, 7);
	cout << "leu leu thua roi" << endl;
	gotoxy(7, 8);
	cout << "score: " << score << endl;
	getch();
}