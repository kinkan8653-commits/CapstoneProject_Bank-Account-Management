#ifndef ACCOUNT_STORAGE_H
#define ACCOUNT_STORAGE_H

#include <string>
#include <vector>
#include "account.h"

class AccountStorage {
private:
    std::string filename;

public:
    AccountStorage(const std::string& file);

    bool save(const std::vector<Account>& accounts) const;
    std::vector<Account> load() const;
};

#endif
