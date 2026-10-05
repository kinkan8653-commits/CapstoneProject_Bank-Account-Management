#include "validator.h"
#include <cctype>

bool Validator::isValidName(const std::string& name) {
    if (name.empty() || name.size() > 40) {
        return false;
    }

    bool hasLetter = false;
    for (std::size_t i = 0; i < name.size(); i++) {
        unsigned char c = static_cast<unsigned char>(name[i]);
        if (std::isalpha(c)) {
            hasLetter = true;
        } else if (c != ' ' && c != '.') {
            return false;
        }
    }
    return hasLetter;
}

bool Validator::isValidAmount(double amount) {
    return amount > 0 && amount <= 10000000.0;
}

bool Validator::isValidAccountNumber(int accountNumber) {
    return accountNumber >= 1001;
}
