#include "data_logger.h"
#include <ctime>
#include <fstream>

DataLogger::DataLogger(const std::string& file) {
    filename = file;
}

bool DataLogger::logTransaction(const std::string& type, int accountNumber,
                                double amount, double balanceAfter) {
    std::ofstream file(filename.c_str(), std::ios::app);

    if (!file.is_open()) {
        return false;
    }

    std::time_t now = std::time(nullptr);
    char stamp[32];
    std::strftime(stamp, sizeof(stamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    file << stamp << "," << type << "," << accountNumber << ","
         << amount << "," << balanceAfter << std::endl;

    file.close();
    return true;
}
