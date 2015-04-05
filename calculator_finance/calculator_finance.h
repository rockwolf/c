/* See LICENSE.txt for license and copyright information. */

/// Helper functions

double calculate_percentage_of(double a_value, double a_from_value);
double convert_from_orig(double a_price, double a_exchange_rate);
double convert_to_orig(double a_converted_price, double a_exchange_rate);

/// Before trade

double calculate_stoploss(double a_price, int a_shares, double a_tax, double a_commission, double a_risk, double a_pool, int a_is_long);
