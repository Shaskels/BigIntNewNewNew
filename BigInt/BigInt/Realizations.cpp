#include "BigInt.h"
#include <iostream>
BigInt::BigInt() { // конструктор
    digits.push_back(0);
    sigh = 1;
}

BigInt::BigInt(int x) {
    sigh = (x < 0) ? 0 : 1;
    if (x < 0)
        x = -x;
    if (x == 0)
        digits.push_back(0);
    while (x != 0) {
        digits.push_back(x % base);
        x /= base;
    }
}

BigInt::BigInt(std::string x) {
    if (x.size() == 0) {
        digits.push_back(0);
        sigh = 1;
        return;
    }
    int start = isdigit(x[0]) ? 0 : 1;
    sigh = (x[0] == '-') ? 0 : 1;
    int counter = 0;
    int level = 1;
    digits.push_back(0);
    if (x[start] > '9' || x[start] < '0') throw std::invalid_argument("Wrong symbol");
    for (long long i = x.length() - 1; i >= start; i--) {
        if (x[i] > '9' || x[i] < '0') throw std::invalid_argument("Wrong symbol");
        if (counter >= 9) {
            digits.push_back(x[i] - '0');
            counter = 1;
            level = 10;
        }
        else {
            digits[digits.size() - 1] = digits[digits.size() - 1] + (x[i] - '0') * level;
            level *= 10;
            counter++;
        }
    }
} // бросать исключение std::invalid_argument при ошибке

BigInt::BigInt(const BigInt& x) {
    sigh = x.sigh;
    digits = x.digits;
}

BigInt::~BigInt() {
    (*this).digits.clear();
}

BigInt::operator int() const {
    if ((*this).digits.size() == 1) {
        return (*this).digits[0];
    }
    BigInt x = *this;
    int res;
    size_t len = x.digits.size() - 1;
    int k = 0;
    long long m = x.digits[len];
    while (m < 1000000000) {
        m *= 10;
        k++;
    }
    m = m + x.digits[len - 1] / pow(10, 9 - k);
    if (m > INT_MAX) {
        res = m / 10;
    }
    if ((*this).sigh == 0)
        return -res;
    return res;
}

BigInt::operator std::string() const {
    std::string res;
    if ((*this).sigh == 0)
        res.push_back('-');
    for (int i = (*this).digits.size() - 1; i >= 0; i--) {
        int m = (*this).digits[i];
        std::string tmp;
        while (m != 0) {
            int c = (m % 10);
            tmp.push_back(c + '0');
            m /= 10;
        }
        std::reverse(tmp.begin(), tmp.end());
        res.append(tmp);
    }
    return res;
}

size_t BigInt::size() const {
    size_t res = sizeof(int) + sizeof(bool) + sizeof(int) * (*this).digits.size();
    return res;
}
std::ostream& operator<<(std::ostream& o, const BigInt& i) {
    if (i.sigh == 0 && i.digits[i.digits.size() - 1] != 0)
        o << '-';
    for (int j = i.digits.size() - 1; j >= 0; j--) {
        if (i.digits[j] < 100000000 && j != i.digits.size() - 1) {
            int t = i.digits[j];
            while (t < 100000000) {
                t *= 10;
                o << 0;
            }
        }
        o << i.digits[j];
    }
    return o;
}
BigInt& BigInt::operator=(const BigInt& x) {
    if (this == &x)
        return *this;
    sigh = x.sigh;
    digits = x.digits;
    return *this;

}
bool BigInt::operator==(const BigInt& x) const {
    if ((*this).sigh != x.sigh)
        return 0;
    if ((*this).digits.size() != x.digits.size())
        return 0;
    for (int i = 0; i < x.digits.size(); i++) {
        if ((*this).digits[i] != x.digits[i])
            return 0;
    }
    return 1;
}

bool BigInt::operator!=(const BigInt& x) const {
    return !((*this) == x);
}

bool BigInt::operator<(const BigInt& x) const {
    if ((*this) == x)
        return 0;
    if ((*this).sigh == 0 && x.sigh == 1)
        return 1;
    else if ((*this).sigh == 1 && x.sigh == 0)
        return 0;
    if ((*this).digits.size() < x.digits.size())
        return 1;
    else if ((*this).digits.size() > x.digits.size())
        return 0;
    for (int i = x.digits.size() - 1; i >= 0; i--) {
        if ((*this).digits[i] < x.digits[i])
            return 1;
        else if ((*this).digits[i] > x.digits[i])
            return 0;
    }
    return 0;
}

bool BigInt::operator>(const BigInt& x) const {
    if ((*this) == x)
        return 0;
    return !((*this) < x);
}

bool BigInt::operator<=(const BigInt& x) const {
    if ((*this) == x)
        return 1;
    return (*this) < x;
}

bool BigInt::operator>=(const BigInt& x) const {
    if ((*this) == x)
        return 1;
    return (*this) > x;
}

BigInt BigInt::operator~() const {
    BigInt tmp = (*this);
    if (tmp.sigh == 0) {
        tmp++;
        tmp.sigh = 1;
    }
    else {
        tmp++;
        tmp.sigh = 0;
    }
    return tmp;
}
BigInt operator^(const BigInt& num1, const BigInt& num2) {
    BigInt tmp = num1;
    tmp ^= num2;
    return tmp;
}
BigInt operator&(const BigInt& num1, const BigInt& num2) {
    BigInt tmp = num1;
    tmp &= num2;
    return tmp;
}
BigInt operator|(const BigInt& num1, const BigInt& num2) {
    BigInt tmp = num1;
    tmp |= num2;
    return tmp;
}
std::string Inverter(std::string s) {
    for (long long i = 0; i < s.length(); i++) {
        if (s[i] == 0)
            s[i] = 1;
        else
            s[i] = 0;
    }
    return s;
}

std::string BigInt::BitString(BigInt x, long long len) {
    std::string s;
    BigInt two = 2;
    int sigh = x.sigh;
    if (sigh == 0)
        x = ~x;
    while (x > BigInt(0)) {
        int f = int(x % two);
        s.push_back(f);
        x /= two;
    }
    if (s.length() < len) {
        len -= s.length();
        while (len != 0) {
            s.push_back(0);
            len--;
        }
    }
    if (sigh == 0)
        s = Inverter(s);
    std::reverse(s.begin(), s.end());
    return s;
}

std::vector<int> BigInt::BigIntDigits(std::string x) {
    BigInt res;
    BigInt level = 1;
    BigInt two = 2;
    for (long long i = x.length() - 1; i >= 0; i--) {
        res += BigInt(x[i]) * level;
        level *= two;
    }
    return res.digits;
}

BigInt& BigInt::operator^=(const BigInt& x) {
    BigInt tmp = x;
    std::string num1;
    std::string num2;
    std::string res;
    long long len1;
    if ((*this).digits.size() > tmp.digits.size()) {
        num1 = BitString((*this), 0);
        len1 = num1.length();
        num2 = BitString(tmp, len1);
    }
    else if ((*this).digits.size() < tmp.digits.size()) {
        num1 = BitString(tmp, 0);
        len1 = num1.length();
        num2 = BitString((*this), len1);
    }
    else {
        if ((*this).digits[(*this).digits.size() - 1] > tmp.digits[tmp.digits.size() - 1]) {
            num1 = BitString((*this), 0);
            len1 = num1.length();
            num2 = BitString(tmp, len1);
        }
        else {
            num1 = BitString(tmp, 0);
            len1 = num1.length();
            num2 = BitString((*this), len1);
        }
    }
    for (long long i = 0; i < len1; i++) {
        if (num2[i] == 0 && num1[i] == 1 || num1[i] == 0 && num2[i] == 1)
            res.push_back(1);
        else
            res.push_back(0);
    }
    (*this).digits = BigIntDigits(res);
    if ((*this).sigh == 0 && x.sigh == 1 || (*this).sigh == 1 && x.sigh == 0) {
        res = Inverter(res);
        tmp.digits = BigIntDigits(res);
        tmp.sigh = 1;
        tmp++;
        (*this).digits = tmp.digits;
        (*this).sigh = 0;
    }
    else
        (*this).sigh = 1;
    return (*this);
}

BigInt& BigInt::operator&=(const BigInt& x) {
    BigInt tmp = x;
    std::string num1;
    std::string num2;
    std::string res;
    long long len1;
    if ((*this).digits.size() > tmp.digits.size()) {
        num1 = BitString((*this), 0);
        len1 = num1.length();
        num2 = BitString(tmp, len1);
    }
    else if ((*this).digits.size() < tmp.digits.size()) {
        num1 = BitString(tmp, 0);
        len1 = num1.length();
        num2 = BitString((*this), len1);
    }
    else {
        if ((*this).digits[(*this).digits.size() - 1] > tmp.digits[tmp.digits.size() - 1]) {
            num1 = BitString((*this), 0);
            len1 = num1.length();
            num2 = BitString(tmp, len1);
        }
        else {
            num1 = BitString(tmp, 0);
            len1 = num1.length();
            num2 = BitString((*this), len1);
        }
    }
    for (long long i = 0; i < len1; i++) {
        if (num2[i] == 0 || num1[i] == 0)
            res.push_back(0);
        else
            res.push_back(1);
    }
    (*this).digits = BigIntDigits(res);
    if ((*this).sigh == 0 && x.sigh == 0) {
        res = Inverter(res);
        tmp.digits = BigIntDigits(res);
        tmp.sigh = 1;
        tmp++;
        (*this).digits = tmp.digits;
    }
    if (x.sigh == 1)
        (*this).sigh = 1;
    return (*this);
}

BigInt& BigInt::operator|=(const BigInt& x) {
    BigInt tmp = x;
    std::string num1;
    std::string num2;
    std::string res;
    long long len1;
    if ((*this).digits.size() > tmp.digits.size()) {
        num1 = BitString((*this), 0);
        len1 = num1.length();
        num2 = BitString(tmp, len1);
    }
    else if ((*this).digits.size() < tmp.digits.size()) {
        num1 = BitString(tmp, 0);
        len1 = num1.length();
        num2 = BitString((*this), len1);
    }
    else {
        if ((*this).digits[(*this).digits.size() - 1] > tmp.digits[tmp.digits.size() - 1]) {
            num1 = BitString((*this), 0);
            len1 = num1.length();
            num2 = BitString(tmp, len1);
        }
        else {
            num1 = BitString(tmp, 0);
            len1 = num1.length();
            num2 = BitString((*this), len1);
        }
    }
    for (long long i = 0; i < len1; i++) {
        if (num2[i] == 1 || num1[i] == 1)
            res.push_back(1);
        else
            res.push_back(0);
    }
    (*this).digits = BigIntDigits(res);
    if ((*this).sigh == 0 || x.sigh == 0) {
        res = Inverter(res);
        tmp.digits = BigIntDigits(res);
        tmp.sigh = 1;
        tmp++;
        (*this).digits = tmp.digits;
        (*this).sigh = 0;
    }
    return (*this);
}
BigInt BigInt::DeleteZero(BigInt& x) {
    size_t i = x.digits.size() - 1;
    while (i >= 1 && x.digits[i] == 0) {
        x.digits.pop_back();
        i--;
    }
    return x;
}
BigInt operator%(const BigInt& num1, const BigInt& num2) {
    BigInt tmp = num1;
    tmp %= num2;
    return tmp;
}
BigInt operator+(const BigInt& num1, const BigInt& num2) {
    BigInt tmp = num1;
    tmp += num2;
    return tmp;

}//+
BigInt operator-(const BigInt& num1, const BigInt& num2) {
    BigInt tmp = num1;
    tmp -= num2;
    return tmp;
}//+

BigInt operator/(const BigInt& num1, const BigInt& num2) {
    BigInt tmp = num1;
    tmp /= num2;
    return tmp;
}

BigInt operator*(const BigInt& num1, const BigInt& num2) {
    BigInt tmp = num1;
    tmp *= num2;
    return tmp;
}//+

BigInt& BigInt::operator++() {
    return (*this) += 1;
}

const BigInt BigInt::operator++(int) {
    BigInt tmp = (*this);
    (*this) += 1;
    return tmp;
}

BigInt& BigInt::operator--() {
    return (*this) -= 1;
}

const BigInt BigInt::operator--(int) {
    BigInt tmp = (*this);
    (*this) -= 1;
    return tmp;
}
BigInt BigInt::Summation(BigInt& x, BigInt& y) {
    int carry = 0;
    size_t max = x.digits.size();
    if (x.digits.size() < y.digits.size()) {
        max = y.digits.size();
        x.digits.resize(y.digits.size());
    }
    else
        y.digits.resize(x.digits.size());
    for (int i = 0; i < max; i++) {
        int t = x.digits[i];
        x.digits[i] = (carry + x.digits[i] + y.digits[i]) % base;
        carry = (t + y.digits[i] + carry) / base;
    }
    if (carry != 0)
        x.digits.push_back(carry);
    x = DeleteZero(x);
    return x;
}

BigInt BigInt::Subtraction(BigInt& x, BigInt& y) {
    int carry = 0;
    int i;
    for (i = 0; i < y.digits.size(); i++) {
        x.digits[i] = x.digits[i] - y.digits[i] - carry;
        carry = 0;
        if (x.digits[i] < 0) {
            x.digits[i] += base;
            carry = 1;
        }
    }
    while (carry != 0) {
        x.digits[i] -= carry;
        carry = 0;
        if (x.digits[i] < 0) {
            x.digits[i] += base;
            carry = 1;
        }
        i++;
    }
    x = DeleteZero(x);
    if (x.digits[0] == 0 && x.digits.size() == 1)
        x.sigh = 1;
    return x;
}

BigInt& BigInt::operator+=(const BigInt& x) {
    BigInt tmp = x;
    if ((*this).sigh == 1 && x.sigh == 1 || (*this).sigh == 0 && x.sigh == 0)
        return *this = Summation((*this), tmp);
    if ((*this) >= x) {
        tmp = -x;
        if (*this >= tmp)  return *this = Subtraction((*this), tmp);
        else if (*this <= tmp) return *this = -(Subtraction(tmp, *this));
    }
    else {
        if (-(*this) >= x) return *this = Subtraction((*this), tmp);
        else if (-(*this) <= x) return *this = Subtraction(tmp, (*this));
    }
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& x) {
    BigInt tmp = x;
    if ((*this).sigh == 1 && x.sigh == 0 || (*this).sigh == 0 && x.sigh == 1)
        return *this = Summation((*this), tmp);
    if ((*this) >= x) {
        if ((*this).sigh == 1 && x.sigh == 1) return *this = Subtraction((*this), tmp);
        else if ((*this).sigh == 0 && x.sigh == 0) return *this = -(Subtraction((*this), tmp));
    }
    else {
        if ((*this).sigh == 1 && x.sigh == 1) return *this = -(Subtraction(tmp, *this));
        else if ((*this).sigh == 0 && x.sigh == 0) return *this = -(Subtraction(tmp, *this));
    }

    return *this;
}

BigInt& BigInt::operator*=(const BigInt& x) {
    BigInt res, num1, num2;
    long long tmp;
    for (int i = 0; i < (*this).digits.size() + x.digits.size(); i++) {
        res.digits.push_back(0);
    }
    if ((*this) >= x) {
        num1 = x;
        num2 = (*this);
    }
    else {
        num1 = (*this);
        num2 = x;
    }
    for (int i = 0; i < num1.digits.size(); i++) {
        int carry = 0;
        int j;
        for (j = 0; j < num2.digits.size(); j++) {
            tmp = (static_cast<long long>(num1.digits[i]) * num2.digits[j] + carry);
            carry = 0;
            long long l = res.digits[i + j] + (tmp % base);
            if (l > base - 1) {
                carry += l / base;
                l %= base;
            }
            res.digits[i + j] = l;
            carry += static_cast<int>(tmp / base);
        }
        if (carry != 0) {
            res.digits[i + j] = carry;
        }
    }
    if ((*this).sigh == 0 || x.sigh == 0)
        res.sigh = 0;
    res = DeleteZero(res);
    (*this) = res;
    return (*this);
}

BigInt& shift(BigInt& x) {
    x.digits.push_back(0);
    for (int i = x.digits.size() - 1; i > 0; i--) {
        x.digits[i] = x.digits[i - 1];
    }
    return x;
}
BigInt& BigInt::operator/=(const BigInt& x) {
    if (x == BigInt(0))
        throw std::exception("division by zero");
    BigInt tmp, res, n = x;
    n.sigh = 1;
    for (int i = 0; i < (*this).digits.size(); i++) {
        res.digits.push_back(0);
    }
    for (int i = (*this).digits.size() - 1; i >= 0; i--) {
        tmp = shift(tmp);
        tmp.digits[0] = (*this).digits[i];
        tmp = DeleteZero(tmp);
        int k = 0, b = BigInt::base;
        int quotient = 0;
        while (k <= b) {
            int m = (k + b) / 2;
            BigInt t = n * BigInt(m);
            if (t <= tmp) {
                quotient = m;
                k = m + 1;
            }
            else b = m - 1;
        }
        res.digits[i] = quotient;
        tmp -= BigInt(quotient) * n;
    }
    if ((*this).sigh == 0 || x.sigh == 0)
        res.sigh = 0;
    res = DeleteZero(res);
    (*this) = res;
    return *this;
}
BigInt& BigInt::operator%=(const BigInt& x) {
    BigInt tmp = x;
    tmp.sigh = 1;
    (*this).sigh = 1;
    BigInt quotient = (*this) / tmp;
    return (*this) -= quotient * tmp;
}
BigInt BigInt::operator+() const {
    return BigInt((*this));
}  // unary +

BigInt BigInt::operator-() const {
    BigInt tmp = (*this);
    if (tmp.sigh == 1)
        tmp.sigh = 0;
    else
        tmp.sigh = 1;
    return tmp;
} // unary -
