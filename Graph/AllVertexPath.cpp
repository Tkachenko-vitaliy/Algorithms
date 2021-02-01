#include "Alg.h"
#include "Matrix.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

template<typename T>
void PrintMatrix(const Matrix<T>& matrix)
{
    for (size_t i = 0; i < matrix.rows(); i++)
    {
        for (size_t j = 0; j < matrix.cols(); j++)
        {
            if (matrix[i][j] == WEIGHT_NOT_DEFINED)
            {
                std::cout << std::setw(3) << "XX"  << ' ';
            }
            else
            {
                std::cout << std::setw(3) << matrix[i][j] << ' ';
            }
        }
        std::cout << std::endl;
    }
}

Weight CalcMinimum(Weight first, Weight second, Weight offset)
{
    if (second == WEIGHT_NOT_DEFINED || offset == WEIGHT_NOT_DEFINED)
    {
        return first;
    }
    else
    {
        return std::min(first, second + offset);
    }
}

AdjacencyMatrix ExtendShortestPaths(const AdjacencyMatrix& edgeMatrix, const AdjacencyMatrix& weightMatrix)
{
    size_t dim = edgeMatrix.rows();
    AdjacencyMatrix newMatrix(edgeMatrix.rows(), edgeMatrix.cols());
    for (size_t i = 0; i < dim; i++)
    {
        for (size_t j = 0; j < dim; j++)
        {
            newMatrix[i][j] = WEIGHT_NOT_DEFINED;
            for (size_t k = 0; k < dim; k++)
            {
                newMatrix[i][j] = CalcMinimum(newMatrix[i][j], edgeMatrix[i][k], weightMatrix[k][j]);
            }
        }
    }

    return newMatrix;
}

void PairsAsMatrixMultiplication(Graph& graph)
{
    AdjacencyMatrix weightMatrix = graph.getAdjacencyMatrix();
    AdjacencyMatrix adjMatrix = weightMatrix;
    size_t dim = adjMatrix.rows();

    if (dim == 0) return;

    for (size_t i = 2; i <= dim-1; i++)
    {
        adjMatrix = ExtendShortestPaths(adjMatrix, weightMatrix);
    }
    std::cout << std::endl;
    PrintMatrix(adjMatrix);
}