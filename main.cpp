#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "account.h"
#include "bank_manager.h"
#include "interest_calculator.h"
#include "analytics.h"
#include "data_logger.h"
#include "account_storage.h"
#include "validator.h"

static const char* ACCOUNT_FILE = "data/accounts.csv";
static const char* LOG_FILE = "logs/bank.log";
static const double INTEREST_RATE = 4.0;   // assumed % per year

// ---------- input helpers (return false on EOF) ----------
static bool readLine(const std::string& prompt, std::string& out)
{
    std::cout << prompt;
    return static_cast<bool>(std::getline(std::cin, out));
}

static bool parseInt(const std::string& text, int& value)
{
    std::istringstream ss(text);
    char extra;
    return (ss >> value) && !(ss >> extra);
}

static bool parseDouble(const std::string& text, double& value)
{
    std::istringstream ss(text);
    char extra;
    return (ss >> value) && !(ss >> extra);
}

// Reads a number; sets ok=false on invalid text. Returns false only on EOF.
static bool readInt(const std::string& prompt, int& value, bool& ok)
{
    std::string line;
    if (!readLine(prompt, line)) return false;
    ok = parseInt(line, value);
    return true;
}

static bool readDouble(const std::string& prompt, double& value, bool& ok)
{
    std::string line;
    if (!readLine(prompt, line)) return false;
    ok = parseDouble(line, value);
    return true;
}

// ---------- screens ----------
static void printMenu()
{
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "  1. Create Account" << std::endl;
    std::cout << "  2. Deposit" << std::endl;
    std::cout << "  3. Withdraw" << std::endl;
    std::cout << "  4. Transfer" << std::endl;
    std::cout << "  5. Balance Enquiry" << std::endl;
    std::cout << "  6. Interest Estimate" << std::endl;
    std::cout << "  7. All Accounts & Analytics" << std::endl;
    std::cout << "  8. Exit" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

static void saveState(const BankManager& bank)
{
    AccountStorage storage(ACCOUNT_FILE);
    if (!storage.save(bank.getAccounts()))
    {
        std::cout << "Warning: could not save accounts to " << ACCOUNT_FILE << std::endl;
    }
}

static void createAccount(BankManager& bank, DataLogger& logger)
{
    std::string name;
    double deposit;
    bool ok;

    if (!readLine("Enter account holder name: ", name)) return;
    if (!Validator::isValidName(name))
    {
        std::cout << "Invalid account holder name." << std::endl;
        return;
    }

    if (!readDouble("Enter initial deposit (min Rs. 500): ", deposit, ok)) return;
    if (!ok || !Validator::isValidAmount(deposit) || deposit < Account::MIN_BALANCE)
    {
        std::cout << "Invalid initial deposit. Minimum is Rs. 500." << std::endl;
        return;
    }

    int number = bank.createAccount(name, deposit);
    if (number < 0)
    {
        std::cout << "Account could not be created." << std::endl;
        return;
    }

    logger.logTransaction("OPEN", number, deposit, deposit);
    saveState(bank);

    std::cout << "\nAccount created successfully." << std::endl;
    std::cout << "Account Number    : " << number << std::endl;
    std::cout << "Account Holder    : " << name << std::endl;
    std::cout << "Opening Balance   : Rs. " << deposit << std::endl;
}

static void depositMoney(BankManager& bank, DataLogger& logger)
{
    int number;
    double amount;
    bool ok;

    if (!readInt("Enter account number: ", number, ok)) return;
    if (!ok) { std::cout << "Invalid account number." << std::endl; return; }

    if (!readDouble("Enter deposit amount: ", amount, ok)) return;
    if (!ok) { std::cout << "Invalid amount." << std::endl; return; }

    OperationStatus status = bank.deposit(number, amount);
    std::cout << statusMessage(status) << std::endl;

    if (status == OP_SUCCESS)
    {
        double balance = bank.findAccount(number)->getBalance();
        logger.logTransaction("DEPOSIT", number, amount, balance);
        saveState(bank);
        std::cout << "New Balance       : Rs. " << balance << std::endl;
    }
}

static void withdrawMoney(BankManager& bank, DataLogger& logger)
{
    int number;
    double amount;
    bool ok;

    if (!readInt("Enter account number: ", number, ok)) return;
    if (!ok) { std::cout << "Invalid account number." << std::endl; return; }

    if (!readDouble("Enter withdrawal amount: ", amount, ok)) return;
    if (!ok) { std::cout << "Invalid amount." << std::endl; return; }

    OperationStatus status = bank.withdraw(number, amount);
    std::cout << statusMessage(status) << std::endl;

    if (status == OP_SUCCESS)
    {
        double balance = bank.findAccount(number)->getBalance();
        logger.logTransaction("WITHDRAW", number, amount, balance);
        saveState(bank);
        std::cout << "New Balance       : Rs. " << balance << std::endl;
    }
}

static void transferMoney(BankManager& bank, DataLogger& logger)
{
    int from, to;
    double amount;
    bool ok;

    if (!readInt("Enter source account number: ", from, ok)) return;
    if (!ok) { std::cout << "Invalid account number." << std::endl; return; }

    if (!readInt("Enter destination account number: ", to, ok)) return;
    if (!ok) { std::cout << "Invalid account number." << std::endl; return; }

    if (!readDouble("Enter transfer amount: ", amount, ok)) return;
    if (!ok) { std::cout << "Invalid amount." << std::endl; return; }

    OperationStatus status = bank.transfer(from, to, amount);
    std::cout << statusMessage(status) << std::endl;

    if (status == OP_SUCCESS)
    {
        double fromBalance = bank.findAccount(from)->getBalance();
        double toBalance = bank.findAccount(to)->getBalance();
        logger.logTransaction("TRANSFER_OUT", from, amount, fromBalance);
        logger.logTransaction("TRANSFER_IN", to, amount, toBalance);
        saveState(bank);
        std::cout << "Source Balance    : Rs. " << fromBalance << std::endl;
        std::cout << "Destination Bal.  : Rs. " << toBalance << std::endl;
    }
}

static void balanceEnquiry(BankManager& bank)
{
    int number;
    bool ok;
    AnalyticsEngine analytics;

    if (!readInt("Enter account number: ", number, ok)) return;
    if (!ok) { std::cout << "Invalid account number." << std::endl; return; }

    Account* acc = bank.findAccount(number);
    if (acc == nullptr)
    {
        std::cout << statusMessage(OP_ACCOUNT_NOT_FOUND) << std::endl;
        return;
    }

    std::cout << "\n        ACCOUNT DETAILS" << std::endl;
    std::cout << "\nAccount Number    : " << acc->getAccountNumber() << std::endl;
    std::cout << "Account Holder    : " << acc->getHolderName() << std::endl;
    std::cout << "Current Balance   : Rs. " << acc->getBalance() << std::endl;
    std::cout << "Account Category  : " << analytics.classifyBalance(acc->getBalance()) << std::endl;
    std::cout << "Account Status    : ACTIVE" << std::endl;
}

static void interestEstimate(BankManager& bank)
{
    int number;
    double years;
    bool ok;
    InterestCalculator calculator(INTEREST_RATE);

    if (!readInt("Enter account number: ", number, ok)) return;
    if (!ok) { std::cout << "Invalid account number." << std::endl; return; }

    Account* acc = bank.findAccount(number);
    if (acc == nullptr)
    {
        std::cout << statusMessage(OP_ACCOUNT_NOT_FOUND) << std::endl;
        return;
    }

    if (!readDouble("Enter period (years): ", years, ok)) return;
    if (!ok || years <= 0)
    {
        std::cout << "Invalid period." << std::endl;
        return;
    }

    double interest = calculator.calculateInterest(acc->getBalance(), years);

    std::cout << "\nCurrent Balance   : Rs. " << acc->getBalance() << std::endl;
    std::cout << "Interest Rate     : " << calculator.getRate() << " % per year" << std::endl;
    std::cout << "Period            : " << years << " year(s)" << std::endl;
    std::cout << "Estimated Interest: Rs. " << interest << std::endl;
    std::cout << "Maturity Amount   : Rs. " << acc->getBalance() + interest << std::endl;
}

static void showAllAccounts(BankManager& bank)
{
    const std::vector<Account>& accounts = bank.getAccounts();
    AnalyticsEngine analytics;

    if (accounts.empty())
    {
        std::cout << "No accounts available." << std::endl;
        return;
    }

    std::cout << "\n" << std::left << std::setw(10) << "Acc No"
              << std::setw(24) << "Holder"
              << std::right << std::setw(14) << "Balance (Rs.)"
              << "  " << "Category" << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;

    for (std::size_t i = 0; i < accounts.size(); i++)
    {
        analytics.addBalance(accounts[i].getBalance());
        std::cout << std::left << std::setw(10) << accounts[i].getAccountNumber()
                  << std::setw(24) << accounts[i].getHolderName()
                  << std::right << std::setw(14) << accounts[i].getBalance()
                  << "  " << analytics.classifyBalance(accounts[i].getBalance())
                  << std::endl;
    }

    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << "Total Accounts    : " << analytics.countAccounts() << std::endl;
    std::cout << "Total Deposits    : Rs. " << analytics.calculateTotalBalance() << std::endl;
    std::cout << "Average Balance   : Rs. " << analytics.calculateAverageBalance() << std::endl;
    std::cout << "Highest Balance   : Rs. " << analytics.findHighestBalance() << std::endl;
}

int main()
{
    BankManager bank;
    DataLogger logger(LOG_FILE);
    AccountStorage storage(ACCOUNT_FILE);

    bank.loadAccounts(storage.load());

    std::cout << "========================================" << std::endl;
    std::cout << "     BANK ACCOUNT MANAGEMENT SYSTEM" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Accounts loaded   : " << bank.getAccounts().size() << std::endl;

    std::cout << std::fixed << std::setprecision(2);

    bool running = true;
    while (running)
    {
        printMenu();

        int choice;
        bool ok;
        if (!readInt("Enter your choice: ", choice, ok))
        {
            break;   // end of input
        }
        if (!ok)
        {
            std::cout << "Invalid choice. Please enter a number from 1 to 8." << std::endl;
            continue;
        }

        switch (choice)
        {
            case 1: createAccount(bank, logger); break;
            case 2: depositMoney(bank, logger); break;
            case 3: withdrawMoney(bank, logger); break;
            case 4: transferMoney(bank, logger); break;
            case 5: balanceEnquiry(bank); break;
            case 6: interestEstimate(bank); break;
            case 7: showAllAccounts(bank); break;
            case 8: running = false; break;
            default:
                std::cout << "Invalid choice. Please enter a number from 1 to 8." << std::endl;
        }
    }

    std::cout << "\nLog File          : " << LOG_FILE << std::endl;
    std::cout << "Data File         : " << ACCOUNT_FILE << std::endl;
    std::cout << "\nThank you for using the Bank Account Management System." << std::endl;
    return 0;
}
