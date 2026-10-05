#!/bin/bash

mkdir -p logs data

failed=0
for t in account_test bank_manager_test analytics_test interest_calculator_test validator_test data_logger_test account_storage_test; do
    if [ ! -x "./$t" ]; then
        echo "$t not built. Run ./scripts/run.sh first."
        exit 1
    fi
    ./$t || failed=1
done

if [ $failed -eq 0 ]; then
    echo "All tests passed."
else
    echo "Some tests failed."
    exit 1
fi
