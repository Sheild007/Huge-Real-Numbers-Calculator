#include "RealHex.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;


void RealHex::assign(const RealHex& real)
{


    Size = real.Size;
    dSize = real.dSize;
    isNeg = real.isNeg;
    base = real.base;

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
RealHex RealHex::one(int _base)
{
    RealHex result(1,_base);
    result[0] = 1;
    return result;
}
RealHex RealHex::zero(int _base)
{
    RealHex result(1,_base);
    result[0] = 0;

    return result;
}
RealHex::RealHex(const string& numStr,int _base)
{
    base = _base;
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
        Size = numStr.size() - start;

    }
    else
    {
        dSize = numStr.size() - decimalPos - 1;
        Size = decimalPos - start;

    }
    Is = new int[Size];
    for (int i = 0; i < Size; i++)
    {
        if (numStr[i] >= 'A' && numStr[i] <= 'Z')
        {
            string exception = "Wrong Input from File.";
            if (numStr[i] - 55 < base)
                Is[Size - 1 - i] = numStr[i] - 55;
            else
                throw exception;
        }
        else
            Is[Size - 1 - i] = numStr[i] - '0';
    }
    if (dSize != 0)
    {
        Ds = new int[dSize];
        for (int i = 0; i < dSize; i++)
        {
            if (numStr[decimalPos + 1 + i] >= 'A' && numStr[decimalPos + 1 + i] <= 'Z')
            {
                string exception = "Wrong Input from File.";
                if (numStr[decimalPos + 1 + i] - 55 < base)
                    Ds[i] = numStr[decimalPos + 1 + i] - 55;
                else
                    throw exception;
            }
            else
                Ds[i] = numStr[decimalPos + 1 + i] - '0';
        }
    }

    Trim();
}
RealHex::RealHex(const char* numStr,int _base)
{
    base = _base;
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
        if (numStr[i] >= 'A' && numStr[i] <= 'Z')
        {
            string exception = "Wrong Input from File.";
            if (numStr[i] - 55 < base)
                Is[Size - 1 - i] = numStr[i] - 55;
            else
                throw exception;
        }
        else
            Is[Size - 1 - i] = numStr[i] - '0';
    }
    if (dSize > 0)
    {
        Ds = new int[dSize];
        for (int i = 0; i < dSize; i++)
        {
            if (numStr[decimalPos + 1 + i] >= 'A' && numStr[decimalPos + 1 + i] <= 'Z')
            {
                string exception = "Wrong Input from File.";
                if (numStr[decimalPos + 1 + i] - 55 < base)
                    Ds[i] = numStr[decimalPos + 1 + i] - 55;
                else
                    throw exception;
            }
            else
                Ds[i] = numStr[decimalPos + 1 + i] - '0';
        }
    }
    else
    {
        Ds = nullptr;
    }
    Trim();
}


RealHex::RealHex()
{
    base = 16;

    Size = 0;
    dSize = 0;
    Is = nullptr;
    Ds = nullptr;
    isNeg = false;
}
RealHex::RealHex(int _size,int _base)
{
    base = _base;
    Size = _size;
    dSize = 1;
    isNeg = false;
    Is = new int [Size] {};
    Ds = new int [Size] {};
}
RealHex::RealHex(const RealHex& H)
{
    assign(H);
}
RealHex::RealHex(ifstream& rdr, int _base)
{
    base = _base;
    Load(rdr,base);
}
void RealHex::Load(ifstream& rdr , int _base)
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
        if (numStr[i] >= 'A' && numStr[i] <= 'Z')
        {
            string exception = "Wrong Input from File.";
            if (numStr[i] - 55 < base)
                Is[Size - 1 - i] = numStr[i] - 55;
            else
                throw exception;
        }
        else
            Is[Size - 1 - i] = numStr[i] - '0';
    }
    if (dSize != 0)
    {
        Ds = new int[dSize];
        for (int i = 0; i < dSize; i++)
        {
            if (numStr[decimalPos + 1 + i] >= 'A' && numStr[decimalPos + 1 + i] <= 'Z')
            {
                string exception = "Wrong Input from File.";
                if (numStr[decimalPos + 1 + i] - 55 < base)
                    Ds[i] = numStr[decimalPos + 1 + i] - 55;
                else
                    throw exception;
            }
            else
                Ds[i] = numStr[decimalPos + 1 + i] - '0';
        }
    }


}
const RealHex& RealHex::operator=(const RealHex& H)
{
    if (this == &H)
        return *this;
    if (Is != nullptr)
        delete[] Is;
    assign(H);
    return *this;
}
int  RealHex::operator[](int i) const
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
int& RealHex::operator[](int i)
{
    if (i >= 0 && i < Size)
    {
        return Is[i];
    }
    else
        throw std::invalid_argument("Index out of bounIs");
}
int* RealHex::concatenate(int* P1, int s1, int* P2, int s2)const
{
    int csize = s1 + s2;
    int* C = new int[csize];

    // Copy P1 to C
    int temp = 0;
    for (int i = 0; i < s2; i++)
    {
        C[temp++] = P2[s2 - 1 - i];
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

void RealHex::SplitIntoIntDec(int NOD)
{
    int* NewDs = new int[NOD];
    int* NewIs = new int[Size - NOD];
    int temp = 0;
    for (int i = 0; i < NOD; i++)
    {
        NewDs[NOD - 1 - i] = Is[temp++];
    }
    for (int i = 0; i < Size - NOD; i++)
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
int _atIndex(int i, int* p, int Size)
{
    if (i >= 0 && i < Size)
        return p[i];
    return 0;
}
int* _Add(int* P1, int* P2, int& carry, int Size, int s1, int s2,int base)
{
    int* result;
    result = new int[Size];
    for (int i = Size - 1; i >= 0; i--)
    {
        int ans = (_atIndex(i, P1, s1) + _atIndex(i, P2, s2) + carry) % base;
        carry = (_atIndex(i, P1, s1) + _atIndex(i, P2, s2) + carry) / base;
        result[i] = ans;
    }
    if (carry != 1)
        carry = 0;
    return result;
}
int* _Add1(int* P1, int* P2, int& carry, int Size, int s1, int s2,int base)
{
    int* result;
    result = new int[Size];
    for (int i = 0; i < Size; i++)
    {
        int ans = (_atIndex(i, P1, s1) + _atIndex(i, P2, s2) + carry) % base;
        carry = (_atIndex(i, P1, s1) + _atIndex(i, P2, s2) + carry) / base;
        result[i] = ans;
    }
    if (carry != 1)
        carry = 0;
    return result;
}
RealHex RealHex::ADDQuantityWise(const RealHex& H2) const
{
    RealHex R;
    R.Size = Size + 1;
    R.dSize = max(dSize, H2.dSize);
    int carry = 0;

    R.Ds = _Add(Ds, H2.Ds, carry, R.dSize, dSize, H2.dSize,base);
    R.Is = _Add1(Is, H2.Is, carry, R.Size, Size, H2.Size,base);
    R.Trim();


    return R;
}

int* _Sub(int* P1, int* P2, int& borrow, int Size, int s1, int s2,int base)
{
    int* result;
    result = new int[Size];
    for (int i = Size - 1; i >= 0; i--)
    {
        int diff = (_atIndex(i, P1, s1) - _atIndex(i, P2, s2) - borrow);
        if (diff < 0)
        {
            diff += base;
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
int* _Sub1(int* P1, int* P2, int& borrow, int Size, int s1, int s2,int base)
{
    int* result;
    result = new int[Size];
    for (int i = 0; i < Size; i++)
    {
        int diff = (_atIndex(i, P1, s1) - _atIndex(i, P2, s2) - borrow);
        if (diff < 0)
        {
            diff += base;
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

RealHex RealHex::SUBQuantityWise(const RealHex& H2) const
{
    RealHex R;
    R.Size = Size;
    R.dSize = max(dSize, H2.dSize);
    int  borrow = 0;

    R.Ds = _Sub(Ds, H2.Ds, borrow, R.dSize, dSize, H2.dSize,base);
    R.Is = _Sub1(Is, H2.Is, borrow, R.Size, Size, H2.Size,base);
    R.Trim();

    return R;
}
bool RealHex::LessThanQuantityWise(const RealHex& H2) const
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
bool RealHex::GreaterThanQuantityWise(const RealHex& H2) const
{
    return H2.LessThanQuantityWise(*this);
}
bool RealHex::EqualQuantityWise(const RealHex& H2) const
{
    return (!this->GreaterThanQuantityWise(H2) && !this->LessThanQuantityWise(H2));
}
void RealHex::Trim()
{
    int tSize = Size;
    while (Size > 1 && Is[tSize - 1] == 0)
    {
        tSize--;
    }
    if (tSize != Size)
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
    if (dSize > 1)
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

const RealHex RealHex::operator+(const RealHex& HR) const
{
    RealHex result;
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
RealHex RealHex::ABS() const
{
    RealHex R = *this;
    R.isNeg = false;
    return R;
}
const RealHex RealHex::operator-() const
{
    RealHex result = *this;
    result.isNeg = !isNeg;
    return result;
}
const RealHex RealHex::operator-(const RealHex& HR) const
{
    return *this + (-HR);
}
const RealHex& RealHex::operator+=(const RealHex& HR)
{
    return *this = *this + HR;
}
const RealHex& RealHex::operator-=(const RealHex& HR)
{
    return *this = *this - HR;
}
bool RealHex:: operator>(const RealHex& HI)const
{
    if (isNeg != HI.isNeg)
        return isNeg == false;
    if (isNeg == false)
        return GreaterThanQuantityWise(HI);
    return LessThanQuantityWise(HI);
}
bool RealHex:: operator<(const RealHex& HI)const
{
    return HI > *this;
}
bool RealHex:: operator==(const RealHex& HI)const
{
    return !(*this<HI || *this > HI);
}
bool RealHex:: operator!=(const RealHex& HI)const
{
    return !(*this == HI);
}
bool RealHex:: operator<=(const RealHex& HI)const
{
    return (*this < HI || *this == HI);
}
bool RealHex:: operator>=(const RealHex& HI)const
{
    return (*this > HI || *this == HI);
}
const RealHex RealHex::operator--()
{
    RealHex result(*this);
    result -= one(base);
    return result;
}
const RealHex RealHex::operator++() {
    RealHex result(*this);
    result += one(base);
    return result;
}
const RealHex RealHex::operator++(int d)
{
    RealHex result = *this;
    ++(*this);
    return result;
}
const RealHex RealHex::operator--(int d)
{
    RealHex result = *this;
    --(*this);
    return result;
}
const RealHex RealHex::operator*(const RealHex& HR)const
{
    int NOD = dSize + HR.dSize;
    if (*this == zero(base) || HR == zero(base))
    {
        return zero(base);
    }
    RealHex N1 = *this;
    RealHex N2 = HR;
    N1.Is = concatenate(N1.Is, N1.Size, N1.Ds, N1.dSize);
    N2.Is = concatenate(N2.Is, N2.Size, N2.Ds, N2.dSize);
    N1.Size = Size + dSize;
    N2.Size = N2.Size + N2.dSize;
    N1.dSize = 1;
    N2.dSize = 1;
    N1.Ds = new int[1]{};
    N2.Ds = new int[1]{};
    RealHex result = zero(base), Zero = zero(base);
    RealHex A = N1;
    RealHex B = N2;
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
        RealHex temp = A, C = one(base);
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
void _insertAtStart(int*& Vs, int& size, int T)
{
    int* newPtr = new int[size + 1]{};
    newPtr[0] = T;
    for (int i = 1; i < size; i++)
    {
        newPtr[i] = Vs[i - 1];
    }
    newPtr[size] = Vs[size - 1];
    delete[]Vs;
    size++;
    Vs = newPtr;
    newPtr = nullptr;

}
const RealHex RealHex::operator/(const RealHex& HI) const
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


    int NOD = max(dSize, HI.dSize);
    int NOZ = min(dSize, HI.dSize);
    int presion = 12;
    RealHex N1 = *this;
    RealHex N2 = HI;
    N1.Is = concatenate(N1.Is, N1.Size, N1.Ds, N1.dSize);
    N2.Is = concatenate(N2.Is, N2.Size, N2.Ds, N2.dSize);
    N1.Size = Size + dSize;
    N2.Size = N2.Size + N2.dSize;
    N1.dSize = 1;
    N2.dSize = 1;
    N1.Ds = new int[1]{};
    N2.Ds = new int[1]{};

    for (int i = 0; i < NOZ + presion; i++)
        _insertAtStart(N1.Is, N1.Size, 0);
    N1.Trim();
    N2.Trim();
    RealHex quotient, temp = one(base), divisor = N2;
    RealHex remainder = N1;
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
        temp = one(base);
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
    if (remainder.ABS() == zero(base))
        remainder.isNeg = false;

    quotient.SplitIntoIntDec(NOD + presion);
    quotient.Trim();
    return quotient;
}
const RealHex& RealHex::operator*=(const RealHex& HR)
{
    return *this = *this * HR;
}
const RealHex& RealHex::operator/=(const RealHex& HR)
{
    return *this = *this / HR;
}


istream& operator>>(istream& in, RealHex& H)
{
    static int  b;
    cout << "Enter Base Firt:";
    cin >> b;
    string input;
    in >> input;
    H = RealHex(input,b);
    return in;
}
ifstream& operator>>(ifstream& rdr, RealHex& H)
{
    static int  b;
    rdr >> b;
    string input;
    getline(rdr, input);
    H = RealHex(input,b);
    return rdr;
}
ostream& operator<<(ostream& out, const RealHex& H)
{
    if (H.isNeg)
        out << "-";
    for (int i = 0; i < H.Size; i++)
    {
        if (H.Is[H.Size - 1 - i] >= 'A' - 55 && H.Is[H.Size - 1 - i] <= 'Z' - 55)
            out << char(H.Is[H.Size - 1 - i] + 55);
        else
            out << H.Is[H.Size - 1 - i];
    }
    if (H.dSize != 0)
    {
        out << ".";
        for (int i = 0; i < H.dSize; i++)
        {
            if (H.Ds[i] >= 'A' - 55 && H.Ds[i] <= 'Z' - 55)
                out << char(H.Ds[i] + 55);
            else
                out << H.Ds[i];
        }
    }
    return out;
}
RealHex::~RealHex()
{
    if (Ds != nullptr)
        delete[]Is;
    Is = nullptr;
    if (Ds != nullptr)
        delete[]Ds;
    Ds = nullptr;

}
