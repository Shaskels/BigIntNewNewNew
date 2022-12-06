#pragma once
#include<vector>
#include<string> 
#include<math.h>

class BigInt {
public:
	std::vector<int> digits;
	bool sigh;
	const int base = 1000000000;
	BigInt();//+
	BigInt(int);//+
	BigInt(std::string); // бросать исключение std::invalid_argument при ошибке +
	BigInt(const BigInt&);//+
	~BigInt();//+

	BigInt& operator=(const BigInt&);  //возможно присваивание самому себе!+

	BigInt operator~() const;

	BigInt& operator++();//+
	const BigInt operator++(int);//+
	BigInt& operator--();//+
	const BigInt operator--(int);//+

	BigInt& operator+=(const BigInt&);//+
	BigInt& operator*=(const BigInt&);//+
	BigInt& operator-=(const BigInt&);//+
	BigInt& operator/=(const BigInt&);//+
	BigInt& operator^=(const BigInt&);
	BigInt& operator%=(const BigInt&);//+
	BigInt& operator&=(const BigInt&);
	BigInt& operator|=(const BigInt&);

	BigInt operator+() const;  // unary + +
	BigInt operator-() const;  // unary - +

	bool operator==(const BigInt&) const;//+
	bool operator!=(const BigInt&) const;//+
	bool operator<(const BigInt&) const;//+
	bool operator>(const BigInt&) const;//+
	bool operator<=(const BigInt&) const;//+
	bool operator>=(const BigInt&) const;//+

	operator int() const;//+
	operator std::string() const;//+


	std::string BitString(BigInt, long long);
	size_t size() const;  // size in bytes
	BigInt DeleteZero(BigInt&);
	BigInt Summation(BigInt&, BigInt&);
	BigInt Subtraction(BigInt&, BigInt&);
	std::vector<int> BigIntDigits(std::string);
};
BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream&, const BigInt&);