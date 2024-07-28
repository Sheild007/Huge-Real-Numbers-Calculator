#include "HugeHex.h"
#include "HugeHex.h"
#include<string>
#include<iostream>
#include<stdexcept>


using namespace std;

void HugeHex::SetBase(int b)
{
	base = b;
}
void HugeHex::assign(const HugeHex& integer)
{
	base = integer.base;
	Size = integer.Size;
	isNeg = integer.isNeg;
	Ds = new int[Size];
	for (int i = 0; i < Size; i++)
	{
		Ds[i] = integer.Ds[i];
	}
}
HugeHex HugeHex::one(int _base)
{
	HugeHex result(1,_base);
	result[0] = 1;
	return result;
}
HugeHex HugeHex::zero(int _base)
{
	HugeHex result(1,_base);
	result[0] = 0;
	return result;
}
HugeHex::HugeHex()
{
	base = 16;
	Size = 0;
	Ds = nullptr;
	isNeg = false;
}
HugeHex::HugeHex(int _size,int _base)
{

	base = 16;
	Size = _size;
	isNeg = false;
	Ds = new int[Size] {};
}
HugeHex::HugeHex(const HugeHex& H)
{
	
	assign(H);
}
HugeHex::HugeHex(const string& str,int _base)
{
	base = _base;
	isNeg = false;
	Size = str.size();
	Ds = new int[Size];
	int start = 0;
	if (str[0] == '-') {
		isNeg = true;
		start = 1;
		Size--;
	}
	for (int i = 0; i < Size; i++)
	{
		Ds[i] = str[start + Size - 1 - i] - '0';
	}
	Trim();
}

HugeHex::HugeHex(const char* str,int _base)
{
	base = _base;
	int len = strlen(str);
	if (len == 0) {
		Size = 1;
		Ds = new int[1];
		Ds[0] = 0;
		isNeg = false;
		return;
	}
	int startIndex = 0;
	isNeg = false;
	if (str[0] == '-')
	{
		startIndex = 1;
		isNeg = true;
	}
	else if (str[0] == '+')
	{
		startIndex = 1;
	}
	Size = len - startIndex;
	Ds = new int[Size];
	for (int i = startIndex; i < len; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			Ds[len - i - 1] = str[i] - '0';
		}
		else
		{
			throw invalid_argument("Invalid input string");
		}
	}

	Trim();
}


void HugeHex::insertAtEnd(int*& Vs, int& size, int T)
{
	int* newPtr = new int[size + 1];
	for (int i = 0; i < size; i++)
	{
		newPtr[i] = Vs[i];
	}
	newPtr[size] = T;
	delete[]Vs;
	size++;
	Vs = newPtr;
	newPtr = nullptr;

}
HugeHex::HugeHex(ifstream& rdr,int _base)
{
	base = _base;
	Load(rdr,base);
}
void HugeHex::Load(ifstream& rdr,int _base)
{
	base = _base;
	if (rdr.peek() == '-')
	{
		isNeg = true;
		rdr.ignore();
	}
	else
	{
		if (rdr.peek() == '+')
			rdr.ignore();
		isNeg = false;
	}

	string ReadLine;
	getline(rdr, ReadLine);
	Size = ReadLine.size();
	Ds = new int[Size];
	for (int i = 0; i < Size; i++)
	{
		if (ReadLine[Size - 1 - i] >= 'A' && ReadLine[Size - 1 - i] <= 'Z')
		{
			string exception = "Wrong Input from File.";
			if (ReadLine[Size - 1 - i] - 55 < base)
				Ds[i] = ReadLine[Size - 1 - i] - 55;
			else
				throw exception;
				
		}
			
		else
		Ds[i] = ReadLine[Size - 1 - i] - '0';
	}
}
const HugeHex& HugeHex::operator=(const HugeHex& H)
{
	if (this == &H)
		return *this;
	if (Ds != nullptr)
		delete[] Ds;
	assign(H);
	return *this;
}

int HugeHex:: operator[ ](int i) const
{
	if (i >= Size)
		return 0;
	if (i >= 0 && i < Size)
	{
		return Ds[i];
	}
	else
		throw invalid_argument("Index out of bounds");
}
int& HugeHex:: operator[ ](int i)
{

	if (i >= 0 && i < Size)
	{
		return Ds[i];
	}
	else
		throw invalid_argument("Index out of bounds");
}
HugeHex HugeHex::ADDQuantityWise(const HugeHex& H2) const
{
	HugeHex R;
	R.Size = Size + 1;
	R.Ds = new int[R.Size];
	int carry = 0;
	for (int i = 0; i < R.Size; i++)
	{
		int ans = ((*this)[i] + H2[i] + carry) % base;
		carry = ((*this)[i] + H2[i] + carry) / base;
		R[i] = ans;
	}
	R.Trim();
	return R;
}
//Time complexity O(n).
HugeHex HugeHex::SUBQuantityWise(const HugeHex& H2) const
{
	HugeHex R;
	R.Size = Size;
	R.Ds = new int[R.Size];
	int borrow = 0;
	for (int i = 0; i < R.Size; i++)
	{
		int diff = (*this)[i] - H2[i] - borrow;
		if (diff < 0)
		{
			diff += base;
			borrow = 1;
		}
		else
		{
			borrow = 0;
		}
		R[i] = diff;
	}
	R.Trim();
	return R;
}
//Time complexity O(n).
bool HugeHex::LessThanQuantityWise(const HugeHex& H2) const
{
	
	
		if (Size < H2.Size)
			return true;

		else if (Size > H2.Size)
			return false;
		else
		{
			for (int i = Size - 1; i >= 0; i--)
			{
				if (Ds[i] < H2[i])
				{
					return true;
				}
				else if (Ds[i] > H2[i])
				{
					return false;
				}
			}
			return false;
		}
	
}
//Time complexity O(n).
bool HugeHex::GreaterThanQuantityWise(const HugeHex& H2) const
{
	return H2.LessThanQuantityWise(*this);
}
//Time complexity O(n).
bool HugeHex::EqualQuantityWise(const HugeHex& H2) const
{
	return (!this->GreaterThanQuantityWise(H2) && !this->LessThanQuantityWise(H2));
}
//Time complexity O(n).
void HugeHex::Trim()
{
	int tSize = Size;
	while (Size > 1 && Ds[tSize - 1] == 0)
	{
		tSize--;
	}
	int* NewDs;
	NewDs = new int[tSize];
	for (int i = 0; i < tSize; i++)
	{
		NewDs[tSize - 1 - i] = Ds[tSize - 1 - i];
	}
	delete[]Ds;
	Ds = NewDs;
	Size = tSize;
	NewDs = nullptr;
}

const HugeHex HugeHex::operator+(const HugeHex& HI)const
{
	HugeHex result;
	if (isNeg == HI.isNeg)
	{
		if (GreaterThanQuantityWise(HI))
		{
			result = ADDQuantityWise(HI);
			result.isNeg = isNeg;
			return result;
		}
		else
		{
			result = HI.ADDQuantityWise(*this);
			result.isNeg = HI.isNeg;
			return result;
		}
	}
	else
	{
		if (GreaterThanQuantityWise(HI))
		{
			result = SUBQuantityWise(HI);
			result.isNeg = isNeg;
			return result;
		}
		else
		{
			result = HI.SUBQuantityWise(*this);
			result.isNeg = HI.isNeg;
			return result;
		}
	}
}
//Time complexity O(n).
HugeHex HugeHex::ABS() const
{
	HugeHex R = *this;
	R.isNeg = false;
	return R;
}

const HugeHex HugeHex:: operator -()const
{
	HugeHex result = *this;
	result.isNeg = !isNeg;
	return result;
}
const HugeHex HugeHex::operator-(const HugeHex& HI)const
{
	return *this + (-HI);
}
//Time complexity O(n).
bool HugeHex:: operator>(const HugeHex& HI)const
{
	if (isNeg != HI.isNeg)
		return isNeg == false;
	if (isNeg == false)
		return GreaterThanQuantityWise(HI);
	return LessThanQuantityWise(HI);
}
bool HugeHex:: operator<(const HugeHex& HI)const
{
	return HI > *this;
}
bool HugeHex:: operator==(const HugeHex& HI)const
{
	return !(*this<HI || *this > HI);
}
bool HugeHex:: operator!=(const HugeHex& HI)const
{
	return !(*this == HI);
}
bool HugeHex:: operator<=(const HugeHex& HI)const
{
	return (*this < HI || *this == HI);
}
bool HugeHex:: operator>=(const HugeHex& HI)const
{
	return (*this > HI || *this == HI);
}
// all boleans have Time complexity O(n).
const HugeHex HugeHex::operator--()
{
	HugeHex result(*this);
	result -= one(base);
	return result;
}
const HugeHex HugeHex::operator++() {
	HugeHex result(*this);
	result += one(base);
	return result;
}
const HugeHex HugeHex::operator++(int d)
{
	HugeHex result = *this;
	++(*this);
	return result;
}
const HugeHex HugeHex::operator--(int d)
{
	HugeHex result = *this;
	--(*this);
	return result;
}
const HugeHex& HugeHex::operator+=(const HugeHex& HI)
{
	return *this = *this + HI;
}
const HugeHex& HugeHex::operator-=(const HugeHex& HI)
{
	return *this = *this - HI;
}
//The time complexity of the pre-increment, pre-decrement, post-increment, and post-decrement operators  is O(n)


// naive implemtation
//const HugeHex HugeHex:: operator*(const HugeHex& HI)const
//{
//	HugeHex result;
//	for (HugeHex i = zero(base); i < HI; i++)
//	{
//		result += *this;
//	}
//	return result;
//}
//const HugeHex HugeHex::operator/(const HugeHex& HI) const
//{
//	HugeHex quotient;
//	if (HI == zero(base))
//		throw runtime_error("Error: division by zero");
//	else if (*this < HI)
//		quotient = zero(base);
//	else
//	{
//		HugeHex dividend = *this;
//		while (dividend >= HI)
//		{
//			dividend -= HI;
//			++quotient;
//		}
//	}
//	quotient.Trim();
//	return quotient;
//}

const HugeHex HugeHex:: operator*(const HugeHex& HI)const
{
	if (*this == zero(base) || HI == zero(base))
		return zero(base);
	HugeHex result = zero(base), Zero = zero(base);

	HugeHex A = *this;
	HugeHex B = HI;
	if (isNeg == true)
		A = -A;
	if (HI.isNeg == true)
		B = -B;
	while (B.ABS() != Zero)
	{
		HugeHex temp = A, C = one(base);
		while (C + C < B)
		{
			temp += temp;
			C += C;
		}
		result += temp, B -= C;
	}
	if (isNeg == HI.isNeg)
		result.isNeg = false;
	else
		result.isNeg = true;
	return result;
}
// Time Complexity O(N log N)
const HugeHex& HugeHex::operator*=(const HugeHex& HI)
{
	return *this = *this * HI;
}


void HugeHex::devison(HugeHex HI, HugeHex& Q, HugeHex& R)const
{
	HugeHex quotient, temp = one(base), divisor = HI;
	HugeHex remainder = *this;
	// Make sure remainder and divisor are positive
	if (isNeg == true)
		remainder = -remainder;
	if (HI.isNeg == true)
		divisor = -HI;
	while (remainder.ABS() >= divisor.ABS())
	{
		// Double divisor and temp until divisor is larger than remainder
		while (divisor.ABS() + divisor.ABS() <= remainder.ABS())
		{
			divisor += divisor;
			temp += temp;
		}
		remainder -= divisor;
		quotient += temp;
		temp = one(base);
		// Reset divisor to original value
		if (HI.isNeg == true)
			divisor = -HI;
		else
			divisor = HI;
	}
	// Set quotient sign based on the signs of the original numbers
	if (this->isNeg == HI.isNeg)
	{
		quotient.isNeg = false;
		remainder.isNeg = false;
	}
	else
	{
		quotient.isNeg = true;
		remainder.isNeg = true;
	}
	if (remainder.ABS() == zero(base))
		remainder.isNeg = false;
	Q = quotient;
	R = remainder;
}
const HugeHex HugeHex::operator/(const HugeHex& HI) const
{
	if (HI == zero(base))
		throw invalid_argument("Division by zero");
	// Handle special cases where quotient is one or negative one
	if (*this == HI)
		return one(base);
	if (*this == -HI)
		return -one(base);
	if (*this == zero(base))
		return zero(base);
	HugeHex Q, R;
	devison(HI, Q, R);

	return Q;

}
// Time Complexity O(N log N)
const HugeHex HugeHex::operator%(const HugeHex& HI) const
{
	if (HI == zero(base))
		throw invalid_argument("Modulus by zero");
	// Handle special cases where quotient is one or negative one
	if (*this == HI || *this == -HI || *this == zero(base))
		return zero(base);
	HugeHex Q, R;
	devison(HI, Q, R);

	return R;

}
// Time Complexity O(N log N)
const HugeHex& HugeHex::operator/=(const HugeHex& HI)
{
	return *this = *this / HI;
}
const HugeHex& HugeHex::operator%=(const HugeHex& HI)
{
	return *this = *this % HI;
}
istream& operator>>(istream& in, HugeHex& H)
{
	static int b;
	cout << "Enter base First:";
	cin >> b;
	string input;
	in >> input;
	H = HugeHex(input,b);
	return in;
}
ifstream& operator>>(ifstream& rdr, HugeHex& H)
{
	static int b;
	rdr >> b;
	string input;
	getline(rdr, input);
	H = HugeHex(input,b);
	return rdr;
}
ostream& operator<<(ostream& out, const HugeHex& H)
{
	if (H.isNeg)
		out << "-";
	for (int i = 0; i < H.Size; i++)
	{
		if (H.Ds[H.Size - 1 - i] >= 'A'-55 && H.Ds[H.Size - 1 - i] <= 'Z'-55)
			out<<char ( H.Ds[H.Size - 1 - i]+55);
		else
		out << H.Ds[H.Size - 1 - i];
	}
	return out;
}
HugeHex::~HugeHex()
{
	delete[]Ds;
	Ds = nullptr;

}
