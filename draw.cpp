#include "main.hpp"

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

