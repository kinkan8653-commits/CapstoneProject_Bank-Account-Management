#include "bank_manager.h"
#include "validator.h"

BankManager::BankManager() : nextAccountNumber(1001) {}

int BankManager::createAccount(const std::string& name, double initialDeposit) {
    if (!Validator::isValidName(name)) {
        return -1;
    }
    if (!Validator::isValidAmount(initialDeposit) ||
        initialDeposit < Account::MIN_BALANCE) {
        return -1;
    }

    int number = nextAccountNumber++;
    accounts.push_back(Account(number, name, initialDeposit));
    return number;
}

Account* BankManager::findAccount(int accountNumber) {
    for (std::size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].getAccountNumber() == accountNumber) {
            return &accounts[i];
        }
    }
    return nullptr;
}

OperationStatus BankManager::deposit(int accountNumber, double amount) {
    if (!Validator::isValidAmount(amount)) {
        return OP_INVALID_AMOUNT;
    }
    Account* acc = findAccount(accountNumber);
    if (acc == nullptr) {
        return OP_ACCOUNT_NOT_FOUND;
    }
    acc->deposit(amount);
    return OP_SUCCESS;
}

OperationStatus BankManager::withdraw(int accountNumber, double amount) {
    if (!Validator::isValidAmount(amount)) {
        return OP_INVALID_AMOUNT;
    }
    Account* acc = findAccount(accountNumber);
    if (acc == nullptr) {
        return OP_ACCOUNT_NOT_FOUND;
    }
    if (!acc->withdraw(amount)) {
        return OP_INSUFFICIENT_FUNDS;
    }
    return OP_SUCCESS;
}

OperationStatus BankManager::transfer(int fromAccount, int toAccount, double amount) {
    if (fromAccount == toAccount) {
        return OP_SAME_ACCOUNT;
    }
    if (!Validator::isValidAmount(amount)) {
        return OP_INVALID_AMOUNT;
    }

    Account* from = findAccount(fromAccount);
    Account* to = findAccount(toAccount);
    if (from == nullptr || to == nullptr) {
        return OP_ACCOUNT_NOT_FOUND;
    }
    if (!from->withdraw(amount)) {
        return OP_INSUFFICIENT_FUNDS;
    }
    to->deposit(amount);
    return OP_SUCCESS;
}

const std::vector<Account>& BankManager::getAccounts() const {
    return accounts;
}

void BankManager::loadAccounts(const std::vector<Account>& loaded) {
    accounts = loaded;
    nextAccountNumber = 1001;
    for (std::size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].getAccountNumber() >= nextAccountNumber) {
            nextAccountNumber = accounts[i].getAccountNumber() + 1;
        }
    }
}

const char* statusMessage(OperationStatus status) {
    switch (status) {
        case OP_SUCCESS:            return "Transaction successful.";
        case OP_INVALID_AMOUNT:     return "Invalid amount.";
        case OP_INVALID_NAME:       return "Invalid account holder name.";
        case OP_ACCOUNT_NOT_FOUND:  return "Account not found.";
        case OP_INSUFFICIENT_FUNDS: return "Insufficient funds (minimum balance must be maintained).";
        case OP_SAME_ACCOUNT:       return "Cannot transfer to the same account.";
    }
    return "Unknown error.";
}
