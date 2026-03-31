// Date.cpp
#include "Date.h"
#include <array>
#include <cctype>
#include <limits>
#include <sstream>

const char* Date::monthNames[13] = {
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

bool Date::isLeapYear(int y) noexcept {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return (y % 4 == 0);
}

int Date::daysInMonth(int m, int y) noexcept {
    static const int mdays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && isLeapYear(y)) return 29;
    if (m >= 1 && m <= 12) return mdays[m];
    return 31;
}

int Date::dayOfYear(int m, int d, int y) noexcept {
    int sum = 0;
    for (int i = 1; i < m; ++i) sum += daysInMonth(i, y);
    sum += d;
    return sum;
}

// Convert a Gregorian date to a serial day count (days since 0001-03-01 algorithm base)
// Uses a well-known algorithm to avoid loops and handle Gregorian leap rules.
long Date::toSerial(int m, int d, int y) noexcept {
    // Shift months so March is month 1 (to simplify leap-year handling)
    int a = (14 - m) / 12;
    int y2 = y + 4800 - a;
    int m2 = m + 12 * a - 3;
    long jd = d + (153 * m2 + 2) / 5 + 365L * y2 + y2 / 4 - y2 / 100 + y2 / 400 - 32045;
    // jd is Julian Day Number; convert to a serial by subtracting a constant
    return jd;
}

// Constructors
Date::Date() : month(1), day(1), year(2000) {}

Date::Date(int m, int d, int y) : month(1), day(1), year(2000) {
    setDate(m, d, y);
}

// Accessors
int Date::getMonth() const noexcept { return month; }
int Date::getDay() const noexcept { return day; }
int Date::getYear() const noexcept { return year; }

bool Date::setDate(int m, int d, int y) {
    if (y < 1 || m < 1 || m > 12) return false;
    int dim = daysInMonth(m, y);
    if (d < 1 || d > dim) return false;
    month = m; day = d; year = y;
    return true;
}

void Date::printLong(std::ostream &os) const {
    if (month >= 1 && month <= 12)
        os << monthNames[month] << " " << day << ", " << year;
    else
        os << month << "/" << day << "/" << year;
}

// Prefix increment: ++d
Date& Date::operator++() {
    int dim = daysInMonth(month, year);
    if (day < dim) {
        ++day;
    } else {
        day = 1;
        if (month < 12) ++month;
        else { month = 1; ++year; }
    }
    return *this;
}

// Prefix decrement: --d
Date& Date::operator--() {
    if (day > 1) {
        --day;
    } else {
        if (month > 1) {
            --month;
        } else {
            month = 12;
            --year;
            if (year < 1) year = 1; // clamp to year 1 minimum
        }
        day = daysInMonth(month, year);
    }
    return *this;
}

// Postfix increment: d++
Date Date::operator++(int) {
    Date old = *this;
    ++(*this);
    return old;
}

// Postfix decrement: d--
Date Date::operator--(int) {
    Date old = *this;
    --(*this);
    return old;
}

// Subtraction: number of days between dates (this - other)
long Date::operator-(const Date &other) const {
    long s1 = toSerial(month, day, year);
    long s2 = toSerial(other.month, other.day, other.year);
    return s1 - s2;
}

// Stream insertion
std::ostream& operator<<(std::ostream &os, const Date &dt) {
    dt.printLong(os);
    return os;
}

// Stream extraction: accepts numeric input in forms like "MM/DD/YYYY" or "M D Y" or "M,D,Y"
// Prompts are handled by caller; this function reads three integers separated by non-digit characters.
std::istream& operator>>(std::istream &is, Date &dt) {
    // Read a line from stream to allow flexible separators
    std::string line;
    if (!std::getline(is, line)) return is;

    // If the line is empty (e.g., previous extraction left newline), try again
    if (line.empty()) {
        if (!std::getline(is, line)) return is;
    }

    std::istringstream ss(line);
    int m = 0, d = 0, y = 0;
    char sep1 = 0, sep2 = 0;

    // Try to parse common formats: MM/DD/YYYY or M D Y or M, D, Y
    // First attempt: read ints separated by non-digit characters
    // Extract digits and separators manually
    auto readInt = [&](std::istringstream &s, int &out) -> bool {
        // skip non-digit
        while (s && !std::isdigit(s.peek()) && s.peek() != '-' ) s.get();
        if (!(s >> out)) return false;
        return true;
    };

    bool ok = readInt(ss, m) && readInt(ss, d) && readInt(ss, y);
    if (!ok) {
        // fallback: try to parse three ints with >> (space separated)
        ss.clear();
        ss.str(line);
        if (!(ss >> m >> d >> y)) {
            // leave stream in fail state
            is.setstate(std::ios::failbit);
            return is;
        }
    }

    if (!dt.setDate(m, d, y)) {
        // invalid date: set failbit so caller knows
        is.setstate(std::ios::failbit);
    }
    return is;
}
