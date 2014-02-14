/* See LICENSE.txt file for license info. */

void print_header();
void exit_on_error(PGconn *conn);
int input_drawdown_id();
int input_drawdown_value();
int get_input_int(char *atext);
int update_drawdown(int drawdown_id, int new_value);

static char *db_err_conn1 = "Connection to database \"%s\" failed.\n";
static char *db_qry_upd1 = "update t_set drawdown_current = %s";
static char *db_qry_sel1 =
    "SELECT t.trade_id, t.long_flag, m.name, s.name,"
    " coalesce(date_buy, date_sell) as date,"
    " coalesce(price_buy, price_sell) as price,"
    " coalesce(shares_buy, shares_sell) as shares"
    " FROM t_trade t"
    " inner join t_market m on t.market_id = m.market_id"
    " inner join t_commodity_name s on s.commodity_name_id = t.commodity_name_id"
    " ORDER BY t.trade_id";
static char *msg_input1 = "Enter trade_id to update (q to quit) [q]: ";
static char *msg_input2 = "Enter new value: ";
static char *msg_hdr1 = "id";
static char *msg_hdr2 = "long";
static char *msg_hdr3 = "market_code";
static char *msg_hdr4 = "commodity_name";
static char *msg_hdr5 = "date";
static char *msg_hdr6 = "price";
static char *msg_hdr7 = "shares";
static char *msg_hdr_line = "-";
static char *def_host = "localhost";
static char *def_database = "finance";
static char *def_port = "5432";
