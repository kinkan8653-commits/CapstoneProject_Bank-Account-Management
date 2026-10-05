#!/bin/bash

echo "Building Bank Account Management System..."

mkdir -p logs data

FLAGS="-Wall -Wextra -std=c++11 -Iinclude"

set -e

g++ $FLAGS src/main.cpp src/account.cpp src/bank_manager.cpp src/interest_calculator.cpp src/analytics.cpp src/data_logger.cpp src/account_storage.cpp src/validator.cpp -o bank_system

g++ $FLAGS tests/test_account.cpp src/account.cpp -o account_test

g++ $FLAGS tests/test_bank_manager.cpp src/bank_manager.cpp src/account.cpp src/validator.cpp -o bank_manager_test

g++ $FLAGS tests/test_analytics.cpp src/analytics.cpp -o analytics_test

g++ $FLAGS tests/test_interest_calculator.cpp src/interest_calculator.cpp -o interest_calculator_test

g++ $FLAGS tests/test_validator.cpp src/validator.cpp -o validator_test

g++ $FLAGS tests/test_data_logger.cpp src/data_logger.cpp -o data_logger_test

g++ $FLAGS tests/test_account_storage.cpp src/account_storage.cpp src/account.cpp -o account_storage_test

echo "Build completed successfully."
