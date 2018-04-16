#include "grid.h"

grid_square **init_grid() {
	grid_square **grid;
	if((grid = malloc(ROWS*sizeof(*grid))) == NULL) {
		printf("Error: not enough memory for Grid\n");
		exit(1);
	}

	for(int i = 0; i < ROWS; i++) {
		if((grid[i] = malloc(COLS*sizeof(**grid))) == NULL) {
			printf("Error: not enough memory for Grid\n");
			exit(1);
		} else {
			for(int j = 0; j < COLS; j++) {
				grid[i][j].solved = false;
				for(int k = 1; k < 10; k++) {
					grid[i][j].possible_values[k-1] = k;
				}
			}
		}
	}

	return grid;
}

void destroy_grid(grid_square **grid) {
	if(!grid) return;
	for(int i = 0; i < ROWS; i++) {
		if(grid[i]) free(grid[i]);
	}
	free(grid);
}

int get_num_possibilities(grid_square square) {
	int count = 0;
	for(int i = 0; i < 9; i++) {
		if(square.possible_values[i]) count++;
	}
	return count;
}

int get_value(grid_square square) { return square.value; }
void set_value(grid_square square, int value) { square.value = value; }
bool is_empty(grid_square square) { return square.value ? true:false; }
