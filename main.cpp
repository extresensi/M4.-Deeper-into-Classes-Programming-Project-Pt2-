// main.cpp
#include "Date.h"
#include <iostream>

int main() {
    std::cout << "Date Class Operator Overloading Tests\n\n";

    // Basic creation and output
    std::cout << "1) Default and parameterized construction\n";
    Date d0; // default
    Date d1(4, 18, 2014);
    std::cout << "Default date: " << d0 << '\n';
    std::cout << "Param date:   " << d1 << '\n';
    std::cout << '\n';

    // Validation regression tests
    std::cout << "2) Validation regression tests (expected: rejected)\n";
    Date t;
    bool ok;
    ok = t.setDate(13, 45, 2018);
    std::cout << "13/45/2018 valid? " << (ok ? "yes" : "no") << '\n';
    ok = t.setDate(4, 31, 2000);
    std::cout << "4/31/2000 valid? " << (ok ? "yes" : "no") << '\n';
    ok = t.setDate(2, 29, 2009);
    std::cout << "2/29/2009 valid? " << (ok ? "yes" : "no") << '\n';
    std::cout << '\n';

    // Subtraction operator tests
    std::cout << "3) Subtraction operator tests\n";
    Date a(4,18,2014), b(4,10,2014);
    std::cout << a << " - " << b << " = " << (a - b) << " days (expected 8)\n";
    Date c(2,2,2006), d(11,10,2003);
    std::cout << c << " - " << d << " = " << (c - d) << " days (expected 815)\n";
    std::cout << '\n';

    // Increment / Decrement tests (Leap Year)
    std::cout << "4) Increment/Decrement tests (leap year)\n";
    Date leap(2,29,2008);
    std::cout << "Start: " << leap << '\n';
    Date pre = ++leap;
    std::cout << "After pre-increment: " << pre << " (expected March 1, 2008)\n";
    Date predec = --leap;
    std::cout << "After pre-decrement: " << predec << " (expected Feb 29, 2008)\n";
    Date post = leap++;
    std::cout << "After post-increment (returned): " << post << ", now: " << leap << '\n';
    Date postdec = leap--;
    std::cout << "After post-decrement (returned): " << postdec << ", now: " << leap << '\n';
    std::cout << '\n';

    // Year boundary tests
    std::cout << "5) Year boundary tests\n";
    Date yb(12,31,2024);
    std::cout << "Start: " << yb << '\n';
    Date ypost = yb++;
    std::cout << "Post-increment returned: " << ypost << ", now: " << yb << " (expected Jan 1, 2025)\n";
    Date ypostdec = yb--;
    std::cout << "Post-decrement returned: " << ypostdec << ", now: " << yb << " (expected Dec 31, 2024)\n";
    ++yb;
    std::cout << "After pre-increment: " << yb << '\n';
    --yb;
    std::cout << "After pre-decrement: " << yb << '\n';
    std::cout << '\n';

    // Stream operator tests
    std::cout << "6) Stream operator tests\n";
    std::cout << "Enter a date (format examples: 4/18/2018  or 4 18 2018  or 4,18,2018): ";
    Date user;
    if (std::cin >> user) {
        std::cout << "You entered: " << user << '\n';
    } else {
        std::cout << "Invalid input or format.\n";
        // clear fail and ignore rest for demonstration
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
    }

    std::cout << "\nAll tests completed.\n";
    return 0;
}
