#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <utility>
// #include "raylib.h"

using namespace std;

// draw using RayLib library
void draw_chessboard(int **matrix, int a)
{
}

// display solution (used for debugging)
void display_matrix(int **matrix, int a)
{
    if (!matrix || !*matrix)
    {
        cout << "Error: matrix is null.\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < a; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
// free allocated memory
void free_matrix(int **matrix, int a)
{
    for (int i = 0; i < a; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// check if the position is acceptable or not
bool satisfies_constraint(int **matrix, int a, int row, int col)
{
    // no two queens on same place
    if (matrix[row][col] == 1)
    {
        return false;
    }
    // no two queens on same col or row
    for (int i = 0; i < a; i++)
    {
        if (matrix[i][col] == 1 || matrix[row][i] == 1)
        {
            return false;
        }
    }
    // no two queens on same diagonal
    // ↖ diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (matrix[i][j] == 1)
        {
            return false;
        }
    }
    // ↗ diagonal
    for (int i = row, j = col; i >= 0 && j < a; i--, j++)
    {
        if (matrix[i][j] == 1)
        {
            return false;
        }
    }
    // ↙ diagonal
    for (int i = row, j = col; i < a && j >= 0; i++, j--)
    {
        if (matrix[i][j] == 1)
        {
            return false;
        }
    }
    // ↘ diagonal
    for (int i = row, j = col; i < a && j < a; i++, j++)
    {
        if (matrix[i][j] == 1)
        {
            return false;
        }
    }
    return true;
}

// keep generating a random number until the queen satisfies the constraints
// function takes current matrix
void fill_matrix(int ***matrix, int a)
{
    // loop N times (number of queens to place)
    for (int i = 0; i < a; i++)
    {
        int row = rand() % a;
        int col = rand() % a;
        // make sure the position satisfies the constraints
        while (!satisfies_constraint(*matrix, a, row, col))
        {
            row = rand() % a;
            col = rand() % a;
        }
        (*matrix)[row][col] = 1;
    }
}

// initialize NxN matrix, solve problem, return solution
int **get_solution(int a)
{
    int **matrix = (int **)malloc(sizeof(int *) * a); // rows
    if (!matrix)
    {
        cout << "Error: failure while allocating memory.\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < a; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * a); // cols
        if (!matrix[i])
        {
            cout << "Error: failure while allocating memory.\n";
            // free matrix
            free_matrix(matrix, i);
            exit(EXIT_FAILURE);
        }
    }
    // populate the matrix with 0's (no queens)
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < a; j++)
        {
            matrix[i][j] = 0;
        }
    }
    fill_matrix(&matrix, a);
    return (matrix);
}

// take height and width from the user (valid integers, range [1, 500])
// solve problem
// display solution
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Error: please enter a value for height and width.\n";
        return (EXIT_FAILURE);
    }
    int a = atoi(argv[1]);
    // 4 <= N <= 500
    if (a < 4 || a > 500)
    {
        cout << "Error: height and width value should be between 4 and 500.\n";
        return (EXIT_FAILURE);
    }
    int **matrix = get_solution(a);
    display_matrix(matrix, a);
    // draw_chessboard(matrix, a);
    free_matrix(matrix, a);
    return (EXIT_SUCCESS);
}
