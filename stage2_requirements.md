# Stage 2 – Requirements

## 1. Introduction

This stage defines the functional and non-functional requirements of the **Bank Account Management System**.

The system is a Linux-based C++11 application that simulates core banking operations through a command-line menu.

---

## 2. Functional Requirements

The system shall:

- Display a menu of banking operations.
- Create a new account with a holder name and initial deposit.
- Assign a unique account number to each new account.
- Deposit money into an existing account.
- Withdraw money from an existing account.
- Transfer money between two different accounts.
- Display account details and balance.
- Estimate interest for a given period.
- Classify accounts by balance.
- Display total, average and highest balance across all accounts.
- Validate all user input.
- Store every transaction in `logs/bank.log`.
- Store account data in `data/accounts.csv` and reload it at start-up.
- Support testing of individual modules.

### Business rules

| Rule | Value |
|---|---|
| Minimum opening deposit | Rs. 500 |
| Minimum balance | Rs. 500 |
| First account number | 1001 |
| Interest rate (assumed) | 4.00 % per year |
| Interest type | Simple interest |

### Interest

```text
Interest = (Balance × Rate × Years) / 100
```

### Account category

```text
Below Rs. 5,000            → BASIC
Rs. 5,000 – Rs. 1,00,000   → STANDARD
Above Rs. 1,00,000         → PREMIUM
```

---

## 3. Input Requirements

| Input | Type | Validation |
|---|---|---|
| Menu choice | Integer | Must be 1 to 8 |
| Holder name | Text | Letters, spaces and "."; 1–40 characters; at least one letter |
| Initial deposit | Decimal | At least Rs. 500 and at most Rs. 1,00,00,000 |
| Account number | Integer | Must refer to an existing account |
| Amount | Decimal | Greater than 0 and at most Rs. 1,00,00,000 |
| Period (years) | Decimal | Greater than 0 |

Invalid input (text instead of a number, negative amounts, unknown accounts) must be rejected with a message and must not crash the program.

---

## 4. Output Requirements

For account details the application should display:

```text
Account Number
Account Holder
Current Balance
Account Category
Account Status
```

For an interest estimate:

```text
Current Balance
Interest Rate
Period
Estimated Interest
Maturity Amount
```

For the analytics view:

```text
Account table
Total Accounts
Total Deposits
Average Balance
Highest Balance
```

---

## 5. Non-Functional Requirements

### Platform
- Ubuntu/Linux environment.

### Programming Language
- C++11.

### Compiler
- `g++`

### Build
- Bash build script using `-Wall -Wextra`, with no warnings.

### Maintainability
- Modular header and source files.
- Separate test files for each module.

### Reliability
- Invalid input must be handled without crashing.
- End of input (Ctrl+D) must exit cleanly.
- Corrupted lines in the data file must be skipped safely.

### Data integrity
- A failed transaction must not change any balance.
- A transfer must not create or destroy money.

---

## 6. Project Constraints

- The bank is simulated using software.
- No real money, bank network or payment gateway is involved.
- There is no authentication.
- The interest rate and minimum balance are assumed values.
- The application uses a command-line interface and a single user.

---

## 7. Acceptance Criteria

The requirements are satisfied when:

- The program compiles successfully with C++11 and no warnings.
- Accounts can be created with unique numbers.
- Deposits, withdrawals and transfers update balances correctly.
- The minimum-balance rule is enforced.
- Invalid input is rejected.
- Interest and analytics are calculated correctly.
- Transactions are written to the log file.
- Accounts persist after the program is restarted.
- Every module passes its test.
