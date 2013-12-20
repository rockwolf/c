#include <stdlib.h>
#include <stdio.h>
#include <libpq-fe.h>

#include "celinda.h"
#include "docopt.c"

void exit_on_error(PGconn *conn)
{
    PQfinish(conn);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    char *dbhost, *dbname, *dbport; 
    char *dboptions, *dbtty;
    PGconn *conn; 
    PGresult *db_result;
    
    DocoptArgs args = docopt(argc, argv, /* help */ 1, /* version */ "1.00");
    printf("--host == %s\n", args.host);
    printf("--database == %s\n", args.database);
    printf("--port == %s\n", args.port);
    
    dbhost = args.host ? args.host : def_host;
    dbport = args.port ? args.port : def_port;
    dbname = args.database ? args.database : def_database;
    dboptions = NULL;
    dbtty = NULL;

    conn = PQsetdb(dbhost, dbport, dboptions, dbtty, dbname);
    if (PQstatus(conn) == CONNECTION_BAD)
    {
        fprintf(stderr, db_err_conn1, dbname);
        fprintf(stderr, "%s", PQerrorMessage(conn));
        exit_on_error(conn);
    }

    db_result = PQexec(conn, db_qry_sel1);
    if ((!db_result) || (PQresultStatus(db_result) != PGRES_TUPLES_OK))
    {
        //fprintf(stderr, db_err_qry1);
        fprintf(stderr, PQerrorMessage(db_result));
        PQclear(db_result);
        exit_on_error(conn);
    }

    print_header();
    print_list_data(db_result);
    
    PQclear(db_result);
    PQfinish(conn);

    printf("id = %d\n", input_drawdown_id());
    //update_drawdown(get_drawdown_id(), get_drawdown_value());

    return EXIT_SUCCESS;
}

void print_header()
{
    printf("%-7s%-7s%-20s%-20s%-10s%-10s%-5s\n",
            msg_hdr1,
            msg_hdr2,
            msg_hdr3,
            msg_hdr4,
            msg_hdr5,
            msg_hdr6,
            msg_hdr7);
    for(i=0;i<80;i++)
    {
        printf(msg_hdr_line);
    }
    printf("\n");
}

void print_list_data(PGresult db_result)
{
    char var_id[256];
    char var_long[256];
    char var_market[256];
    char var_stock_name[256];
    char var_date[256];
    char var_price[256];
    char var_shares[256];
    
    int i, recordcount;
    
    recordcount = PQntuples(db_result);
    for(i = 0; i < recordcount; i++)
    {
        sprintf(var_id, "%s", PQgetvalue(db_result, i, 0));
        sprintf(var_long, "%s", PQgetvalue(db_result, i, 1));
        sprintf(var_market, "%s", PQgetvalue(db_result, i, 2));
        sprintf(var_commodity_name, "%s", PQgetvalue(db_result, i, 3));
        sprintf(var_date, "%s", PQgetvalue(db_result, i, 4));
        sprintf(var_price, "%s", PQgetvalue(db_result, i, 5));
        sprintf(var_shares, "%s", PQgetvalue(db_result, i, 6));
        printf("%-7s%-7s%-20s%-20s%-10s%-10s%-5s\n",
            var_id,
            var_long,
            var_market,
            var_commodity_name,
            var_date,
            var_price,
            var_shares);
    }
}

int input_drawdown_id()
{
    return get_input_int(msg_input1);
}

int input_drawdown_value()
{
    return get_input_int(msg_input2);
}

int get_input_int(char *atext)
{
    char input[256] = "";
    
    printf(atext);
    fgets(input, 256, stdin);
    printf("\n");
    return input == "" ? -1 : (int)input;
}

int update_drawdown(int drawdown_id, int new_value)
{
    PGresult db_result;
    //This ain't gonna work man...
    db_result = PQexec(conn, db_qry_upd1, (char *)drawdown_id);

    if ((!db_result) || (PQresultStatus(db_result) != PGRES_COMMAND_OK))
    {
        //fprintf(stderr, db_err_upd1);
        fprintf(stderr, PQerrorMessage(db_result));
        PQclear(db_result);
        exit_on_error(conn);
    }
    PQclear(db_result);
    return EXIT_SUCCESS;
}
