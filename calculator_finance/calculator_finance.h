/* See LICENSE.txt for license and copyright information. */

// Helper functions

double calculate_percentage_of(double a_value, double a_from_value);
double convert_from_orig(double a_price, double a_exchange_rate);
double convert_to_orig(double a_converted_price, double a_exchange_rate);

// Before trade

double calculate_stoploss(double a_price, int a_shares, double a_tax, double a_commission, double a_risk, double a_pool, int a_is_long);
double calculate_risk_input(double a_pool, double a_risk);
double calculate_risk_initial(double a_price, int a_shares, double a_tax, double a_commission, double a_stoploss, int a_is_long);
double calculate_amount(double a_price, int a_shares);
double calculate_amount_with_tax_and_commission(double a_price, int a_shares, double a_tax, double a_commission, transaction_type_t a_transaction_type);
double calculate_amount_with_tax(double a_price, int a_shares, double a_tax, transaction_type_t a_transaction_type);
double cost_transaction(double a_price, int a_shares, double a_tax, double a_commission);
