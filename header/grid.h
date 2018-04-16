#ifndef __ABORGAN_GRIDSQUARE__
#define __ABORGAN_GRIDSQUARE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ROWS 9
#define COLS 9

typedef struct grid_square {
	int value;
	int possible_values[10];
	bool solved;
}grid_square;

grid_square **init_grid();
void destroy_grid(grid_square **grid);
int get_num_possibilities(grid_square square);

int get_value(grid_square square);
void set_value(grid_square square, int value);
bool is_empty(grid_square square);

#endif
