//OPERATING SYSTEMS - SOFE 3950U - LAB 3
//CRN 74025
//GROUP 6

//GROUP MEMBERS - ROHAN RADADIYA (100704614), SIBI SABESAN (100750081), SYED AIRAJ HUSSAIN (100789134)

// libraries utilized within the laboratory project.
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


// Defines the number of threads, more than the required amount.
#define thread_number 28

// Defines a structure to hold parameters for the threads utilized in the project.
typedef struct {
	// Defines the row index.
	int row; 
	// Defines the column index.
	int column;
} 

parameters;

// Defines the Sudoku puzzle
// Sudoku values and inputs are given here. If need to change, they are changed here in the source file.
int sudoku[9][9] = 
{
	{5, 3, 4, 6, 7, 8, 9, 1, 2},
	{6, 7, 2, 1, 9, 5, 3, 4, 8},
	{1, 9, 8, 3, 4, 2, 5, 6, 7},
	{8, 5, 9, 7, 6, 1, 4, 2, 3},
	{4, 2, 6, 8, 5, 3, 7, 9, 1},
	{7, 1, 3, 9, 2, 4, 8, 5, 6},
	{9, 6, 1, 5, 3, 7, 2, 8, 4},
	{2, 8, 7, 4, 1, 9, 6, 3, 5},
	{3, 4, 5, 2, 8, 6, 1, 7, 9}
};

// Array to check validity of rows, columns, and subgrids
int validityCheck[thread_number] = {0};

// Function to print the Sudoku puzzle
void *printPuzzle(){
	// Iterates over each cell in the puzzle
	for (int i = 0; i < 9; i++){
		// Prints a horizontal separator for every third row. (Used to design the output given to the user)
		if(i!=0 && i%3==0)
			printf("\n- - - - - - - - - - - - - - -\n");
		// Print an empty line for every first row or after each block of 3 rows (Used to design the output given to the user)
		else if(i==0)
			printf("\n\n");
		else
			printf("\n         |         |         \n"); // Print a vertical separator for each block of 3 columns (Used to design the output given to the user)

		// Iterate over each cell in the current row
		for (int j = 0; j < 9; j++){	
			// Prints a vertical separator for every third column (Used to design the output given to the user)
			if(j!=0 && j%3==0){
				printf("|");
			}
			// Prints the value of the cell
			printf(" %d ", sudoku[i][j]);
		}
	}
	
	//Gives the output after some space of blank lines
	printf("\n");	
	printf("\n");	
	printf("\n");	
	pthread_exit(NULL);
}

// Function to check the validity of a row
void *checkRow(void *param){
	// Get parameters from the passed argument
	parameters *params = (parameters*) param;
	int row = params->row; // Row index
	int col = params->column; // Column index		

	// Checks if the column index is not 0 or if the row index is out of bounds
	if (col != 0 || row > 8){
		printf("There seems to be an invalid row or column input.\nRow:%d, Col:%d\n", row, col);
		pthread_exit(NULL);
	}

	int num_exists_in_puzzle[9] = {0}; // Array to track the presence of numbers in the row

	// Iterate over each cell in the row
	for (int i = 0; i < 9; i++){
		int num = sudoku[row][i]; // Get the value of the cell

		// Check for invalid entries
		if (num < 1 || num > 9){
			printf("There seems to be an invalid entry... (Row:%d, Col:%d)\n", row, i);
			pthread_exit(NULL);
		}
		// Check for repeated values in the row
		else if(num_exists_in_puzzle[num - 1] == 1) {
			printf("There seems to be one or more repeated value found in row... (Row:%d)\n", row);
			pthread_exit(NULL);
		}
		else {
			num_exists_in_puzzle[num - 1] = 1; // Mark the number as found		
		}
	}

	validityCheck[9 + row] = 1; // Mark the row as valid
	pthread_exit(NULL);
}

// Function to check the validity of a column
void *checkColumn(void* param){
	// Get parameters from the passed argument
	parameters *params = (parameters*) param;
	int row = params->row; // Row index
	int col = params->column; // Column index		

	// Check if the row index is not 0 or if the column index is out of bounds
	if (row != 0 || col > 8){
		// Invalid output
		printf("There seems to be an invalid row or column input.\nRow:%d, Col:%d\n", row, col);
		pthread_exit(NULL);
	}
	
	int num_exists_in_puzzle[9] = {0}; // Array to track the presence of numbers in the column

	// Iterate over each cell in the column
	for (int i = 0; i < 9; i++){
		int num = sudoku[i][col]; // Get the value of the cell

		// Check for invalid entries
		if (num < 1 || num > 9){
			// Output for invalidity
			printf("There seems to be an invalid entry... (Row:%d, Col:%d)\n", i, col);
			pthread_exit(NULL);
		} 
		// Check for repeated values in the column
		else if(num_exists_in_puzzle[num - 1] == 1) {
			// Output for invalidity
			printf("We seem to have found a repeated value found in column... (Col:%d)\n", col);
			pthread_exit(NULL);
		} 
		else {
			num_exists_in_puzzle[num - 1] = 1; // Mark the number as found		
		}
	}

	// Marks the column as valid
	validityCheck[18 + col] = 1; 
	pthread_exit(NULL);
}

// Function to check the validity of each subgrid
void *checkEachSubGrid(void* param){
	// Get parameters from the passed argument
	parameters *params = (parameters*) param;
	// Index representation of the row
	int row = params->row; 
	// Index representation of the column
	int col = params->column; 

	// Check if the row and column indices are valid for a subgrid
	if (row > 6){
		//Prints the necessary output of an invalid case.
		printf("There seems to be an invalid row or column input...\nRow:%d, Col:%d\n", row, col);
		pthread_exit(NULL);
	}
	else if (col > 6)
	{
		//Prints the necessary output of an invalid case.
		printf("There seems to be an invalid row or column input....\nRow:%d, Col:%d\n", row, col);
		pthread_exit(NULL);
	}
	else if (row % 3 != 0)
	{
		//Prints the necessary output of an invalid case.
		printf("There seems to be an invalid row or column input....\nRow:%d, Col:%d\n", row, col);
		pthread_exit(NULL);
	}
	else if(col % 3 != 0)
	{
		//Prints the necessary output of an invalid case.
		printf("There seems to be an invalid row or column input....\nRow:%d, Col:%d\n", row, col);
		pthread_exit(NULL);	
	}
	int num_exists[9] = {0}; // Array to track the presence of numbers in the subgrid

	// Iterates over each cell in the subgrid
	for (int i = row; i < row + 3; i++){
		for (int j = col; j < col + 3; j++){
			// Gets the value of the cell
			int num = sudoku[i][j];

			// Check for invalid entries
			if (num < 1 || num > 9 ){
				//Prints the necessary output of an invalid case.
				printf("There seems to be an invalid input given.... (Row:%d, Col:%d)\n", row, col);
				pthread_exit(NULL);
			} 
			// Check for repeated values in the subgrid
			else if (num_exists[num - 1] == 1){
				//Prints the necessary output of an invalid case.
				printf("We can see that there seem to be one or more repeated values found in a subgrid. (Row:%d, Col:%d)\n", row, col);
				pthread_exit(NULL);
			} 
			else {
				num_exists[num - 1] = 1; // Mark the number as found		
			}
		}
	}

	// Marks the subgrid as valid
	validityCheck[row + col/3] = 1; 
	pthread_exit(NULL);
}

// Main function code is structured here...
int main(){	
	// Array to hold thread IDs
	pthread_t threads[thread_number];
	int threadIndex = 0;

	// Prints a header for the Sudoku puzzle
	printf("\n");
	// Print function used as a title for the Sudoku program...
	printf(R"(Sudoku Puzzle Algorithm)");
	printf("\n");
	printf("\n");
	//Print function used as a output line before giving the actual output representation of the puzzle.
	printf(R"(Here is your puzzle:)");

	// Creates a thread to print the Sudoku puzzle
	pthread_create(&threads[threadIndex++], NULL, printPuzzle, NULL);
	pthread_join(threads[0], NULL);	

	// Checks within each row, column, and subgrid in separate threads
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){	
			parameters *params = (parameters *) malloc(sizeof(parameters));					
			params->row = i;		
			params->column = j;
			
			// Creates a thread to check columns
			if (i == 0){
				pthread_create(&threads[threadIndex++], NULL, checkColumn, params);
			}
			// Creates a thread to check rows
			if (j == 0){
				pthread_create(&threads[threadIndex++], NULL, checkRow, params);
			}
			// Creates a thread to check subgrids at intersections of each 3x3 block
			if (i%3 == 0 && j%3 == 0){
				pthread_create(&threads[threadIndex++], NULL, checkEachSubGrid, params);
			}
		}
	}

	// Join all threads
	for (int i = 0; i < thread_number; i++){
		pthread_join(threads[i], NULL);			
	}

	// Check validity of the puzzle
	for (int i = 0; i < thread_number-1; i++){
		if (validityCheck[i] == 0){
			// Used as a print output in case the values provided for the Sudoku puzzle are invalid
			// Based on the requirements and cases.
			printf("The sudoku solution with the given inputs seems to be invalid!!! Please try again or give other inputs.\n");
			return EXIT_SUCCESS;
		}
	}
	// Print function for a case when the Sudoku puzzle has valid outputs.
	// Values provided in this lab file represent a valid combination.

	printf("The sudoku solution seems to be valid!!!\n");
	return EXIT_SUCCESS;
	// Exits from the program.
}