#include "analytics.h"

void AnalyticsEngine::addBalance(double balance) {
    balances.push_back(balance);
}

int AnalyticsEngine::countAccounts() const {
    return static_cast<int>(balances.size());
}

double AnalyticsEngine::calculateTotalBalance() const {
    double total = 0.0;
    for (double b : balances) {
        total += b;
    }
    return total;
}

double AnalyticsEngine::calculateAverageBalance() const {
    if (balances.empty()) {
        return 0.0;
    }
    return calculateTotalBalance() / balances.size();
}

double AnalyticsEngine::findHighestBalance() const {
    if (balances.empty()) {
        return 0.0;
    }
    double highest = balances[0];
    for (double b : balances) {
        if (b > highest) {
            highest = b;
        }
    }
    return highest;
}

std::string AnalyticsEngine::classifyBalance(double balance) const {
    if (balance < 5000) {
        return "BASIC";
    } else if (balance <= 100000) {
        return "STANDARD";
    }
    return "PREMIUM";
}
