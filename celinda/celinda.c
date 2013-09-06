#include <stdlib.h>
#include <stdio.h>
#include <libpq-fe.h>

void exit_nicely(PGconn *conn)
{
    PQfinish(conn);
    exit(1);
}

int main(int argc, char *argv[])
{
    char *dbhost, *dbport, *dboptions, *dbtty;
    char *dbname;
    
    char name[256];

    int i, recordcount;

    PGconn *conn;
    PGresult *result;

    dbhost = "testdb";
    dbport = NULL;
    dboptions = NULL;
    dbtty = NULL;
    dbname = "finance";

    conn = PQsetdb(dbhost, dbport, dboptions, dbtty, dbname);
    if (PQstatus(conn) == CONNECTION_BAD)
    {
        fprintf(stderr, "Connection to database \"%s\" failed.\n", dbname);
        fprintf(stderr, "%s", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    result = PQexec(conn, "SET DateStyle = 'European'");

    if ((!result) || (PQresultStatus(result) != PGRES_COMMAND_OK))
    {
        fprintf(stderr, "SET command failed\n");
        PQclear(result);
        exit_nicely(conn);
    }
    PQclear(result);

    result = PQexec(conn,
        "SELECT t.trade_id, t.long_flag, m.name, s.name,"
        " coalesce(date_buy, date_sell) as date,"
        " coalesce(price_buy, price_sell) as price,"
        " coalesce(shares_buy, shares_sell) as shares"
        " FROM t_trade t"
        " inner join t_market m on t.market_id = m.market_id"
        " inner join t_stock_name s on s.stock_name_id = t.stock_name_id"
        " ORDER BY t.trade_id"
    );
    if ((!result) || (PQresultStatus(result) != PGRES_TUPLES_OK))
    {
        fprintf(stderr, "SELECT command did not return tuples properly\n");
        PQclear(result);
        exit_nicely(conn);
    }

    printf("%-7s%-7s%-20s%-20s%-10s%-10s%-5s\n", "id", "long", "market", "stock_name", "date", "price", "shares");
    for(i=0;i<80;i++)
    {
        printf("-");
    }
    printf("\n");

    recordcount = PQntuples(result);

    for(i = 0; i < recordcount; i++)
    {
        sprintf(name, "%s", PQgetvalue(result, i, 0));
        printf("%-5s%-20s%-20s\n", name, PQgetvalue(result, i, 1), PQgetvalue(result, i, 2));
    }

    PQclear(result);

    PQfinish(conn);

    return EXIT_SUCCESS;
}
