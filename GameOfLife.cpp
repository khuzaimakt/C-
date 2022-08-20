#include<iostream>
#include<conio.h>
using namespace std;
#define Rows 82
#define Cols 118
void INIT(char world[Rows][Cols], int R, int C, int lifesym)
{
	for (int ri = 0; ri < R; ri++)
	{
		for (int ci = 0; ci < C; ci++)
		{
			world[ri][ci] = ' ';
		}
	}
	for (int ci = 0; ci < C; ci++)
	{
		world[R / 2][ci] = lifesym;
	}
	for (int ri = 0; ri < R; ri++)
	{
		world[ri][C / 2] = lifesym;
	}

}
void INIT1(char world[Rows][Cols], int R, int C)
{
	for (int ri = 0; ri < R; ri++)
	{
		for (int ci = 0; ci < C; ci++)
		{
			world[ri][ci] = ' ';
		}
	}
}
void displayworld(char world[Rows][Cols], int R, int C)
{
	system("cls");
	for (int ri = 0; ri < R; ri++)
	{
		for (int ci = 0; ci < C; ci++)
			cout << world[ri][ci];
	}

}
int neighbourhoodlifecount(char world[Rows][Cols], int R, int C, int ri, int ci, char LS)
{
	int count = 0;
	for (int r = ri - 1; r <= ri + 1; r++)
	{
		if (r < 0 || r == R)
			continue;
		for (int c = ci - 1; c <= ci + 1; c++)
		{
			if (c < 0 || c == C)
				continue;
			if (r == ri && c == ci)
				continue;
			if (world[r][c] == LS)
				count++;
		}
	}
	return count;
}
void repopulate(char world[Rows][Cols], int R, int C, int sym)
{  
	char dworld[Rows][Cols];
	

	
		for (int ri = 0; ri < R; ri++)
		{
			for (int ci = 0; ci < C; ci++)
			{
				int count = neighbourhoodlifecount(world, R, C, ri, ci, sym);
				if (world[ri][ci] == sym && count < 2)
				{
					dworld[ri][ci] = ' ';
				}
				else if (world[ri][ci] == sym && (count >= 2 && count <= 3))
				{
					dworld[ri][ci] = world[ri][ci];
				}
				else if (world[ri][ci] == sym && count > 3)
				{
					dworld[ri][ci] = ' ';
				}
				else if (world[ri][ci] == ' ' && count == 3)
				{
					dworld[ri][ci] = sym;
				}
				else
					dworld[ri][ci] = world[ri][ci];
			}
		}
		for (int ri = 0; ri < R; ri++)
		{
			for (int ci = 0; ci < C; ci++)
			{
				world[ri][ci] = dworld[ri][ci];
			}
		}
	

}
int main()
{
	_getch();
	char world[Rows][Cols];

	int sym = '*';
	INIT(world, Rows, Cols, sym);
	do {
		displayworld(world, Rows, Cols);
		repopulate(world, Rows, Cols, sym);
	} while (true);




	return 0;
}  