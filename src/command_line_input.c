#include <stdio.h>
#include "errors.h"
#include "grid.h"
#include "command_line_input.h"

// GLOBALS
const Flag flags;
/* added '=' to make string comparing easier,
intentionally put the "no value" flags in front to ease searching for "need value" flag indices (using NO_VALUE_OPTIONS macro) */
const char *short_flags[TOTAL_OPTIONS] = {"w", "t=", "s=", "l=", "u="};
const char *long_flags[TOTAL_OPTIONS] = {"wrap", "total=", "step=", "lower=", "upper="};
int flag_values[TOTAL_OPTIONS]; // stores the values extracted from the flags, -1 is not used, -2 means bad value (to make debugging easier)

// FUNCTION DEFINITIONS
/* Read input from argv: flags, argument for grid.
Returns 0 when success.
Returns 1 when encountering bad inputs.*/
int take_input(int argc, char **argv)
{
    // set flags_values all to -1 (not used by default)
    for (int i = 0; i < TOTAL_OPTIONS; i++)
        flag_values[i] = -1;

    // go through the arguments
    for (int i = 1; i < argc; i++)
    {
        /* Flag Options */
        if (FIRST_CHAR == '-')
        {
            // first cell telling if arg is a valid option, -1 being invalid, and [0 - 4] being valid (index of the option in the flag array)
            // second cell telling where to read the numbers next
            int result_buffer[2] = {0};

            /* Long Options */
            if (SECOND_CHAR == '-')
            {
                // run through the valid long option flags
                // start from the third char (first and second are '-')
                is_option(&THIRD_CHAR, long_flags, result_buffer);
                result_buffer[1]++; // add 1 to char index since we have two '-'

                if ((OPTION_INDEX >= 0) && (OPTION_INDEX / TOTAL_OPTIONS) == 0) // precaution, check if in range of valid options
                {
                    // make error to avoid collision with repeated flags
                    if (flag_values[OPTION_INDEX] != -1)
                        return BAD_INPUT;

                    // extract value from flag (that needs input value)
                    if (OPTION_INDEX >= NO_VALUE_OPTIONS)
                        flag_values[OPTION_INDEX] = atoi(argv[i], result_buffer[1]);
                    // flags without value
                    else
                        flag_values[OPTION_INDEX] = 1;

                    // if still -1 means bad input
                    if (flag_values[OPTION_INDEX] == -1)
                        flag_values[OPTION_INDEX] = -2;

                    if (chk_flag_value(OPTION_INDEX) == FALSE)
                        return BAD_INPUT;
                }

                // invalid input (not in the flags list)
                else
                    return BAD_INPUT;
            }

            /* Short Options */
            else
            {
                // run through the valid short option flags
                // start from the second char (first is '-')
                is_option(&SECOND_CHAR, short_flags, result_buffer);

                if ((OPTION_INDEX >= 0) && (OPTION_INDEX / TOTAL_OPTIONS) == 0) // precaution, check if in range of valid index
                {
                    // make error to avoid collision with repeated flags
                    if (flag_values[OPTION_INDEX] != -1)
                        return BAD_INPUT;

                    // extract value from flag (that needs input value)
                    if (OPTION_INDEX >= NO_VALUE_OPTIONS)
                        flag_values[OPTION_INDEX] = atoi(argv[i], result_buffer[1]);
                    // flags without value
                    else
                        flag_values[OPTION_INDEX] = 1;

                    // if still -1 means bad input
                    if (flag_values[OPTION_INDEX] == -1)
                        flag_values[OPTION_INDEX] = -2;

                    if (chk_flag_value(OPTION_INDEX) == FALSE)
                        return BAD_INPUT;
                }

                // invalid input (not in the flags list)
                else
                    return BAD_INPUT;
            }
        }

        /* Input of Grid */
        else // if ((FIRST_CHAR == '0') || (FIRST_CHAR == '1'))
        {
            // go through the sequence
            int char_index = 0;
            int row = 0;
            int column = 0;

            char c = FIRST_CHAR;
            // no need to check for invalid characters
            while (c != '\0')
            {
                // no need to worry about overflows
                // do nothing when c == '0'; grids was initialised to contain all 0
                if (c == '0')
                    column++;

                else if (c == '1')
                    grid_even[row][column++] = 1;

                else if (c == '/')
                {
                    // check if grid length is uniform
                    // no need to increment column, because each encounter with '0' or '1' increments it
                    if (column > grid_width && row == 0) // first row, set the width
                        grid_width = column;
                    else if (column != grid_width)
                    {
                        not_rectangular();
                        return BAD_INPUT;
                    }

                    row++;
                    column = 0;
                }

                // update c as next character
                c = argv[i][++char_index];
            }

            // let one line cells live, but no wrapping up and down allowed later
            if (row == 0)
                grid_width = column;

            // increment is needed as encountering '/' n times, we have n+1 rows
            grid_length = ++row;

            // last check if grid is uniform and has width and has width
            if ((column != grid_width) || (grid_width == 0))
            {
                not_rectangular();
                return BAD_INPUT;
            }
        }
    }

    //  in case user skip flag, and additional checks
    if (extra_flag_chk() == FALSE)
        return BAD_INPUT;

    return SUCCESS;
}

/* Compares flag from input to the valid flags.
Returns 0 if strings are different.
Returns 1 if they're the same. */
int arg_strcmp(const char *arg, const char *option, int *result_buffer)
{
    int index = 0;
    while (1)
    {
        // if different, return 0
        if (arg[index] != option[index])
            return 0;

        // if same at till '=' or terminating null, set result_buffer[1] to index of next character after '=' or '\0', return 1
        /*
        No need to check if it's the same with option[index], already checked above
        Comparisons are evaluated from left to right until one is true, place '=' in front because many of the options use '='
        If the option has reached '=' or '\0', this means every char in front is the same with the option
        */
        if ((arg[index] == '=') || (arg[index] == '\0'))
        {
            result_buffer[1] = index + 2; // implicit '-' + moving one to the next character
            return 1;
        }

        index++;
    }
}

/* Checks if user's input option is in flags list.
Sets result_buffer[0] (option index) to be the index if the flag in flags list (TRUE).
Else, sets result_buffer[0] (option index) to be -1 (FALSE). */
void is_option(const char *str, const char **str_list, int *result_buffer)
{
    for (int i = 0; i < TOTAL_OPTIONS; i++)
    {
        if (arg_strcmp(str, str_list[i], result_buffer))
        {
            result_buffer[0] = i;
            return;
        }
    }

    result_buffer[0] = -1;
    return;
}

/* Converts string to int.
Returns the converted string as integer.
Returns -1 if string starts with -, implying negative number or non numeric */
int atoi(char *flag, int char_index)
{
    int n = 0;

    // MUST not be negative sign
    if (flag[char_index] == '-')
        return -1;

    // skip positive sign
    if (flag[char_index] == '+')
        char_index++;

    while (flag[char_index] != '\0')
    {
        // characters MUST be numeric
        if (flag[char_index] < '0' || flag[char_index] > '9')
            return -1;

        n *= 10;
        n += (flag[char_index] - '0');
        char_index++;
    }

    return n;
}
