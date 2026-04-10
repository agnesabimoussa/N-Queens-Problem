#include "main.hpp"

// free allocated memory
void free_matrix(int **matrix, int a)
{
    for (int i = 0; i < a; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// validate the N-Queens solution: verify no two queens can attack each other
// reads the solution from the output.txt file
bool is_valid_solution(void)
{
    // Open and read from output.txt
    ifstream file("output.txt");
    if (!file.is_open())
    {
        cerr << "Error: Could not open output.txt for validation.\n";
        return false;
    }
    // Read board size
    int n;
    if (!(file >> n))
    {
        cerr << "Error: Could not read board size from output.txt.\n";
        file.close();
        return false;
    }
    // Allocate matrix
    int **matrix = (int **)malloc(sizeof(int *) * n);
    if (!matrix)
    {
        cerr << "Error: Memory allocation failed.\n";
        file.close();
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * n);
        if (!matrix[i])
        {
            cerr << "Error: Memory allocation failed.\n";
            file.close();
            return false;
        }
    }
    // Read matrix from file
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!(file >> matrix[i][j]))
            {
                cerr << "Error: Could not read matrix from output.txt.\n";
                file.close();
                // Free memory
                free_matrix(matrix, n);
                return false;
            }
        }
    }
    file.close();
    // Validate the solution
    int queen_count = 0;
    // Count queens and get their positions
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1)
            {
                queen_count++;
                // Check if this queen violates constraints when compared to other queens
                for (int k = 0; k < n; k++)
                {
                    // Check row conflicts (excluding itself)
                    if (k != j && matrix[i][k] == 1)
                    {
                        cerr << "Error: Two queens on same row at (" << i << "," << j << ") and (" << i << "," << k << ")\n";
                        // Free memory
                        free_matrix(matrix, n);
                        return false;
                    }
                    // Check column conflicts (excluding itself)
                    if (k != i && matrix[k][j] == 1)
                    {
                        cerr << "Error: Two queens on same column at (" << i << "," << j << ") and (" << k << "," << j << ")\n";
                        // Free memory
                        free_matrix(matrix, n);
                        return false;
                    }
                }
                // Check diagonal conflicts
                for (int di = -n; di <= n; di++)
                {
                    for (int dj = -n; dj <= n; dj++)
                    {
                        if ((di != 0 && dj != 0) && (abs(di) == abs(dj)))
                        {
                            int ni = i + di, nj = j + dj;
                            if (ni >= 0 && ni < n && nj >= 0 && nj < n && matrix[ni][nj] == 1)
                            {
                                cerr << "Error: Two queens on same diagonal at (" << i << "," << j << ") and (" << ni << "," << nj << ")\n";
                                // Free memory
                                free_matrix(matrix, n);
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    // Verify we have exactly n queens
    if (queen_count != n)
    {
        cerr << "Error: Expected " << n << " queens, but found " << queen_count << ".\n";
        // Free memory
        free_matrix(matrix, n);
        return false;
    }
    // Free memory
    free_matrix(matrix, n);
    cout << "Validation successful! Solution has " << queen_count << " queens with no conflicts.\n";
    return true;
}

int main(void)
{
    if (is_valid_solution())
    {
        std::cout << "✓ Validation PASSED!\n";
        return EXIT_SUCCESS;
    }
    else
    {
        std::cout << "✗ Validation FAILED!\n";
        return EXIT_FAILURE;
    }
}
