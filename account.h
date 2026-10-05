#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    int accountNumber;
    std::string holderName;
    double balance;

public:
    static const double MIN_BALANCE;

    Account(int number, const std::string& name, double initialBalance);

    int getAccountNumber() const;
    std::string getHolderName() const;
    double getBalance() const;

    bool deposit(double amount);
    bool withdraw(double amount);
};

#endif
