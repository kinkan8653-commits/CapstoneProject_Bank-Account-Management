#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <string>
#include <vector>

class AnalyticsEngine {
private:
    std::vector<double> balances;

public:
    void addBalance(double balance);
    int countAccounts() const;
    double calculateTotalBalance() const;
    double calculateAverageBalance() const;
    double findHighestBalance() const;
    std::string classifyBalance(double balance) const;
};

#endif
