#ifndef __ABORGAN_SOLVER__
#define __ABORGAN_SOLVER__

void simple_elimination(grid_square **grid);
void simple_row_elimination(grid_square **grid, int row_num, int current_col);
void simple_column_elimination(grid_square **grid, int col_num, int current_row);
void simple_box_elimination(grid_square **grid, int current_row, int current_col);
void brute_force_solve(grid_square **grid);

bool brute_force_check(grid_square **grid, int row, int col);
bool fill_values(grid_square **grid);
bool fill_row(grid_square **grid, int row);
bool fill_col(grid_square **grid, int column);
bool fill_box(grid_square **grid, int row, int column);

bool done(grid_square **grid);
bool can_continue(grid_square **grid);

#endif
