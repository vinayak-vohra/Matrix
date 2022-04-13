#include "Matrix.h"

// -------------------- HELPERS --------------------
/**
 * @brief Find the maximum element in Matrix
 *
 * @return Max element in matrix
 */
float Matrix::maxElement()
{
    float _max = INT_MIN; // Set Max as min value

    // Iterate and find max element
    for (auto row : __mat)    // each row
        for (auto cell : row) // each element
            if (cell > _max)  // compare
                _max = cell;  // update max

    return _max;
}

/**
 * @brief Overload output operator for Matrix
 *
 * @param out ostream output
 * @param x Matrix object
 * @return ostream output
 */
ostream &operator<<(ostream &out, Matrix x)
{
    // find width
    int width = log10(x.maxElement()) + 3;

    for (auto row : x.__mat)
    {
        for (auto el : row)
            out << std::fixed << setprecision(1) << setw(width) << el << "  ";
        out << "\n";
    }
    return out;
}

/**
 * @brief Finds the max row length
 *
 * @param m matrix (vector<vector<float>>)
 * @return Max length of row
 */
int Matrix::__max__(matrix m)
{
    int _max = 0; // Set max as min value

    for (auto row : m)         // iterate rows
        if (row.size() > _max) // compare
            _max = row.size(); // update

    return _max;
}

/**
 * @brief Checks whether the matrix is empty or not
 *
 * @return True if empty matrix
 */
bool Matrix::isEmpty()
{
    return !__mat.size();
}

// -------------------- CONSTRUCTORS --------------------
/**
 * @brief Construct a new Matrix:: Matrix object
 *
 */
Matrix::Matrix()
{
    __rows = 0;
    __cols = 0;
    __mat = {};
}

/**
 * @brief Construct a new Matrix:: Matrix object
 *
 * @param mat Init matrix via vector<vector<float>>
 */
Matrix::Matrix(matrix mat)
{
    __rows = mat.size();
    __cols = __max__(mat);

    uint k = 0;

    // Iterate through values
    for (auto x : mat)
    {
        // create empty vector for kth row
        __mat.push_back({});

        // push list values in kth row
        for (auto y : x)
            __mat[k].push_back(y);

        // fill empty cells with 0
        for (int i = x.size(); i < __cols; i++)
            __mat[k].push_back(0);

        k++;
    }
}

/**
 * @brief Construct a new Matrix:: Matrix object
 *
 * @param dElem List of diagonal elements
 */
Matrix::Matrix(list dElem)
{
    __rows = __cols = dElem.size();
    __mat = matrix(__rows, list(__cols, 0));

    for (int i = 0; i < __rows; i++)
        __mat[i][i] = dElem[i];
}

/**
 * @brief Construct a new Matrix:: Matrix object
 *
 * @param rows No of rows/cols in Matrix
 * @param dia value of each diagonal
 */
Matrix::Matrix(uint rows, float dia)
{
    __rows = __cols = rows;
    __mat = matrix(__rows, list(__cols, 0));

    for (int i = 0; i < __rows; i++)
        __mat[i][i] = dia;
}

// -------------------- ACCESSORS --------------------
/**
 * @brief Access to ith row and jth column element
 *
 * @param i Row number
 * @param j Column number
 * @return element present at provided index
 */
float &Matrix::operator()(const uint i, const uint j)
{
    // 0 <= i < __rows
    // 0 <= j < __cols
    if (i >= 0 && i < __rows && j >= 0 && j < __cols)
        return __mat[i][j];
    else
        throw std::out_of_range("Index out of range.");
}

/**
 * @brief Return the number of rows in matrix
 *
 * @return row count
 */
uint Matrix::rows() { return __rows; }

/**
 * @brief Return the number of cols in matrix
 *
 * @return col count
 */
uint Matrix::cols() { return __cols; }

// -------------------- SCALAR OPERATIONS --------------------
/**
 * @brief Scalar addition
 *
 * @param b Value to add
 * @return Matrix
 */
Matrix Matrix::operator+(float b)
{
    Matrix res = *this;
    for (int i = 0; i < __rows; i++)
        for (int j = 0; j < __cols; j++)
            res(i, j) = __mat[i][j] + b;
    return res;
}

/**
 * @brief Scalar subtraction
 *
 * @param b Value to subtract
 * @return Matrix
 */
Matrix Matrix::operator-(float b)
{
    Matrix res = *this;
    for (int i = 0; i < __rows; i++)
        for (int j = 0; j < __cols; j++)
            res(i, j) = __mat[i][j] - b;
    return res;
}

/**
 * @brief Scalar multiplication
 *
 * @param b Value to multiply
 * @return Matrix
 */
Matrix Matrix::operator*(float b)
{
    Matrix res = *this;
    for (int i = 0; i < __rows; i++)
        for (int j = 0; j < __cols; j++)
            res(i, j) = __mat[i][j] * b;
    return res;
}

/**
 * @brief Scalar multiplication
 *
 * @param b Value to multiply
 * @return Matrix
 */
Matrix Matrix::operator/(float b)
{
    Matrix res = *this;
    for (int i = 0; i < __rows; i++)
        for (int j = 0; j < __cols; j++)
            res(i, j) = __mat[i][j] / b;
    return res;
}

// -------------------- MATRIX OPERATIONS --------------------
/**
 * @brief Add two matrices
 *
 * @param m Second Matrix
 * @return Summed Matrix
 */
Matrix Matrix::operator+(Matrix &m)
{
    if (m.rows() != __rows || m.cols() != __cols)
        throw std::range_error("Unequal dimesions");

    Matrix mat = *this;
    for (int i = 0; i < __rows; i++)
        for (int j = 0; j < __cols; j++)
            mat(i, j) = __mat[i][j] + m(i, j);

    return mat;
}

/**
 * @brief Subtract two matrices
 *
 * @param m Second Matrix
 * @return Diff Matrix
 */
Matrix Matrix::operator-(Matrix &m)
{
    /**
     * Note: Matrix subtraction is not commutative
     * i.e A - B != B - A
     *
     */
    if (m.rows() != __rows || m.cols() != __cols)
        throw std::range_error("Unequal dimesions");

    Matrix mat = *this;
    for (int i = 0; i < __rows; i++)
        for (int j = 0; j < __cols; j++)
            mat(i, j) = __mat[i][j] - m(i, j);

    return mat;
}

/**
 * @brief Multiply two matrices
 *
 * @param m Second Matrix
 * @return Product Matrix
 */
Matrix Matrix::operator*(Matrix &m)
{
    /**
     * Note: Matrix multiplication is not commutative
     * i.e A * B != B * A
     *
     */
    if (__cols != m.rows())
        throw std::range_error("Invalid dimensions");

    uint i, j, k;
    double temp;
    Matrix res(matrix(__rows, list(m.cols(), 0)));

    for (i = 0; i < __rows; i++)
    {
        for (j = 0; j < m.cols(); j++)
        {
            temp = 0;
            for (k = 0; k < __cols; k++)
                temp += __mat[i][k] * m(k, j);

            res(i, j) = temp;
        }
    }
    return res;
}

// -------------------- SWAPS --------------------
/**
 * @brief Swap two rows
 *
 * @param i row 1
 * @param j row 2
 * @throws std::out_of_range : if indexes are out of range
 */
void Matrix::swapRows(uint i, uint j)
{
    if (i < 0 || i >= __rows || j < 0 || j >= __rows)
        throw std::out_of_range("Index out of range");

    // Swap each element of two rows
    // for (auto x = 0; x < __cols; x++)
    //     swap(i, x, j, x);

    // Directly swap the row vectors
    auto x = __mat[i];
    __mat[i] = __mat[j];
    __mat[j] = x;
}

/**
 * @brief Swap two cols
 *
 * @param i col 1
 * @param j col 2
 * @throws std::out_of_range : if indexes are out of range
 */
void Matrix::swapCols(uint i, uint j)
{
    if (i < 0 || i >= __cols || j < 0 || j >= __cols)
        throw std::out_of_range("Index out of range");

    for (auto x = 0; x < __rows; x++)
        swap(x, i, x, j);
}

/**
 * @brief Swap two elements of a matrix
 *
 * @param r1 row of element 1
 * @param c1 col of element 1
 * @param r2 row of element 2
 * @param c2 col of element 2
 * @throws std::out_of_range : if indexes are out of range
 */
void Matrix::swap(uint r1, uint c1, uint r2, uint c2)
{
    if (r1 < 0 || r1 >= __rows || r2 < 0 || r2 >= __rows)
        throw std::out_of_range("Index out of range");

    if (c1 < 0 || c1 >= __cols || c2 < 0 || c2 >= __cols)
        throw std::out_of_range("Index out of range");

    auto temp = __mat[r1][c1];
    __mat[r1][c1] = __mat[r2][c2];
    __mat[r2][c2] = temp;
}

// -------------------- REVERSE --------------------
/**
 * @brief Reverse a col
 *
 * @param i col to reverse
 * @throws std::out_of_range : if index is out_of_range
 */
void Matrix::revCol(uint i)
{
    if (i < 0 || i >= __cols)
        throw std::out_of_range("Index out of range");

    // swap elements
    for (int x = 0; x < __rows / 2; x++)
        swap(x, i, __cols - x - 1, i);
}

/**
 * @brief Reverse a row
 *
 * @param i row to reverse
 * @throws std::out_of_range : if index is out_of_range
 */
void Matrix::revRow(uint i)
{
    if (i < 0 || i >= __rows)
        throw std::out_of_range("Index out of range");

    // via swapping
    for (int x = 0; x < __cols / 2; x++)
        swap(i, x, i, __cols - x - 1);

    // add #include <algorithm>
    // to use below code
    // std::reverse(__mat[i].begin(), __mat[i].end());
}

// -------------------- FLIP --------------------
/**
 * @brief Flip matrix horizontally
 *
 * @return Flipped Matrix
 */
Matrix Matrix::flipX()
{
    /**
     * Flip the matrix on X-axis
     *
     * Swap rows inwards
     *        or
     * Reverse all cols
     *
     * Note: Both methods use
     *       the swap function
     */

    Matrix x = (*this); // copy

    // swap rows
    for (int i = 0; i < __cols / 2; i++)
        x.swapRows(i, __cols - i - 1);

    // reverse cols
    // for(int i = 0; i < __rows; i++)
    //     x.revCol(i);
    return x;
}

/**
 * @brief Flip matrix vertically
 *
 * @return Flipped Matrix
 */
Matrix Matrix::flipY()
{
    /**
     * Flip the matrix on Y-axis
     *
     * Swap columns inwards
     *        or
     * Reverse all rows
     *
     * Note: Both methods use
     *       the swap function
     */

    Matrix x = (*this); // copy

    // swap columns inward
    for (int i = 0; i < __rows / 2; i++)
        x.swapCols(i, __rows - i - 1);

    // reverse all rows
    // for(int i = 0; i < __cols; i++)
    //     x.revRow(i);

    return x;
}

// -------------------- ROTATE --------------------
/**
 * @brief Rotate Matrix 90deg clockwise
 *
 * @return Matrix
 */
Matrix Matrix::rotate90()
{
    /**
     * Logic:
     *
     * Transpose the matrix
     * Reverse all rows
     *
     */

    Matrix x = (*this).transpose(); // transpose

    // reverse all rows
    for (int i = 0; i < x.rows(); i++)
        x.revRow(i);

    return x;
}

// -------------------- OTHERS --------------------
/**
 * @brief Find the determinant of the matrix
 *
 * @return float
 */
float Matrix::det()
{
    /**
     * Logic: Convert into upper triangle matrix using row operations.
     *
     * If diagonal_elem(x) is 0:
     *  Search for next non-zero el in same column
     *    If found:
     *      swap rows
     *      change sign appropriately
     *    Else:
     *      continue for next diagonal_elem
     * Else:
     *  Convert below elems to zero using row operations.
     *
     * repeat for each row
     *
     */
    Matrix X = (*this); // copy matrix
    int idx, sign(1), k(1);
    float piv, mpl, res(1);

    // iterate over rows
    for (int i = 0; i < __rows; i++)
    {
        idx = i;

        // check for non-zero elem in current column
        while (idx < __cols && !X(idx, i))
            idx++;

        // non-zero elem not found
        if (idx == __rows)
            return 0; // det is 0

        // non-zero elem is not current diagonal elem
        if (idx != i)
        {
            X.swapRows(i, idx);            // swap rows
            sign *= std::pow(-1, idx - i); // change sign
        }

        piv = X(i, i); // pivot i.e diagnoal element

        // iterate over rows under current row
        for (int j = i + 1; j < __rows; j++)
        {
            mpl = X(j, i); // multiplier

            // iterate over row elements
            for (int k = i; k < __cols; k++)
                X(j, k) -= X(i, k) * (mpl / piv);
        }
        res *= piv; // result: product of diagonals
    }
    return res * sign; // sign may change due to row swap
}

/**
 * @brief Power of matrix
 *
 * @param n power
 * @return Matrix
 */
Matrix Matrix::pow(uint n)
{
    if (n < 2)
        return (*this);

    Matrix x = (*this) * (*this);

    while (n-- > 2)
        x = x * (*this);
    return x;
}

/**
 * @brief Transpose of Matrix
 *
 * @return Matrix
 */
Matrix Matrix::transpose()
{
    Matrix res(matrix(__cols, list(__rows, 0)));

    for (int i = 0; i < __rows; i++)
        for (int j = 0; j < __cols; j++)
            res(j, i) = __mat[i][j];
    return res;
}
