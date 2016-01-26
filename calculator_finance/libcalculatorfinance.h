/* See LICENSE.txt for license and copyright information. */
#pragma once

// Helper functions

typedef struct
{
    int sp_shares;
    double sp_price;
} SharesPrice;

extern char *version();
extern double calculate_average_price(int a_nargs, ...);
extern double calculate_percentage_of(double a_value, double a_from_value);
extern double convert_from_orig(double a_price, double a_exchange_rate);
extern double convert_to_orig(double a_converted_price, double a_exchange_rate);

// Before trade

extern int calculate_shares_recommended(double a_pool, double a_commission, double a_tax, double a_price);
extern int calculate_leveraged_contracts(int a_n);
extern double calculate_stoploss(double a_price, int a_shares, double a_tax, double a_commission, double a_risk, double a_pool, int a_is_long);
extern double calculate_risk_input(double a_pool, double a_risk);
extern double calculate_risk_initial(double a_price, int a_shares, double a_tax, double a_commission, double a_stoploss, int a_is_long);
extern double calculate_amount(double a_price, int a_shares);
extern double calculate_amount_with_tax_and_commission(double a_price, int a_shares, double a_tax, double a_commission, transaction_type_t a_transaction_type);
extern double calculate_amount_with_tax(double a_price, int a_shares, double a_tax, transaction_type_t a_transaction_type);
extern double cost_transaction(double a_price, int a_shares, double a_tax, double a_commission);
extern double cost_tax(double a_amount, double a_commission, int a_shares, double a_price, transaction_type_t a_transaction_type);
extern double calculate_price(double a_amount, int a_shares, double a_tax, double a_commission, transaction_type_t a_transaction_type);

// After trade

extern double calculate_risk_actual(double a_price_buy, int a_shares_buy, double a_tax_buy,
    double a_commission_buy, double a_price_sell, int a_shares_sell, double a_tax_sell,
    double a_commission_sell, double a_risk_initial, double a_profit_loss);
extern double calculate_r_multiple(double a_profit_loss, double a_risk_initial);
extern double calculate_cost_total(double a_amount_buy, double a_tax_buy, double a_commission_buy,
    double a_amount_sell, double a_tax_sell, double a_commission_sell);
extern double calculate_profit_loss(double a_price_buy, int a_shares_buy, double a_price_sell, int a_shares_sell);
extern double calculate_profit_loss_total(double a_price_buy, int a_shares_buy, double a_tax_buy, double a_commission_buy,
    double a_price_sell, int a_shares_sell, double a_tax_sell, double a_commission_sell);
extern double calculate_cost_other(double a_profit_loss, double a_profit_loss_total, double a_cost_total);
