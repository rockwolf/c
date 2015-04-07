/* See LICENSE.txt file for license and copyright information. */

#include <stdio.h>
#include <stdbool.h>
#include "types.h"
#include "calculator_finance.h"

// Helper functions

/**********************************************************************
 * calculate_percentage_of:
 * Calculate what percentage a_value is from a_from_value.
 **********************************************************************/
double calculate_percentage_of(double a_value, double a_from_value)
{
  return (a_value / a_from_value * 100.0);
};

/**********************************************************************
 * convert_from_orig:
 * Returns a price, with an exchange rate applied to it.
 * Used to convert a given currency to a new currency.
 **********************************************************************/
double convert_from_orig(double a_price, double a_exchange_rate)
{
    return a_price * a_exchange_rate;
}

/**********************************************************************
 * convert_to_orig:
 * Returns a price in the original currency, with the
 * exchange rate no longer applied to it.
 **********************************************************************/
double convert_to_orig(double a_converted_price, double a_exchange_rate)
{
    return a_converted_price / a_exchange_rate;
}

// Before trade

/**********************************************************************
 * calculate_stoploss:
 * Calculates the stoploss.
 * Note:
 * Long
 * ----
 * amount selling at stoploss - amount at buying = initial risk of pool
 * (S.Pb + S.Pb.T + C) - (S.Ps - S.Ps.T - C) = R/100 * pool
 * Short
 * -----
 * amount selling - amount buying at stoploss = initial risk of pool
 * (S.Psl + S.Psl.T + C) - (S.Ps - S.Ps.T - C) = R/100 * pool
 **********************************************************************/
double calculate_stoploss(double a_price, int a_shares, double a_tax, double a_commission, double a_risk, double a_pool, int a_is_long)
{
    double l_numerator = 0.0;
    double l_denominator = 0.0;
    if (a_is_long == 1)
    {
        l_numerator = a_shares * a_price * (1.0 + a_tax / 100.0) - a_risk / 100.0 * a_pool + 2.0 * a_commission;
        l_denominator = a_shares * 1.0 - a_tax / 100.0;
    }
    else
    {
        l_numerator = a_risk / 100.0 * a_pool + a_shares * a_price * (1.0 - a_tax / 100.0) - 2.0 * a_commission;
        l_denominator = a_shares * 1.0 + a_tax / 100.0;
    }
    return l_numerator / l_denominator;
}

/**********************************************************************
 * calculate_risk_input:
 * Calculates the risk based on total pool and input.
 * Consider this the theoretical risk we want to take.
 **********************************************************************/
double calculate_risk_input(double a_pool, double a_risk)
{
    return a_risk / 100.0 * a_pool;
}

/**********************************************************************
 * calcculate_risk_initial:
 * Calculates the initial risk.
 * This is the risk we will take if our stoploss is reached.
 * This should be equal to the risk_input if everything was
 * correctly calculated.
 * Note:
 * Long
 * ----
 * S.Pb + S.Pb.T + C - (S.Psl - S.Psl.T - C)
 * Short
 * -----
 * S.Ps + S.Psl.T + C - (S.Ps - S.Ps.T - C)
 **********************************************************************/
double calculate_risk_initial(double a_price, int a_shares, double a_tax, double a_commission, double a_stoploss, int a_is_long)
{
    if (a_is_long)
        return a_shares * a_price * (1.0 + a_tax / 100.0) - a_shares * a_stoploss * (1.0 - a_tax / 100.0) + 2.0 * a_commission;
    else
        return a_shares * a_stoploss * (1.0 + a_tax / 100.0) - a_shares * a_price * (1.0 - a_tax / 100.0) + 2.0 * a_commission;
}

/**********************************************************************
 * calculate_amount:
 * Calculates the amount without tax and commission.
 **********************************************************************/
double calculate_amount(double a_price, int a_shares)
{
    return a_price * a_shares;
}

/**********************************************************************
 * Calculates the amount, including tax and commission.
 * Note:
 * -----
 * AMT = SP + SPT + C (buy)
 * AMT = SP - SPT - C (sell)
 **********************************************************************/
double calculate_amount_with_tax_and_commission(double a_price, int a_shares, double a_tax, double a_commission, transaction_type_t a_transaction_type)
{
    if (a_transaction_type == BUY)
        return a_shares * a_price + a_shares * a_price * a_tax + a_commission;
    else
        return a_shares * a_price - a_shares * a_price * a_tax - a_commission;
}

/**********************************************************************
 * calculate_amount_with_tax:
 * Calculates the amount (buy/sell) with tax included, but not the commission.
 * Note:
 * -----
 * profit_loss = S.P + S.P.T (buy)
 * profit_loss = S.P - S.P.T (sell)
 **********************************************************************/
double calculate_amount_with_tax(double a_price, int a_shares, double a_tax, transaction_type_t a_transaction_type)
{
    if (a_transaction_type == BUY)
        return a_shares * a_price * (1.0 - a_tax / 100.0);
    else
        return a_shares * a_price * (1.0 + a_tax / 100.0);
}

/**********************************************************************
 * cost_transaction:
 * Cost of transaction (tax and commission)
 **********************************************************************/
double cost_transaction(double a_price, int a_shares, double a_tax, double a_commission)
{
    return a_price * a_shares * a_tax / 100.0 + a_commission;
}

/*const
C_BINB00 = 'BINB00';
C_WHSI00 = 'WHSI00';
implementation
uses
Math;
{%REGION 'Before trade'}

{*******************************************************************************
Cost of tax (buy and sell)
*******************************************************************************}
function CostTax(a_amount, a_commission, a_shares, a_price: Double; a_transaction_type: TTransactionType): Double;
begin
if a_transaction_type = ttSell then
begin
Result := - a_amount - a_commission + a_shares * a_price;
end
else
begin
Result := a_amount - a_shares * a_price - a_commission;
end;
end;
{*******************************************************************************
Calculates the recommended amount of shares you can buy.
*******************************************************************************}
function CalculateSharesRecommended(a_pool, a_commission, a_tax, a_price: Double): Double;
begin
Result := (a_pool - (a_tax / 100.0 * a_pool) - a_commission) / a_price;
end;
{*******************************************************************************
Calculates the price when buying or selling.
*******************************************************************************}
function CalculatePrice(a_amount, a_shares, a_tax, a_commission: Double; a_transaction_type: TTransactionType): Double;
var
l_numerator, var_N: Double;
begin
if a_transaction_type = ttBuy then
begin
l_numerator := a_amount - a_commission;
l_denominator := (1.0 + a_tax / 100.0) * a_shares;
end
else
begin
l_numerator := a_amount + a_commission;
l_denominator := (1.0 - a_tax / 100.0) * a_shares;
end;
Result := l_numerator / l_denominator;
end;
{*******************************************************************************
Calculates the number of contracts to buy, according to an algorithm
that determines an ideal amount of leverage.
*******************************************************************************}
function CalculateLeveragedContracts(a_n: Integer): Integer;
begin
Result := Ceil(a_n / 3.0) - 1 + a_n;
end;
{%ENDREGION}
{%REGION 'After trade'}
{*******************************************************************************
Calculates the risk we actually took,
based on the data in TABLE_TRADE.
Note:
risk_actual = S.Pb + S.Pb.T + Cb - (S.Ps - S.Ps.T - Cs)
Note:
-----
It's the same for long and short.
*******************************************************************************}
function CalculateRiskActual(a_price_buy, a_shares_buy, a_tax_buy, a_commission_buy,
a_price_sell, a_shares_sell, a_tax_sell, a_commission_sell,
a_risk_initial, a_profit_loss: Double): Double;
begin
// TODO: DEFAULT_DECIMAL + abs?
if ((a_profit_loss < 0.0) and (abs(a_profit_loss) < a_risk_initial)) or (a_profit_loss >= 0.0) then
begin
Result := a_risk_initial;
end
else
begin
Result := a_shares_buy * a_price_buy * (1.0 + a_tax_buy / 100.0) - a_shares_sell * a_price_sell * (1.0 - a_tax_sell / 100.0) + a_commission_buy + a_commission_sell;
end;
end;
{*******************************************************************************
Function to calculate R-multiple.
*******************************************************************************}
function CalculateRMultiple(a_profit_loss, a_risk_initial: Double): Double;
begin
Result := a_profit_loss / a_risk_initial;
end;
{*******************************************************************************
Function to calculate the total cost associated with the given trade.
*******************************************************************************}
function CalculateCostTotal(a_tax_buy, a_commission_buy, a_tax_sell, a_commission_sell: Double): Double;
begin
//TODO: fix this: tax * amount_buy_simple !
Result := a_tax_buy / 100.0 + a_commission_buy + a_tax_sell / 100.0 + a_commission_sell;
end;
{*******************************************************************************
Calculates the profit_loss, without taking tax and commission into account.
Note:
-----
profit_loss = S.Ps - S.Pb
=> it's the same for long and short
*******************************************************************************}
function CalculateProfitLoss(a_price_buy, a_shares_buy, a_price_sell, a_shares_sell: Double): Double;
begin
Result := a_shares_sell * a_price_sell - a_shares_buy * a_price_buy;
end;
{*******************************************************************************
Calculates the total profit_loss.
Note:
-----
profit_loss = S.Ps - S.Ps.T - C - (S.Pb + S.Pb.T + C)
=> it's the same for long and short
*******************************************************************************}
function CalculateProfitLossTotal(a_price_buy, a_shares_buy, a_price_sell, a_shares_sell, a_tax_buy, a_tax_sell, a_commission_buy, a_commission_sell: Double): Double;
begin
Result := a_shares_sell * a_price_sell * (1.0 - a_tax_sell / 100.0) - a_shares_buy * a_price_buy * (1.0 - a_tax_buy / 100.0) - (a_commission_buy + a_commission_sell);
end;
{*******************************************************************************
Calculates other costs based on the difference that remains.
*******************************************************************************}
function CalculateCostOther(a_cost_total, a_profit_loss: Double): Double;
var
l_diff_cost_profit: Double;
begin
l_diff_cost_profit := a_cost_total - a_profit_loss;
if l_diff_cost_profit > 0.0 then
begin
Result := l_diff_cost_profit;
end
else
begin
Result := 0.0;
end;
end;*/
