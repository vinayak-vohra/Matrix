#ifndef __MAT__
#define __MAT__

// ---------- INCLUDES ----------
#include <ostream>
#include <vector>
#include <cmath>
#include <iomanip>

using std::log10;
using std::ostream;
using std::setprecision;
using std::setw;
using std::vector;

typedef unsigned int uint;
typedef vector<float> list;
typedef vector<list> matrix;

//
// ---------- MATRIX ----------
class Matrix
{
    uint __rows;
    uint __cols;
    matrix __mat;

public:
    // Constructors
    Matrix();            // Default
    Matrix(matrix);      // NxM Matrix
    Matrix(list);        // Diagonal Matrix
    Matrix(uint, float); // Scalar Matrix | Identity Matrix

    // Accessors
    float &operator()(const uint, const uint); // Access element
    uint rows();                               // no of rows
    uint cols();                               // no of cols

    // Scalar Operations
    Matrix operator+(float); // add
    Matrix operator-(float); // sub
    Matrix operator*(float); // multiply
    Matrix operator/(float); // divide

    // Matrix Operations
    Matrix operator+(Matrix &); // Matrix addition
    Matrix operator-(Matrix &); // Matrix subtraction
    Matrix operator*(Matrix &); // Matrix multiplication

    // Swaps
    void swapRows(uint, uint);         // swap two rows
    void swapCols(uint, uint);         // swap cols via index
    void swap(uint, uint, uint, uint); // swap elements

    // Reverse
    void revRow(uint); // reverse a row
    void revCol(uint); // reverse a column

    // Flips
    Matrix flipX(); // flip vertically
    Matrix flipY(); // flip horizontally

    // Rotates
    Matrix rotate90(); // rotate 90deg clockwise

    //  Other Ops
    Matrix transpose(); // transpose
    Matrix pow(uint);   // power op
    float det();        // determinant

    // Other Operations
    friend ostream &operator<<(ostream &, Matrix); // Print matrix
    int __max__(matrix);                           // max column
    float maxElement();                            // returns max element
    bool isEmpty();                                // empty matrix
};
#endif // __MAT__