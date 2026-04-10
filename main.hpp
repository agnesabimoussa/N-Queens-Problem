#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <cstdio>
#include <fstream>
#include "raylib.h"

using namespace std;

void draw_chessboard(int **matrix, int a);
void write_matrix(int **matrix, int a);
void free_matrix(int **matrix, int a);
bool satisfies_constraint(int **matrix, int a, int row, int col);
void fill_matrix(int ***matrix, int a);
int **get_solution(int a);
bool is_valid_solution(void);