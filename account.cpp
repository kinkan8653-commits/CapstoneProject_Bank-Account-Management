#include "account.h"

const double Account::MIN_BALANCE = 500.0;

Account::Account(int number, const std::string& name, double initialBalance)
    : accountNumber(number), holderName(name), balance(initialBalance) {}

int Account::getAccountNumber() const { return accountNumber; }

std::string Account::getHolderName() const { return holderName; }

double Account::getBalance() const { return balance; }

bool Account::deposit(double amount) {
    if (amount <= 0) {
        return false;
    }
    balance += amount;
    return true;
}

bool Account::withdraw(double amount) {
    if (amount <= 0) {
        return false;
    }
    // A minimum balance must always remain in the account
    if (balance - amount < MIN_BALANCE) {
        return false;
    }
    balance -= amount;
    return true;
}
