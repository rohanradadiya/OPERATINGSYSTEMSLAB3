# OPERATINGSYSTEMSLAB3
OPERATING SYSTEMS LAB 3 - SOFE 3950U - GROUP 6

# Sudoku Solution Validator

## Task Overview
- **Course:** SOFE 3950: Operating Systems
- **Lab:** Lab 3
- **Task:** Sudoku Solution Validator

## Description
In this lab, we worked on validating a Sudoku solution using multithreading techniques. A Sudoku puzzle consists of a 9 × 9 grid where each column, row, and 3 × 3 subgrid must contain all digits from 1 to 9.

## Multithreading Strategy
The strategy involves creating threads to check the following criteria:
- One thread per column containing digits 1 through 9.
- One thread per row containing digits 1 through 9.
- Nine threads to check each of the 3 × 3 subgrids for digits 1 through 9.

## Passing Parameters to Threads
To pass parameters to each thread, a struct contains the row and column where a thread must begin validating.

```c
/* Structure for passing data to threads */
typedef struct {
    int row;
    int column;
} parameters;
```

## Code Implementation
The code creates threads to validate rows, columns, and subgrids of the Sudoku puzzle. Each thread checks for valid digits within its area. The parent thread collects results from all worker threads to determine the validity of the entire puzzle.

## Prerequisite: 
Make sure to have gcc installed

## Running the Code:
1. In command prompt make sure directory is on the specific repository folder

2. Compile the code:
3. gcc sudokuValidatorReal.c -o OSLAB3
4. ./OSLAB3

5. If the Sudoku solution is valid, it will print "The sudoku solution seems to be valid!!!". Otherwise, it will indicate that the solution is invalid and prompt for correction.

## Contributors
- Rohan Radadiya (100704614)
- Sibi Sabesan (100750081)
- Syed Airaj Hussain (100789134)
