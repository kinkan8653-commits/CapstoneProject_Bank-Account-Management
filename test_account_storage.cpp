#include <iostream>
#include <vector>
#include "account_storage.h"

int main() {
    AccountStorage storage("data/test_accounts.csv");

    std::vector<Account> accounts;
    accounts.push_back(Account(1001, "Alice", 2500.50));
    accounts.push_back(Account(1002, "Bob", 900.00));

    bool ok = storage.save(accounts);

    std::vector<Account> loaded = storage.load();
    ok = ok && loaded.size() == 2;
    ok = ok && loaded[0].getAccountNumber() == 1001;
    ok = ok && loaded[0].getHolderName() == "Alice";
    ok = ok && loaded[1].getBalance() == 900.00;

    if (ok) {
        std::cout << "AccountStorage test passed" << std::endl;
        return 0;
    }
    std::cout << "AccountStorage test failed" << std::endl;
    return 1;
}
