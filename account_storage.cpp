#include "account_storage.h"
#include <fstream>
#include <sstream>

AccountStorage::AccountStorage(const std::string& file) {
    filename = file;
}

bool AccountStorage::save(const std::vector<Account>& accounts) const {
    std::ofstream file(filename.c_str());

    if (!file.is_open()) {
        return false;
    }

    file.precision(2);
    file << std::fixed;
    for (std::size_t i = 0; i < accounts.size(); i++) {
        file << accounts[i].getAccountNumber() << ","
             << accounts[i].getHolderName() << ","
             << accounts[i].getBalance() << "\n";
    }
    return true;
}

std::vector<Account> AccountStorage::load() const {
    std::vector<Account> accounts;
    std::ifstream file(filename.c_str());

    if (!file.is_open()) {
        return accounts;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string number, name, balance;

        if (std::getline(ss, number, ',') && std::getline(ss, name, ',') &&
            std::getline(ss, balance)) {
            try {
                accounts.push_back(Account(std::stoi(number), name, std::stod(balance)));
            } catch (...) {
                // skip corrupted line
            }
        }
    }
    return accounts;
}
