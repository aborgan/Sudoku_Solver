#include "grid.h"
#include "sudoku_io.h"
#include "solver.h"

int main(int argc, char *argv[]) {

	grid_square **grid;
	int num_loops = 0;
	int filled = 0;

	if(argc != 2) {
		printf("incorrect number of command line arguments.  Run with -h for help\n");
		return 1;
	} else if(!strcmp(argv[1], "-h")) {
		printf("Run the program with ./solver <path_to_file> where the file path contains a 9x9 grid of numbers with a sudoku grid to solve (0 means empty)\n");
		return 0;
	}

	
	grid = init_grid();
	load_grid(argv[1], grid);
	simple_elimination(grid);
	while(!done(grid)) {
		filled = 0;
		simple_elimination(grid);
		for(int i = 0; i < 9; i++) {
			simple_elimination(grid);
			if(fill_row(grid, i)) {
			       	filled++;
			}
			simple_elimination(grid);
			if(fill_col(grid, i)) {
				filled++;
			}
		}
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				simple_elimination(grid);
				if(fill_box(grid, i, j)) {
					filled++;
				}
			}
		}
		simple_elimination(grid);
		if(fill_values(grid)) {
			filled++;
		}
		if(!filled) {
			printf("too hard!\n");
			exit(1);
		}
		num_loops++;
		printf("num_filled; %d\n", filled);
		print_grid(grid);
	}
	//brute_force_solve(grid);
	print_grid(grid);
	//printf("it took %d times through the algorithm to solve the sudoku\n", num_loops);
	destroy_grid(grid);
	return 0;
}

