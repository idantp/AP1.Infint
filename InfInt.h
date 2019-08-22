//
// Created by Idan Twito on 11/6/18.
// ID number: 311125249.
// User ID: twitoid.
//

#ifndef ADVANCEDEX1_INFINT_H
#define ADVANCEDEX1_INFINT_H

#include <string>
#include <stdexcept>

using namespace std;

/**
 * this Class describes Integer numbers which is not size-limited.
 * The class supports int's operators including input output,
 * and Bitwise operators.
 */
class InfInt {
private:
    //contains the binary expression.
    string binaryStr;
    //indicates the number's sign - positive or negative.
    bool isNegative;

private:

    string zeroCutter(string str1);

    string stringToBinaryStr(string inputStr, string outputStr);

public:

    InfInt();

    InfInt(const char *strPar);

    InfInt(const long num);

    InfInt(const int num);

    InfInt(string strPar);

    string getBinaryStr() const;

    bool getSign() const;

    void setSign(bool sign);

    bool operator==(InfInt other) const;

    bool operator>(InfInt other) const;

    bool operator>=(InfInt other) const;

    bool operator<=(InfInt other) const;

    bool operator<(InfInt other) const;

    InfInt operator&(InfInt other) const;

    InfInt operator|(InfInt other) const;

    InfInt operator^(InfInt other) const;

    InfInt operator+(InfInt other) const;

    InfInt operator-(InfInt other) const;

    InfInt &operator+=(InfInt other);

    InfInt &operator&=(InfInt other);

    InfInt &operator>>=(int k);

    InfInt operator++(int);

    InfInt &operator++();

    InfInt operator--(int);

    InfInt &operator--();

    InfInt operator<<(int k) const;

    InfInt operator>>(int k) const;

    InfInt operator/(InfInt other) const;

    InfInt operator%(InfInt other) const;

    InfInt operator*(InfInt other) const;

    InfInt divisionAndMod(InfInt dividend, InfInt divisor, bool isDivision) const;

    friend istream &operator>>(istream &is, InfInt &thisInfInt);

    friend ostream &operator<<(ostream &os, const InfInt &thisInfInt);

    explicit operator int() const;

};

#endif //ADVANCEDEX1_INFINT_H
