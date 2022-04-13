#include <iostream>
#include <sstream>
#include "classes/Matrix.cpp"

using std::cin;
using std::cout;
using std::string;

/**
 * @brief Split string input into float values
 *
 * @param s string to split
 * @return vector of float values
 */
vector<float> split(string s)
{
    std::stringstream ss(s);
    string x;
    vector<float> res;

    while (ss >> x)
    {
        auto f = std::stof(x);
        res.push_back(f);
    }

    return res;
}

static Matrix M;
Matrix B;
float scalar = INT_MIN;

Matrix inputMatrix(string); // For Matrix Input
void menu();                // Main Menu
bool scalarOp();            // Scalar operation Menu
bool matrixOp();            // Matrix operation Menu
bool otherOp();             // Other operation Menu

int main()
{

    M = inputMatrix("Initial Matrix: ");

    do
    {
        menu();
    } while (1);
}

/**
 * @brief Matrix Input Function
 *
 * @param hint string
 * @return Matrix
 */
Matrix inputMatrix(string hint)
{
    system("cls");
    cout << hint << "\n";

    cout << "Select Matrix Type:\n";
    cout << "1. Normal Matrix\n";
    cout << "2. Diagnonal Matrix\n";
    cout << "3. Zero / Identity / Scalar Matrix\n";
    cout << "\nSelect: ";
    int ch;
    cin >> ch;
    system("cls");
    cin.ignore();
    switch (ch)
    {
    case 1:
    {
        cout << "\nEnter no of rows: ";
        int rows;
        cin >> rows;
        cin.ignore();
        cout << "\nEnter space separated elements for each row: \n";
        cout << "Note: Empty cells will be filled 0\n\n";
        matrix mat;
        for (int i = 0; i < rows; i++)
        {
            cout << "Row " << i + 1 << ": ";
            string row;
            getline(cin, row, '\n');
            mat.push_back(split(row));
        }
        return Matrix(mat);
    }

    case 2:
        cout << "\nEnter space separated diagonal elements:\n";
        {
            string row;
            getline(cin, row, '\n');
            return Matrix(split(row));
        }
        break;

    case 3:
    {
        cout << "\nEnter rows(rows=cols): ";
        int rows;
        cin >> rows;
        cout << "\nEnter diagonal value(0/1/X for Null/Identity/Scalar): ";
        int d;
        cin >> d;
        return Matrix(rows, d);
    }

    default:
        system("cls");
        return inputMatrix(hint);
        break;
    }
}

/**
 * @brief Main Menu Function
 *
 */
void menu()
{
    system("cls");
    cout << "\nMENU";
    cout << "\n1. Scalar Operations (Matrix, scalar)";
    cout << "\n2. Matrix Operations (Matrix, Matrix)";
    cout << "\n3. Other Operations (trans, det, swap etc)";
    cout << "\n4. Change Current Matrix";
    cout << "\n5. Exit";

    cout << "\n\nCurrent Matrix: \n";
    cout << M;

    cout << "\n\nSelect: ";
    int ch;
    cin >> ch;

    switch (ch)
    {
    case 1:
    {
        bool con = 1;
        do
        {
            con = scalarOp();
        } while (con);
    }
    break;

    case 2:
    {
        bool con = 1;
        do
        {
            con = matrixOp();
        } while (con);
    }
    break;

    case 3:
    {
        bool con = 1;
        do
        {
            con = otherOp();
        } while (con);
    }
    break;

    case 4:
        M = inputMatrix("Update Current Matrix");
        break;

    case 5:
        system("cls");
        cout << "Thanks for using this program : )";
        exit(0);
    default:
        break;
    }
}

/**
 * @brief Scalar Menu Function
 *
 * @return true while in Scalar menu
 */
bool scalarOp()
{
    system("cls");
    if (scalar == INT_MIN)
    {
        cout << "Enter Scalar value: ";
        cin >> scalar;
        system("cls");
    }
    cout << "Scalar Operations: \n";
    cout << "1. Addition\n";
    cout << "2. Subtraction\n";
    cout << "3. Multiplication\n";
    cout << "4. Division\n";
    cout << "5. Update Scalar\n";
    cout << "6. Back to Main Menu\n";

    cout << "\nCurrent Scalar: " << scalar;

    cout << "\nCurrent Matrix: \n";
    cout << M;

    cout << "\n\nSelect: ";
    int ch;
    cin >> ch;

    system("cls");
    if (ch == 5)
    {
        cout << "Enter Scalar value: ";
        cin >> scalar;
        return 1;
    }

    if (ch == 6)
        return 0;

    string sc;
    cout << "\nEnter Scalar(enter to use " << scalar << "):";
    cin.ignore();
    getline(cin, sc, '\n');

    if (sc.length())
        scalar = std::stof(sc);

    Matrix temp;
    switch (ch)
    {
    case 1:
        temp = M + scalar;
        break;

    case 2:
        temp = M - scalar;
        break;

    case 3:
        temp = M * scalar;
        break;

    case 4:
        if (!scalar)
        {
            cout << "Can't divide by 0\n";
            system("pause");
            return 1;
        }
        temp = M / scalar;

        break;

    default:
        return 1;
    }

    cout << "\nResult:\n"
         << temp;

    cout << "\nSet above matrix as current(y: yes; enter: skip)?";
    string s;
    getline(cin, s, '\n');
    if (s.length() && s[0] == 'y')
        M = temp;

    return 1;
}

/**
 * @brief Matrix Menu Function
 *
 * @return true while in Matrix menu
 */
bool matrixOp()
{
    system("cls");
    if (B.isEmpty())
    {
        B = inputMatrix("Enter Matrix B:");
        system("cls");
    }

    cout << "Matrix Operations: \n";
    cout << "1. Addition\n";
    cout << "2. Subtraction\n";
    cout << "3. Multiplication\n";
    cout << "4. Update Matrix B\n";
    cout << "5. Back to Main Menu\n";

    cout << "\nCurrent Matrix: \n";
    cout << M;

    cout << "\nMatrix B: \n";
    cout << B;

    cout << "\n\nSelect: ";
    int ch;
    cin >> ch;
    cin.ignore();

    Matrix temp;
    system("cls");
    switch (ch)
    {
    case 1:
        try
        {
            temp = M + B;
        }
        catch (std::range_error e)
        {
            cout << "\nError: "
                 << e.what();
            cout << "\n";
            system("pause");
            return 1;
        }
        break;

    case 2:
        try
        {
            temp = M - B;
        }
        catch (std::range_error e)
        {
            cout << "\nError: "
                 << e.what();
            cout << "\n";
            system("pause");
            return 1;
        }
        break;

    case 3:
        try
        {
            temp = M * B;
        }
        catch (std::range_error e)
        {
            cout << "\nError: "
                 << e.what();
            cout << "\n";
            system("pause");
            return 1;
        }
        break;

    case 4:
        B = inputMatrix("Enter Matrix B: ");
        return 1;

    case 5:
        return 0;

    default:
        return 1;
    }

    cout << "\nResult:\n"
         << temp;

    cout << "\nSet above matrix as current(y: yes; enter: skip)?";
    string s;
    getline(cin, s, '\n');
    if (s.length() && s[0] == 'y')
        M = temp;

    return 1;
}

/**
 * @brief Other Menu Function
 *
 * @return true while in Other menu
 */
bool otherOp()
{
    system("cls");

    cout << "Other Operations: ";
    cout << "\n 1. Swap Rows ";
    cout << "\n 2. Swap Cols ";
    cout << "\n 3. Swap Elements \n";

    cout << "\n 4. Reverse Row";
    cout << "\n 5. Reverse Col\n";

    cout << "\n 6. Power";
    cout << "\n 7. Transpose";
    cout << "\n 8. Determinant \n";

    cout << "\n 9. Flip Horizontally";
    cout << "\n10. Flip Vertically";

    cout << "\n11. Update Current Matrix";
    cout << "\n12. Back to main menu";
    cout << "\n\nNote: \n    -Swap & Rev operations are by reference";
    cout << "\n    -Swap & Rev operations are 0-indexed";

    cout << "\n\nCurrent Matrix: \n";
    cout << M;

    cout << "\n\nSelect: ";
    int ch;
    cin >> ch;
    system("cls");
    Matrix temp;
    try
    {
        int r1, r2, c1, c2;

        switch (ch)
        {
        case 1:
            cout << "\nEnter rows(r1, r2) to swap (space separated): ";
            cin >> r1 >> r2;
            M.swapRows(r1, r2);
            cout << "\n"
                 << M;
            break;

        case 2:
            cout << "\nEnter cols(c1, c2) to swap (space separated): ";
            cin >> c1 >> c2;
            M.swapCols(c1, c2);
            cout << "\n"
                 << M;
            break;

        case 3:
            cout << "\nEnter r1, c1, r2, c2 (space separated): ";
            cin >> r1 >> c1 >> r2 >> c2;
            M.swap(r1, c1, r2, c2);
            cout << "\n"
                 << M;
            break;

        case 4:
            cout << "\nEnter Row to reverse: ";
            cin >> r1;
            M.revRow(r1);
            cout << "\n"
                 << M;
            break;

        case 5:
            cout << "\nEnter Col to reverse: ";
            cin >> c1;
            M.revRow(c1);
            cout << "\n"
                 << M;
            break;

        case 6:
            cout << "\nEnter Power to raise: ";
            cin >> r1;
            temp = M.pow(r1);

            cout << "\n"
                 << temp;
            break;

        case 7:
            temp = M.transpose();
            cout << "\n"
                 << temp;
            break;

        case 8:
            cout << "\n"
                 << M.det()
                 << "\n";
            break;

        case 9:
            temp = M.flipX();
            cout << "\n"
                 << temp;
            break;

        case 10:
            temp = M.flipY();
            cout << "\n"
                 << temp;
            break;

        case 11:
            M = inputMatrix("Update Current Matrix");
            return 1;

        case 12:
            return 0;
        }
    }
    catch (std::range_error e)
    {
        cout << "\nError: " << e.what();
        cout << "\n";
    }
    catch (std::out_of_range e)
    {
        cout << "\nError: " << e.what();
        cout << "\n";
    }

    if (ch > 5 && ch < 11 && ch != 8)
    {
        cout << "\nSet above matrix as current(y: yes; enter: skip)?";
        string s;
        cin.ignore();
        getline(cin, s, '\n');
        if (s.length() && s[0] == 'y')
            M = temp;
    }
    else
        system("pause");

    return 1;
}
