#include "math/Matrix.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace Math {
    Matrix::Matrix(int size) : Matrix(size, size, 0.0f) {
        for (auto i = 0; i < size; i++) {
            this->at(i, i) = 1.0f;
        }
    }

    Matrix::Matrix(int rows, int cols, float defaultValue)
            : rows(rows),
              cols(cols) {
        this->data = new float[rows * cols];
        for (auto i = 0; i < rows * cols; i++) {
            this->data[i] = defaultValue;
        }
    }

    Matrix::Matrix(const Matrix &m)
            : rows(m.rows),
              cols(m.cols) {
        this->data = new float[this->rows * this->cols];
        for (auto i = 0; i < this->rows * this->cols; i++) {
            this->data[i] = m.data[i];
        }
    }

    Matrix::~Matrix() {
        this->freeArray();
    }

    void Matrix::freeArray() {
        if (this->data != nullptr) {
            delete[] this->data;
        }
    }

    Matrix &Matrix::operator=(Matrix other) {
        swap(*this, other);
        return *this;
    }

    Matrix Matrix::operator*(const Matrix &rhs) const {
        Matrix m(*this);
        m *= rhs;
        return m;
    }

    Matrix &Matrix::operator*=(const Matrix &other) {
        Matrix m(this->rows, other.cols);
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j) {
                float val = 0.0f;
                for (int k = 0; k < this->cols; ++k) {
                    val += this->at(i, k) * other.at(k, j);
                }
                m.at(i, j) = val;
            }
        }

        this->freeArray();
        this->rows = m.rows;
        this->cols = m.cols;
        this->data = new float[m.rows * m.cols];
        for (int i = 0; i < m.rows * m.cols; ++i) {
            this->data[i] = m.data[i];
        }

        return *this;
    }

    Matrix Matrix::operator*(const float &rhs) const {
        Matrix m(*this);
        m *= rhs;
        return m;
    }

    Matrix &Matrix::operator*=(const float &rhs) {
        for (int i = 0; i < this->rows; ++i) {
            this->multiplyRow(i, rhs);
        }
        return *this;
    }

    Matrix Matrix::operator*(const HPoint &rhs) const {
        Matrix m(*this);
        m *= rhs;
        return m;
    }

    Matrix &Matrix::operator*=(const HPoint &rhs) {
        Matrix m(4, 1);
        m(0, 0) = rhs.x();
        m(0, 1) = rhs.y();
        m(0, 2) = rhs.z();
        m(0, 3) = rhs.w();
        this->operator*=(m);

        return *this;
    }

    Matrix Matrix::operator*(const HVector &rhs) const {
        Matrix m(*this);
        m *= rhs;
        return m;
    }

    Matrix &Matrix::operator*=(const HVector &rhs) {
        Matrix m(4, 1);
        m(0, 0) = rhs.x();
        m(0, 1) = rhs.y();
        m(0, 2) = rhs.z();
        m(0, 3) = rhs.w();
        this->operator*=(m);

        return *this;
    }

    Matrix Matrix::operator-() const {
        Matrix m(*this);
        m *= -1.0f;
        return m;
    }

    float &Matrix::operator[](const int index) {
        return this->data[index];
    }

    const float &Matrix::operator[](const int index) const {
        return this->data[index];
    }

    float &Matrix::operator()(const int i, const int j) {
        return this->data[this->index(i, j)];
    }

    const float &Matrix::operator()(const int i, const int j) const {
        return this->data[this->index(i, j)];
    }

    void Matrix::checkRange(const int index) const {
        if (index < 0 || index > this->cols * this->rows) {
            throw std::out_of_range("Matrix index is out of range");
        }
    }

    float &Matrix::at(const int index) {
        this->checkRange(index);
        return this->data[index];
    }

    const float &Matrix::at(const int index) const {
        this->checkRange(index);
        return this->data[index];
    }

    float &Matrix::at(const int i, const int j) {
        auto index = this->index(i, j);
        this->checkRange(index);
        return this->data[index];
    }

    const float &Matrix::at(const int i, const int j) const {
        auto index = this->index(i, j);
        this->checkRange(index);
        return this->data[index];
    }

    void swap(Matrix &a, Matrix &b) {
        std::swap(a.rows, b.rows);
        std::swap(a.cols, b.cols);
        std::swap(a.data, b.data);
    }

    int Matrix::getCols() const {
        return this->cols;
    }

    int Matrix::getRows() const {
        return this->rows;
    }

    int Matrix::index(int i, int j) const {
        return i * this->cols + j;
    }

    void Matrix::set(int i, int j, float val) {
        this->data[this->index(i, j)] = val;
    }

    float Matrix::get(int i, int j) const {
        return this->data[this->index(i, j)];
    }

    Matrix Matrix::inverse() const {
        // Create an augmented matrix
        Matrix m(this->rows, this->cols * 2, 0.0f);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                m(i, j) = this->get(i, j);
            }
        }
        // Identity matrix for the augmented side
        for (int i = 0; i < this->rows; ++i) {
            m(i, this->cols + i) = 1.0f;
        }

        int r = 0;
        for (int j = 0; j < this->cols; ++j) {
            float max = 0.0f;
            int k = 0;
            for (int i = r; i < this->rows; ++i) {
                float val = std::fabs(m.at(i, j));
                if (val > max) {
                    max = val;
                    k = i;
                }
            }

            if (std::fabs(m.at(k, j)) > 0.00001f) { // m(k, j) != 0
                m.multiplyRow(k, 1.0f / m.at(k, j));
                m.swapRows(k, r);

                for (int i = 0; i < this->rows; ++i) {
                    if (i != r) {
                        m.addRows(i, -1.0f * m.at(i, j), r);
                    }
                }
                r++;
            }
        }

        // Get augmented part as a matrix
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                result(i, j) = m.at(i, this->cols + j);
            }
        }
        return result;
    }

    void Matrix::multiplyRow(int row, float mul) {
        for (int i = 0; i < this->cols; ++i) {
            this->at(row, i) *= mul;
        }
    }

    void Matrix::swapRows(int rowA, int rowB) {
        if (rowA == rowB) {
            return;
        }

        for (int i = 0; i < this->cols; ++i) {
            float a = this->at(rowA, i);
            float b = this->at(rowB, i);
            this->at(rowB, i) = a;
            this->at(rowA, i) = b;
        }
    }

    void Matrix::addRows(int resultRow, float factor, int rowToAdd) { // resultRow = resultRow + factor * rowToAdd
        for (int i = 0; i < this->cols; ++i) {
            this->at(resultRow, i) += factor * this->at(rowToAdd, i);
        }
    }

    void Matrix::print() const {
        for (int i = 0; i < this->rows; ++i) {
            std::cout << "[ ";
            for (int j = 0; j < this->cols; ++j) {
                std::cout << std::setprecision(3) << std::setw(6) << this->at(i, j) << " ";
            }
            std::cout << "]" << std::endl;
        }
    }
}
