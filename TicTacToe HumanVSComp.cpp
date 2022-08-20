#include <iostream>
#include<conio.h>
#include <fstream>
#include<ctime>
using namespace std;
#define Capacity 50
enum TYPE{HUMAN, COMPUTER};
void init(char board[][Capacity], int& Dim, char PName[][30], int& Turn)
{
	ifstream Rdr("Text.txt");
	Rdr >> Dim;
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			Rdr >> board[ri][ci];

		}
	}
	cout << "Player 1 Name: " << endl;
	cin >> PName[0];
	cout << "Player 2 Name: " << endl;
	cin >> PName[1];
	Turn = rand() % 2;




}
void DisplayBoard(char board[][Capacity], int Dim)
{
	system("cls");
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			cout << board[ri][ci] << " ";
		}
		cout << endl;
	}

}
void DisplayTurnMsg(char aiknaam[], char aiksym)
{
	cout << endl << "Symbol: " << aiksym << endl << aiknaam << " 's Turn[ri,ci]: " << endl;
}
void SelectPosition(int& ri, int& ci)
{
	cin >> ri >> ci;
	ri--;
	ci--;
}
bool IsValidDestination(int ri, int ci, int Dim, char board[][Capacity])
{
	return(ri >= 0 && ci >= 0) && (ri < Dim&& ci < Dim) && (board[ri][ci] == '-');
}

void UpdateBoard(char board[][Capacity], int ri, int ci, char aiksym)
{
	board[ri][ci] = aiksym;
}
void TurnChange(int& Turn)
{
	Turn = (Turn + 1) % 2;
}
bool ishorwin(char board[][Capacity], int Dim, int ri, int ci, int WinCount, char Player)
{
	if (ci + WinCount - 1 >= Dim)
		return false;
	for (int i = 0; i < WinCount; i++)
	{

		if (board[ri][ci + i] != Player)
			return false;
	}
	return true;
}
bool isvertwin(char board[][Capacity], int Dim, int ri, int ci, int WinCount, char Player)
{
	if (ri + WinCount - 1 >= Dim)
		return false;
	for (int i = 0; i < WinCount; i++)
	{


		if (board[ri + i][ci] != Player)
			return false;
	}
	return true;
}
bool isdiagrightwin(char board[][Capacity], int Dim, int ri, int ci, int WinCount, char Player)
{
	if (ri + WinCount - 1 >= Dim)
		return false;
	if (ci + WinCount - 1 >= Dim)
		return false;

	for (int i = 0; i < WinCount; i++)
	{

		if (board[ri + i][ci + i] != Player)
			return false;
	}
	return true;
}
bool isdiagftwin(char board[][Capacity], int Dim, int ri, int ci, int WinCount, char Player)
{
	if (ri + WinCount - 1 >= Dim)
		return false;
	if (ci - (WinCount - 1) < 0)
		return false;

	for (int i = 0; i < WinCount; i++)
	{

		if (board[ri + i][ci - i] != Player)
			return false;
	}
	return true;
}


bool  IsWin(char board[][Capacity], int Dim, int WinCount, char Player)
{
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)
		{
			if (ishorwin(board, Dim, ri, ci, WinCount, Player) ||
				isvertwin(board, Dim, ri, ci, WinCount, Player) ||
				isdiagrightwin(board, Dim, ri, ci, WinCount, Player) ||
				isdiagftwin(board, Dim, ri, ci, WinCount, Player))
			{
				return true;
			}
		}
	}
	return false;
}



bool isdraw(char board[][Capacity], int Dim)
{
	for (int ri = 0; ri < Dim; ri++)
	{
		for (int ci = 0; ci < Dim; ci++)

		{
			if (board[ri][ci] == '-')
				return false;
		}
	}
	return true;
}
void HumanvsComputer(char board[][Capacity], int& ri, int& ci, int Dim, int WinCount, char aiksym)
{



	for (WinCount = WinCount; WinCount > 3; WinCount--)
	{
		for (ri = 0; ri < Dim; ri++)
		{
			for (ci = 0; ci < Dim; ci++)
			{
				if (board[ri][ci] == '-')
					board[ri][ci] = aiksym;
				if (IsWin(board, Dim, WinCount, aiksym))
				{
					board[ri][ci] = '-';


					return;
				}
				else
					board[ri][ci] = '-';

			}

		}
	}
	do {
		ri = rand() % Dim;
		ci = rand() % Dim;
	} while (board[ri][ci] != '-');
}
void HvsC(char board[][Capacity], int& ri, int& ci, int Dim, int WinCount, char CS, char HS)

{
	char T[Capacity][Capacity];
	for (int r = 0; r < Dim; r++)
	{
		for (int c = 0; c < Dim; c++)
		{
			T[r][c] = board[r][c];
		}
	}
	for (int WC = WinCount; WC > WinCount - 3; WC--)
	{
		for (int r = 0; r < Dim; r++)
		{
			for (int c = 0; c < Dim; c++)
			{
				if (IsValidDestination(r, c, Dim, board))
				{
					board[r][c] = CS;
					if (IsWin(board, Dim, CS, WC))
					{
						ri = r;
						ci = c;
						board[r][c] = '-';
						return;
					}
					else
					{
						board[r][c] = '-';
					}
				}
			}
				
		}
		for (int r = 0; r < Dim; r++)
		{
			for (int c = 0; c < Dim; c++)
			{
				if (IsValidDestination(r, c, Dim, T))
				{
					T[r][c] = HS;
					if (IsWin(T, Dim, HS, WC))
					{
						ri = r;
						ci = c;
						return;
					}
					else
					{
						T[r][c] = '-';
					}
				}
			}
		}
	}

	do {
		ri = rand() % Dim;
		ci = rand() % Dim;
	} while (!IsValidDestination(ri, ci, Dim, board));
}







int main()
{
	srand(time(0));
	char board[Capacity][Capacity];
	int Dim;
	int ri, ci;
	char PName[2][30];
	char PSym[2] = { '#','*' };
	int Turn;
	int WinCount = 3;
	bool GameOver = false;
	int Winner = -1;
	init(board, Dim, PName, Turn);
	DisplayBoard(board, Dim);
	do
	{
		
		if (Turn == HUMAN)
		{
			DisplayTurnMsg(PName[Turn], PSym[Turn]);
			do {

				SelectPosition(ri, ci);


			} while (!IsValidDestination(ri, ci, Dim, board));
		}
		else
		{
			HvsC(board, ri, ci, Dim, WinCount, PSym[COMPUTER], PSym[HUMAN]);
		}
		UpdateBoard(board, ri, ci, PSym[Turn]);
		DisplayBoard(board, Dim);

		GameOver = IsWin(board, Dim, WinCount, PSym[Turn]);
		if (GameOver)  
			Winner = Turn;
		if (!GameOver)
			GameOver = isdraw(board, Dim);
		if (!GameOver)
			TurnChange(Turn);
	} while (!GameOver);
	if (Winner == -1)

		cout << " The game is draw";
	else
		cout << PName[Winner] << " has won the match";



	return 0;


}