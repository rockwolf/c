/* See LICENSE.txt file for license info. */

#include <stdlib.h>
#include <stdio.h>
#include <libpq-fe.h>

#include "celinda.h"
#include "docopt.c"

#define MAX_INT               50
#define MAX_COL              256
#define HEADER_LENGTH         80

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

    // Set the connection
    conn = PQsetdb(dbhost, dbport, dboptions, dbtty, dbname);
    if (PQstatus(conn) == CONNECTION_BAD)
    {
        fprintf(stderr, db_err_conn1, dbname);
        fprintf(stderr, "%s", PQerrorMessage(conn));
        exit_on_error(conn);
    }

    // Get the main list
    db_result = get_main_list(conn);

    // Print the results
    print_header();
    print_list_data(db_result);
    
    PQclear(db_result);
    PQfinish(conn);

    // Enter new drawdown value for an id in the list
    printf("id = %d\n", input_drawdown_id());
    //update_drawdown(get_drawdown_id(), get_drawdown_value());

    return EXIT_SUCCESS;
}

/* Finish Postgresql actions, to exit in a clean way. */
void exit_on_error(PGconn *conn)
{
    PQfinish(conn);
    exit(EXIT_FAILURE);
}

/* Get the main list. */
PGresult get_main_list(PGconn *conn)
{
    PGresult *db_result;
    
    //TODO: add a limit to the query, based on a parameter
    // to e.g. only show the last <count> records.
    PQexec(conn, db_qry_sel1);
    if ((!db_result) || (PQresultStatus(db_result) != PGRES_TUPLES_OK))
    {
        //fprintf(stderr, db_err_qry1);
        fprintf(stderr, PQerrorMessage(db_result));
        PQclear(db_result);
        exit_on_error(conn);
    }
    return db_result;
}

/* Print output headers for main list. */
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
    for(i=0;i<HEADER_LENGTH;i++)
    {
        printf(msg_hdr_line);
    }
    printf("\n");
}

/* Print data for main list. */
void print_list_data(PGresult db_result)
{
    char var_id[MAX_COL];
    char var_long[MAX_COL];
    char var_market[MAX_COL];
    char var_stock_name[MAX_COL];
    char var_date[MAX_COL];
    char var_price[MAX_COL];
    char var_shares[MAX_COL];
    
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

/* Ask for the drawdown id (found in the main list). */
int input_drawdown_id()
{
    return get_input_int(msg_input1);
}

/* Ask for a new drawdown value. */
int input_drawdown_value()
{
    return get_input_int(msg_input2);
}

/* Ask for an integer in a safe way. */
int get_input_int(char *atext)
{
    char input[MAX_INT] = "";
    
    printf(atext);
    fgets(input, MAX_INT, stdin);
    printf("\n");
    return input == "" ? -1 : (int)input;
}

int update_drawdown(int drawdown_id, int new_value)
{
    PGresult db_result;
    //This ain't gonna work man...
    //TODO: db_qry_upd1 needs a where clause! Use drawdown_id to select, new_value to update.
    //See also celinda.h
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
