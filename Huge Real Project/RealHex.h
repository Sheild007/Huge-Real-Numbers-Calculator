#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class RealHex
{
	int base;
	int* Is;
	int* Ds;
	int  Size;
	int dSize;
	bool isNeg;
	void assign(const RealHex&);
	int* concatenate(int* P1, int s1, int* P2, int s2)const;
	RealHex ADDQuantityWise(const RealHex& H2) const;
	RealHex SUBQuantityWise(const RealHex& H2) const;
	bool LessThanQuantityWise(const RealHex& H2) const;
	bool GreaterThanQuantityWise(const RealHex& H2) const;
	bool EqualQuantityWise(const RealHex& H2) const;
	static RealHex one(int);
	static RealHex zero(int);
	void SplitIntoIntDec(int NOD);
	

public:
	RealHex();
	RealHex(int _size,int);
	RealHex(const string& str,int);
	RealHex(const char* str,int);
	RealHex(const RealHex&);
	RealHex(ifstream& rdr, int _base);
	void Load(ifstream& rrd,int);
	const RealHex& operator=(const RealHex&);
	int  operator[ ](int i) const;
	int& operator[ ](int i);
	RealHex ABS() const;

	void Trim();
	const RealHex operator+(const RealHex& HR)const;
	const RealHex operator -()const;
	const RealHex operator-(const RealHex& HR)const;
	bool operator>(const RealHex& HR)const;
	bool operator<(const RealHex& HR)const;
	bool operator==(const RealHex& HR)const;
	bool operator!=(const RealHex& HR)const;
	bool operator<=(const RealHex& HR)const;
	bool operator>=(const RealHex& HR)const;
	const RealHex operator --();
	const RealHex operator++();
	const RealHex operator --(int d);
	const RealHex operator++(int d);
	const RealHex& operator+=(const RealHex& HR);
	const RealHex& operator*=(const RealHex& HR);
	const RealHex& operator/=(const RealHex& HR);
	const RealHex& operator-=(const RealHex& HR);
	const RealHex operator*(const RealHex& HR)const;
	const RealHex operator/(const RealHex& HR)const;
	friend ostream& operator<<(ostream& out, const RealHex& H);
	friend istream& operator>>(istream& in, RealHex& H);
	friend ifstream& operator>>(ifstream& rdr, RealHex& H);


	~RealHex();


};

