# Stage 1 – Introduction

## 1. Project Title

**Bank Account Management System**

---

## 2. Domain

**Financial Software, System Programming and Linux**

This project is a Linux-based C++11 application that simulates the basic operations of a retail bank account system.

It demonstrates how account data can be created, validated, updated, analysed and stored using modular C++ on a Linux platform.

---

## 3. Project Overview

A bank maintains accounts for its customers and records every deposit, withdrawal and transfer. In this project, a real banking system is replaced by a software-based simulation controlled through a command-line menu.

The system performs the following operations:

1. Creates bank accounts with unique account numbers.
2. Deposits money into an account.
3. Withdraws money while enforcing a minimum balance.
4. Transfers money between two accounts.
5. Displays account details and balance.
6. Estimates simple interest on a balance.
7. Classifies accounts as BASIC, STANDARD or PREMIUM.
8. Calculates bank-wide analytics.
9. Logs every transaction with a timestamp.
10. Saves accounts to a file so they persist between runs.
11. Validates all user input.

The project is implemented using **C++11** and developed on **Ubuntu Linux**.

---

## 4. Problem Statement

Banking software must handle money correctly. A withdrawal must never overdraw an account, a transfer must never lose or create money, and every transaction must be recorded.

Understanding how this works requires knowledge of data validation, object-oriented design, file handling and testing.

The objective of this project is to create a simplified banking simulation so that the complete workflow — from account creation to transaction logging — can be demonstrated and tested without any real financial infrastructure.

---

## 5. Objectives

- To develop a bank account management system using C++.
- To work with C++ on the Linux operating system.
- To implement deposit, withdrawal and transfer operations.
- To enforce a minimum-balance rule.
- To estimate interest using a simple formula.
- To classify accounts by balance.
- To validate user input.
- To store transactions in a log file.
- To store account data persistently.
- To demonstrate modular and object-oriented C++ programming.
- To demonstrate Linux compilation, execution and shell scripting.
- To perform unit testing of individual modules.
- To maintain the project using Git.

---

## 6. System Concept

```text
User Menu Input
    |
    v
Input Validation
    |
    v
Bank Manager
    |
    +----> Account (deposit / withdraw)
    |
    +----> Interest Calculator
    |
    +----> Analytics Engine ----> Account Category
    |
    v
Data Logger ----> logs/bank.log
    |
    v
Account Storage ----> data/accounts.csv
```

The user selects an operation from a menu. The input is validated, the Bank Manager locates the account(s) and applies the transaction rules, and the result is logged and saved.

---

## 7. Banking Rules

### Minimum balance

```text
Minimum Balance = Rs. 500
```

An account can only be opened with at least Rs. 500, and no withdrawal or transfer may bring the balance below Rs. 500.

### Interest

The project uses an assumed rate of **4.00 % per year** with simple interest:

```text
Interest = (Balance × Rate × Years) / 100
```

For example:

```text
Balance = Rs. 10,000
Rate = 4 %
Years = 2

Interest = (10000 × 4 × 2) / 100
         = Rs. 800
```

### Account category

```text
Balance < Rs. 5,000                → BASIC
Rs. 5,000 to Rs. 1,00,000          → STANDARD
Balance > Rs. 1,00,000             → PREMIUM
```

These values are project-defined assumptions for demonstration.

---

## 8. Main Modules

### 8.1 Account

Stores the account number, holder name and balance. Provides `deposit()` and `withdraw()`.

```text
include/account.h
src/account.cpp
```

### 8.2 Validator

Checks names, amounts and account numbers.

```text
include/validator.h
src/validator.cpp
```

### 8.3 Bank Manager

Creates accounts and performs deposit, withdrawal and transfer across the account list.

```text
include/bank_manager.h
src/bank_manager.cpp
```

### 8.4 Interest Calculator

Calculates simple interest.

```text
include/interest_calculator.h
src/interest_calculator.cpp
```

### 8.5 Analytics Engine

Calculates total, average and highest balance and classifies accounts.

```text
include/analytics.h
src/analytics.cpp
```

### 8.6 Data Logger

Writes timestamped transactions to `logs/bank.log`.

```text
include/data_logger.h
src/data_logger.cpp
```

### 8.7 Account Storage

Saves and loads account data from `data/accounts.csv`.

```text
include/account_storage.h
src/account_storage.cpp
```

---

## 9. Technologies Used

| Technology | Purpose |
|---|---|
| C++11 | Main programming language |
| Ubuntu Linux | Development and execution platform |
| g++ | C++ compiler |
| Bash | Build/test automation |
| Git | Version control |
| File I/O | Logging and persistent storage |
| C++ Classes | Modular software design |

---

## 10. Linux Concepts Demonstrated

- Working with the Linux terminal.
- Directory and file management.
- Compiling C++ programs using `g++`.
- Executing Linux binaries.
- Bash scripting.
- File permissions (`chmod +x`).
- File-based logging.
- Git version control.
- Building multiple source files.
- Using compiler warning options (`-Wall -Wextra`).

---

## 11. C++ Concepts Demonstrated

- Classes and objects.
- Constructors and initializer lists.
- Private and public members.
- Static members and static methods.
- Enumerations.
- Header and source files.
- Encapsulation.
- Modular programming.
- `std::vector` and `std::string`.
- File handling (`ofstream`, `ifstream`).
- String streams and parsing.
- Exception handling for corrupted data.
- Input validation.
- Unit testing.

---

## 12. Project Scope

The current scope includes:

- Account creation.
- Deposit, withdrawal and transfer.
- Balance enquiry.
- Interest estimation.
- Account classification and analytics.
- Transaction logging.
- Persistent storage.
- Input validation.
- Unit testing.
- Linux-based development.

The project does not include:

- Real banking network connectivity.
- Login / authentication.
- A database.
- Multiple account types.
- A graphical interface.
- Multi-user access.

---

## 13. Expected Outcome

```text
Input:
Create account for "Kinkan Maiti" with Rs. 10000
Deposit Rs. 2500
Transfer Rs. 1500 to another account

Output:
Account 1001 created
Balance after deposit  : Rs. 12500.00
Balance after transfer : Rs. 11000.00
Every step recorded in logs/bank.log
Account data saved in data/accounts.csv
```

---

## 14. Development Approach

```text
Stage 1 → Introduction
Stage 2 → Requirements
Stage 3 → System Design
Stage 4 → Prototype / Implementation
Stage 5 → Testing
Stage 6 → Final Report
```

---

## 15. Conclusion

Stage 1 establishes the purpose and scope of the Bank Account Management System.

The project provides a software-based simulation of banking operations using C++11 on Linux, combining account management, transaction rules, analytics, logging and persistent storage.

---

**Author:** Kinkan Maiti  
**Course:** B.Tech Electrical and Electronics Engineering  
**Project:** Bank Account Management System
