#pragma once
#include<iostream>
#include<fstream>

using namespace std;
class HugeReal
{
private:
	int* Is;
	int* Ds;
	int  Size;
	int dSize;
	bool isNeg;
	void assign(const HugeReal&);
	int* concatenate(int* P1, int s1, int* P2, int s2)const;
	HugeReal ADDQuantityWise(const HugeReal& H2) const;
	HugeReal SUBQuantityWise(const HugeReal& H2) const;
	bool LessThanQuantityWise(const HugeReal& H2) const;
	bool GreaterThanQuantityWise(const HugeReal& H2) const;
	bool EqualQuantityWise(const HugeReal& H2) const;
	static HugeReal one();
	static HugeReal zero();
	void SplitIntoIntDec(int NOD);
	

public:
	HugeReal();
	HugeReal(int _size);
	HugeReal(const string& str);
	HugeReal(const char* str);
	HugeReal(const HugeReal&);
	HugeReal(ifstream& rdr);
	void Load(ifstream& rrd);
	const HugeReal& operator=(const HugeReal&);
	int  operator[ ](int i) const;
	int& operator[ ](int i);
	HugeReal ABS() const;

	void Trim();
	const HugeReal operator+(const HugeReal& HR)const;
	const HugeReal operator -()const;
	const HugeReal operator-(const HugeReal& HR)const;
	bool operator>(const HugeReal& HR)const;
	bool operator<(const HugeReal& HR)const;
	bool operator==(const HugeReal& HR)const;
	bool operator!=(const HugeReal& HR)const;
	bool operator<=(const HugeReal& HR)const;
	bool operator>=(const HugeReal& HR)const;
	const HugeReal operator --();
	const HugeReal operator++();
	const HugeReal operator --(int d);
	const HugeReal operator++(int d);
	const HugeReal& operator+=(const HugeReal& HR);
	const HugeReal& operator*=(const HugeReal& HR);
	const HugeReal& operator/=(const HugeReal& HR);
	const HugeReal& operator-=(const HugeReal& HR);
	const HugeReal operator*(const HugeReal& HR)const;
	const HugeReal operator/(const HugeReal& HR)const;
	friend ostream& operator<<(ostream& out, const HugeReal& H);
	friend istream& operator>>(istream& in, HugeReal& H);
	friend ifstream& operator>>(ifstream& rdr, HugeReal& H);
	~HugeReal();

};

