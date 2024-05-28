#ifndef ROMAN_H
#define ROMAN_H
#include <string>
#include <map>

using namespace std;

class RomanFraction{
private:
    map<int, string> arabicToRomanMap = {
        {1, "I"},
        {4, "IV"},
        {5, "V"},
        {9, "IX"},
        {10, "X"},
        {40, "XL"},
        {50, "L"},
        {90, "XC"},
        {100, "C"},
        {400, "CD"},
        {500, "D"},
        {1000, "M"}
    };

    int arabicValues[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string romanValues[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    string numerator;
    string denominator;

    int romanToArabic(string &);
    string arabicToRoman(int);
public:
    RomanFraction(string);
    RomanFraction(int, int);

    RomanFraction operator *(RomanFraction&);
    RomanFraction operator /(RomanFraction&);
    RomanFraction operator +(RomanFraction&);
    RomanFraction operator -(RomanFraction&);
    bool operator >(RomanFraction&);
    bool operator <(RomanFraction&);

    string fraction();
};

#endif // ROMAN_H
