// Date.h
#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
    int month; // 1-12
    int day;   // 1-31
    int year;  // full year, e.g., 2024

    static const char* monthNames[13];
    static int daysInMonth(int m, int y) noexcept;
    static bool isLeapYear(int y) noexcept;
    static int dayOfYear(int m, int d, int y) noexcept;
    static long toSerial(int m, int d, int y) noexcept; // days since a fixed epoch

public:
    // Constructors
    Date();                          // default: 1/1/2000
    Date(int m, int d, int y);      // parameterized (validated)

    // Accessors
    int getMonth() const noexcept;
    int getDay() const noexcept;
    int getYear() const noexcept;

    // Mutator with validation
    bool setDate(int m, int d, int y);

    // Utilities
    void printLong(std::ostream &os) const;

    // Operator overloads
    // Prefix
    Date& operator++(); // ++d
    Date& operator--(); // --d
    // Postfix
    Date operator++(int); // d++
    Date operator--(int); // d--

    // Subtraction: days between (this - other)
    long operator-(const Date &other) const;

    // Stream operators (non-member friends)
    friend std::ostream& operator<<(std::ostream &os, const Date &dt);
    friend std::istream& operator>>(std::istream &is, Date &dt);
};

#endif // DATE_H
