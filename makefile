sudoku_solver: src/grid.c header/grid.h src/solver.c header/solver.h
	gcc -Wall -std=c99 -Iheader/ -o sudoku_solver src/solver.c src/grid.c src/sudoku_io.c src/sudoku_solver.c

clean:
	rm sudoku_solver header/*~ src/*~
