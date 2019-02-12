#include <cmath>

#include "Matrix.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace Math {
    Matrix::Matrix(int rows, int cols, float defaultValue) {
        this->rows = rows;
        this->cols = cols;
        this->data = new float[rows * cols];
        for (auto i = 0; i < rows * cols; i++) {
            this->data[i] = defaultValue;
        }
    }

    Matrix::Matrix(const Matrix &m) {
        this->rows = m.rows;
        this->cols = m.cols;
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
        Matrix m(this->rows, this->cols * 2, 0.0f);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                m(i, j) = this->get(i, j);
            }
        }
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
