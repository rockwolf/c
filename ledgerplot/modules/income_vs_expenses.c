/* See LICENSE file for copyright and license info. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ledgerplot.h"
#include "../c_generic/functions.h"
#include "../enum.h"
#include "income_vs_expenses.h"


static char *f_cmd_yearly =
    "ledger -f %s --strict bal --real -X EUR -s -p %d -d \"T&l<=1\" expenses income | grep -Eo '[-0-9][0-9\\.]{1,100}'";
static char *f_cmd_monthly =
    "ledger -f %s --strict bal --real -X EUR -s -p \"%s %d\" -d \"T&l<=1\" expenses income | grep -Eo '[-0-9][0-9\\.]{1,100}'";
// Note: substitute s with the month names january, february, etc. Define an enum or something for that.
// e.g. -p "may 2015"
// TODO: -b "startdate" -e "enddate"
//static char *f_cmd_income_vs_expenses_range =
//    "ledger -f %s --strict bal --real -X EUR -s -p %d -d \"T&l<=1\" expenses income | grep -Eo '[-0-9][0-9\\.]{1,100}'";


/*
 * prepare_temp_file:
 * This function prepares the data to be plotted,
 * in a temporary file that can be read by gnuplot.
 */
int ive_prepare_temp_file(
    char *a_input_file,
    FILE *a_output_file,
    int a_start_year,
    int a_end_year,
    enum enum_plot_timeframe_t a_plot_timeframe_t
)
{
    int l_records;
    int i;
    FILE *l_fp;
    char l_cmd[MS_INPUT_LINE];
    char l_line_temp[MS_INPUT_LINE];
    char l_line_input[MS_INPUT_LINE];
    char l_line_output[MS_INPUT_LINE]; /* The output line may be just as long. */
    double l_d1;
    double l_d2;
    double l_d3;
    char *l_tmp;
    char l_current_datetime[20];
    int l_current_year;

    l_records = (a_end_year - a_start_year) + 1;    
    l_current_year = a_start_year;
    for (i = 0; i < l_records; i++)
    {   
        if (i > 0)
            l_current_year++;
        l_cmd = ive_get_full_cmd(a_plot_timeframe_t, a_input_file, l_current_year); 
        l_fp = popen(l_cmd, "r");
        if (l_fp == NULL)
        {
            fprintf(stderr, "Could not execute ledger command.\n");
            exit(1);
        }

        *l_line_output = '\0';
        while (fgets(l_line_input, MS_INPUT_LINE, l_fp) != NULL)
        {
            *l_line_temp = '\0'; /* Make sure temp string is empty. */
            trim_whitespace(l_line_temp, l_line_input, MS_INPUT_LINE);
            if (strlen(l_line_output) <= 0)
            {
                sprintf(l_line_output, "%s", l_line_temp);
            }
            else
            {
                sprintf(l_line_output, "%s %s", l_line_output, l_line_temp);
            }
        }
        l_d1 = strtod(l_line_output, &l_tmp);
        l_d2 = -1.0 * strtod(l_tmp, &l_tmp); /* Income is the second number, it's
                                              * always negative in accounting.
                                              * Reverse for correct display in graph.
                                              */
        l_d3 = strtod(l_tmp, NULL);
        //printf("test: l_d1 = %.2f, l_d2 = %.2f, l_d3 = %.2f\n", l_d1, l_d2, l_d3);
        
        if (pclose(l_fp) == -1)
            fprintf(stderr, "Error reported by pclose().\n");
        
        /* Initialize tmp file */    
        if (i == 0) 
        {
            // TODO: move timestamp function in its own module.
            // TODO: make format an enum?
            timestamp(l_current_datetime, "%02d%02d%02d_%02d%02d%02d", sizeof(l_current_datetime));
            fprintf(a_output_file, "# Generated by ledgerplot %s on %s.\n", VERSION, l_current_datetime);
            fprintf(a_output_file, "year expenses income difference\n");
        }
        /* Write data to tmp file */
        fprintf(a_output_file, "%d %.2lf %.2lf %.2lf\n", l_current_year, l_d1, l_d2, l_d3); 
    }
    return 0;
}

char *ive_get_full_cmd(
    enum a_enum_plot_timeframe_t,
    char *a_input_file,
    int a_current_year
)
{
    char *l_result;
    switch(a_enum_plot_timeframe_t)
    {
        case daily:
            //sprintf(l_result, f_cmd_daiy, a_input_file, l_current_year);
            break;
        case weekly:
            //sprintf(l_result, f_cmd_weekly, a_input_file, l_current_year);
            break;
        case monthly:
            sprintf(l_result, f_cmd_monthly, a_input_file, l_current_year);
            break;
        else:
            sprintf(l_result, f_cmd_yearly, a_input_file, l_current_year);
    }
    return l_result;
}
