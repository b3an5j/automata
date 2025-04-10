#include <stdio.h>
#include "command_line_input.h"
#include "grid.h"

// GLOBALS
/* To avoid copying here and there, use 2 grids alternately. */
bool grid_even[MAX_ROW][MAX_COLUMN]; // the grid for even iterations
bool grid_odd[MAX_ROW][MAX_COLUMN];  // the grid for odd iterations
int grid_length = 0;
int grid_width = 0;

// FUNCTION DECLARATIONS
/* Prints the state of board */
void print_grid(bool even_odd)
{
    bool (*grid)[10] = (even_odd) ? grid_odd : grid_even; // pointer to which grid
    for (int i = 0; i < grid_length; i++)
    {
        for (int j = 0; j < grid_width; j++)
        {
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }

    return;
}

/* Count 8 neighboring cells for living neighbors */
int count_neighbors(int column, int row, bool even_odd)
{
    bool (*grid)[10] = (even_odd) ? grid_odd : grid_even; // pointer to which grid we read from
    int neighbors = 0;
    int neighbor_x, neighbor_y;

    // start from top left, left to right,
    // then next row etc, ends at bottom right.
    for (int i = -1; i < NEIGHBOR_RANGE; i++)
    {
        for (int j = -1; j < NEIGHBOR_RANGE; j++)
        {
            // no wrap by default
            neighbor_x = column + j;
            neighbor_y = row + i;

            if (flag_values[WRAP] == 1) // wrap
            {
                // must add grid_width or grid length to avoid negatives for it to work
                // ex: row -1 should wrap as last row; without adding grid_length, it will return 1st row
                neighbor_x = (neighbor_x + grid_width) % grid_width;
                if ((grid_length == 1) && (neighbor_y != 0)) // disallow one line cells to do up down wrapping
                    continue;
                neighbor_y = (neighbor_y + grid_length) % grid_length;
            }

            // ignore out of bounds cells, counts as dead
            // (for no wrap, but no effect to wrap, since board wrapping yields non-negative cordinates)
            if (neighbor_x < 0 || neighbor_y < 0)
                continue;

            if (grid[neighbor_y][neighbor_x] == TRUE)
                neighbors++;
        }
    }
    return (grid[row][column]) ? neighbors - 1 : neighbors; // exclude the living cell
}

/* Give life to cell if enough neighbors are alive */
void give_life(int column, int row, bool even_odd)
{
    bool (*grid)[10] = (even_odd) ? grid_odd : grid_even;
    grid[row][column] = TRUE;
    return;
}

/* Kill cell if not enough or too many neighbors are alive*/
void give_death(int column, int row, bool even_odd)
{
    bool (*grid)[10] = (even_odd) ? grid_odd : grid_even;
    grid[row][column] = FALSE;
    return;
}