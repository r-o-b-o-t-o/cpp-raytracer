#ifndef MATRIX_HPP
#define MATRIX_HPP

namespace Math {
    class Matrix {
    public:
        Matrix(int rows, int cols, float defaultValue = 1.0f);
        Matrix(const Matrix &m);
        ~Matrix();

        Matrix& operator=(Matrix other);
        float& operator[](int);
        const float& operator[](int) const;
        float& operator()(int, int);
        const float& operator()(int, int) const;

        float& at(int);
        const float& at(int) const;
        float& at(int, int);
        const float& at(int, int) const;

        friend void swap(Matrix& a, Matrix& b);

        int getCols() const;
        int getRows() const;

        void set(int i, int j, float val);
        float get(int i, int j) const;

        Matrix inverse() const;
        void print() const;

    protected:
        int rows;
        int cols;

        float* data;

        int index(int i, int j) const;
        void freeArray();
        void checkRange(int) const;

        void multiplyRow(int, float);
        void swapRows(int, int);
        void addRows(int, float, int);
    };
}

#endif // MATRIX_HPP
