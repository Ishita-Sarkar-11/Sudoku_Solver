#include <iostream>
using namespace std;

// Sudoku grid size
const int N = 9;

// function to print sudoku grid
void print(int sudokuGrid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cout << sudokuGrid[row][col] << " ";
        }
        cout << endl;
    }
}

// check if placing number at sudokuGrid[row][col] is valid
bool isSafe(int sudokuGrid[N][N], int row, int col, int num)
{
    // check row
    for (int i = 0; i < N; i++)
    {
        if (sudokuGrid[row][i] == num)
            return false;
    }

    // check column
    for (int i = 0; i < N; i++)
    {
        if (sudokuGrid[i][col] == num)
            return false;
    }

    // check 3*3 subgrid boxes
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int j = 0; j < 3; j++)
    {
        for (int k = 0; k < 3; k++)
        {
            if (sudokuGrid[startRow + j][startCol + k] == num)
                return false;
        }
    }

    return true;
}

// backtracking solver
bool solveSudoku(int sudokuGrid[N][N], int row, int col)
{

    // if we reached the last cell
    if (row == N - 1 && col == N)
        return true;

    // Move to next row if col exceeds
    if (col == N)
    {
        row++;
        col = 0;
    }

    // Skip filled cells
    if (sudokuGrid[row][col] != 0)
        return solveSudoku(sudokuGrid, row, col + 1);

    // try placing numbers 1-9
    for (int i = 0; i <= 9; i++)
    {
        if (isSafe(sudokuGrid, row, col, i))
        {
            sudokuGrid[row][col] = i;

            // recursive call
            if (solveSudoku(sudokuGrid, row, col + 1))
                return true;
        }

        // backtrcak
        sudokuGrid[row][col] = 0;
    }

    return false;
}

int main()
{

    // sudoku example (0 = empty cell)
    int sudokuGrid[N][N] = {
        {6, 0, 0, 0, 0, 0, 3, 0, 0},
        {0, 0, 0, 9, 0, 0, 0, 0, 0},
        {2, 0, 0, 4, 0, 8, 0, 1, 0},
        {0, 5, 0, 0, 3, 0, 0, 7, 2},
        {0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 7, 9, 0, 0},
        {5, 0, 6, 0, 0, 9, 0, 0, 8},
        {7, 0, 0, 8, 5, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 4, 0, 0}};

    if (solveSudoku(sudokuGrid, 0, 0))
    {
        cout << "Solved Sudoku:\n";
        print(sudokuGrid);
    }
    else
    {
        cout << "No solution exists" << endl;
    }

    return 0;
}