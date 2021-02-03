#include "Alg.h"
#include "Matrix.h"

#include <algorithm>
#include <stack>
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
    PrintMatrix(adjMatrix);
}

void PrintPath(const Matrix<VertexNumber>& matrix, VertexNumber i, VertexNumber j)
{
    if (matrix[i-1][j-1] == WEIGHT_NOT_DEFINED)
    {
        return;
    }

    std::stack<VertexNumber> out;
    out.push(j);
    while (i != j)
    {
        out.push(matrix[i-1][j-1]);
        j = matrix[i-1][j-1];
    }
    
    while (!out.empty())
    {
        std::cout << out.top() << '-';
        out.pop();
    }
};

Weight plus(Weight w1, Weight w2)
{
    if (w1 == WEIGHT_NOT_DEFINED || w2 == WEIGHT_NOT_DEFINED)
    {
        return WEIGHT_NOT_DEFINED;
    }
    else
    {
        return w1 + w2;
    }
};

void FloydWarshall(Graph& graph)
{
    using VertexMatrix = Matrix<VertexNumber>;
    using VertexMatrixList = std::list<VertexMatrix>;

    AdjacencyMatrix weightMatrix = graph.getAdjacencyMatrix();
    size_t dim = weightMatrix.rows();

    VertexMatrix predecessorMatrix(dim, dim);

    for (size_t i = 0; i < dim; i++)
    {
        for (size_t j = 0; j < dim; j++)
        {
            if (i == j || weightMatrix[i][j] == WEIGHT_NOT_DEFINED)
            {
                predecessorMatrix[i][j] = NIL_VERTEX;
            }
            else
            {
                predecessorMatrix[i][j] = i+1;
            }
        }
    }

    for (size_t k = 0; k < dim; k++)
    {
        AdjacencyMatrix newMatrix(dim,dim);
        VertexMatrix newPredecessorMatrix(dim, dim);
        for (size_t i = 0; i < dim; i++)
        {
            for (size_t j = 0; j < dim; j++)
            {
                newMatrix[i][j] = CalcMinimum(weightMatrix[i][j], weightMatrix[i][k], weightMatrix[k][j]);
                if (weightMatrix[i][j] <= plus(weightMatrix[i][k], weightMatrix[k][j]))
                {
                    newPredecessorMatrix[i][j] = predecessorMatrix[i][j];
                }
                else
                {
                    newPredecessorMatrix[i][j] = predecessorMatrix[k][j];
                }
            }
        }
        weightMatrix = std::move(newMatrix);
        predecessorMatrix = std::move(newPredecessorMatrix);
    }

    //Output
    PrintMatrix(weightMatrix);
    std::cout << std::endl;
    PrintMatrix(predecessorMatrix);

    std::cout << std::endl;
    for (size_t i = 1; i <= dim; i++)
    {
        for (size_t j = 1; j <= dim; j++)
        {
            std::cout << '[' << i<<'-' << j << "]: ";
            PrintPath(predecessorMatrix, i, j);
            std::cout << std::endl;
        }
    }
}