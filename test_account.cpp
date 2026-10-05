#include <iostream>
#include "account.h"

int main() {
    Account acc(1001, "Test User", 1000.0);

    bool ok = true;
    ok = ok && acc.deposit(500.0) && acc.getBalance() == 1500.0;
    ok = ok && !acc.deposit(-10.0);
    ok = ok && acc.withdraw(500.0) && acc.getBalance() == 1000.0;
    ok = ok && !acc.withdraw(600.0);          // would breach minimum balance
    ok = ok && acc.withdraw(500.0) && acc.getBalance() == 500.0;
    ok = ok && !acc.withdraw(1.0);            // minimum balance reached

    if (ok) {
        std::cout << "Account test passed" << std::endl;
        return 0;
    }
    std::cout << "Account test failed" << std::endl;
    return 1;
}
