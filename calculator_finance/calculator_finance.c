/* See LICENSE.txt file for license and copyright information. */

#include "calculator_finance.h"

/**********************************************************************
 * Calculate what percentage a_value is from a_from_value.
 **********************************************************************/
double calculate_percentage_of(double a_value, double a_from_value)
{
  return (a_value / a_from_value * 100.0);
};

/**********************************************************************
 *  ConvertFromOrig:
 * Returns a price, with an exchange rate applied to it.
 * Used to convert a given currency to a new currency.
 **********************************************************************/
double convert_from_orig(double a_price, double a_exchange_rate)
{
    return a_price * a_exchange_rate;
}

/*function ConvertFromOrig(a_price, a_exchange_rate: Double): Double;
function ConvertToOrig(a_converted_price, a_exchange_rate: Double): Double;
{%ENDREGION}
{%REGION 'Before trade'}
function CalculateStoploss(a_price, a_shares, a_tax, a_commission, a_risk, a_pool: Double; a_is_long: Boolean): Double;
function CalculateRiskInput(a_pool, a_risk: Double): Double;
function CalculateRiskInitial(a_price, a_shares, a_tax, a_commission, a_stoploss: Double; a_is_long: Boolean): Double;
function CalculateAmount(a_price, a_shares: Double): Double;
function CalculateAmountWithTaxAndCommission(a_price, a_shares, a_tax, a_commission: Double; a_transaction_type: TTransactionType): Double;
function CalculateAmountWithTax(a_shares, a_price, a_tax: Double; a_transaction_type: TTransactionType): Double;
function CostTransaction(a_price, a_shares, a_tax, a_commission: Double): Double;
function CostTax(a_amount, a_commission, a_shares, a_price: Double; a_transaction_type: TTransactionType): Double;
function CalculateSharesRecommended(a_pool, a_commission, a_tax, a_price: Double): Double;
function CalculatePrice(a_amount, a_shares, a_tax, a_commission: Double; a_transaction_type: TTransactionType): Double;
function CalculateLeveragedContracts(a_n: Integer): Integer;
{%ENDREGION}
{%REGION 'After trade'}
function CalculateRiskActual(a_price_buy, a_shares_buy, a_tax_buy, a_commission_buy,
a_price_sell, a_shares_sell, a_tax_sell, a_commission_sell,
a_risk_initial, a_profit_loss: Double): Double;
function CalculateRMultiple(a_profit_loss, a_risk_initial: Double): Double;
function CalculateCostTotal(a_tax_buy, a_commission_buy, a_tax_sell, a_commission_sell: Double): Double;
function CalculateProfitLoss(a_price_buy, a_shares_buy, a_price_sell, a_shares_sell: Double): Double;
function CalculateProfitLossTotal(a_price_buy, a_shares_buy, a_price_sell, a_shares_sell, a_tax_buy, a_tax_sell, a_commission_buy, a_commission_sell: Double): Double;
function CalculateCostOther(a_cost_total, a_profit_loss: Double): Double;
{%ENDREGION}
const
C_BINB00 = 'BINB00';
C_WHSI00 = 'WHSI00';
implementation
uses
Math;
{%REGION 'Other'}
{*******************************************************************************
ConvertFromOrig:
Returns a price, with an exchange rate applied to it.
Used to convert a given currency to a new currency.
*******************************************************************************}
function ConvertFromOrig(a_price, a_exchange_rate: Double): Double;
begin
Result := a_price * a_exchange_rate;
end;
{*******************************************************************************
ConvertToOrig:
Returns a price in the original currency, with the
exchange rate no longer applied to it.
*******************************************************************************}
function ConvertToOrig(a_converted_price, a_exchange_rate: Double): Double;
begin
Result := a_converted_price / a_exchange_rate;
end;
{%ENDREGION}
{%REGION 'Before trade'}
{*******************************************************************************
Calculates the stoploss.
Note:
Long
----
amount selling at stoploss - amount at buying = initial risk of pool
(S.Pb + S.Pb.T + C) - (S.Ps - S.Ps.T - C) = R/100 * pool
Short
-----
amount selling - amount buying at stoploss = initial risk of pool
(S.Psl + S.Psl.T + C) - (S.Ps - S.Ps.T - C) = R/100 * pool
*******************************************************************************}
function CalculateStoploss(a_price, a_shares, a_tax, a_commission, a_risk, a_pool: Double; a_is_long: Boolean): Double;
var
l_numerator, l_denominator: extended;
begin
if is_long then
begin
l_numerator := a_shares * a_price * (1.0 + a_tax / 100.0) - a_risk / 100.0 * a_pool + 2.0 * a_commission;
l_denominator := a_shares * 1.0 - a_tax / 100.0;
end
else
begin
l_numerator := a_risk / 100.0 * a_pool + a_shares * a_price * (1.0 - a_tax / 100.0) - 2.0 * a_commission;
l_denomitator := a_shares * 1.0 + a_tax / 100.0;
end;
Result := l_numerator / l_denominator;
end;
{*******************************************************************************
Calculates the risk based on total pool and input.
Consider this the theoretical risk we want to take.
*******************************************************************************}
function CalculateRiskInput(a_pool, a_risk: Double): Double;
begin
Result := a_risk / 100.0 * a_pool;
end;
{*******************************************************************************
Calculates the initial risk.
This is the risk we will take if our stoploss is reached.
This should be equal to the risk_input if everything was
correctly calculated.
Note:
Long
----
S.Pb + S.Pb.T + C - (S.Psl - S.Psl.T - C)
Short
-----
S.Ps + S.Psl.T + C - (S.Ps - S.Ps.T - C)
*******************************************************************************}
function CalculateRiskInitial(a_price, a_shares, a_tax, a_commission, a_stoploss: Double; a_is_long: Boolean): Double;
begin
if a_is_long then
begin
Result := a_shares * a_price * (1.0 + a_tax / 100.0) - a_shares * a_stoploss * (1.0 - a_tax / 100.0) + 2.0 * a_commission;
end
else
begin
Result := a_shares * a_stoploss * (1.0 + a_tax / 100.0) - a_shares * a_price * (1.0 - a_tax / 100.0) + 2.0 * a_commission;
end;
end;
{*******************************************************************************
Calculates the amount without tax and commission.
*******************************************************************************}
function CalculateAmount(a_price, a_shares: Double): Double;
begin
Result := a_price * a_shares;
end;
{*******************************************************************************
Calculates the amount, including tax and commission.
Note:
-----
AMT = SP + SPT + C (buy)
AMT = SP - SPT - C (sell)
*******************************************************************************}
function CalculateAmountWithTaxAndCommission(a_price, a_shares, a_tax, a_commission: Double; a_transaction_type: TTransactionType): Double;
begin
if a_transaction_type = ttBuy then
begin
Result := a_shares * a_price + a_shares * a_price * a_tax + commission;
end
else
Result := a_shares * a_price - a_shares * a_price * a_tax - a_commission;
begin
end;
end;
{*******************************************************************************
Calculates the amount (buy/sell) with tax included, but not the commission.
Note:
-----
profit_loss = S.P + S.P.T (buy)
profit_loss = S.P - S.P.T (sell)
*******************************************************************************}
function CalculateAmountWithTax(a_shares, a_price, a_tax: Double; a_transaction_type: TTransactionType): Double;
begin
if a_transaction_type = ttBuy then
begin
Result := a_shares * a_price * (1.0 - a_tax / 100.0);
end
else
begin
Result := a_shares * a_price * (1.0 + a_tax / 100.0);
end;
end;
{*******************************************************************************
Cost of transaction (tax and commission)
*******************************************************************************}
function CostTransaction(a_price, a_shares, a_tax, a_commission: Double): Double;
begin
Result := a_shares * a_price * a_tax + a_commission;
end;
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
