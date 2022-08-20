#include<iostream>
#include<fstream>
using namespace std;
#define MaxDeg 100
#define MaxPoly 10
struct Polynomial
{
	int d;
	char vname;
	int Cs[MaxDeg];
};

void LoadAPolynomial(ifstream& Rdr, Polynomial& p)
{
	Rdr >> p.d;
	for (int ci = 0; ci <= p.d; ci++)
	{
		int coeff;              // can also do it if put an int i variable in for loop starting from the 
		                          //degree value and decrementing it in the for loop
		Rdr >> coeff;              //for (int ci = 0,i=p.d; ci <= p.d; ci++,i--)
		p.Cs[p.d - ci] = coeff;   // p.Cs[i]=coeff;
		                          //for (int i = p.d; i >=0; i--)
	}

}
void PrintPolynomial(const Polynomial& p)
{
	
	for (int i = 0, ci = p.d; i <= p.d; i++, ci--)
	{
		if (p.Cs[ci] != 0)
		{
			if (i != 0)
				cout << ((p.Cs[ci] >= 0) ? "+" : " ");
			cout << p.Cs[ci];
			if (i != p.d)
			{
				if (i != p.d - 1)
					cout << "x^" << ci;
				else
					cout << "x";
			}
		}
		
			
	}
}
int max(int a, int b)
{
	return ((a < b) ? b : a);
}
int min(int a, int b)
{
	return ((a > b) ? b : a);
}

Polynomial Add(const Polynomial& p, const Polynomial& s)
{
	Polynomial R{};
	R.d = max(p.d, s.d);
	for (int i = 0; i <= R.d; i++)
	{
		R.Cs[i] = p.Cs[i] + s.Cs[i];
	}
	return R;
}
Polynomial Sub(const Polynomial& p, const Polynomial& s)
{
	Polynomial R{};
	R.d = max(p.d, s.d);
	for (int i = 0; i <= R.d; i++)
	{
		R.Cs[i] = p.Cs[i] - s.Cs[i];
	}
	for (int i = R.d; i >= 0; i--)
	{
		if (R.Cs[i] == 0)
			R.d--;
	}
	return R;
}
Polynomial Mult(const Polynomial& p, const Polynomial& s)
{
	Polynomial R{};
	R.d = p.d + s.d;
	for (int i = 0;i<=p.d; i++)
	{
		for (int j = 0; j <= s.d; j++)
		{
			R.Cs[i + j] += p.Cs[i] * s.Cs[j];
		}
	}
	return R;
}
Polynomial Div(const Polynomial& p, const Polynomial& s)
{  
	Polynomial R{};
	R.d = max(p.d, s.d);
	for (int i = 0; i <= R.d; i++)
	{
		R.Cs[i] = p.Cs[i] / s.Cs[i];
	}
	return R;
}
void LoadAllPolynomials(Polynomial Ps[MaxPoly], int& PSize)
{
	ifstream Rdr("poly.txt");
	Rdr >> PSize;
	for (int pi = 0; pi < PSize; pi++)
	{
		LoadAPolynomial(Rdr, Ps[pi]);
	}
}
void PrintAllPolynomials(const Polynomial Ps[MaxPoly], int PSize)
{
	system("cls");
	for (int pi = 0; pi < PSize; pi++)
	{
		PrintPolynomial(Ps[pi]);
		cout << endl;

	}
}
int main()
{
	Polynomial Ps[MaxPoly]{};
	int PSize;
	Polynomial Addition;
	Polynomial Subtraction;
	Polynomial M;
	Polynomial D;
	LoadAllPolynomials(Ps, PSize); 
	
	int ri, oli, ori;
	char opr,dummy, ToCont='Y';
	do {
		PrintAllPolynomials(Ps, PSize);
		cin >> dummy >> ri >> dummy >> dummy >> oli >> opr >> dummy >> ori;
		switch (opr)
		{
		case '+':
			Ps[ri] = Add(Ps[oli], Ps[ori]);
			break;
		case'-':
			Ps[ri] = Sub(Ps[oli], Ps[ori]);
			break;
		case'*':
			Ps[ri] = Mult(Ps[oli], Ps[ori]);
			break;


		}
		PrintAllPolynomials(Ps, PSize);
		cout << " Do you want to continue(Y/N) :" << endl;
		cin >> ToCont;
	} while (ToCont == 'Y' );
	

	/*Addition = Add(Ps[0], Ps[1]);
	cout << " Addition of polynomials" << endl;
	PrintPolynomial(Addition);
	cout << endl;
	Subtraction = Sub(Ps[0], Ps[1]);
	cout << " Subtraction of polynomials" << endl;
	PrintPolynomial(Subtraction);
	cout << endl;
	M = Mult(Ps[0], Ps[1]);
	cout << " Multiplication of polynomials" << endl;
	PrintPolynomial(M);
	cout << endl;
	D = Div(Ps[0], Ps[1]);
	cout << " Division of polynomials" << endl;
	PrintPolynomial(D);
	cout << endl;*/
	return 0;
}
