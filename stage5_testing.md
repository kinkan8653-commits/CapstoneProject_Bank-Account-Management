# Stage 5 – Testing

## 1. Testing Overview

Testing was performed to verify that the Bank Account Management System applies banking rules correctly, handles invalid input safely and persists data.

The project was compiled using **C++11** with:

```text
-Wall -Wextra
```

The build produced no warnings.

---

## 2. Unit Testing

| Test | What it checks | Result |
|---|---|---|
| Account | Deposit, withdraw, minimum balance, negative amounts | PASS |
| BankManager | Account creation, deposit, withdraw, transfer, error codes | PASS |
| AnalyticsEngine | Total, average, highest, categories, empty case | PASS |
| InterestCalculator | Simple-interest formula | PASS |
| Validator | Valid and invalid names, amounts, account numbers | PASS |
| DataLogger | Log file can be written | PASS |
| AccountStorage | Save then load returns the same accounts | PASS |

### Test Commands

```bash
./scripts/run_tests.sh
```

Output:

```text
Account test passed
BankManager test passed
AnalyticsEngine test passed
InterestCalculator test passed
Validator test passed
DataLogger test passed
AccountStorage test passed
All tests passed.
```

---

## 3. Valid Transaction Testing

Scenario:

```text
Create 1001  Kinkan Maiti   Rs. 10000
Create 1002  Rahul Das      Rs. 2000
Deposit Rs. 2500 into 1001
Withdraw Rs. 1000 from 1002
Transfer Rs. 1500 from 1001 to 1002
```

Expected balances:

```text
1001 : 10000 + 2500 − 1500 = Rs. 11000
1002 : 2000 − 1000 + 1500  = Rs. 2500
```

Application result:

```text
1001      Kinkan Maiti                  11000.00  STANDARD
1002      Rahul Das                      2500.00  BASIC
```

Total money in the bank = 13500, which equals 10000 + 2000 + 2500 − 1000 (deposits minus withdrawals). The transfer neither created nor lost money.

**Result: PASS**

---

## 4. Business-Rule Testing

### Minimum balance

Account 1002 had Rs. 2000. Withdrawing Rs. 1800 would leave Rs. 200.

```text
Insufficient funds (minimum balance must be maintained).
```

The balance stayed at Rs. 2000.

**Result: PASS**

### Interest

Balance Rs. 11000, 2 years at 4 %:

```text
Interest = 11000 × 4 × 2 / 100 = Rs. 880
Maturity = Rs. 11880
```

The application displayed `Estimated Interest: Rs. 880.00` and `Maturity Amount: Rs. 11880.00`.

**Result: PASS**

---

## 5. Invalid Input Testing

| Input | Output | Result |
|---|---|---|
| Menu choice `abc` | Invalid choice message | PASS |
| Menu choice `9` | Invalid choice message | PASS |
| Name `Bad123` | `Invalid account holder name.` | PASS |
| Opening deposit `100` | `Invalid initial deposit. Minimum is Rs. 500.` | PASS |
| Deposit `-5` | `Invalid amount.` | PASS |
| Unknown account `9999` | `Account not found.` | PASS |
| Transfer to same account | `Cannot transfer to the same account.` | PASS |
| End of input (Ctrl+D) | Clean exit | PASS |

---

## 6. Log File Testing

After the valid scenario, `logs/bank.log` contained one line per transaction, including both sides of the transfer:

```text
2026-10-04 17:41:33,OPEN,1001,10000,10000
2026-10-04 17:41:33,OPEN,1002,2000,2000
2026-10-04 17:41:33,DEPOSIT,1001,2500,12500
2026-10-04 17:41:33,WITHDRAW,1002,1000,1000
2026-10-04 17:41:33,TRANSFER_OUT,1001,1500,11000
2026-10-04 17:41:33,TRANSFER_IN,1002,1500,2500
```

Failed transactions were not logged.

**Result: PASS**

---

## 7. Persistence Testing

The application was closed and started again. It reported `Accounts loaded : 2` and showed the same balances.

**Result: PASS**

---

## 8. Build Testing

```bash
./scripts/run.sh
```

The build completed with no errors and no warnings under C++11 `-Wall -Wextra`.

**Result: PASS**

---

## 9. Testing Summary

```text
+---------------------------+--------+
| Test                      | Result |
+---------------------------+--------+
| Account                   | PASS   |
| BankManager               | PASS   |
| AnalyticsEngine           | PASS   |
| InterestCalculator        | PASS   |
| Validator                 | PASS   |
| DataLogger                | PASS   |
| AccountStorage            | PASS   |
| Valid Transactions        | PASS   |
| Minimum Balance Rule      | PASS   |
| Interest Calculation      | PASS   |
| Invalid Input Handling    | PASS   |
| Log File Verification     | PASS   |
| Data Persistence          | PASS   |
| Build Verification        | PASS   |
+---------------------------+--------+
```

All tests completed successfully.
