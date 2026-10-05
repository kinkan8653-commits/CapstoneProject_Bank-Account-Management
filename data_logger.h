#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include <string>

class DataLogger {
private:
    std::string filename;

public:
    DataLogger(const std::string& file);

    bool logTransaction(const std::string& type, int accountNumber,
                        double amount, double balanceAfter);
};

#endif
