#ifndef ROMAN_H
#define ROMAN_H
#include <string>
#include <map>

using namespace std;

class RomanFraction{
private:
    map<char, int> romanToArabicMap = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };

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

    string numerator;
    string denominator;

    int romanToArabic(string &);
    string arabicToRoman(int);
public:
    RomanFraction(string, string);
    RomanFraction(int, int);

    RomanFraction operator *(RomanFraction&);
    RomanFraction operator /(RomanFraction&);
    RomanFraction operator +(RomanFraction&);
    RomanFraction operator -(RomanFraction&);

    string fraction();
};

#endif // ROMAN_H
