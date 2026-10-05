#include <iostream>
#include "validator.h"

int main() {
    bool ok = Validator::isValidName("Kinkan Maiti");
    ok = ok && Validator::isValidName("A. Kumar");
    ok = ok && !Validator::isValidName("");
    ok = ok && !Validator::isValidName("User123");
    ok = ok && !Validator::isValidName("a,b");

    ok = ok && Validator::isValidAmount(100.0);
    ok = ok && !Validator::isValidAmount(0.0);
    ok = ok && !Validator::isValidAmount(-50.0);

    ok = ok && Validator::isValidAccountNumber(1001);
    ok = ok && !Validator::isValidAccountNumber(5);

    if (ok) {
        std::cout << "Validator test passed" << std::endl;
        return 0;
    }
    std::cout << "Validator test failed" << std::endl;
    return 1;
}
