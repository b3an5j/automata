#ifndef GRID_H
#define GRID_H

#include "typedefs.h"

#define MAX_ROW 10
#define MAX_COLUMN 10
#define NEIGHBOR_RANGE 2                       // [-1,1]
#define FIRST_ITER EVEN                        // first iteration is 0, uses grid_even
#define PREV_ITER (i % 2 == 0) ? ODD : EVEN    // see if previous iter is EVEN or ODD
#define CURRENT_ITER (i % 2 == 0) ? EVEN : ODD // see if current iter is EVEN or ODD
#define EVEN 0
#define ODD 1

extern bool grid_even[MAX_ROW][MAX_COLUMN];
extern bool grid_odd[MAX_ROW][MAX_COLUMN];
extern int grid_length;
extern int grid_width;

void print_grid(bool even_odd);
int count_neighbors(int column, int row, bool even_odd);
void give_life(int column, int row, bool even_odd);
void give_death(int column, int row, bool even_odd);

#endif