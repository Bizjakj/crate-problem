#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct max{
	int *row;
	int *col;
	int *rowDup;
	int *colDup;
};

int main()
{
	int row, col;
	cin >> row;
	cin >> col;
	int **grid = new int*[row];
	for (int i = 0; i < row; i++)	//make 2d array to hold grid
		grid[i] = new int[col];

	for (int i = 0; i < row; i++) {		//fill grid from user input
		for(int j = 0; j < col; j++){
			cin >> grid[i][j];
		}
	}

	struct max max;
	max.row = new int[row];		//arrays to store max of each row
	max.col = new int[col];
	max.rowDup = new int[row];	//arrays to show if a column has already been combined, could be bools
	max.colDup = new int[col];

	for (int i = 0; i < row; i++) {	//initialize arrays to 0
		max.row[i] = 0;
		max.rowDup[i] = 0;
	}
	for (int j = 0; j < col; j++) {
		max.col[j] = 0;
		max.colDup[j] = 0;
	}

	int crates = 0;
	int occsquares = 0;
	for (int i = 0; i < row; i++) {		//find max of each row/column and sum up all grid elements
		for (int j = 0; j < col; j++) {
			if (grid[i][j] > 0) {
				occsquares++;
			}
			crates += grid[i][j];
			if (grid[i][j] > max.row[i]) {
				max.row[i] = grid[i][j];
			}
			if (grid[i][j] > max.col[j]) {
				max.col[j] = grid[i][j];
			}

		}
	}

	int sum = occsquares;
	for (int i = 0; i < row; i++) {	//after this, sum = num squares that have at least 1 crate + sum of all the columns max, + sum of all rows max
									//we now subtract each row/col we can combine
		sum += max.row[i] - 1;
	}
	for (int j = 0; j < col; j++) {
		sum += max.col[j] - 1;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			//checks if we can combine, this is based off row and column being the same max, neither already having been combined,
			//and the square starting with at least 1 crate so top view wont change if we combine them
			if (max.row[i] == max.col[j] && max.rowDup[i] == 0 && max.colDup[j] == 0 && grid[i][j] != 0) {
				sum -= max.row[i] - 1;
				max.rowDup[i] = 1;
				max.colDup[j] = 1;
			}
		}
	}
	//sum is now lowest amount of crates to preserve image, so crates-sum is the answer
	cout << crates - sum << endl;
	
	return 0;
}
