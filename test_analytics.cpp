#include <iostream>
#include "analytics.h"

int main() {
    AnalyticsEngine analytics;

    analytics.addBalance(3000.0);
    analytics.addBalance(20000.0);
    analytics.addBalance(250000.0);

    bool ok = analytics.countAccounts() == 3;
    ok = ok && analytics.calculateTotalBalance() == 273000.0;
    ok = ok && analytics.calculateAverageBalance() == 91000.0;
    ok = ok && analytics.findHighestBalance() == 250000.0;
    ok = ok && analytics.classifyBalance(3000.0) == "BASIC";
    ok = ok && analytics.classifyBalance(20000.0) == "STANDARD";
    ok = ok && analytics.classifyBalance(250000.0) == "PREMIUM";

    AnalyticsEngine empty;
    ok = ok && empty.calculateAverageBalance() == 0.0;

    if (ok) {
        std::cout << "AnalyticsEngine test passed" << std::endl;
        return 0;
    }
    std::cout << "AnalyticsEngine test failed" << std::endl;
    return 1;
}
