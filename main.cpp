#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <cstdio>
#include "raylib.h"

using namespace std;

// draw using RayLib library
void draw_chessboard(int **matrix, int a)
{
    (void)matrix;
    // Determine cell size
    int cell_size = 25;

    // derive the width and height of window
    int dimensions = a * cell_size;
    int window_width = dimensions;
    int window_height = dimensions;

    char buffer[47];
    snprintf(buffer, sizeof(buffer), "N Queens Problem Solution for %dx%d chessboard", a, a);
    // Initialization
    InitWindow(window_width, window_height, buffer);
    SetTargetFPS(60);
    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE); // Background color

        // draw cells with checkerboard pattern
        for (int i = 0; i < a; i++)
        {
            for (int j = 0; j < a; j++)
            {
                int x = i * cell_size;
                int y = j * cell_size;
                if (matrix[i][j] == 1)
                {
                    // draw queen inside the cell
                    Texture2D queen = LoadTexture("assets/queen.png");
                    Rectangle cell = {(float)x, (float)y, (float)cell_size, (float)cell_size};
                    DrawTexturePro(
                        queen,
                        (Rectangle){0, 0, (float)queen.width, (float)queen.height},
                        cell,
                        (Vector2){0, 0},
                        0.0f,
                        WHITE);
                }
                else
                {
                    // Checkerboard pattern: alternating white and cream colors
                    Color cellColor = ((i + j) % 2 == 0) ? WHITE : (Color){240, 220, 200, 255};
                    DrawRectangle(x, y, cell_size, cell_size, cellColor);
                    DrawRectangleLines(x, y, cell_size, cell_size, BLACK);
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
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

// validate the N-Queens solution: verify no two queens can attack each other
bool is_valid_solution(int **matrix, int a)
{
    int queen_count = 0;
    // Count queens and get their positions
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < a; j++)
        {
            if (matrix[i][j] == 1)
            {
                queen_count++;
                // Check if this queen violates constraints when compared to other queens
                for (int k = 0; k < a; k++)
                {
                    // Check row conflicts (excluding itself)
                    if (k != j && matrix[i][k] == 1)
                        return false;
                    // Check column conflicts (excluding itself)
                    if (k != i && matrix[k][j] == 1)
                        return false;
                }
                // Check diagonal conflicts
                for (int di = -a; di <= a; di++)
                {
                    for (int dj = -a; dj <= a; dj++)
                    {
                        if ((di != 0 && dj != 0) && (abs(di) == abs(dj)))
                        {
                            int ni = i + di, nj = j + dj;
                            if (ni >= 0 && ni < a && nj >= 0 && nj < a && matrix[ni][nj] == 1)
                                return false;
                        }
                    }
                }
            }
        }
    }
    // Verify we have exactly a queens
    return queen_count == a;
}

// keep generating a random number until the queen satisfies the constraints
// function takes current matrix
void fill_matrix(int ***matrix, int a)
{
    bool success = false;
    while (!success)
    {
        success = true;
        // loop N times (number of queens to place)
        for (int i = 0; i < a; i++)
        {
            int row = rand() % a;
            int col = rand() % a;
            int attempts = 0;
            int max_attempts = a * a * 10;
            // make sure the position satisfies the constraints
            while (!satisfies_constraint(*matrix, a, row, col) && attempts < max_attempts)
            {
                row = rand() % a;
                col = rand() % a;
                attempts++;
            }
            // If we couldn't find a valid position, restart the entire board
            if (attempts >= max_attempts)
            {
                for (int i = 0; i < a; i++)
                    for (int j = 0; j < a; j++)
                        (*matrix)[i][j] = 0;
                success = false;
                break;
            }
            (*matrix)[row][col] = 1;
        }
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

// take height and width from the user (valid integers, range [4, 40])
// solve problem
// display solution
int main(int argc, char **argv)
{
    srand(time(0));
    if (argc != 2)
    {
        cout << "Error: please enter a value for height and width.\n";
        return (EXIT_FAILURE);
    }
    int a = atoi(argv[1]);
    // 4 <= N <= 40
    if (a < 4 || a > 40)
    {
        cout << "Error: height and width value should be between 4 and 40.\n";
        return (EXIT_FAILURE);
    }
    int **matrix = get_solution(a);
    display_matrix(matrix, a);
    // Validate the solution before displaying
    if (!is_valid_solution(matrix, a))
    {
        cout << "Error: Invalid solution generated! Queens can attack each other.\n";
        free_matrix(matrix, a);
        return (EXIT_FAILURE);
    }
    cout << "Solution is valid! No queens can attack each other.\n";
    draw_chessboard(matrix, a);
    free_matrix(matrix, a);
    return (EXIT_SUCCESS);
}
