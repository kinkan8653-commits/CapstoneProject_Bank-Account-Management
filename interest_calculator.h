#ifndef INTEREST_CALCULATOR_H
#define INTEREST_CALCULATOR_H

class InterestCalculator {
private:
    double annualRate;   // percent per year

public:
    InterestCalculator(double ratePercent);

    double getRate() const;
    double calculateInterest(double balance, double years) const;
};

#endif
