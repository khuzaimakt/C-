#include<iostream>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<math.h>
#include<iomanip>
using namespace std;
#define UPKey 72
#define DOWNKey 80
#define RIGHTKey 77
#define LEFTKey 75
#define ROWS 80
#define COLS 80
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

struct position
{
	int c, r;
};

struct snake
{
	int size;
	position* Ps;
	char sym;
	int color;
	int LKey;
	int RKey;
	int UKey;
	int DKey;
	int direction;
};
bool Isvalidfoodposition(snake S, position FPosition)
{
	for (int pi = 0; pi < S.size; pi++)
	{
		if (FPosition.r == S.Ps[pi].r && FPosition.c == S.Ps[pi].c)
			return false;
	}
	return true;
	
}

void foodgenerate( snake S,position& FPosition)
{
	do
	{
		FPosition.r = rand() % ROWS;
		FPosition.c = rand() % COLS;
	} while (!Isvalidfoodposition(S, FPosition));
}
void displayfood(position& FPosition)
{
	char fsym = -37;
	gotoRowCol(FPosition.r, FPosition.c);
	cout << fsym;
}
bool gameover(snake S)
{
	for (int si = 1; si < S.size; si++)
	{
		if (S.Ps[0].r == S.Ps[si].r && S.Ps[0].c == S.Ps[si].c)
			return true;
	}
	return false;
}
bool foodcapture(snake S, position FPosition)
{
	return S.Ps[0].r == FPosition.r && S.Ps[0].c == FPosition.c;
}
void extendsnake(snake &S,position TP)
{
	position* HPs = new position[S.size + 1];
	for (int pi = 0; pi < S.size; pi++)
	{
		HPs[pi] = S.Ps[pi];
	}
	HPs[S.size] = TP;
	delete[] S.Ps;
	S.Ps = HPs; 
	S.size++;

}

void displaysnake(snake S, char sym)
{
	for (int si = 0; si < S.size; si++)
	{
	gotoRowCol(S.Ps[si].r, S.Ps[si].c);
			cout << sym;
		}
	gotoRowCol(S.Ps[0].r, S.Ps[0].c);
}
void movesnake(snake &S)
{
	for (int pi = S.size; pi > 0; pi--)
	{
		S.Ps[pi] = S.Ps[pi - 1];
	}
	switch (S.direction)
	{
	case UP:
		S.Ps[0].r--;
		if(S.Ps[0].r==-1)
		{ 
			S.Ps[0].r = ROWS - 1;

			 }
		break;
	case DOWN:
		S.Ps[0].r++;
		if (S.Ps[0].r == ROWS)
		{
			S.Ps[0].r == 0;
		}
		break;
	case LEFT:
		S.Ps[0].c--;
		if (S.Ps[0].c == -1)
		{
			S.Ps[0].c == COLS - 1;
		}
		break;
	case RIGHT:
		S.Ps[0].c++;
		if (S.Ps[0].c == COLS)
		{
			S.Ps[0].c == 0;
		}
		break;
	}
}
void init(snake& S, position& FPosition)
{
	S.size = 3;
	S.sym = -37;
	S.Ps = new position[S.size];
	S.Ps[0].r = ROWS / 2;
	S.Ps[0].c = COLS / 2;
	S.Ps[0].r = ROWS / 2;
	S.Ps[0].c = COLS / 2-1;
	S.Ps[0].r = ROWS / 2;
	S.Ps[0].c = COLS / 2-2;
	

	S.LKey = LEFTKey;
	S.RKey = RIGHTKey;
	S.UKey = UPKey;
	S.DKey = DOWNKey;
	S.direction = UP;
	foodgenerate(S,FPosition);
}


int main()
{
	int keycode = 0;
	int key;
	snake S;
	position FPosition;
	position TPosition;
	
	
	init(S,FPosition);
	do
	{
		displayfood(FPosition);
		TPosition = S.Ps[S.size - 1];
		displaysnake(S,S.sym);
		
		if (_kbhit())
		{
			
			keycode = _getch();
			if (S.LKey == keycode && S.direction != RIGHT)
			{
				S.direction = LEFT;
			}
			else if (S.RKey == keycode && S.direction !=LEFT)
			{
				S.direction = RIGHT;
			}
			else if(S.UKey == keycode && S.direction !=DOWN)
			{
				S.direction = UP;
			}
			else if (S.DKey == keycode && S.direction!=UP)
			{
				S.direction = DOWN;
			}

		}
		
		Sleep(100);
		displaysnake(S,' ');
		movesnake(S);
		if (foodcapture(S, FPosition))
		{
			extendsnake(S, TPosition);
			foodgenerate(S,FPosition);

		}

	} while (!gameover(S));
	return 0;
}