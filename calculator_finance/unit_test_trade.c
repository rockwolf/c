/* See LICENSE.txt for license and copyright information. */

#include <stdio.h>
#include <math.h>
#include "const.h"
#include "types.h"
#include "unit_test_trade.h"
#include "calculator_finance.h"
#include "general_functions.h"
#include "minunit.h"

// Helper functions

char* test_calculate_percentage_of()
{
    mu_assert(
        "[FAIL] Wrong result for calculate_percentage_of(2.0, 50.0)!",
        calculate_percentage_of(2.0, 50.0) == 4.0
    ); 
    return 0;
}

char* test_convert_from_orig()
{
    mu_assert(
            "[FAIL] Wrong result for convert_from_orig(12.0, 0.5)!",
            convert_from_orig(12.0, 0.5) == 6.0
    ); 
    return 0;
}

char* test_convert_to_orig()
{
    mu_assert(
        "[FAIL] Wrong result for convert_to_orig(12.0, 0.5)!",
        convert_from_orig(12.0, 0.5) == 6.0
    ); 
    return 0;
}

// Before trade

char* test_calculate_shares_recommended()
{
    mu_assert(
        "[FAIL] Wrong result for calculate_shares_recommended(10000.0, 1.0, 3.0, 12.0)!",
        calculate_shares_recommended(10000.0, 1.0, 3.0, 12.0) == 808
    ); 
    return 0;
}

char* test_calculate_leveraged_contracts()
{
    mu_assert(
        "[FAIL] Wrong result for calculate_leveraged_contracts(4)!",
        calculate_leveraged_contracts(4) == 5
    );
    return 0;
}

char* test_calculate_stoploss()
{
    mu_assert(
        "[FAIL] -short- Wrong result for calculate_stoploss(12.0, 2, 3.0, 1.0, 2.0, 10000.0, 0)!",
        equals(calculate_stoploss(12.0, 2, 3.0, 1.0, 2.0, 10000.0, 0), 109.004926, C_PRECISION)
    ); 
    mu_assert(
        "[FAIL] -long- Wrong result for calculate_stoploss(12.0, 2, 3.0, 1.0, 2.0, 10000.0, 1)!",
        equals(calculate_stoploss(12.0, 2, 3.0, 1.0, 2.0, 10000.0, 1), -87.9593908629, C_PRECISION)
    ); 
    return 0;
}

char* test_calculate_risk_input()
{
    mu_assert(
        "[FAIL] Wrong result for calculate_risk_input(10000.0, 2.0)!",
        equals(calculate_risk_input(10000.0, 2.0), 200.0, C_PRECISION)
    ); 
    return 0;
}

char* test_calculate_risk_initial()
{
    mu_assert(
        "[FAIL] -short- Wrong result for calculate_risk_initial(12.0, 2, 3.0, 1.0, 2.0, 0)!",
        equals(calculate_risk_initial(12.0, 2, 3.0, 1.0, 10.0, 0), -0.68, C_PRECISION)
    ); 
    mu_assert(
            "[FAIL] -long- Wrong result for calculate_risk_initial(12.0, 2, 3.0, 1.0, 2.0, 1)!",
            equals(calculate_risk_initial(12.0, 2, 3.0, 1.0, 10.0, 1), 7.32, C_PRECISION)
    ); 
    return 0;
}

char* test_calculate_amount()
{
    mu_assert(
        "[FAIL] Wrong result for calculate_amount(12.0, 2)!",
        calculate_amount(12.0, 2) == 24.0
    ); 
    return 0;
}

char* test_calculate_amount_with_tax_and_commission()
{
    transaction_type_t a_transaction_type_t;
    a_transaction_type_t = BUY;
    mu_assert(
        "[FAIL] -buy- Wrong result for calculate_amount_with_tax_and_commission(12.0, 2, 3.0, 1.0, BUY)!",
        equals(calculate_amount_with_tax_and_commission(12.0, 2, 3.0, 1.0, a_transaction_type_t), 97.0, C_PRECISION)
    ); 
    a_transaction_type_t = SELL;
    mu_assert(
        "[FAIL] -sell- Wrong result for calculate_amount_with_tax_and_commission(12.0, 2, 3.0, 1.0, SELL)!",
        equals(calculate_amount_with_tax_and_commission(12.0, 2, 3.0, 1.0, a_transaction_type_t), -49.0, C_PRECISION)
    ); 
    return 0;
}

char* test_calculate_amount_with_tax()
{
    transaction_type_t a_transaction_type_t;
    a_transaction_type_t = BUY;
    mu_assert(
        "[FAIL] -buy- Wrong result for calculate_amount_with_tax(12.0, 2, 3.0, BUY)!",
        equals(calculate_amount_with_tax(12.0, 2, 3.0, a_transaction_type_t), 23.28, C_PRECISION)
    ); 
    a_transaction_type_t = SELL;
    mu_assert(
            "[FAIL] -sell- Wrong result for calculate_amount_with_tax(12.0, 2, 3.0, SELL)!",
            equals(calculate_amount_with_tax(12.0, 2, 3.0, a_transaction_type_t), 24.72, C_PRECISION)
    ); 
    return 0;
}

char* test_cost_transaction()
{
    mu_assert(
        "[FAIL] Wrong result for cost_transaction(12.0, 2, 3.0, 1.0)!",
        cost_transaction(12.0, 2, 3.0, 1.0) == 1.72
    );
    return 0;
}

char* test_cost_tax()
{
    transaction_type_t a_transaction_type_t;
    a_transaction_type_t = BUY;
    mu_assert(
        "[FAIL] -buy- Wrong result for cost_tax(5000.0, 1.0, 2, 12.0, BUY)!",
        equals(cost_tax(25.75, 1.0, 2, 12.0, a_transaction_type_t), 0.75, C_PRECISION)
    ); 
    a_transaction_type_t = SELL;
    mu_assert(
            "[FAIL] -sell- Wrong result for cost_tax(5000.0, 1.0, 2, 12.0, SELL)!",
            equals(cost_tax(22.25, 1.0, 2, 12.0, a_transaction_type_t), 0.75, C_PRECISION)
    ); 
    return 0;
}

char* test_all_trade()
{
    mu_run_test(test_calculate_percentage_of);
    mu_run_test(test_convert_from_orig);
    mu_run_test(test_convert_to_orig);
    mu_run_test(test_calculate_shares_recommended);
    mu_run_test(test_calculate_leveraged_contracts);
    mu_run_test(test_calculate_stoploss);
    mu_run_test(test_calculate_risk_input);
    mu_run_test(test_calculate_risk_initial);
    mu_run_test(test_calculate_amount);
    mu_run_test(test_calculate_amount_with_tax_and_commission);
    mu_run_test(test_calculate_amount_with_tax);
    mu_run_test(test_cost_transaction);
    mu_run_test(test_cost_tax);
    return 0;
}
