/* See LICENSE.txt for license and copyright information. */
#pragma once

int ive_prepare_temp_file(
    const char *a_input_file,
    FILE *a_output_file,
    int a_start_year,
    int a_end_year,
    enum enum_plot_timeframe_t a_plot_timeframe_t
);

char *ive_get_full_cmd(
    enum enum_plot_timeframe_t a_enum_plot_timeframe_t,
    char *a_input_file,
    int a_current_year
);
