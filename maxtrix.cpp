#include <iostream>
using namespace std;

    class Matrix
    {
    private:
        int columns, rows;
        double* data;

    public:
        Matrix() : rows(0), columns(0), data(nullptr) {}

        Matrix(int row, int col) : rows(row), columns(col) 
        {
            data = new double[rows * columns];
            for (int i = 0; i < rows * columns; i++)
                data[i] = 0.0;
        }

        ~Matrix()
        {
            delete[] data;
        }

        double& getData(int row, int col)
        {
            return data[row * columns + col];
        }

        void print()
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < columns; j++)
                    cout << getData(i, j) << ' ';
                cout << endl;
            }
        }

        Matrix& operator*(int scalar)
        {
            for (int i = 0; i < rows * columns; i++)
                data[i] *= scalar;
            return *this;
        }

        Matrix& operator*(Matrix& matrix)
        {
            Matrix res(rows, matrix.columns);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < matrix.columns; j++) 
                    for (int k = 0; k < columns; k++)
                        res.getData(i, j) += getData(i, k) * matrix.getData(k, j);
            *this = res;
            return *this;
        }

        Matrix& operator=(const Matrix& other) {
            if (this != &other) {
                delete[] data;

                rows = other.rows;
                columns = other.columns;
                data = new double[rows * columns];

                for (int i = 0; i < rows * columns; i++) {
                    data[i] = other.data[i];
                }
            }
            return *this;
        }

    };

    int main()
    {
        Matrix A(2, 2);
        A.getData(0, 0) = 1;
        A.getData(0, 1) = 2;
        A.getData(1, 0) = 3;
        A.getData(1, 1) = 4;

        Matrix B(2, 2);
        B.getData(0, 0) = 5;
        B.getData(0, 1) = 6;
        B.getData(1, 0) = 7;
        B.getData(1, 1) = 8;

        A = A * 2;
        A.print();

        A = A * B;
        A.print();
}

