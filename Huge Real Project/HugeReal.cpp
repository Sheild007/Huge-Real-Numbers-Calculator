#include "HugeReal.h"
#include<string>
#include<iostream>


using namespace std;

void HugeReal::assign(const HugeReal& real)
{
    

    Size = real.Size;
    dSize = real.dSize;
    isNeg = real.isNeg;
   
        Is = new int[Size];
        for (int i = 0; i < Size; i++)
        {
            Is[i] = real.Is[i];
        }

        Ds = new int[dSize];
        for (int i = 0; i < dSize; i++)
        {
            Ds[i] = real.Ds[i];
        }
    

}
HugeReal HugeReal::one()
{
    HugeReal result(1);
    result[0] = 1;
    return result;
}
HugeReal HugeReal::zero()
{
    HugeReal result(1);
    result[0] = 0;
  
    return result;
}
HugeReal::HugeReal(const string& numStr)
{
    isNeg = false;
    Size = numStr.size();
    int start = 0;
    if (numStr[0] == '-') 
    {
        isNeg = true;
        start = 1;
        Size--;
    }
    int decimalPos = numStr.find('.');
    if (decimalPos == string::npos)
    {
        dSize = 0;
        Size = numStr.size()-start;

    }
    else
    {
        dSize = numStr.size() - decimalPos - 1;
        Size = decimalPos-start;

    }
    Is = new int[Size];
    for (int i = 0; i < Size; i++)
    {
        Is[Size - 1 - i] = numStr[start+i] - '0';
    }
    if (dSize != 0)
    {
        Ds = new int[dSize];
        for (int i = 0; i < dSize; i++)
        {
            Ds[i] = numStr[decimalPos + 1 + i] - '0';
        }
    }
  
    Trim();
}
HugeReal::HugeReal(const char* numStr)
{
    isNeg = false;
    Size = strlen(numStr);
    int start = 0;
    if (numStr[0] == '-')
    {
        isNeg = true;
        start = 1;
        Size--;
    }
    int decimalPos = -1;
    for (int i = 0; i < Size; i++)
    {
        if (numStr[i] == '.') 
        {
            decimalPos = i;
            break;
        }
    }
    if (decimalPos == -1)
    {
        dSize = 0;
        Size -= start;
    }
    else 
    {
        dSize = Size - decimalPos - 1;
        Size -= (start + dSize + 1);
    }
    Is = new int[Size];
    for (int i = 0; i < Size; i++)
    {
        Is[Size-1-i] = numStr[start + i] - '0';
    }
    if (dSize > 0)
    {
        Ds = new int[dSize];
        for (int i = 0; i < dSize; i++) 
        {
            Ds[i] = numStr[decimalPos + 1 + i] - '0';
        }
    }
    else 
    {
        Ds = nullptr;
    }
    Trim();
}


HugeReal::HugeReal()
{

    Size = 0;
    dSize = 0;
    Is = nullptr;
    Ds = nullptr;
    isNeg = false;
}
HugeReal::HugeReal(int _size)
{

    Size = _size;
    dSize = 1;
    isNeg = false;
    Is = new int [Size] {};
    Ds = new int [Size] {};
}
HugeReal::HugeReal(const HugeReal& H)
{
    assign(H);
}
HugeReal::HugeReal(ifstream& rdr)
{
    Load(rdr);
}
void HugeReal::Load(ifstream& rdr)
{
 
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
    string numStr;
    getline(rdr, numStr);
    int decimalPos = numStr.find('.');
    if (decimalPos == string::npos) 
    {
        dSize = 0;
        Size = numStr.size();

    }
    else 
    {
        dSize = numStr.size() - decimalPos - 1;
        Size = decimalPos;
    
    }
    Is = new int[Size];
    for (int i = 0; i < Size; i++)
    {
        Is[Size - 1 - i] = numStr[i] - '0';
    }
    if (dSize != 0)
    {
        Ds = new int[dSize];
        for (int i = 0; i < dSize; i++)
        {
            Ds[i] = numStr[decimalPos + 1 + i] - '0';
        }
    }
  
  
}

const HugeReal& HugeReal::operator=(const HugeReal& H)
{
    if (this == &H)
        return *this;
    if (Is != nullptr)
        delete[] Is;
    assign(H);
    return *this;
}

int  HugeReal::operator[](int i) const
{
    if (i >= Size)
        return 0;
    if (i >= 0 && i < Size)
    {
        return Is[i];
    }
    else
        throw std::invalid_argument("Index out of bounIs");
}
int& HugeReal::operator[](int i)
{
    if (i >= 0 && i < Size)
    {
        return Is[i];
    }
    else
        throw std::invalid_argument("Index out of bounIs");
}

int* HugeReal::concatenate(int* P1, int s1, int* P2, int s2)const 
{
    int csize = s1 + s2;
    int* C = new int[csize];

    // Copy P1 to C
    int temp = 0;
    for (int i = 0; i < s2; i++)
    {
        C[temp++] = P2[s2-1-i];
    }
    for (int i = 0; i < s1; i++)
    {
        C[temp++] = P1[i];
    }

    // Copy P2 to C
 
    delete[]P1;
    delete[]P2;
    P1 = nullptr;
    P2 = nullptr;

    return C;
}

void HugeReal::SplitIntoIntDec(int NOD)
{
    int* NewDs= new int[NOD];
    int* NewIs = new int[Size - NOD];
    int temp = 0;
    for (int i = 0; i < NOD; i++)
    {
        NewDs[NOD - 1 - i] = Is[temp++];
    }
    for (int i = 0; i <Size-NOD; i++)
    {
        NewIs[i] = Is[temp++];
    }
    delete[]Is;
    delete[]Ds;
    Is = NewIs;
    Ds = NewDs;
    Size = Size - NOD;
    dSize = NOD;
    NewIs = nullptr;
    NewDs = nullptr;
}
int atIndex(int i,int *p,int Size)
{
    if (i >= 0 && i < Size)
        return p[i];
    return 0;
}
int* Add(int*P1, int* P2,int&carry,int Size,int s1,int s2 ) 
{
    int* result;
    result = new int[Size];     
    for (int i = Size-1; i >=0; i--)
    {
        int ans = (atIndex(i,P1,s1) + atIndex(i, P2, s2) + carry) % 10;
        carry = (atIndex(i, P1, s1) + atIndex(i, P2, s2) + carry) / 10;
        result[i] = ans;
    }
    if (carry != 1)
        carry = 0;
    return result;
}
int* Add1(int* P1, int* P2, int& carry, int Size, int s1, int s2)
{
    int* result;
    result = new int[Size];
    for (int i = 0; i <Size; i++)
    {
        int ans = (atIndex(i, P1, s1) + atIndex(i, P2, s2) + carry) % 10;
        carry = (atIndex(i, P1, s1) + atIndex(i, P2, s2) + carry) / 10;
        result[i] = ans;
    }
    if (carry != 1)
        carry = 0;
    return result;
}
HugeReal HugeReal::ADDQuantityWise(const HugeReal& H2) const
{
    HugeReal R;
    R.Size = Size + 1;
    R.dSize = max(dSize, H2.dSize);
    int carry = 0;
 
        R.Ds = Add(Ds, H2.Ds, carry, R.dSize, dSize, H2.dSize);
        R.Is = Add1(Is, H2.Is, carry, R.Size, Size, H2.Size);
        R.Trim();
   
   
    return R;
}

int* Sub(int* P1, int* P2, int& borrow, int Size, int s1, int s2)
{
    int* result;
    result = new int[Size];
    for (int i = Size - 1; i >= 0; i--)
    {
        int diff = (atIndex(i, P1, s1) - atIndex(i, P2, s2) -borrow) ;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result[i] = diff;
    }
    if (borrow != 1)
        borrow = 0;
    return result;
}
int* Sub1(int* P1, int* P2, int& borrow, int Size, int s1, int s2)
{
    int* result;
    result = new int[Size];
    for (int i = 0; i <Size; i++)
    {
        int diff = (atIndex(i, P1, s1) - atIndex(i, P2, s2) - borrow);
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result[i] = diff;
    }
    if (borrow != 1)
        borrow = 0;
    return result;
}

HugeReal HugeReal::SUBQuantityWise(const HugeReal& H2) const
{
    HugeReal R;
    R.Size = Size;
    R.dSize = max(dSize, H2.dSize);
    int  borrow = 0;

        R.Ds = Sub(Ds, H2.Ds, borrow, R.dSize, dSize, H2.dSize);
        R.Is = Sub1(Is, H2.Is, borrow, R.Size, Size, H2.Size);
        R.Trim();

    return R;
}
bool HugeReal::LessThanQuantityWise(const HugeReal& H2) const
{

        if (Size < H2.Size)
            return true;

        else if (Size > H2.Size)
            return false;
        else
        {
            for (int i = Size - 1; i >= 0; i--)
            {
                if (Is[i] < H2.Is[i])
                {
                    return true;
                }
                else if (Is[i] > H2.Is[i])
                {
                    return false;
                }
            }
        }
        if (dSize < H2.dSize)
            return true;

        else if (dSize > H2.dSize)
            return false;
        else
        {
            for (int i = 0; i < dSize; i++)
            {
                if (Ds[i] < H2.Ds[i])
                {
                    return true;
                }
                else if (Ds[i] > H2.Ds[i])
                {
                    return false;
                }
            }
            return false;
        }
    
}
bool HugeReal::GreaterThanQuantityWise(const HugeReal& H2) const
{
    return H2.LessThanQuantityWise(*this);
}
bool HugeReal::EqualQuantityWise(const HugeReal& H2) const
{
    return (!this->GreaterThanQuantityWise(H2) && !this->LessThanQuantityWise(H2));
}
void HugeReal::Trim()
{
    int tSize = Size;
    while (Size > 1 && Is[tSize - 1] == 0)
    {
        tSize--;
    }
    if (tSize!=Size)
    {
        int* NewIs;
        NewIs = new int[tSize];
        for (int i = 0; i < tSize; i++)
        {
            NewIs[tSize - 1 - i] = Is[tSize - 1 - i];
        }
        delete[]Is;
        Is = NewIs;
        Size = tSize;
        NewIs = nullptr;
    }
    if (dSize>1)
    {
        tSize = dSize;
        while (dSize > 1 && Ds[tSize - 1] == 0)
        {
            tSize--;
        }
        if (tSize != dSize)
        {
            int* NewDs;
            NewDs = new int[tSize];
            for (int i = 0; i < tSize; i++)
            {
                NewDs[i] = Ds[i];
            }
            delete[]Ds;
            Ds = NewDs;
            dSize = tSize;
            NewDs = nullptr;
        }
    }
}

const HugeReal HugeReal::operator+(const HugeReal& HR) const
{
    HugeReal result;
    if (isNeg == HR.isNeg)
    {
        if (GreaterThanQuantityWise(HR))
        {
            result = ADDQuantityWise(HR);
            result.isNeg = isNeg;
            return result;
        }
        else
        {
            result = HR.ADDQuantityWise(*this);
            result.isNeg = HR.isNeg;
            return result;
        }
    }
    else
    {
        if (GreaterThanQuantityWise(HR))
        {
            result = SUBQuantityWise(HR);
            result.isNeg = isNeg;
            return result;
        }
        else
        {
            result = HR.SUBQuantityWise(*this);
            result.isNeg = HR.isNeg;
            return result;
        }
    }
}
HugeReal HugeReal::ABS() const
{
    HugeReal R = *this;
    R.isNeg = false;
    return R;
}
const HugeReal HugeReal::operator-() const
{
    HugeReal result = *this;
    result.isNeg = !isNeg;
    return result;
}
const HugeReal HugeReal::operator-(const HugeReal& HR) const
{
    return *this + (-HR);
}
const HugeReal& HugeReal::operator+=(const HugeReal& HR)
{
    return *this = *this + HR;
}
const HugeReal& HugeReal::operator-=(const HugeReal& HR)
{
    return *this = *this - HR;
}
bool HugeReal:: operator>(const HugeReal& HI)const
{
    if (isNeg != HI.isNeg)
        return isNeg == false;
    if (isNeg == false)
        return GreaterThanQuantityWise(HI);
    return LessThanQuantityWise(HI);
}
bool HugeReal:: operator<(const HugeReal& HI)const
{
    return HI > *this;
}
bool HugeReal:: operator==(const HugeReal& HI)const
{
    return !(*this<HI || *this > HI);
}
bool HugeReal:: operator!=(const HugeReal& HI)const
{
    return !(*this == HI);
}
bool HugeReal:: operator<=(const HugeReal& HI)const
{
    return (*this < HI || *this == HI);
}
bool HugeReal:: operator>=(const HugeReal& HI)const
{
    return (*this > HI || *this == HI);
}
const HugeReal HugeReal::operator--()
{
    HugeReal result(*this);
    result -= one();
    return result;
}
const HugeReal HugeReal::operator++() {
    HugeReal result(*this);
    result += one();
    return result;
}
const HugeReal HugeReal::operator++(int d)
{
    HugeReal result = *this;
    ++(*this);
    return result;
}
const HugeReal HugeReal::operator--(int d)
{
    HugeReal result = *this;
    --(*this);
    return result;
}
const HugeReal HugeReal::operator*( const HugeReal& HR)const 
{
    int NOD = dSize + HR.dSize;
    if (*this == zero() || HR == zero()) 
    {
        return zero();
    }
    HugeReal N1 = *this;
    HugeReal N2 = HR;
    N1.Is = concatenate(N1.Is, N1.Size, N1.Ds, N1.dSize);
    N2.Is = concatenate(N2.Is, N2.Size, N2.Ds, N2.dSize);
    N1.Size = Size + dSize;
    N2.Size = N2.Size + N2.dSize;
    N1.dSize = 1;
    N2.dSize = 1;
    N1.Ds = new int[1]{};
    N2.Ds = new int[1]{};
    HugeReal result = zero(), Zero = zero();
    HugeReal A = N1;
    HugeReal B = N2;
    if (N1.isNeg == true) 
    {
        A = -A;
    }
    if (N2.isNeg == true)
    {
        B = -B;
    }
    while (B.ABS() != Zero) 
    {
        HugeReal temp = A, C = one();
        while (C + C < B) 
        {
            temp += temp;
            C += C;
        }
        result += temp;
        B -= C;
    }
    if (isNeg == HR.isNeg) 
    {
        result.isNeg = false;
    }
    else 
    {
        result.isNeg = true;
    }
    result.SplitIntoIntDec(NOD);
    result.Trim();
    return result;
}
void insertAtStart(int*& Vs, int& size, int T)
{
    int* newPtr = new int[size + 1]{};
    newPtr[0] = T;
    for (int i = 1; i < size; i++)
    {
        newPtr[i] = Vs[i-1];
    }
    newPtr[size] = Vs[size - 1];
    delete[]Vs;
    size++;
    Vs = newPtr;
    newPtr = nullptr;

}
const HugeReal HugeReal::operator/(const HugeReal& HI) const
{
    if (HI == zero())
        throw invalid_argument("Division by zero");
    // Handle special cases where quotient is one or negative one
    if (*this == HI)
        return one();
    if (*this == -HI)
        return -one();
    if (*this == zero())
        return zero();

  
    int NOD = max(dSize , HI.dSize);
    int NOZ = min(dSize, HI.dSize);
    int presion = 12;
    HugeReal N1 = *this;
    HugeReal N2 = HI;
    N1.Is = concatenate(N1.Is, N1.Size, N1.Ds, N1.dSize);
    N2.Is = concatenate(N2.Is, N2.Size, N2.Ds, N2.dSize);
    N1.Size = Size + dSize;
    N2.Size = N2.Size + N2.dSize;
    N1.dSize = 1;
    N2.dSize = 1;
    N1.Ds = new int[1]{};
    N2.Ds = new int[1]{};
    
    for (int i = 0; i < NOZ+presion; i++)
        insertAtStart(N1.Is, N1.Size, 0);
    N1.Trim();
    N2.Trim();
    HugeReal quotient, temp = one(), divisor = N2;
    HugeReal remainder = N1;
    // Make sure remainder and divisor are positive
    if (isNeg == true)
        remainder = -remainder;
    if (HI.isNeg == true)
        divisor = -N2;
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
        temp = one();
        // Reset divisor to original value
        if (HI.isNeg == true)
            divisor = -N2;
        else
            divisor = N2;
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
    if (remainder.ABS() == zero())
        remainder.isNeg = false;

    quotient.SplitIntoIntDec(NOD+presion);
    quotient.Trim();
    return quotient;
}
const HugeReal& HugeReal::operator*=(const HugeReal& HR)
{
    return *this = *this * HR;
}
const HugeReal& HugeReal::operator/=(const HugeReal& HR)
{
    return *this = *this / HR;
}


istream& operator>>(istream& in,  HugeReal& H)
{
	string input;
	in >> input;
	H = HugeReal(input);
	return in;
}
ifstream& operator>>(ifstream& rdr, HugeReal& H)
{
	string input;
	getline(rdr, input);
	H = HugeReal(input);
	return rdr;
}
ostream& operator<<(ostream& out, const HugeReal& H)
{
    if (H.isNeg)
        out << "-";
    for (int i = 0; i < H.Size; i++)
    {
        out << H.Is[H.Size - 1 - i];
    }
    if(H.dSize!=0)
    {
        out << ".";
        for (int i = 0; i < H.dSize; i++)
        {
            out << H.Ds[i];
        }
    }
    return out;
}
HugeReal::~HugeReal()
{
    if (Ds != nullptr)
    delete[]Is;
    Is = nullptr;
    if(Ds!=nullptr)
    delete[]Ds;
    Ds = nullptr;

}