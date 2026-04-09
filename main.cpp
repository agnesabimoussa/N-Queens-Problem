#include <iostream>
#include <stdlib.h>
#include "raylib.h"

using namespace std;

// draw using RayLib library
void draw_chessboard(int **matrix)
{
}

// initialze NxN matrix, solve problem, return solution
int **get_solution(int a, int b)
{
    int **matrix;

    matrix = (int **)malloc(sizeof(int) * a); //rows
    *matrix = (int *)malloc(sizeof(int) * b); // cols
    if (!matrix || !*matrix)
        exit(EXIT_FAILURE);
}

// take height and width from the user (valid integers, range [1, 500])
// solve problem
// display solution
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Error: please enter height and width.\n";
        return (EXIT_FAILURE);
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    if (a <= 0 || b <= 0 || a > 500 || b > 500)
    {
        cout << "Error: height and width should be between 1 and 500.\n";
        return (EXIT_FAILURE);
    }
    int **matrix = get_solution(a, b);
    draw_chessboard(matrix);
    return (EXIT_SUCCESS);
}
