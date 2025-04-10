#include <stdio.h>
#include "errors.h"
#include "command_line_input.h"

const RetVal err_codes;

/* Returns TRUE when positive, else FALSE*/
bool chk_positive(int value)
{
    return (value > 0) ? TRUE : FALSE;
}

/* Returns TRUE when positive, else FALSE*/
bool chk_non_negative(int value)
{
    return (value >= 0) ? TRUE : FALSE;
}

/* Check if the flag value follow the rules.
Returns TRUE if no rules are broken.
Returns FALSE and reprimand the user if a rule is broken */
bool chk_flag_value(int option_index)
{
    // if flag is not used, it's by default -1
    switch (option_index)
    {
    case TOTAL: // total
        if (!chk_non_negative(flag_values[option_index]))
        {
            fprintf(stderr, "Must provide a non-negative integer for total.\n");
            return FALSE;
        }
        break;

    case STEP: // step
        if (!chk_positive(flag_values[option_index]))
        {
            fprintf(stderr, "Must provide a positive integer for step.\n");
            return FALSE;
        }
        break;

    case LOWER: // lower
        if (!chk_non_negative(flag_values[option_index]))
        {
            fprintf(stderr, "Must provide a non-negative integer for lower.\n");
            return FALSE;
        }
        break;

    case UPPER: // upper
        if (!chk_non_negative(flag_values[option_index]) || flag_values[option_index] > 8)
        {
            fprintf(stderr, "Must provide an integer no larger than 8 for upper.\n");
            return FALSE;
        }
        break;

    default:
        break;
    }
    return TRUE;
}

/* Checks for missing inputs and additional rule.
Returns TRUE if no rules are broken.
Returns FALSE and reprimand the user if a rule is broken */
bool extra_flag_chk()
{
    // check for missing input
    for (int index = NO_VALUE_OPTIONS; index < TOTAL_OPTIONS; index++)
        if (chk_flag_value(index) == FALSE)
            return FALSE;

    // --lower is larger than --upper
    if (flag_values[LOWER] > flag_values[UPPER])
    {
        fprintf(stderr, "lower must be no larger than upper.\n");
        return FALSE;
    }

    return TRUE;
}

/* Reprimand user that board is not uniform. */
void not_rectangular()
{
    fprintf(stderr, "Board must be a rectangle.\n");
    return;
}
