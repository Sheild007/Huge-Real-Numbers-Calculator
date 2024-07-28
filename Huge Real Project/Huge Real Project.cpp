#include<iostream>
#include<fstream>
#include<stdexcept>
#include"HugeReal.h"
#include"HugeHex.h"
#include"RealHex.h" 

using namespace std;

HugeReal* Load(const char* fName, int& Size)
{
	ifstream rdr(fName);
	if (!rdr)
		cout << "Loading Fail...." << endl, exit(1);

	rdr >> Size;
	HugeReal* rtr;
	rtr = new HugeReal[Size];
	while (rdr.peek() == '\n' || rdr.peek() == ' ')
	{
		rdr.ignore();
	}
	for (int i = 0; i < Size; i++)
	{
		rtr[i].Load(rdr);
	}

	return rtr;
}
void Print(HugeReal* Is, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		cout << "N" << i + 1 << "=" << Is[i] << endl;

	}
}
void StoreResult(HugeReal*& Is, int& Size, HugeReal result)
{

	HugeReal* NewIs;
	NewIs = new HugeReal[Size + 1];
	for (int i = 0; i < Size; i++)
	{
		NewIs[i] = Is[i];
	}
	NewIs[Size] = result;
	delete[]Is;
	Is = NewIs;
	Size++;
	NewIs = NULL;
}
void menuReal()
{
	cout << "Add(+)\t\tSubtract(-)" << endl;
	cout << "Multiplay(x)\tDivide(/)" << endl;
	cout << "Trim(t)" << endl;
	cout << "Less(<)\t\tGreater(>)" << endl;
	cout << "Equal(=) \tNew Number(n)" << endl;
	cout << "0.Return" << endl;
}
void mainReal()
{
	int size = 0;
	HugeReal* Is = Load("double.txt", size);
	HugeReal result;
	char choice = '1', s;
	int  i, j;

	while (choice != '0')
	{
		system("cls");
		cout << "Input Data From File:" << endl;
		cout << "\n_____________________________________\n";
		Print(Is, size);
		cout << "\n_____________________________________\n\n";
		menuReal();
		cout << "\n_____________________________________\n\n";
	
		cout << "Choice:";
		cin >> choice;
		try{
			try
			{
				switch (choice)
				{
				case '0':
					break;
				case '+':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					result = Is[i - 1] + (Is[j - 1]);
					cout << " Result=" << result << endl;
					cout << " Wanna Store Result (y/n):";
					cin >> s;
					if (toupper(s) == 'Y')
					{
						StoreResult(Is, size, result);
						cout << "Result is stored." << endl;
					}
					break;
				case '-':
					cout << " Enter number 1:";
cin >> i;
cout << " Enter number 2:";
cin >> j;
result = Is[i - 1] - (Is[j - 1]);
cout << " Result=" << result << endl;
cout << " Wanna Store Result (y/n):";
cin >> s;
if (toupper(s) == 'Y')
{
	StoreResult(Is, size, result);
	cout << "Result is stored." << endl;
}
break;
				case '/':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					result = Is[i - 1] / (Is[j - 1]);
					cout << " Result=" << result << endl;
					cout << " Wanna Store Result (y/n):";
					cin >> s;
					if (toupper(s) == 'Y')
					{
						StoreResult(Is, size, result);
						cout << "Result is stored." << endl;
					}
					break;
				case '*':
				case 'x':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					result = Is[i - 1] * (Is[j - 1]);
					cout << " Result=" << result << endl;
					cout << " Wanna Store Result (y/n):";
					cin >> s;
					if (toupper(s) == 'Y')
					{
						StoreResult(Is, size, result);
						cout << "Result is stored." << endl;
					}
					break;
				case '=':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					if (Is[i - 1] == (Is[j - 1]))
						cout << "HI" << i << " is equal to HI" << j << endl;
					else
						cout << "HI" << i << " is not  equal to HI" << j << endl;


					break;
				case '<':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					if (Is[i - 1] < (Is[j - 1]))
						cout << "HI" << i << " is less than HI" << j << endl;
					else
						cout << "HI" << i << " is not less than HI" << j << endl;

					break;
				case '>':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					if (Is[i - 1] > (Is[j - 1]))
						cout << "HI" << i << " is greater than HI" << j << endl;
					else
						cout << "HI" << i << " is not greater than HI" << j << endl;

					break;
				case 't':
					cout << " Enter a number :";
					cin >> i;
					Is[i - 1].Trim();
					cout << "After Trim:" << Is[i - 1] << endl;
					break;
				case'n':
					cout << " Enter Number:";
					cin >> result;
					StoreResult(Is, size, result);
					cout << "Number is added." << endl;
					break;
				default:
					break;
				}
			}
			catch (invalid_argument& e)
			{
				cout << "Error: " << e.what() << endl;
			}
		}
		catch(string exp)
		{
			cout << exp<<endl;
        }
		system("pause");
	}
	
}
HugeHex* Load1(const char* fName, int& Size,int b)
{
	ifstream rdr(fName);
	if (!rdr)
		cout << "Loading Fail...." << endl, exit(1);

	rdr >> Size;
	HugeHex* rtr;
	rtr = new HugeHex[Size];
	while (rdr.peek() == '\n' || rdr.peek() == ' ')
	{
		rdr.ignore();
	}
	
		for (int i = 0; i < Size; i++)
		{
			rtr[i].Load(rdr, b);
		}
	
	return rtr;
}
void Print1(HugeHex* Is, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		cout << "N" << i + 1 << "=" << Is[i] << endl;

	}
}
void StoreResult(HugeHex*& Is, int& Size, HugeHex result)
{

	HugeHex* NewIs;
	NewIs = new HugeHex[Size + 1];
	for (int i = 0; i < Size; i++)
	{
		NewIs[i] = Is[i];
	}
	NewIs[Size] = result;
	delete[]Is;
	Is = NewIs;
	Size++;
	NewIs = NULL;
}
void menuHex()
{
	cout << "Add(+)\t\tSubtract(-)" << endl;
	cout << "Multiplay(x)\tDivide(/)" << endl;
	cout << "Modulus(%)\tTrim(t)" << endl;
	cout << "Less(<)\t\tGreater(>)" << endl;
	cout << "Equal(=) \tNew Number(n)" << endl;
	cout << "0.Return" << endl;
}
void mainHex()
{
	
	cout << "Enter Base:";
		int b;
	cin >> b;
	if (b > 36 || b < 2)
	{
		cout << " invalid Base" << endl;
		return;
	}
	int size = 0;
	HugeHex* Is;
	try 
	{
		 Is = Load1("Hex.txt", size, b);
	}
	catch (string exp)
	{
		cout << "Error: the given Input from file is greater than base " << b << endl;
		return;
	}


	HugeHex result;
	char choice = '1', s;
	int  i, j;
	while (choice != '0')
	{
		system("cls");
		cout << "Input Data From File:" << endl;
		cout << "\n_____________________________________\n";
		Print1(Is, size);
		cout << "\n_____________________________________\n\n";
		menuHex();
		cout << "\n_____________________________________\n\n";

		cout << "Choice:";
		cin >> choice;
		try
		{
			try
			{
				switch (choice)
				{
				case '0':
				
					break;
				case '+':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					result = Is[i - 1] + (Is[j - 1]);
					cout << " Result=" << result << endl;
					cout << " Wanna Store Result (y/n):";
					cin >> s;
					if (toupper(s) == 'Y')
					{
						StoreResult(Is, size, result);
						cout << "Result is stored." << endl;
					}
					break;
				case '-':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					result = Is[i - 1] - (Is[j - 1]);
					cout << " Result=" << result << endl;
					cout << " Wanna Store Result (y/n):";
					cin >> s;
					if (toupper(s) == 'Y')
					{
						StoreResult(Is, size, result);
						cout << "Result is stored." << endl;
					}
					break;
				case '/':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					result = Is[i - 1] / (Is[j - 1]);
					cout << " Result=" << result << endl;
					cout << " Wanna Store Result (y/n):";
					cin >> s;
					if (toupper(s) == 'Y')
					{
						StoreResult(Is, size, result);
						cout << "Result is stored." << endl;
					}
					break;
				case '*':
				case 'x':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					result = Is[i - 1] * (Is[j - 1]);
					cout << " Result=" << result << endl;
					cout << " Wanna Store Result (y/n):";
					cin >> s;
					if (toupper(s) == 'Y')
					{
						StoreResult(Is, size, result);
						cout << "Result is stored." << endl;
					}
					break;
				case '%':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					result = Is[i - 1] % (Is[j - 1]);
					cout << " Result=" << result << endl;
					cout << " Wanna Store Result (y/n):";
					cin >> s;
					if (toupper(s) == 'Y')
					{
						StoreResult(Is, size, result);
						cout << "Result is stored." << endl;
					}
					break;
				case '=':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					if (Is[i - 1] == (Is[j - 1]))
						cout << "HI" << i << " is equal to HI" << j << endl;
					else
						cout << "HI" << i << " is not  equal to HI" << j << endl;


					break;
				case '<':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					if (Is[i - 1] < (Is[j - 1]))
						cout << "HI" << i << " is less than HI" << j << endl;
					else
						cout << "HI" << i << " is not less than HI" << j << endl;

					break;
				case '>':
					cout << " Enter number 1:";
					cin >> i;
					cout << " Enter number 2:";
					cin >> j;
					if (Is[i - 1] > (Is[j - 1]))
						cout << "HI" << i << " is greater than HI" << j << endl;
					else
						cout << "HI" << i << " is not greater than HI" << j << endl;

					break;
				case 't':
					cout << " Enter a number :";
					cin >> i;
					Is[i - 1].Trim();
					cout << "After Trim:" << Is[i - 1] << endl;
					break;
				case'n':
					cout << " Enter Number:";
					cin >> result;
					StoreResult(Is, size, result);
					cout << "Number is added." << endl;
					break;
				default:
					break;
				}
			}
			catch (invalid_argument& e)
			{
				cout << "Error: " << e.what() << endl;
			}
		}
		catch (string exp)
		{
			cout << exp << endl;
		}
		system("pause");
	}

}
RealHex* Load2(const char* fName, int& Size,int b)
{
	ifstream rdr(fName);
	if (!rdr)
		cout << "Loading Fail...." << endl, exit(1);

	rdr >> Size;
	RealHex* rtr;
	rtr = new RealHex[Size];
	while (rdr.peek() == '\n' || rdr.peek() == ' ')
	{
		rdr.ignore();
	}
	for (int i = 0; i < Size; i++)
	{
		rtr[i].Load(rdr,b);
	}

	return rtr;
}
void Print(RealHex* Is, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		cout << "N" << i + 1 << "=" << Is[i] << endl;

	}
}
void StoreResult(RealHex*& Is, int& Size, RealHex result)
{

	RealHex* NewIs;
	NewIs = new RealHex[Size + 1];
	for (int i = 0; i < Size; i++)
	{
		NewIs[i] = Is[i];
	}
	NewIs[Size] = result;
	delete[]Is;
	Is = NewIs;
	Size++;
	NewIs = NULL;
}
void menuRHex()
{
	cout << "Add(+)\t\tSubtract(-)" << endl;
	cout << "Multiplay(x)\tDivide(/)" << endl;
	cout << "Trim(t)" << endl;
	cout << "Less(<)\t\tGreater(>)" << endl;
	cout << "Equal(=) \tNew Number(n)" << endl;
	cout << "0.Return" << endl;
}
void mainRHex()
{
	cout << "Enter Base:";
	int b;
	cin >> b;
	if (b > 36 || b < 2)
	{
		cout << " invalid Base"<<endl;
		return;
	}
	int size = 0;
	RealHex* Is;
	try{
	Is = Load2("FloatHex.txt", size, b);
	}
	catch (string exp)
	{
		cout << "Error: the given Input from file is greater than base " << b << endl;
		return;
	}

	RealHex result;
	char choice = '1', s;
	int  i, j;

	while (choice != '0')
	{
		system("cls");
		cout << "Input Data From File:" << endl;
		cout << "\n_____________________________________\n";
		Print(Is, size);
		cout << "\n_____________________________________\n\n";
		menuRHex();
		cout << "\n_____________________________________\n\n";

		cout << "Choice:";
		cin >> choice;
		try
		{
			switch (choice)
			{
			case '0':
				break;
			case '+':
				cout << " Enter number 1:";
				cin >> i;
				cout << " Enter number 2:";
				cin >> j;
				result = Is[i - 1] + (Is[j - 1]);
				cout << " Result=" << result << endl;
				cout << " Wanna Store Result (y/n):";
				cin >> s;
				if (toupper(s) == 'Y')
				{
					StoreResult(Is, size, result);
					cout << "Result is stored." << endl;
				}
				break;
			case '-':
				cout << " Enter number 1:";
				cin >> i;
				cout << " Enter number 2:";
				cin >> j;
				result = Is[i - 1] - (Is[j - 1]);
				cout << " Result=" << result << endl;
				cout << " Wanna Store Result (y/n):";
				cin >> s;
				if (toupper(s) == 'Y')
				{
					StoreResult(Is, size, result);
					cout << "Result is stored." << endl;
				}
				break;
			case '/':
				cout << " Enter number 1:";
				cin >> i;
				cout << " Enter number 2:";
				cin >> j;
				result = Is[i - 1] / (Is[j - 1]);
				cout << " Result=" << result << endl;
				cout << " Wanna Store Result (y/n):";
				cin >> s;
				if (toupper(s) == 'Y')
				{
					StoreResult(Is, size, result);
					cout << "Result is stored." << endl;
				}
				break;
			case '*':
			case 'x':
				cout << " Enter number 1:";
				cin >> i;
				cout << " Enter number 2:";
				cin >> j;
				result = Is[i - 1] * (Is[j - 1]);
				cout << " Result=" << result << endl;
				cout << " Wanna Store Result (y/n):";
				cin >> s;
				if (toupper(s) == 'Y')
				{
					StoreResult(Is, size, result);
					cout << "Result is stored." << endl;
				}
				break;
	
			case '=':
				cout << " Enter number 1:";
				cin >> i;
				cout << " Enter number 2:";
				cin >> j;
				if (Is[i - 1] == (Is[j - 1]))
					cout << "HI" << i << " is equal to HI" << j << endl;
				else
					cout << "HI" << i << " is not  equal to HI" << j << endl;


				break;
			case '<':
				cout << " Enter number 1:";
				cin >> i;
				cout << " Enter number 2:";
				cin >> j;
				if (Is[i - 1] < (Is[j - 1]))
					cout << "HI" << i << " is less than HI" << j << endl;
				else
					cout << "HI" << i << " is not less than HI" << j << endl;

				break;
			case '>':
				cout << " Enter number 1:";
				cin >> i;
				cout << " Enter number 2:";
				cin >> j;
				if (Is[i - 1] > (Is[j - 1]))
					cout << "HI" << i << " is greater than HI" << j << endl;
				else
					cout << "HI" << i << " is not greater than HI" << j << endl;

				break;
			case 't':
				cout << " Enter a number :";
				cin >> i;
				Is[i - 1].Trim();
				cout << "After Trim:" << Is[i - 1] << endl;
				break;
			case'n':
				cout << " Enter Number:";
				cin >> result;
				StoreResult(Is, size, result);
				cout << "Number is added." << endl;
				break;
			default:
				break;
			}
		}
		catch (invalid_argument& e)
		{
			cout << "Error: " << e.what() << endl;
		}
		system("pause");
	}

}
void menu()
{
	cout << "1. Real Number Calculator" << endl;
	cout << "2. HexaDecimal or any Base Calculator" << endl;
	cout << "3. Real HexaDecimal or any Base Calculator" << endl;
	cout << "0.Return" << endl;
}
int main()
{

	int choice = -1;
	while (choice!=0)
	{
		system("cls");
		cout << "\n___________________________________\n";
		menu();
		cout << "\n___________________________________\n";
		cout << "Enter Option:";
		cin >> choice;
		switch (choice)
		{
		case 0:
			break;
		case 1:
			mainReal();
			break;
		case 2:
			mainHex();
			break;
		case 3:
			mainRHex();
			break;
		default:
			break;
		}
		system("pause");
	 
	}




}








