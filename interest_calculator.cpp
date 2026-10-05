#include "interest_calculator.h"

InterestCalculator::InterestCalculator(double ratePercent) {
    annualRate = ratePercent;
}

double InterestCalculator::getRate() const {
    return annualRate;
}

// Simple interest: (P x R x T) / 100
double InterestCalculator::calculateInterest(double balance, double years) const {
    return (balance * annualRate * years) / 100.0;
}
