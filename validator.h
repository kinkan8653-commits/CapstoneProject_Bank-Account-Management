#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

class Validator {
public:
    static bool isValidName(const std::string& name);
    static bool isValidAmount(double amount);
    static bool isValidAccountNumber(int accountNumber);
};

#endif
