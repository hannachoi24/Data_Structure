#include <iostream>

int **alloc2DInt(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
    {
        return nullptr;
    }
    int **mat = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new int[cols];
    }
    return mat;
}

void free2DInt(int **mat, int rows, int cols = 0)
{
    if (mat != NULL)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] mat[i];
        }
        delete[] mat;
    }
}

void set2DRandom(int **mat, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = rand() % 100;
        }
    }
}

void print2DInt(int **mat, int rows, int cols)
{
    std::cout << "행의 수 = " << rows << ", 열의 수 = " << cols << "\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << mat[i][j] << "";
        }
        std::cout << "\n";
    }
}

int main()
{
    int **mat;
    int rows, cols;
    std::cout << "행과 열의 크기를 입력하시오: ";
    std::cin >> rows >> cols;
    mat = alloc2DInt(rows, cols);
    set2DRandom(mat, rows, cols);
    print2DInt(mat, rows, cols);
    free2DInt(mat, rows, cols);
    return 0;
}