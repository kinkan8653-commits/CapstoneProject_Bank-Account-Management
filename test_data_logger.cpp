#include <iostream>
#include "data_logger.h"

int main() {
    DataLogger logger("data/test_transactions.csv");

    if (logger.logTransaction("DEPOSIT", 1001, 500.0, 1500.0)) {
        std::cout << "DataLogger test passed" << std::endl;
        return 0;
    }

    std::cout << "DataLogger test failed" << std::endl;
    return 1;
}
