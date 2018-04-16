#include "grid.h"
#include "solver.h"
#include "sudoku_io.h"

void load_grid(char *file_path, grid_square **grid) {
	FILE *fp = fopen(file_path, "r");
	int row = 0;
	char line[12];

	if(!fp) {
		printf("Error opening file");
		exit(1);
	}
	while(fgets(line, 12, fp) != NULL) {
		for(int i = 0; i < COLS; i++) {
			grid[row][i].value = line[i]-'0';
			if(grid[row][i].value != 0) {
				for(int j = 0; j < 9; j++) {
					if(grid[row][i].value != grid[row][i].possible_values[j])
						grid[row][i].possible_values[j] = 0;
				}
			}
		}
		row+=1;
	}

	fclose(fp);
}

void print_grid(grid_square **grid) {
	printf("printing grid\n");
	printf("----------------------------------------\n");
	for(int i = 0; i < 9; i++) {	
		if(i%3 == 0) {
			printf("| - - - | - - - | - - - |\n");
		}
		for(int j = 0; j < 9; j++) {
			if(j%3 == 0) {
				printf("| ");
			}
			if(grid[i][j].value) {
				printf("%d ", grid[i][j].value);
			} else {
				printf(". ");
			}
			if(j == 8) {
				printf("|");
			}
		}
		printf("\n");
		if(i == 8) {	
			printf("| - - - | - - - | - - - |\n");
		}
	}
	printf("----------------------------------------\n");
}

void print_possible_values(grid_square square) {
	printf("num_possible_values: %d, possible values: ", get_num_possibilities(square));
	for(int i = 0; i < 9; i++) {
		if(square.possible_values[i]) {
			printf("%d ", square.possible_values[i]);
		}
	}
	printf("\n");
}

void print_all_possibilities_for_remaining_squares(grid_square **grid) {
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS; j++) {
			if(!grid[i][j].value) {
				printf("[%d][%d]: ", i, j);
				print_possible_values(grid[i][j]);
			}
		}
	}
}

