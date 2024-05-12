#ifndef ROMAN_H
#define ROMAN_H
#include <iostream>
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
    RomanFraction(string roman_num, string roman_denom) {
        numerator = roman_num;
        denominator = roman_denom;
        if (numerator[0] == denominator[0] && denominator[0] == '-'){
            numerator = numerator.substr(1);
            denominator = denominator.substr(1);
        }
        else if (numerator[0] != denominator[0] && denominator[0] == '-'){
            denominator = denominator.substr(1);
            numerator = '-' + numerator;
        }
    };
    RomanFraction(int n, int d) : numerator(arabicToRoman(n)), denominator(arabicToRoman(d)){};

    RomanFraction operator *(RomanFraction&);
    RomanFraction operator /(RomanFraction&);
    RomanFraction operator +(RomanFraction&);
    RomanFraction operator +=(RomanFraction&);
    RomanFraction operator -(RomanFraction&);

    friend ostream& operator<<(ostream&, RomanFraction&);

    string fraction();
};

#endif // ROMAN_H
