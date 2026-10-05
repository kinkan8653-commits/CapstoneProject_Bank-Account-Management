#include <cmath>
#include <iostream>
#include "interest_calculator.h"

int main() {
    InterestCalculator calculator(4.0);

    double interest = calculator.calculateInterest(10000.0, 2.0);   // 10000*4*2/100

    if (std::fabs(interest - 800.0) < 1e-9) {
        std::cout << "InterestCalculator test passed" << std::endl;
        return 0;
    }
    std::cout << "InterestCalculator test failed" << std::endl;
    return 1;
}
