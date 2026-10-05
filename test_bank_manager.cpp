#include <iostream>
#include "bank_manager.h"

int main() {
    BankManager bank;

    int a = bank.createAccount("Alice", 2000.0);
    int b = bank.createAccount("Bob", 1000.0);

    bool ok = (a == 1001 && b == 1002);
    ok = ok && bank.createAccount("Carol", 100.0) == -1;      // below minimum
    ok = ok && bank.createAccount("R2D2", 1000.0) == -1;      // invalid name

    ok = ok && bank.deposit(a, 500.0) == OP_SUCCESS;
    ok = ok && bank.deposit(9999, 500.0) == OP_ACCOUNT_NOT_FOUND;
    ok = ok && bank.deposit(a, -5.0) == OP_INVALID_AMOUNT;

    ok = ok && bank.withdraw(a, 500.0) == OP_SUCCESS;
    ok = ok && bank.withdraw(b, 900.0) == OP_INSUFFICIENT_FUNDS;

    ok = ok && bank.transfer(a, b, 1000.0) == OP_SUCCESS;
    ok = ok && bank.findAccount(a)->getBalance() == 1000.0;
    ok = ok && bank.findAccount(b)->getBalance() == 2000.0;
    ok = ok && bank.transfer(a, a, 10.0) == OP_SAME_ACCOUNT;
    ok = ok && bank.transfer(a, 9999, 10.0) == OP_ACCOUNT_NOT_FOUND;

    if (ok) {
        std::cout << "BankManager test passed" << std::endl;
        return 0;
    }
    std::cout << "BankManager test failed" << std::endl;
    return 1;
}
