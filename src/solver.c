
#include "grid.h"
#include "sudoku_io.h"
#include "solver.h"

void simple_elimination(grid_square **grid) {
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS; j++) {
			simple_row_elimination(grid, i, j);
			simple_column_elimination(grid, j, i);
			simple_box_elimination(grid, i, j);
		}
	}
}

void simple_row_elimination(grid_square **grid, int row_num, int current_col) {
	if(grid[row_num][current_col].value) return;
	for(int i = 0; i < COLS; i++) {
		if(grid[row_num][i].value != 0) {
			if(grid[row_num][current_col].possible_values[grid[row_num][i].value-1])
				grid[row_num][current_col].possible_values[grid[row_num][i].value-1] = 0;
		}
	}
}

void simple_column_elimination(grid_square **grid, int col_num, int current_row) {
	if(grid[current_row][col_num].value) return;
	for(int i = 0; i < ROWS; i++) {
		if(grid[i][col_num].value != 0) {	
			if(grid[current_row][col_num].possible_values[grid[i][col_num].value-1]) 
				grid[current_row][col_num].possible_values[grid[i][col_num].value-1] = 0;
		}
	}
}

void simple_box_elimination(grid_square **grid, int current_row, int current_col) {
	int box_row = current_row/3;
	int box_col = current_col/3;

	if(grid[current_row][current_col].value) return;
	for(int i = box_row*3; i < box_row*3+3; i++) {
		for(int j = box_col*3; j < box_col*3+3; j++) {
			if(grid[i][j].value != 0) {
				if(grid[current_row][current_col].possible_values[grid[i][j].value-1])
					grid[current_row][current_col].possible_values[grid[i][j].value-1] = 0;
			}
		}
	}
}

bool fill_values(grid_square **grid) {
	bool did_fill = false;
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS; j++) {
			if(get_num_possibilities(grid[i][j]) == 1 && !grid[i][j].value) {
				for(int k = 0; k < 9; k++) {
					if(grid[i][j].possible_values[k]) {
						grid[i][j].value = grid[i][j].possible_values[k];
						grid[i][j].solved = true;
						did_fill = true;
						break;
					}
				}
			}
		}
	}
	return did_fill;
}

bool fill_row(grid_square **grid, int row) {
	bool did_fill = false;
	for(int i = 0; i < 9; i++) {
		int count = 0;
		int index = 0;
		for(int j = 0; j < COLS; j++) {
			if(grid[row][j].possible_values[i] && !grid[row][j].value) {
				index = j;
				count++;
			}
		}
		if(count == 1) {
			for(int k = 0; k < 9; k++) {
				if(k == i) {
					grid[row][index].value = i+1;
					grid[row][index].solved = true;
					did_fill = true;
				}
				else
					grid[row][index].possible_values[k] = 0;
			}
		}
	}
	return did_fill;
}

bool fill_col(grid_square **grid, int col) {
	bool did_fill = false;
	for(int i = 0; i < 9; i++) {
		int count = 0;
		int index = 0;
		for(int j = 0; j < ROWS; j++) {
			if(grid[j][col].possible_values[i] && !grid[j][col].value) {
				index = j;
				count++;
			}
		}
		if(count == 1) {
			for(int k = 0; k < 9; k++) {
				if(k == i) {
					grid[index][col].value = i+1;
					grid[index][col].solved = true;
					did_fill = true;
				}
				else
					grid[index][col].possible_values[k] = 0;
			}
		}
	}
	return did_fill;
}

bool fill_box(grid_square **grid, int row, int col) {
	bool did_fill = false;
	for(int i = 0; i < 9; i++) { 
		int count = 0;
		int row_index = 0;
		int col_index = 0;
		for(int j = row*3; j < row*3+3; j++) {
			for(int k = col*3; k < col*3+3; k++) {
				if(grid[j][k].possible_values[i] && !grid[j][k].value) {
					row_index = j;
					col_index = k;
					count++;
				}
			}
		}
		if(count == 1) {
			for(int l = 0; l < 9; l++) {
				if(l == i) {
					grid[row_index][col_index].value = i+1;
					grid[row_index][col_index].solved = true;
					did_fill = true;
				}
				else
					grid[row_index][col_index].possible_values[l] = 0;
			}
		}
	}
	return did_fill;
}

void brute_force_solve(grid_square **grid) {
	int row = 0;
	int col = 0;
	int count = 0;
	while(!done(grid)) {
		if(grid[row][col].value < 9 && !grid[row][col].solved) {
			printf("value: %d\n", grid[row][col].value);
			grid[row][col].value++;
		}
		if(brute_force_check(grid, row, col)) {
			if(col < COLS-1) {
				col++;
			} else if(col == COLS && row < ROWS) {
				col = 0;
				row++;
			}
		} else {
			if(grid[row][col].value < 9) {
				continue;
			} else {
				if(col > 0) {
					col-=1;
				} else if(col == 0 && row > 0) {
					row-=1;
					col = 8;
				} else {
					printf("ERROR: something weird happened\n");
					destroy_grid(grid);
					exit(1);
				}
			}
		}

		count++;
		if(count % 1 == 0) {
			print_grid(grid);
		}
	}
}

bool brute_force_check(grid_square **grid, int row, int col) {
	int box_row = (row/3)*3;
	int box_col = (col/3)*3;
	//row check
	for(int i = 0; i < ROWS; i++) {
		if(i == col) continue;
		if(grid[row][i].value == grid[row][col].value) return false;
	}
	//col check
	for(int i = 0; i < COLS; i++) {
		if(i == row) continue;
		if(grid[i][col].value == grid[row][col].value) return false;
	}
	//box check
	for(int i = box_row*3; i < (box_row*3)+3; i++) {
		for(int j = box_col*3; j < (box_col*3)+3; j++) {
			if(i == row && j == col) continue;
			if(grid[i][j].value == grid[row][col].value) return false;
		}
	}
	return true;
}


bool done(grid_square **grid) {
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS; j++) {
			if(!grid[i][j].value) return false;
		}
	}
	return true;
}

bool can_continue(grid_square **grid) {
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS; j++) {
			if(get_num_possibilities(grid[i][j]) == 1 && !grid[i][j].value)
				return true;
		}
	}
	return false;
}


