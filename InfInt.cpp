//
// Created by Idan Twito on 11/6/18.
// ID number: 311125249.
// User ID: twitoid.
//

#include <stdio.h>
#include "InfInt.h"
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

/**
 * checks whether the input string consists of digits only or not.
 * @param str1 - indicates the string the needs to be checked.
 */
void isNumber(string str1) {
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] < 48 || str1[i] > 57) {
            throw invalid_argument("an invalid number was entered");
        }
    }
}

/**
 * the function gets 2 string. it converts inputStr from decimal expression
 * into binary expression and put it in outputStr (which always gets "").
 * @param inputStr  - the decimal string
 * @param outputStr - the returned binary expression string.
 * @return outputStr.
 */
string InfInt::stringToBinaryStr(string inputStr, string outputStr) {
    //finish the recursive function
    if (inputStr == "0") {
        //if the input is just "0" -> return "0"
        if (outputStr == "") { outputStr += "0"; }
        reverse(outputStr.begin(), outputStr.end());
        return outputStr;
    } else {
        string remaindersStr = "0";
        string newOutputStr;
        int digit;
        //runs all over the number to find the matching binary expression
        for (int i = 0; i < inputStr.length(); i++) {
            digit = inputStr.at(i) - '0';
            if (digit % 2 == 1) {
                digit = 5;
            } else {
                digit = 0;
            }
            remaindersStr += to_string(digit);
            newOutputStr += to_string((inputStr.at(i) - '0') / 2 + (remaindersStr.at(i) - '0'));
        }
        // string outputStr will comprise the binary expression
        if (digit == 0) {
            outputStr += '0';
        } else { outputStr += '1'; }
        newOutputStr.erase(0, min(newOutputStr.find_first_not_of('0'), newOutputStr.size() - 1));
        //calls and returns a recursive call
        return stringToBinaryStr(newOutputStr, outputStr);
    }
}

/**
 * the function gets 2 string, given that longStr is longer than
 * shortStr. It adds zeros on the left of the shortStr until that
 * string and longStr have the same length.
 * @param longStr - the longer string
 * @param shortStr - the shorter string which is padded with 0's.
 * @return string paddedStr.
 */
string zeroPadding(string longStr, string shortStr) {
    string paddedStr;
    int longInfLength = longStr.length();
    int shortInfLength = shortStr.length();
    int difference = longInfLength - shortInfLength;
    for (int i = 0; i < difference; i++) {
        paddedStr += '0';
    }
    for (int i = 0; i < shortInfLength; ++i) {
        paddedStr += shortStr.at(i);
    }
    return paddedStr;
}

/**
 * This is an assisting method of binaryToDecimal. It gets 2 string of
 * digits, add the addition of them into a new string which in decimal
 * representation and returns that decimal expression-String.
 * @param decimalStr the first digits-String
 * @param exponentStr the second digits-String
 * @return string resultStr.
 */
string oneBitToDecimal(string decimalStr, string exponentStr) {
    int decimalLen = decimalStr.length();
    int exponentLen = exponentStr.length();
    string newDecimal = decimalStr;
    string newExponent = exponentStr;
    int decimalStrBit;
    int exponentBit;
    int sum = 0;
    string resultStr;
    int extraAddition = 0;
    int maxLength = decimalLen;
    if (decimalLen > exponentLen) {
        newDecimal = decimalStr;
        newExponent = zeroPadding(decimalStr, exponentStr);
        maxLength = decimalLen;
    } else if (decimalLen < exponentLen) {
        newDecimal = zeroPadding(exponentStr, decimalStr);
        newExponent = exponentStr;
        maxLength = exponentLen;
    }
    for (int i = maxLength - 1; i >= 0; i--) {
        decimalStrBit = newDecimal[i] - '0';
        exponentBit = newExponent[i] - '0';
        sum = decimalStrBit + exponentBit + extraAddition;
        if (sum < 10) {
            extraAddition = 0;
            resultStr += to_string(sum);
        } else if (sum >= 10) {
            extraAddition = 1;
            resultStr += to_string(sum - 10);
        }
    }
    if (extraAddition == 1) {
        resultStr += "1";
    }
    reverse(resultStr.begin(), resultStr.end());
    return resultStr;
}

/**
 * this function converts binary expression string into decimal expression
 * string via oneBitToDecimal. Via oneBitToDecimal I raise the exponent
 * and sums all the binary digits (which show 1) into decimal expression.
 * @param binaryStr - the binary expression
 * @return string decimalStr
 */
string binaryToDecimal(string binaryStr) {
    string decimalStr = "0";
    string exponent = "1";
    for (int i = binaryStr.length() - 1; i >= 0; i--) {
        if (binaryStr[i] - '0' == 1) {
            decimalStr = oneBitToDecimal(decimalStr, exponent);
        }
        exponent = oneBitToDecimal(exponent, exponent);
    }
    return decimalStr;
}

/**
 * default constructor - the number is initialized with 0 and positive.
 */
InfInt::InfInt() {
    this->binaryStr = "0";
    this->isNegative = false;
}


/**
 * constructor in which InfInt gets const char *.
 * the input can start with "-" to indicate a negative number, but
 * beside that it must contain digits only, otherwise an exception is thrown.
 * @param strPar const char *
 */
InfInt::InfInt(const char *strPar) {
    string decimalStr = strPar;
    //removes '-' and marks as negative num
    if (decimalStr[0] == '-') {
        decimalStr.erase(0, 1);
        this->isNegative = true;
    } else {
        this->isNegative = false;
    }
    //removes all the zeros on the left
    decimalStr = zeroCutter(decimalStr);
    //makes sure "-0" is not negative.
    if (decimalStr == "0") {
        this->isNegative = false;
    }
    //verifies its a valid number.
    isNumber(decimalStr);
    this->binaryStr = stringToBinaryStr(decimalStr, "");
}

/**
 * constructor in which InfInt gets string.
 * the input can start with "-" to indicate a negative number, but
 * beside that it must contain digits only, otherwise an exception is thrown.
 * @param strPar string
 */
InfInt::InfInt(string strPar) {
    string decimalStr = strPar;
    decimalStr = strPar;
    if (decimalStr[0] == '-') {
        decimalStr.erase(0, 1);
        this->isNegative = true;
    } else {
        this->isNegative = false;
    }
    decimalStr = zeroCutter(decimalStr);
    isNumber(decimalStr);
    this->binaryStr = stringToBinaryStr(decimalStr, "");
}

/**
 * constructor in which InfInt gets const long.
 * the input can start with "-" to indicate a negative number, but
 * beside that it must contain digits only, otherwise an exception is thrown.
 * @param strPar const long
 */
InfInt::InfInt(const long num) {
    string decimalStr = (to_string(num));
    if (decimalStr[0] == '-') {
        //remove the "-" and mark as negative number.
        decimalStr.erase(0, 1);
        this->isNegative = true;
    } else {
        this->isNegative = false;
    }
    this->binaryStr = stringToBinaryStr(decimalStr, "");
}

/**
 * constructor in which InfInt gets const int.
 * the input can start with "-" to indicate a negative number, but
 * beside that it must contain digits only, otherwise an exception is thrown.
 * @param strPar const int
 */
InfInt::InfInt(const int num) {
    string decimalStr = (to_string(num));
    if (decimalStr[0] == '-') {
        decimalStr.erase(0, 1);
        this->isNegative = true;
    } else {
        this->isNegative = false;
    }
    this->binaryStr = stringToBinaryStr(decimalStr, "");
}

/**
 * sets the sign of the InfInt - true indicates negative, false
 * indicates positive number.
 * @param sign
 */
void InfInt::setSign(bool sign) {
    this->isNegative = sign;
}

/**
 * gets the binary expression string of this InfInt.
 * @return this->binaryStr.
 */
string InfInt::getBinaryStr() const {
    return this->binaryStr;
}

/**
 * gets the sign of the InfInt - true indicates negative, false
 * indicates positive number.
 * @param sign
 */
bool InfInt::getSign() const {
    return this->isNegative;
}

/**
 * removes all the 0's on the left until finds the first 1.
 * if the number contains 0's only - return "0".
 * @param str1 binary string
 * @return string without 0's on the left, except for "0".
 */
string InfInt::zeroCutter(string str1) {
    return str1.erase(0, min(str1.find_first_not_of('0'), str1.size() - 1));
}

/**
 * implements the operator == between two InfInts.
 * @param other other InfInt.
 * @return bool variable.
 */
bool InfInt::operator==(InfInt other) const {
    if (this->getSign() == other.getSign()) {
        if (this->getBinaryStr().length() == other.getBinaryStr().length()) {
            for (int i = 0; i < this->getBinaryStr().length(); i++) {
                if (this->getBinaryStr()[i] != other.getBinaryStr()[i]) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

/**
 * implements the operator > between two InfInts.
 * @param other other InfInt.
 * @return bool variable.
 */
bool InfInt::operator>(InfInt other) const {
    //left number is positive, the right one is negative
    if (!(this->getSign()) && other.getSign()) {
        return true;
        //left number is negative, the right one is positive
    } else if ((this->getSign()) && !(other.getSign())) {
        return false;
        //both positive numbers
    } else if (!(this->getSign()) && !(other.getSign())) {
        //if the numbers have different amount of digits
        if (this->getBinaryStr().length() != other.getBinaryStr().length()) {
            if (this->getBinaryStr().length() > other.getBinaryStr().length()) {
                return true;
            }
            return false;
            //the numbers have same amount of digits
        } else {
            //if the numbers are equal return false
            if (*this == other) {
                return false;
            } else {
                //the numbers are positive and have same length-check by digits
                for (int i = 0; i < this->getBinaryStr().length(); i++) {
                    if (this->getBinaryStr()[i] < other.getBinaryStr()[i]) {
                        return false;
                    } else if (this->getBinaryStr()[i] > other.getBinaryStr()[i]) {
                        return true;
                    }
                }
            }
        }
        //both negative numbers
    } else if ((this->getSign()) && (other.getSign())) {
        //if the numbers have different amount of digits
        if (this->getBinaryStr().length() != other.getBinaryStr().length()) {
            if (this->getBinaryStr().length() < other.getBinaryStr().length()) {
                return true;
            }
            return false;
            //the numbers have same amount of digits
        } else {
            if (*this == other) {
                return false;
            } else {
                for (int i = 0; i < this->getBinaryStr().length(); i++) {
                    if (this->getBinaryStr()[i] > other.getBinaryStr()[i]) {
                        return false;
                    } else if (this->getBinaryStr()[i] < other.getBinaryStr()[i]) {
                        return true;
                    }
                }
            }
        }
    }
}

/**
 * implements the operator >= between two InfInts, and returns the bool result.
 * @param other other InfInt.
 * @return bool variable.
 */
bool InfInt::operator>=(InfInt other) const {
    if (*this > other || *this == other) {
        return true;
    }
    return false;
}

/**
 * implements the operator < between two InfInts, and returns the bool result.
 * @param other other InfInt.
 * @return bool variable.
 */
bool InfInt::operator<(InfInt other) const {
    return (!(*this >= other));
}

/**
 * implements the operator <= between two InfInts, and returns the bool result.
 * @param other other InfInt.
 * @return bool variable.
 */
bool InfInt::operator<=(InfInt other) const {
    return (!(*this > other));
}

/**
 * implements the Bitwise operator & between two InfInts,
 * and returns the InfInt result.
 * @param other the other InfInt
 * @return infIntResult
 */
InfInt InfInt::operator&(InfInt other) const {
    string str;
    string paddedStr;
    InfInt infIntResult;
    string thisStr = this->getBinaryStr();
    string otherStr = other.getBinaryStr();
    int thisLength = this->getBinaryStr().length();
    int otherLength = other.getBinaryStr().length();
    if (thisLength == otherLength) {
        for (int i = 0; i < thisLength; i++) {
            str += to_string(((this->getBinaryStr().at(i) - '0') & (other.getBinaryStr().at(i) - '0')));
        }
    } else {
        if (thisLength > otherLength) {
            paddedStr = zeroPadding(thisStr, otherStr);
            for (int i = 0; i < thisLength; i++) {
                str += to_string((this->getBinaryStr().at(i) - '0') & (paddedStr.at(i) - '0'));
            }
        } else {
            paddedStr = zeroPadding(otherStr, thisStr);
            for (int i = 0; i < otherLength; i++) {
                str += to_string((other.getBinaryStr().at(i) - '0') & (paddedStr.at(i) - '0'));
            }
        }
    }
    infIntResult = binaryToDecimal(str);
    if (this->getSign() && other.getSign()) {
        infIntResult.setSign(true);
    } else {
        infIntResult.setSign(false);
    }
    if (infIntResult.getBinaryStr() == "0") {
        infIntResult.setSign(false);
    }
    return infIntResult;
}

/**
 * implements the Bitwise operator | between two InfInts,
 * and returns the InfInt result.
 * @param other the other InfInt
 * @return infIntResult
 */
InfInt InfInt::operator|(InfInt other) const {
    string str;
    string paddedStr;
    InfInt infIntResult;
    string thisStr = this->getBinaryStr();
    string otherStr = other.getBinaryStr();
    int thisLength = this->getBinaryStr().length();
    int otherLength = other.getBinaryStr().length();
    if (thisLength == otherLength) {
        for (int i = 0; i < thisLength; i++) {
            str += to_string(((this->getBinaryStr().at(i) - '0') | (other.getBinaryStr().at(i) - '0')));
        }
    } else {
        if (thisLength > otherLength) {
            paddedStr = zeroPadding(thisStr, otherStr);
            for (int i = 0; i < thisLength; i++) {
                str += to_string((this->getBinaryStr().at(i) - '0') | (paddedStr.at(i) - '0'));
            }
        } else {
            paddedStr = zeroPadding(otherStr, thisStr);
            for (int i = 0; i < otherLength; i++) {
                str += to_string((other.getBinaryStr().at(i) - '0') | (paddedStr.at(i) - '0'));
            }
        }
    }
    infIntResult = binaryToDecimal(str);
    if (this->getSign() || other.getSign()) {
        infIntResult.setSign(true);
    } else {
        infIntResult.setSign(false);
    }
    if (infIntResult.getBinaryStr() == "0") {
        infIntResult.setSign(false);
    }
    return infIntResult;
}

/**
 * implements the Bitwise operator ^ between two InfInts,
 * and returns the InfInt result.
 * @param other the other InfInt
 * @return infIntResult
 */
InfInt InfInt::operator^(InfInt other) const {
    string str;
    string paddedStr;
    InfInt infIntResult;

    int thisLength = this->getBinaryStr().length();
    int otherLength = other.getBinaryStr().length();
    if (thisLength == otherLength) {
        for (int i = 0; i < thisLength; i++) {
            str += to_string(((this->getBinaryStr().at(i) - '0') ^ (other.getBinaryStr().at(i) - '0')));
        }
    } else {
        if (thisLength > otherLength) {
            paddedStr = zeroPadding(this->getBinaryStr(), other.getBinaryStr());
            for (int i = 0; i < thisLength; i++) {
                str += to_string((this->getBinaryStr().at(i) - '0') ^ (paddedStr.at(i) - '0'));
            }
        } else {
            paddedStr = zeroPadding(other.getBinaryStr(), this->getBinaryStr());
            for (int i = 0; i < otherLength; i++) {
                str += to_string((other.getBinaryStr().at(i) - '0') ^ (paddedStr.at(i) - '0'));
            }
        }
    }
    infIntResult = binaryToDecimal(str);
    if (this->getSign() != other.getSign()) {
        infIntResult.setSign(true);
    } else {
        infIntResult.setSign(false);
    }
    if (infIntResult.getBinaryStr() == "0") {
        infIntResult.setSign(false);
    }
    return infIntResult;
}

/**
 * the function implements "+" operation on two InfInts by summing them
 * into a new InfInt (infIntResult) and returns it. The operation is made
 * on 2 binary expression strings and returns an InfInt that contains the
 * binary expression result.
 * @param other the second InfInt
 * @return InfInt infIntResult
 */
InfInt InfInt::operator+(InfInt other) const {
    string thisStr;
    string otherStr;
    int thisLength = this->getBinaryStr().length();
    int otherLength = other.getBinaryStr().length();
    int maxLength;
    bool areNegative;
    string resultStr;
    InfInt infIntResult;
    int extraAddition = 0;
    int digitsSum = 0;
    //both numbers are positive
    if (!(this->getSign()) && !(other.getSign())) {
        areNegative = false;
    }
        //both are negative number
    else if (this->getSign() && other.getSign()) {
        areNegative = true;
    }
        //left number is negative, the right one is positive
    else if (this->getSign() && !(other.getSign())) {
        InfInt temp = *this;
        temp.setSign(false);
        return (other - temp);
    }//the left number is positive, the right one is negative
    else if (!(this->getSign()) && other.getSign()) {
        other.setSign(false);
        return (*this - other);
    }
    if (thisLength == otherLength) {
        thisStr = this->getBinaryStr();
        otherStr = other.getBinaryStr();
        maxLength = thisLength;
    } else if (thisLength > otherLength) {
        thisStr = this->getBinaryStr();
        otherStr = zeroPadding(this->getBinaryStr(), other.getBinaryStr());
        maxLength = thisLength;
    } else {
        thisStr = zeroPadding(other.getBinaryStr(), this->getBinaryStr());
        otherStr = other.getBinaryStr();
        maxLength = otherLength;
    }
    for (int i = maxLength - 1; i >= 0; i--) {
        digitsSum = (thisStr[i] - '0') + (otherStr[i] - '0') + extraAddition;
        if (digitsSum == 0) {
            extraAddition = 0;
            resultStr += "0";
        } else if (digitsSum == 1) {
            extraAddition = 0;
            resultStr += "1";
        } else if (digitsSum == 2) {
            extraAddition = 1;
            resultStr += "0";
        } else if (digitsSum == 3) {
            extraAddition = 1;
            resultStr += "1";
        }
    }
    if (extraAddition == 1) {
        resultStr += "1";
    }
    reverse(resultStr.begin(), resultStr.end());
    infIntResult = binaryToDecimal(resultStr);
    if (areNegative) {
        infIntResult.setSign(true);
    }
    return infIntResult;
}

/**
 * the function implements "-" operation on two InfInts by subtracting the
 * other InfInt from this InfInt. the result is stored in a new InfInt
 * (infIntResult),the method output. The operation is made
 * on 2 binary expression strings and returns an InfInt that contains the
 * binary expression result.
 * @param other the second InfInt
 * @return InfInt infIntResult
 */
InfInt InfInt::operator-(InfInt other) const {
    string biggerBinary;
    string smallerBinary;
    string resultStr;
    InfInt infIntResult;
    int digitsSubtraction = 0;
    //marks if needed to multiply by 1 or (-1)
    int flag = 1;
    //left number is positive, right one is neg
    if (!(this->getSign()) && other.getSign()) {
        other.setSign(false);
        return (*this + other);
        //left number is neg, right one is pos
    } else if (this->getSign() && !(other.getSign())) {
        other.setSign(true);
        return (*this + other);
        //both are negative numbers: fixing -x-(-y) into y-x
    } else if (this->getSign() && other.getSign()) {
        InfInt infInt = *this;
        //set both numbers as positive nums
        infInt.setSign(false);
        other.setSign(false);
        //return a parallel expression
        return (other - infInt);
    }
    //here I calculate X-Y expressions, while X,Y >=0
    if (*this == other) {
        return (infIntResult = "0");
    }
    //making sure (bigger number - smaller number):
    if (*this > other) {
        biggerBinary = this->getBinaryStr();
        smallerBinary = other.getBinaryStr();
    } else {
        //in this case I switch the number so instead of x-y && y>x
        //lets change it to (y-x)* (-1)
        biggerBinary = other.getBinaryStr();
        smallerBinary = this->getBinaryStr();
        flag = -1;
    }
    for (int i = (biggerBinary.length() - 1), j = (smallerBinary.length() - 1); j >= 0; i--, j--) {
        digitsSubtraction = (biggerBinary[i] - '0') - (smallerBinary[j] - '0');
        if (digitsSubtraction == 0) {
            resultStr += "0";
        } else if (digitsSubtraction == 1) {
            resultStr += "1";
        }
            //in cases of '0'-'1'
        else {
            //adding 1 to the result-"loaning" is guaranteed because X>y, X-Y
            resultStr += "1";
            //"loaning" 1 from the next '1' digit to all the '0' digits.
            int k = i - 1;
            while (biggerBinary[k] != '1') {
                biggerBinary[k] = '1';
                k--;
            }
            biggerBinary[k] = '0';
        }
    }
    //adding the rest of the digits from the bigger string if exist
    int difference = biggerBinary.length() - smallerBinary.length();
    for (int i = (difference - 1); i >= 0; i--) {
        resultStr += biggerBinary[i];
    }
    reverse(resultStr.begin(), resultStr.end());
    infIntResult = binaryToDecimal(resultStr);
    //in case I switched the numbers from (x-y)&& y>x to (y-x)*(-1) && y>x
    if (flag == -1) {
        infIntResult.setSign(true);
    }
    return infIntResult;
}

/**
 * implements the operator "+=" on two InfInts. Adding other InfInt
 * to this InfInt.
 * @param other the second InfInt
 * @return *this
 */
InfInt &InfInt::operator+=(InfInt other) {
    *this = (*this + other);
    return *this;
}

/**
 * implements the operator "&=" on two InfInts.
 * @param other the second InfInt
 * @return *this
 */
InfInt &InfInt::operator&=(InfInt other) {
    *this = (*this & other);
    return *this;
}

/**
 * implements the operator Post increment (x++) on this InfInt.
 * @return InfInt temp
 */
InfInt InfInt::operator++(int) {
    InfInt temp = *this;
    InfInt other = "1";
    *this += other;
    return temp;
}

/**
 * implements the operator Pre increment (++x) on this InfInt.
 * @return InfInt *this
 */
InfInt &InfInt::operator++() {
    InfInt other = "1";
    *this += other;
    return *this;
}

/**
 * implements the operator Post subtraction (x--) on this InfInt.
 * @return InfInt temp
 */InfInt InfInt::operator--(int) {
    InfInt temp = *this;
    InfInt other = "1";
    *this = (*this - other);
    return temp;
}

/**
 * implements the operator Pre subtraction (--x) on this InfInt.
 * @return InfInt *this
 */
InfInt &InfInt::operator--() {
    InfInt other = "1";
    *this = (*this - other);
    return *this;
}

/**
 * implements the operator <<k. the method multiplies this InfInt
 * by 2^k.
 * @param k int
 * @return InfInt infIntResult
 */
InfInt InfInt::operator<<(int k) const {
    if (k == 0) {
        return *this;
    }
    InfInt infIntResult;
    int thisInfLength = this->getBinaryStr().length();
    int newInfLength = thisInfLength + k;
    string resultStr;
    for (int i = 0; i < newInfLength; i++) {
        if (i < thisInfLength) {
            resultStr += (this->getBinaryStr()[i]);
        } else {
            resultStr += "0";
        }
    }
    infIntResult = binaryToDecimal(resultStr);
    infIntResult.setSign(this->getSign());
    return infIntResult;
}

/**
 * implements the operator <<k. the method devides this InfInt
 * by 2^k.
 * @param k int
 * @return InfInt infIntResult
 */
InfInt InfInt::operator>>(int k) const {
    int thisInfLength = this->getBinaryStr().length();
    InfInt infIntResult;
    if (k == 0) {
        return *this;
    } else if (k >= thisInfLength) {
        return (infIntResult = "0");
    }
    int newInfLength = thisInfLength - k;
    string resultStr;
    for (int i = 0; i < newInfLength; i++) {
        resultStr += this->getBinaryStr()[i];
    }
    infIntResult = binaryToDecimal(resultStr);
    infIntResult.setSign(this->getSign());
    return infIntResult;
}

/**
 * implements the operator ">>=k"
 * @param k int
 * @return *this
 */
InfInt &InfInt::operator>>=(int k) {
    *this = (*this >> k);
    return *this;
}

/**
 * the function implements "/" operation on two InfInts by dividing
 * this InfInt by other InfInt. The operation is made
 * on 2 binary expression strings, and returns an InfInt that contains the
 * binary expression result by calling the method divisionAndMod with a
 * true bool variable.
 * @param other the second InfInt
 * @return InfInt divisionAndMod output.
 */
InfInt InfInt::operator/(InfInt other) const {
    bool isDivision = true;
    return divisionAndMod(*this, other, isDivision);
}

/**
 * the function implements "%" operation on two InfInts by calculating
 * the modulo this InfInt by other InfInt. The operation is made
 * on 2 binary expression strings, and returns an InfInt that contains the
 * binary expression result by calling the method divisionAndMod with a
 * false bool variable.
 * @param other the second InfInt
 * @return InfInt divisionAndMod output.
 */
InfInt InfInt::operator%(InfInt other) const {
    bool isDivision = false;
    return divisionAndMod(*this, other, isDivision);

}

/**
 * the function gets two InfInts and bool variable. it calculates the
 * division of the first InfInt by the second InfInt and the modulo at the
 * same time. it returns the division result or the modulo according to
 * the bool variable -
 * if bool isDivision == true -> the method returns the division result.
 * if bool isDivision == false -> the method returns the modulo result.
 * the result in an InfInt.
 * @param dividend the first InfInt
 * @param divisor the second InfInt
 * @param isDivision indicates the result which is returned.
 * @return InfInt. if bool isDivision == true -> return InfInt q.
 * if bool isDivision == false -> return InfInt r.
 */
InfInt InfInt::divisionAndMod(InfInt dividend, InfInt divisor, bool isDivision) const {
    InfInt unsignedDividend = dividend;
    unsignedDividend.setSign(false);
    InfInt unsignedDivisor = divisor;
    unsignedDivisor.setSign(false);
    int dividendLen = unsignedDividend.getBinaryStr().length();

    if (unsignedDivisor.getBinaryStr() == "0") {
        throw invalid_argument("You're trying to divide by zero - an unsupported action");
    }
    InfInt q, r;
    for (int i = 0; i < dividendLen; ++i) {
        r = r << 1;
        r += (unsignedDividend.getBinaryStr()[i] - '0');
        q = q << 1;
        if (r >= unsignedDivisor) {
            r = r - unsignedDivisor;
            q += 1;
        }
    }
    //if the signs of the dividend and divisor are different q is negative
    if (dividend.getSign() ^ divisor.getSign()) {
        q.setSign(true);
    } else {
        q.setSign(false);
    }
    if (!(dividend.getSign())) {
        r.setSign(false);
    } else { r.setSign(true); }
    if (isDivision) {
        if (q.getBinaryStr() == "0") {
            q.setSign(false);
        }
        return q;
    }

    if (r.getBinaryStr() == "0") {
        r.setSign(false);
    }
    return r;
}

/**
 * the function implements "*" operation on two InfInts by multiplying
 * other InfInt and this InfInt. the result is stored in a new InfInt
 * (infIntResult),the method output. The operation is made
 * on 2 binary expression strings and returns an InfInt that contains the
 * binary expression result.
 * @param other the second InfInt
 * @return InfInt infIntResult
 */
InfInt InfInt::operator*(InfInt other) const {
    //default constructor -> resultInf = 0.
    InfInt resultInf;
    if (*this == resultInf || other == resultInf) {
        return resultInf;
    }
    InfInt leftNum = *this;
    leftNum.setSign(false);
    InfInt rightNum = other;
    rightNum.setSign(false);
    int rightNumLen = rightNum.getBinaryStr().length();
    for (int i = rightNumLen - 1; i >= 0; i--) {
        if (leftNum.getBinaryStr()[i] - '0' == 1) {
            resultInf += leftNum;
        }
        rightNum >>= 1;
        leftNum = leftNum << 1;
    }
    resultInf.setSign((this->getSign() ^ other.getSign()));
    return resultInf;
}

/**
 * implements ">>" input operator.
 * @param is istream &
 * @param thisInfInt InfInt &
 * @return istream &is
 */
istream &operator>>(istream &is, InfInt &thisInfInt) {
    string thisStr;
    is >> thisStr;
    thisInfInt = InfInt(thisStr);
    return is;
}

/**
 * implements "<<" output operator.
 * @param os ostream &os
 * @param thisInfInt const InfInt &
 * @return os
 */
ostream &operator<<(ostream &os, const InfInt &thisInfInt) {
    //the number is positive
    if (!(thisInfInt.getSign())) {
        os << binaryToDecimal(thisInfInt.getBinaryStr());
    } else {
        os << ("-" + binaryToDecimal(thisInfInt.getBinaryStr()));
    }
    return os;
}

/**
 * the function gets a binary expression string and returns the
 * first 31 bits from the LSB.
 * @param strToCut string
 * @return string resultStr;
 */
string cutToIntSize(string strToCut) {
    string resultStr;
    int strCutLen = strToCut.length();
    //the first bit of the 31 bits which needs to be copied.
    int firstBit = strCutLen - 31;
    for (int i = firstBit; i < strCutLen; i++) {
        resultStr += strToCut[i];
    }
    int x = resultStr.length();
    return resultStr;
}

/**
 * this method enables explicit casting from InfInt to int.
 * in case that this InfInt stores a a number which is beyond the
 * int memory (int variable cannot store this number because is too big)
 * I return the first 31 bits from the LSB (by calling cutToIntSize method).
 * the function returns the decimal value of InfInt !
 * @return int resultInteger;
 */
InfInt::operator int() const {
    int bitsAmount = this->getBinaryStr().length();
    string thisStr = binaryToDecimal(this->getBinaryStr());
    string tempStr;
    int resultInteger;
    if (bitsAmount > 31) {
        tempStr = cutToIntSize(this->getBinaryStr());
    } else { tempStr = thisStr; }
    resultInteger = stoi(binaryToDecimal(tempStr));
    if (this->getSign()) {
        resultInteger *= (-1);
    }
    return resultInteger;
}