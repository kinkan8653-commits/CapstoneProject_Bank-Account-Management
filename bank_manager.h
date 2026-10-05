#ifndef BANK_MANAGER_H
#define BANK_MANAGER_H

#include <string>
#include <vector>
#include "account.h"

enum OperationStatus {
    OP_SUCCESS,
    OP_INVALID_AMOUNT,
    OP_INVALID_NAME,
    OP_ACCOUNT_NOT_FOUND,
    OP_INSUFFICIENT_FUNDS,
    OP_SAME_ACCOUNT
};

class BankManager {
private:
    std::vector<Account> accounts;
    int nextAccountNumber;

public:
    BankManager();

    int createAccount(const std::string& name, double initialDeposit);
    Account* findAccount(int accountNumber);

    OperationStatus deposit(int accountNumber, double amount);
    OperationStatus withdraw(int accountNumber, double amount);
    OperationStatus transfer(int fromAccount, int toAccount, double amount);

    const std::vector<Account>& getAccounts() const;
    void loadAccounts(const std::vector<Account>& loaded);
};

const char* statusMessage(OperationStatus status);

#endif
