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

void free_matrix(int **matrix, int a)
{
    for (int i = 0; i < a; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}
// generate a new position that satisfies constraint
pair<int, int> get_position(int **matrix, int a)
{
}

// keep generating a random number until the queen satisfies the constraints
// function takes current matrix
void fill_matrix(int ***matrix, int a)
{
    // use *matrix
    // formula for a number in [min, max]: rand() % (max - min + 1) + min;
    // place the first queen
    int row = rand() % a;
    int col = rand() % a;
    *matrix[row][col] = 1;
    // place the second queen such that it satisfies the constraint
    // recursively solve the rest

    // loop N times (number of queens to place)
    for (int i = 0; i < a; i++)
    {
        int row = rand() % a;
        int col = rand() % a;
        *matrix[row][col] = 1;
        // get_position(*matrix, a)
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
