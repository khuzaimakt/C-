#include<iostream>
#include<math.h>
#include<windows.h>

using namespace std;
#define background -37
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
void INIT(char BOARD[][8])
{

	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			if (ri == 0)
			{

				{

					if (ci == 0)
						BOARD[ri][ci] = 'R';
					else if (ci == 7)
						BOARD[ri][ci] = '@';


					else if (ci == 1)
						BOARD[ri][ci] = 'H';
					else if (ci == 6)

						BOARD[ri][ci] = '#';


					else if (ci == 2)

						BOARD[ri][ci] = 'B';
					else if (ci == 5)

						BOARD[ri][ci] = '!';

					else if (ci == 3)

						BOARD[ri][ci] = 'Q';

					else if (ci == 4)

						BOARD[ri][ci] = 'K';


				}
			}



			if (ri == 7)
			{

				if (ci == 0 )
					BOARD[ri][ci] = 'r';
				if (ci == 7)
					BOARD[ri][ci] = '$';



				else if (ci == 1 )

					BOARD[ri][ci] = 'h';
				else if (ci == 6)

					BOARD[ri][ci] = '%';


				else if (ci == 2 )

					BOARD[ri][ci] = 'b';
				else if (ci == 5)

					BOARD[ri][ci] = '&';

				else if (ci == 3)

					BOARD[ri][ci] = 'q';

				else if (ci == 4)

					BOARD[ri][ci] = 'k';


			}
			if (ri == 1)
			{


				BOARD[ri][ci] = 'P';

			}

			if (ri == 6)
			{

				BOARD[ri][ci] = 'p';

			}
			if (ri == 2 || ri == 3 || ri == 4 || ri == 5)
				BOARD[ri][ci] = '-';
		}
	}
}
void display(char BOARD[8][8])
{
	system("cls");
	cout << "\n\t\t\t***************************************" << endl;
	cout << "\n\t\t\t\t WELCOME TO CHESS BOARD" << endl << endl;
	cout << "\t\t\t***************************************" << endl;
	cout << endl << endl;
	for (int ri = 0; ri < 8; ri++)
	{
		cout << "\t\t";

		for (int ci = 0; ci < 8; ci++)
		{

			cout << BOARD[ri][ci] << "\t";
		}
		cout << endl << endl;

	}
}
void MakeMoveSlection(int& sri, int& sci)
{


	cin >> sri >> sci;
	sri--;
	sci--;

}
void MakeDestSelection(int& dri, int& dci)
{
	cin >> dri >> dci;
	dri--;
	dci--;
}
bool IsBlack(char Sym)
{
	if (Sym >= 'A' && Sym <= 'Z'||(Sym=='!'||Sym=='@'||Sym=='#'))
		return true;
	else
		return false;
}
bool IsWhite(char Sym)
{
	if (Sym >= 'a' && Sym <= 'z'||(Sym=='$'||Sym=='%'||Sym=='&'))
		return true;
	else
		return false;
}
bool IsValidSelection(char sym, int Turn, int sri, int sci)
{
	if (sri >= 0 && sci >= 0 && sri <= 8 && sci <= 8)
	{
		if (Turn == 0)
		{
			return (IsBlack(sym));
		}
		if (Turn == 1)
		{
			return (IsWhite(sym));
		}
	}
	else
		return false;
}
bool IsValidDestination(char destsym, int Turn, int dri, int dci)
{
	if (dri >= 0 && dci >= 0 && dri <= 8 && dci <= 8)
	{
		if (Turn == 0)
		{
			if (destsym >= 'A' && destsym <= 'Z')
				return false;
			else
				return true;
		}
		if (Turn == 1)
		{
			if (destsym >= 'a' && destsym <= 'z')
				return false;
			else
				return true;
		}
	}
	else return false;


}
bool northsouthmove(int sri, int sci, int dri, int dci)
{
	return sci == dci;
}
bool eastwestmove(int sri, int sci, int dri, int dci)
{
	return sri == dri;
}
bool sloppymove(int sri, int sci, int dri, int dci)
{
	int deltarow = dri - sri;
	int deltacol = dci - sci;
	if (abs(deltarow) == abs(deltacol))
		return true;
	else
		return false;

}
bool DiagonalForPawn(char B[][8], int sri, int sci, int dri, int dci)
{
	char pawn;
	int deltar = dri - sri;
	int deltac = dci - sci;


	if (deltar > 0 && deltac < 0)
	{
		pawn = B[sri + 1][sci - 1];\
		if (IsWhite(pawn))
			return true;
		else
			return false;
	}

	if (deltar > 0 && deltac > 0)
	{
		pawn = B[sri + 1][sci + 1];
		if (IsWhite(pawn))
			return true;
		else
			return false;
	}


}
bool diagonalforpawn(char B[][8], int sri, int sci, int dri, int dci)
{
	char pawn;
	int deltar = dri - sri;
	int deltac = dci - sci;


	if (deltar < 0 && deltac < 0)
	{
		pawn = B[sri - 1][sci - 1];
		if (IsBlack(pawn))
			return true;
		else
			return false;
	}


	if (deltar < 0 && deltac > 0)
	{
		pawn = B[sri - 1][sci + 1];
		if (IsBlack(pawn))
			return true;
		else
			return false;
	}

}
bool isnorthsouthpath(char B[][8], int sri, int sci, int dri, int dci)
{
	int rs, re;
	if (sri < dri)
	{
		rs = sri + 1;
		re = dri - 1;
	}
	else
	{
		rs = dri + 1;
		re = sri - 1;
	}
	for (int r = rs; r <= re; r++)
	{
		if (B[r][dci] != '-')
			return false;
	}
	return true;


}
bool IsNSPathCLear(char B[][8], int sri, int sci, int dri, int dci)
{
	if (sri < dri)
	{
		for (int r = sri + 1; r < dri; r++)
		{
			if (B[r][sci] != '-')
				return false;
		}
		return true;
	}
	else
		for (int ri = sri - 1; ri > dri; ri--)
		{
			if (B[ri][sci] != '-')
				return false;
		}
	return true;


}
bool IsEWPathClear(char B[][8], int sri, int sci, int dri, int dci)
{

	if (sci < dci)
	{
		for (int r = sci+1 ; r < dci; r++)
		{
			if (B[sri][r] != '-')
				return false;
		}
		return true;
	}
	else
		for (int ri = sci - 1; ri > dci; ri--)
		{
			if (B[sri][ri] != '-')
				return false;
		}
	return true;

	
}
bool IsEastWestPathClear(char B[][8], int sri, int sci, int dri, int dci)
{
	int cs, ce;
	if (sci < dci)
	{
		cs = sci + 1;
		ce = dci - 1;
	}
	else
	{
		cs = dci + 1;
		ce = sci - 1;
	}
	for (int c = cs; c <= ce; c++)
	{
		if (B[sri][c] != '-')
			return false;
	}
	return true;
}
bool IsSloppyPathClear(char B[][8], int sri, int sci, int dri, int dci)
{
	int deltar = dri - sri;
	int deltac = dci - sci;
	if (deltar > 0 && deltac < 0)
	{
		for (int i = 1; i < deltar; i++)
		{
			if (B[sri + i][sci - i] != '-')
				return false;
		}
		return true;
	}
	if (deltar > 0 && deltac > 0)
	{
		for (int i = 1; i < deltar; i++)
		{
			if (B[sri + i][sci + i] != '-')
				return false;
		}
		return true;
	}
	if (deltar < 0 && deltac > 0)
	{
		for (int i = 1; i < deltar; i++)
		{
			if (B[sri - i][sci + i] != '-')
				return false;
		}
		return true;
	}
	if (deltar < 0 && deltac < 0)
	{
		for (int i = 1; i < deltar; i++)
		{
			if (B[sri - i][sci - i] != '-')
				return false;
		}
		return true;
	}



}
void MakeAMoveonBoard(char B[8][8], int sri, int sci, int dri, int dci)
{
	B[dri][dci] = B[sri][sci];
	B[sri][sci] = '-';
}
void TurnChange(int& Turn)
{
	Turn = (Turn + 1) % 2;
}
bool RookLegal(char B[][8], int sri, int sci, int dri, int dci)
{
	return (northsouthmove(sri, sci, dri, dci) && IsNSPathCLear(B, sri, sci, dri, dci)) ||
		(eastwestmove(sri, sci, dri, dci) && IsEWPathClear(B, sri, sci, dri, dci));
}
bool BishopLegal(char B[][8], int sri, int sci, int dri, int dci)
{
	return sloppymove(sri, sci, dri, dci) && IsSloppyPathClear(B, sri, sci, dri, dci);
}
bool QueenLegal(char B[][8], int sri, int sci, int dri, int dci)
{
	return RookLegal(B, sri, sci, dri, dci) || BishopLegal(B, sri, sci, dri, dci);
}

bool KingLegal(char B[][8], int sri, int sci, int dri, int dci)
{
	int deltar = abs(dri - sri);
	int deltac = abs(dci - sci);
	return (northsouthmove(sri, sci, dri, dci) || eastwestmove(sri, sci, dri, dci) || sloppymove(sri, sci, dri, dci))
		&& (deltar == 1 || deltac == 1);

}
bool KnightLegal(char B[][8], int sri, int sci, int dri, int dci)
{
	int deltar = abs(dri - sri);
	int deltac = abs(dci - sci);
	return (deltar == 1 && deltac == 2) || (deltar == 2 && deltac == 1);


}
bool iskill(int Turn, int destsym)
{
	if (Turn == 0)
	{
		if (destsym >= 'a' && destsym <= 'z')
			return true;
		else return false;
	}
	if (Turn == 1)
	{
		if (destsym >= 'A' && destsym <= 'Z')
			return true;
	}
}
bool PawnLegal(char B[][8], int sri, int sci, int dri, int dci)
{
	int deltar = dri - sri;
	int deltac = dci - sci;
	if (deltac == 0 && deltar > 0)
	{
		char sym;
		sym = B[sri + 1][sci];
		if (!IsWhite(sym))

			if (sri == 1)
			{
				if (deltar == 2 || deltar == 1)
				{
					return (northsouthmove(sri, sci, dri, dci) && IsNSPathCLear(B, sri, sci, dri, dci));
				}
			}
			else if (sri != 1)
			{
				if (deltar == 1)
				{
					return (northsouthmove(sri, sci, dri, dci) && IsNSPathCLear(B, sri, sci, dri, dci));
				}
			}
	}

	if (sloppymove(sri, sci, dri, dci))
	{
		char pawn;
		if (deltar > 0 && deltac < 0)
		{
			pawn = B[sri + 1][sci - 1];
			if (IsWhite(pawn))
				return true;
			else
				return false;
		}

		if (deltar > 0 && deltac > 0)
		{
			pawn = B[sri + 1][sci + 1];
			if (IsWhite(pawn))
				return true;
			else
				return false;
		}
	}





}
bool pawnlegall(char B[][8], int sri, int sci, int dri, int dci)
{
	int deltar = dri - sri;
	int deltac = dci - sri;
	if (deltac == 0 && deltar > 0)
	{
		char sym;
		sym = B[sri - 1][sci];
		if (!IsBlack(sym))
		{

			if (sri == 7)
			{
				if (deltar == -2 || deltar == -1)
				{
					return (northsouthmove(sri, sci, dri, dci) && IsNSPathCLear(B, sri, sci, dri, dci));
				}
			}


			else
			{
				if (deltar == 1)
				{
					return(northsouthmove(sri, sci, dri, dci) && IsNSPathCLear(B, sri, sci, dri, dci));
				}
			}
		}
	}
	char pawn;



	if (sloppymove(sri, sci, dri, dci))
	{
		if (deltar < 0 && deltac < 0)
		{
			pawn = B[sri - 1][sci - 1];
			if (IsBlack(pawn))
				return true;
			else
				return false;
		}


		if (deltar < 0 && deltac > 0)
		{
			pawn = B[sri - 1][sci + 1];
			if (IsBlack(pawn))
				return true;
			else
				return false;
		}
	}
}
bool PawnLegally(char B[][8], int sri, int sci, int dri, int dci)
{
	int deltar = dri - sri;
	int deltac = dci - sci;

	if (deltac == 0 && deltar < 0)
	{
		char sym;
		sym = B[sri - 1][sci];
		if (!IsBlack(sym))

			if (sri == 6)
			{
				if (deltar == -2 || deltar == -1)
				{
					return  IsNSPathCLear(B, sri, sci, dri, dci);
				}
			}
			else
			{
				if (deltar == -1)
				{
					return (northsouthmove(sri, sci, dri, dci) && IsNSPathCLear(B, sri, sci, dri, dci));
				}
			}
	}

	if (sloppymove(sri, sci, dri, dci))
	{
		char pawn;
		if (deltar < 0 && deltac > 0)
		{
			pawn = B[sri - 1][sci + 1];
			if (IsBlack(pawn))
				return true;
			else
				return false;
		}

		if (deltar < 0 && deltac < 0)
		{
			pawn = B[sri - 1][sci - 1];
			if (IsBlack(pawn))
				return true;
			else
				return false;
		}
	}





}
bool islegalmove(char B[][8], int sri, int sci, int dri, int dci)
{
	switch (B[sri][sci])
	{
	case 'R':
	case '@':
	case 'r':
	case '$':
		return RookLegal(B, sri, sci, dri, dci);
		break;

	case 'H':
	case '#':
	case'h':
	case'%':
		return KnightLegal(B, sri, sci, dri, dci);
		break;

	case 'B':
	case '!':
	case'b':
	case '&':
		return BishopLegal(B, sri, sci, dri, dci);
		break;

	case 'K':
	case'k':
		return KingLegal(B, sri, sci, dri, dci);
		break;

	case 'Q':
	case'q':
		return QueenLegal(B, sri, sci, dri, dci);
		break;

	case 'P':

		return PawnLegal(B, sri, sci, dri, dci);


		break;
	case 'p':
		return	PawnLegally(B, sri, sci, dri, dci);
		break;
	}
}
bool islegalhighlight(char B[][8], char sym, int sri, int sci, int dri, int dci)
{
	switch (sym)
	{
	case 'R':
	case 'r':
		return RookLegal(B, sri, sci, dri, dci);
		break;

	case 'H':
	case 'h':
		return KnightLegal(B, sri, sci, dri, dci);
		break;

	case 'B':
	case 'b':
		return BishopLegal(B, sri, sci, dri, dci);
		break;

	case 'K':
	case'k':
		return KingLegal(B, sri, sci, dri, dci);
		break;

	case 'Q':
	case'q':
		return QueenLegal(B, sri, sci, dri, dci);
		break;

	case 'P':

		return PawnLegal(B, sri, sci, dri, dci);


		break;
	case 'p':
		return	PawnLegally(B, sri, sci, dri, dci);
		break;
	}
}
bool iskingkill(char B[][8], int Turn, int sri, int sci, int dri, int dci)
{
	if (Turn == 0)
	{
		return(B[dri][dci] == 'k' && islegalmove(B, sri, sci, dri, dci));


	}
	else if (Turn == 1)
	{

		return (B[dri][dci] == 'K' && islegalmove(B, sri, sci, dri, dci));



	}

}
void highlight(char B[][8], int sri, int sci)
{


	for (int toR = 8; toR > 0; toR--)
	{
		for (int toC = 8; toC > 0; toC--)
		{
			if (islegalmove(B, sri, sci, toR, toC))
			{
				if (B[toR][toC] == '-')
				{
					B[toR][toC] = '*';
				}
			}

		}
	}


}
void displayspace(char B[][8])
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (B[r][c] == '*')
			{
				B[r][c] = '-';
			}
		}

	}
}
void kingposition(char B[][8], int& kri, int& kci, int turn)
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			switch (turn)
			{
			case 1:
				if (B[ri][ci] == 'k')
				{
					kri = ri;
					kci = ci;
					break;
				}
			case 0:
				if (B[ri][ci] == 'K')
				{
					kri = ri;
					kci = ci;
					break;
				}
			}
		}
	}
}
void queenposition(char B[][8], int& qri, int& qci, int& QRI, int& QCI, int turn)
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			switch (turn)
			{
			case 0:
				if (B[ri][ci] == 'q')
				{
					qri = ri;
					qci = ci;
					break;

				}
			case 1:
				if (B[ri][ci] == 'Q')
				{
					QRI = ri;
					QCI = ci;
					break;
				}
			}
		}
	}
}
void queenposition1(char B[][8], int& qri, int& qci, int& QRI, int& QCI, int turn)
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			switch (turn)
			{
			case 1:
				if (B[ri][ci] == 'q')
				{
					qri = ri;
					qci = ci;

				}
			case 0:
				if (B[ri][ci] == 'Q')
				{
					QRI = ri;
					QCI = ci;
				}
			}
		}
	}
}
void pawnposition(char B[][8], int& pri, int& pci, int turn)
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			switch (turn)
			{
			case 1:
				if (B[ri][ci] == 'p')
				{
					pri = ri;
					pci = ci;
					break;
				}
			case 0:
				if (B[ri][ci] == 'P')
				{
					pri = ri;
					pci = ci;
					break;
				}
			}
		}
	}
}
void rookposition(char B[][8], int& rri, int& rci, int turn)
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			switch (turn)
			{
			case 0:
				if (B[ri][ci] == 'r')
				{
					rri = ri;
					rci = ci;
					break;

				}
			case 1:
				if (B[ri][ci] == 'R')
				{
					rri = ri;
					rci = ci;
					break;
				}
			}
		}
	}
}
void horseposition(char B[][8], int& hri, int& hci, int& HRI, int& HCI, int turn)
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			switch (turn)
			{
			case 0:
				if (B[ri][ci] == 'h')
				{
					hri = ri;
					hci = ci;
					break;

				}
			case 1:
				if (B[ri][ci] == 'H')
				{
					HRI = ri;
					HCI = ci;
					break;
				}
			}
		}
	}
}
void bishopposition(char B[][8], int& bri, int& bci, int& BRI, int& BCI, int turn)
{
	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			switch (turn)
			{
			case 0:
				if (B[ri][ci] == 'b')
				{
					bri = ri;
					bci = ci;
					break;
				}
			case 1:
				if (B[ri][ci] == 'B')
				{
					BRI = ri;
					BCI = ci;
					break;
				}
			}
		}
	}
}
void rookiecheck(char B[][8], int kri, int kci, int turn)
{
	if (turn == 0)
	{
		for (int ri = 0; ri < 8; ri++)
		{
			for (int ci = 0; ci < 8; ci++)
			{


				if (B[ri][ci] == 'r')
				{

					if (RookLegal(B, ri, ci, kri, kci))
					{
						cout << "Check";
					}
				}
			}
		}
		for (int ri = 0; ri < 8; ri++)
		{
			for (int ci = 0; ci < 8; ci++)
			{

				if (B[ri][ci] == '$')
				{

					if (RookLegal(B, ri, ci, kri, kci))
					{
						cout << "Check";
					}
				}
			}
		}

	}

	
	if (turn == 1)
	{
		for (int ri = 0; ri < 8; ri++)
		{
			for (int ci = 0; ci < 8; ci++)
			{
				if (B[ri][ci] == 'R')
				{

					if (RookLegal(B, ri, ci, kri, kci))
					{
						cout << "Check";
					}
				}
			}
		}
		for (int ri = 0; ri < 8; ri++)
		{
			for (int ci = 0; ci < 8; ci++)
			{
				if (B[ri][ci] == '@')
				{

					if (RookLegal(B, ri, ci, kri, kci))
					{
						cout << "Check";
					}
				}
			}
		}
	}
	

}
bool rookiecheck1(char B[][8], int kri, int kci, int turn)
{



	for (int ri = 0; ri < 8; ri++)
	{
		for (int ci = 0; ci < 8; ci++)
		{
			if (B[ri][ci] == 'R')
			{

				return(RookLegal(B, ri, ci, kri, kci));
			}
		}
	}

}
bool check(char B[][8], int kri, int kci, int turn)

{
	if (turn == 0)
	{
		for (int i = 0; i < 64; i++)
		{
			for (int ri = 0; ri < 8; ri++)
			{
				for (int ci = 0; ci < 8; ci++)
				{
					switch (B[ri][ci])
					{
					case 'r':
						return(RookLegal(B, ri, ci, kri, kci));
						
					case '$':
						return(RookLegal(B, ri, ci, kri, kci));
						

					case 'q':
						return (QueenLegal(B, ri, ci, kri, kci));
					
					case 'p':
						return(PawnLegally(B, ri, ci, kri, kci));
						
					case 'h':
						return(KnightLegal(B, ri, ci, kri, kci));
						
					case '%':
						return(KnightLegal(B, ri, ci, kri, kci));
					
					case 'b':
						return(BishopLegal(B, ri, ci, kri, kci));
						
					case '&':
						return(BishopLegal(B, ri, ci, kri, kci));
						

					}




				}
			}
		}
	}
	if (turn == 1)
	{
		for (int i = 0; i <= 64; i++)
		{
			for (int ri = 8; ri > 0; ri--)
			{
				for (int ci = 8; ci > 0; ci--)
				{
					switch (B[ri][ci])
					{
					case 'R':

						/*return (northsouthmove(ri, ci, kri, kci) && IsNSPathCLear(B, ri, ci, kri, kci)) ||
							(eastwestmove(ri, ci, kri, kci) && IsEWPathClear(B, ri, ci, kri, kci));*/
						return(RookLegal(B, ri, ci, kri, kci));
					case '@':
						return(RookLegal(B, ri, ci, kri, kci));
					case 'Q':
						return (QueenLegal(B, ri, ci, kri, kci));
					case 'P':
						return(PawnLegal(B, ri, ci, kri, kci));
					case 'H':
						return(KnightLegal(B, ri, ci, kri, kci));
					case '#':
						return(KnightLegal(B, ri, ci, kri, kci));
					case 'B':
						return(BishopLegal(B, ri, ci, kri, kci));
					case '!':
						return(BishopLegal(B, ri, ci, kri, kci));

					}
				}
			}
		}
	}
	return false;
}
void highlighting(char B[][8], int sri, int sci, int qri, int qci, int QRI, int QCI, int Turn)
{


	for (int toR = 8; toR > 0; toR--)
	{
		for (int toC = 8; toC > 0; toC--)
		{
			if (Turn == 0)
			{

				if (B[sri][sci] == 'Q')
				{

					if (islegalmove(B, QRI, QCI, toR, toC))
					{
						if (B[toR][toC] == '-')
						{
							B[toR][toC] = '*';
						}
					}

				}

			}
		}
	}




}

int main()
{
	int Turn = 0;
	char B[8][8] = {};
	int sri, sci, dri, dci;
	char sym;
	int kri, kci;
	int pri, pci;
	
	int count=0;
	
	bool win = false;
	char destsym;
	char prom,prom1;
	
	INIT(B);
	do {
		display(B);
		kingposition(B, kri, kci, Turn);
		pawnposition(B, pri, pci, Turn);





		if (check(B, kri, kci, Turn))
		{
			cout << "CHECK";

		}
		if (Turn == 0 && pri == 7)
		{

			cout << " Pawn promotion enter any piece you want to replace with pawn" << endl;
			cin >> prom;
			B[pri][pci] = prom;
		}
		if (Turn == 1 && pri == 0)
		{

			cout << " Pawn promotion enter any piece you want to replace with pawn" << endl;
			cin >> prom1;
			B[pri][pci] = prom1;
		}




		cout << endl << endl;
		cout << "Player No " << Turn + 1 << " turn: " << endl << endl;
		do {
			cout << " Enter Selection Row And Column:(1-8) " << endl;
			MakeMoveSlection(sri, sci);


			sym = B[sri][sci];



		} while (!IsValidSelection(sym, Turn, sri, sci));
		

		do {
          cout << "Enter Destination Row And Column:(1-8) " << endl;
			MakeDestSelection(dri, dci);
			destsym = B[dri][dci];
			
		} while (!IsValidDestination(destsym, Turn, dri, dci));
		
		 if (islegalmove(B, sri, sci, dri, dci) && (!iskingkill(B, Turn, sri, sci, dri, dci)))
		{
			MakeAMoveonBoard(B, sri, sci, dri, dci);
			TurnChange(Turn);
		}
		
		
			
		
		
		
		
	} while (!iskingkill(B, Turn, sri, sci, dri, dci));
	system("cls");
	if (Turn==0)
	{
		cout << "\n\t\t\t******************************************" << endl;
		cout << "\n\t\t\t\t PLAYER 1 HAS WON" << endl << endl;
		cout << "\t\t\t***************************************" << endl;
		cout << endl << endl;
	}
	if(Turn==1)
	{
		cout << "\n\t\t\t***************************************" << endl;
		cout << "\n\t\t\t\t PLAYER 2 HAS WON" << endl << endl;
		cout << "\t\t\t***************************************" << endl;
		cout << endl << endl;
	}

	


	return 0;
}