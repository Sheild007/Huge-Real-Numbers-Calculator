#pragma once

#include<iostream>
#include<fstream>

using namespace std;
class HugeHex
{
private:
	int base;
	int* Ds;
     int  Size;
	 bool isNeg;
	void assign(const HugeHex&);
	static void insertAtEnd(int*& Vs, int& size, int T);
	HugeHex ADDQuantityWise(const HugeHex& H2) const;
	HugeHex SUBQuantityWise(const HugeHex& H2) const;
	bool LessThanQuantityWise(const HugeHex& H2) const;
	bool GreaterThanQuantityWise(const HugeHex& H2) const;
	bool EqualQuantityWise(const HugeHex& H2) const;
	static HugeHex one(int);
	static HugeHex zero(int);
	void devison(HugeHex HI, HugeHex& Q, HugeHex& R)const;
public:
	HugeHex();
	HugeHex(int _size,int);
	HugeHex(const string& str,int);
	HugeHex(const char* str,int);
	HugeHex(const HugeHex&);
	HugeHex(ifstream& rdr,int base);
	void Load(ifstream& rrd,int);
	const HugeHex& operator=(const HugeHex&);
	int operator[ ](int i) const;
	int& operator[ ](int i);
	HugeHex ABS() const;
	void SetBase(int);
	void Trim();
	const HugeHex operator+(const HugeHex& HI)const;
	const HugeHex operator -()const;
	const HugeHex operator-(const HugeHex& HI)const;
	bool operator>(const HugeHex& HI)const;
	bool operator<(const HugeHex& HI)const;
	bool operator==(const HugeHex& HI)const;
	bool operator!=(const HugeHex& HI)const;
	bool operator<=(const HugeHex& HI)const;
	bool operator>=(const HugeHex& HI)const;
	const HugeHex operator --();
	const HugeHex operator++();
	const HugeHex operator --(int d);
	const HugeHex operator++(int d);
	const HugeHex& operator+=(const HugeHex& HI);
	const HugeHex& operator*=(const HugeHex& HI);
	const HugeHex& operator/=(const HugeHex& HI);
	const HugeHex& operator%=(const HugeHex& HI);
	const HugeHex& operator-=(const HugeHex& HI);
	const HugeHex operator*(const HugeHex& HI)const;
	const HugeHex operator/(const HugeHex& HI)const;
	const HugeHex operator%(const HugeHex& HI)const;

	friend ostream& operator<<(ostream&out, const HugeHex&H);
	friend istream& operator>>(istream& in,  HugeHex& H);
	friend ifstream& operator>>(ifstream& rdr, HugeHex& H);
	~HugeHex();




};

