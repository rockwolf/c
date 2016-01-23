/* See LICENSE.txt for license and copyright information. */
#ifndef types_h__
#define types_h__

// Enum
typedef enum {BUY, SELL} transaction_type_t;
typedef struct
{
    int sp_shares;
    double sp_price;
} SharesPrice;

#endif  // types_h__
