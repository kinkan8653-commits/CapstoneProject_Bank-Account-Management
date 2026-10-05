# Stage 6 – Final Report

## 1. Project Overview

The **Bank Account Management System** is a Linux-based C++11 application developed to simulate the core operations of a retail bank.

The system creates accounts, processes deposits, withdrawals and transfers, enforces a minimum balance, estimates interest, classifies accounts, logs every transaction and stores account data persistently.

---

## 2. Final System Architecture

```text
User Menu Input
    ↓
Input Validation
    ↓
Bank Manager
    ↓
Account  /  Interest Calculator  /  Analytics Engine
    ↓
Data Logger  →  logs/bank.log
    ↓
Account Storage  →  data/accounts.csv
```

---

## 3. Technologies Used

- **C++11**
- **Ubuntu Linux**
- **g++ Compiler**
- **Bash**
- **Git**
- File I/O
- C++ Object-Oriented Programming

---

## 4. Main Features

- Account creation with unique account numbers.
- Deposit, withdrawal and fund transfer.
- Minimum-balance enforcement.
- Balance enquiry with account category.
- Simple-interest estimation.
- Bank-wide analytics.
- Input validation.
- Timestamped transaction logging.
- Persistent account storage.
- Modular C++ implementation.
- Unit testing.
- Linux-based build and execution.

---

## 5. Final Calculation Example

Starting position:

```text
Account 1001 : Rs. 10000
Account 1002 : Rs. 2000
```

Operations:

```text
Deposit  Rs. 2500 → 1001   : 12500
Withdraw Rs. 1000 ← 1002   : 1000
Transfer Rs. 1500 1001→1002: 1001 = 11000,  1002 = 2500
```

Interest on account 1001 for 2 years at 4 %:

```text
Interest = (11000 × 4 × 2) / 100
         = Rs. 880
Maturity = Rs. 11880
```

Categories:

```text
1001 (Rs. 11000) → STANDARD
1002 (Rs. 2500)  → BASIC
```

---

## 6. Testing Summary

| Test | Result |
|---|---|
| Account | PASS |
| BankManager | PASS |
| AnalyticsEngine | PASS |
| InterestCalculator | PASS |
| Validator | PASS |
| DataLogger | PASS |
| AccountStorage | PASS |
| Valid Transactions | PASS |
| Invalid Input Handling | PASS |
| Data Persistence | PASS |
| Build Verification | PASS |

The complete project builds successfully using C++11 with `-Wall` and `-Wextra`.

---

## 7. Linux and C++ Concepts Applied

### Linux

- Terminal commands.
- File and directory management.
- C++ compilation.
- Executable generation.
- Bash scripting.
- File permissions.
- File-based logging and storage.
- Git version control.

### C++

- Classes and objects.
- Constructors and initializer lists.
- Encapsulation.
- Static members.
- Enumerations.
- Header and source files.
- `std::vector`, `std::string`, string streams.
- File handling.
- Exception handling.
- Input validation.
- Modular programming.
- Unit testing.

---

## 8. Limitations

- It is a software simulation and is not connected to any real bank.
- There is no login or PIN protection.
- The interest rate and minimum balance are assumed values.
- Only simple interest is supported.
- Data is stored in a CSV file instead of a database.
- Money is stored as `double`, which can accumulate rounding error; a real system would use integer paise.
- The application is single-user and command-line only.

---

## 9. Future Improvements

- Authentication with PIN / password.
- Savings, current and fixed-deposit account types.
- Compound interest and automatic interest posting.
- Per-account transaction history and statements.
- Database storage (for example SQLite).
- Fixed-point money type.
- Graphical or web interface.
- Multi-user and network support.

---

## 10. Project Outcome

The project successfully demonstrates a complete software-based banking workflow.

The final application can create accounts, process transactions safely, enforce business rules, estimate interest, produce analytics, record every transaction and keep data between runs.

The modular structure also makes it easy to test and extend individual components.

---

## 11. Conclusion

The **Bank Account Management System** successfully demonstrates how core banking operations can be simulated using C++11 and Linux.

The project combines modular object-oriented programming, business-rule validation, file handling, Bash scripting, testing and Git-based development.

Although it does not include authentication or a real banking back end, it provides a practical foundation for understanding how account and transaction systems are designed and implemented.

---

## 12. Author

**Kinkan Maiti**

**B.Tech Electrical and Electronics Engineering**

**Project:** Bank Account Management System
