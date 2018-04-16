#ifndef __ABORGAN_SUDOKUIO__
#define __ABORGAN_SUDOKUIO__

void load_grid(char *file_path, grid_square **grid);
void print_grid(grid_square **grid);
void print_possible_values(grid_square square);
void print_all_possibilities_for_remaining_squares(grid_square **grid);

#endif
