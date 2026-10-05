# Stage 3 – System Design

## 1. System Architecture

The Bank Account Management System follows a modular architecture.

```text
+----------------------+
|   User Menu Input    |
+----------+-----------+
           |
           v
+----------------------+
|  Input Validation    |
|     (Validator)      |
+----------+-----------+
           |
           v
+----------------------+
|    Bank Manager      |
+----+-------+-----+---+
     |       |     |
     v       v     v
+--------+ +----------+ +-----------+
|Account | | Interest | | Analytics |
|        | |Calculator| |  Engine   |
+---+----+ +----------+ +-----+-----+
    |                         |
    v                         v
+----------------+      Account Category
|  Data Logger   |
+-------+--------+
        |
        v
  logs/bank.log

+----------------------+
|   Account Storage    |
+----------+-----------+
           |
           v
  data/accounts.csv
```

---

## 2. Module Design

### Account

Holds one customer account.

```text
Account
   |
   +-- getAccountNumber()
   +-- getHolderName()
   +-- getBalance()
   +-- deposit(amount)
   +-- withdraw(amount)      (keeps MIN_BALANCE)
```

### Validator

```text
Validator
   |
   +-- isValidName()
   +-- isValidAmount()
   +-- isValidAccountNumber()
```

### Bank Manager

Owns the list of accounts and applies business rules.

```text
BankManager
   |
   +-- createAccount()
   +-- findAccount()
   +-- deposit()
   +-- withdraw()
   +-- transfer()
   +-- getAccounts()
   +-- loadAccounts()
```

Operations return an `OperationStatus` value:

```text
OP_SUCCESS
OP_INVALID_AMOUNT
OP_INVALID_NAME
OP_ACCOUNT_NOT_FOUND
OP_INSUFFICIENT_FUNDS
OP_SAME_ACCOUNT
```

### Interest Calculator

```text
Interest = (Balance × Rate × Years) / 100
```

### Analytics Engine

```text
AnalyticsEngine
   |
   +-- addBalance()
   +-- countAccounts()
   +-- calculateTotalBalance()
   +-- calculateAverageBalance()
   +-- findHighestBalance()
   +-- classifyBalance()
```

### Data Logger

Appends one line per transaction:

```text
timestamp,TYPE,accountNumber,amount,balanceAfter
```

### Account Storage

Saves and loads accounts as:

```text
accountNumber,holderName,balance
```

---

## 3. Data Flow

### Deposit / Withdrawal

```text
User selects operation
          |
          v
Input validation
          |
          v
Find account
          |
          v
Apply rules (amount valid? minimum balance kept?)
          |
          v
Update balance
          |
          v
Log transaction
          |
          v
Save accounts
          |
          v
Display result
```

### Transfer

```text
Validate amount and accounts
          |
          v
Source and destination different?
          |
          v
Withdraw from source (minimum balance rule)
          |
          v
Deposit to destination
          |
          v
Log TRANSFER_OUT and TRANSFER_IN
          |
          v
Save accounts
```

The withdrawal happens first. If it fails, nothing is deposited, so money is never created or lost.

---

## 4. Main Rules

```text
Minimum balance        = Rs. 500
Interest rate          = 4.00 % per year (simple)
Category BASIC         < Rs. 5,000
Category STANDARD      Rs. 5,000 – Rs. 1,00,000
Category PREMIUM       > Rs. 1,00,000
First account number   = 1001
```

---

## 5. Project Structure

```text
bank-account-management-system/
|
├── include/
│   ├── account.h
│   ├── account_storage.h
│   ├── analytics.h
│   ├── bank_manager.h
│   ├── data_logger.h
│   ├── interest_calculator.h
│   └── validator.h
|
├── src/
│   ├── account.cpp
│   ├── account_storage.cpp
│   ├── analytics.cpp
│   ├── bank_manager.cpp
│   ├── data_logger.cpp
│   ├── interest_calculator.cpp
│   ├── main.cpp
│   └── validator.cpp
|
├── tests/
│   ├── test_account.cpp
│   ├── test_account_storage.cpp
│   ├── test_analytics.cpp
│   ├── test_bank_manager.cpp
│   ├── test_data_logger.cpp
│   ├── test_interest_calculator.cpp
│   └── test_validator.cpp
|
├── data/
├── docs/
├── logs/
├── scripts/
└── README.md
```

---

## 6. Design Approach

The project uses a modular object-oriented design.

Each major responsibility is separated into its own class and source file. Header files contain class declarations, while source files contain implementations. `BankManager` coordinates the work, while `main.cpp` handles only the user interface.

This approach makes the project:

- Easier to understand.
- Easier to test (each module has its own test).
- Easier to maintain.
- Easier to extend (for example, adding account types or a database).
