# Stage 4 – Prototype / Implementation

## 1. Implementation Overview

The Bank Account Management System was implemented as a modular **C++11 application on Ubuntu Linux**.

The prototype consists of separate classes for accounts, validation, bank operations, interest calculation, analytics, transaction logging and persistent storage.

---

## 2. Implemented Modules

### Account

Stores account data and applies the deposit and minimum-balance rules.

```text
src/account.cpp
include/account.h
```

### Validator

Validates holder names, amounts and account numbers.

```text
src/validator.cpp
include/validator.h
```

### BankManager

Creates accounts and performs deposit, withdrawal and transfer.

```text
src/bank_manager.cpp
include/bank_manager.h
```

### InterestCalculator

Calculates simple interest.

```text
src/interest_calculator.cpp
include/interest_calculator.h
```

### AnalyticsEngine

Calculates total, average and highest balance and classifies accounts.

```text
src/analytics.cpp
include/analytics.h
```

### DataLogger

Writes timestamped transactions to the log file.

```text
src/data_logger.cpp
include/data_logger.h
```

### AccountStorage

Saves and loads account data.

```text
src/account_storage.cpp
include/account_storage.h
```

---

## 3. Main Program Flow

```text
Start
  ↓
Load saved accounts
  ↓
Show menu
  ↓
Read choice → validate
  ↓
Run selected operation
  ↓
Log transaction
  ↓
Save accounts
  ↓
Back to menu (until Exit or end of input)
```

---

## 4. Input Validation

All input is read line by line and parsed strictly, so text such as `abc` or `100xyz` is rejected instead of being half-read.

| Situation | Message |
|---|---|
| Non-numeric menu choice | `Invalid choice. Please enter a number from 1 to 8.` |
| Invalid name | `Invalid account holder name.` |
| Opening deposit below Rs. 500 | `Invalid initial deposit. Minimum is Rs. 500.` |
| Zero / negative amount | `Invalid amount.` |
| Unknown account | `Account not found.` |
| Minimum balance breach | `Insufficient funds (minimum balance must be maintained).` |
| Transfer to same account | `Cannot transfer to the same account.` |

---

## 5. Build Process

```bash
./scripts/run.sh
```

The script creates the `logs/` and `data/` folders, then compiles the application and every test program using:

```text
-Wall
-Wextra
-std=c++11
```

The script stops at the first compilation error.

---

## 6. Sample Prototype Execution

```text
Enter your choice: 2
Enter account number: 1001
Enter deposit amount: 2500
Transaction successful.
New Balance       : Rs. 12500.00
```

```text
Enter your choice: 3
Enter account number: 1002
Enter withdrawal amount: 1800
Insufficient funds (minimum balance must be maintained).
```

```text
Enter your choice: 4
Enter source account number: 1001
Enter destination account number: 1002
Enter transfer amount: 1500
Transaction successful.
Source Balance    : Rs. 11000.00
Destination Bal.  : Rs. 2500.00
```

```text
Acc No    Holder                   Balance (Rs.)  Category
--------------------------------------------------------------
1001      Kinkan Maiti                  11000.00  STANDARD
1002      Rahul Das                      2500.00  BASIC
--------------------------------------------------------------
Total Accounts    : 2
Total Deposits    : Rs. 13500.00
Average Balance   : Rs. 6750.00
Highest Balance   : Rs. 11000.00
```

---

## 7. Data Logging and Storage

### Transaction log — `logs/bank.log`

```text
2026-10-04 17:41:33,OPEN,1001,10000,10000
2026-10-04 17:41:33,OPEN,1002,2000,2000
2026-10-04 17:41:33,DEPOSIT,1001,2500,12500
2026-10-04 17:41:33,WITHDRAW,1002,1000,1000
2026-10-04 17:41:33,TRANSFER_OUT,1001,1500,11000
2026-10-04 17:41:33,TRANSFER_IN,1002,1500,2500
```

### Account data — `data/accounts.csv`

```text
1001,Kinkan Maiti,11000.00
1002,Rahul Das,2500.00
```

On the next start-up the accounts are reloaded and new account numbers continue after the highest existing number.

---

## 8. Prototype Status

The prototype successfully implements:

- Account creation with unique numbers.
- Deposit, withdrawal and transfer.
- Minimum-balance enforcement.
- Balance enquiry and account category.
- Interest estimation.
- Bank-wide analytics.
- Input validation.
- Transaction logging.
- Persistent storage.
- Modular C++11 implementation.
- Linux build and execution.
- Unit-test programs.
