/**
 * @file Lau-Natalie.cc
 *
 * @author Natalie Lau
 * Contact: nklau2016@gmail.com
 *
 * @brief Computes matrix multiplication and matrix transposes
 * of MxN matrices.
 *
 * Matrices are stored as std::array<std::array<int, width>, height>
 * 
 * Compile using 'g++ -std=c++11 Lau-Natalie.cc -o Lau-Natalie && ./Lau-Natalie'
 *
 * @date 2022-02-18
 *
 */

#include <iostream>
#include <vector>

using namespace std;

// A matrix is represented by a vector of integer vectors.
typedef vector<int> matrixRow;
typedef vector<matrixRow> matrix;

// Prototypes
// Menus
void printMenu();
void printMatrixInputMenu();
void printTransposeMenu();
void printMultiplyMenu();
void printMatrixMenu();

// Main functions
matrix fillMatrix(int, int);
matrix transposeMatrix(matrix);
matrix multiplyMatrices(matrix, matrix);
void printMatrix(matrix);

// Helper functions
void getDimensions(int *, int *);
matrixRow fillRow(int);
int dotProduct(matrixRow, matrixRow);
bool isMultiplicationValid(matrix, matrix);

// User input
void multiplyUserInput(matrix, matrix);
void printMatrixUserInput(matrix, matrix);
bool isNumber(string);
bool checkChar(char);
int userInt();

int main()
{
    int input;
    matrix matrixA, matrixB;
    char matrixChoice;

    while (1)
    {
        printMenu();
        input = userInt();
        // Continually ask for user input until input is an int from 1 to 5 (inclusive)
        while (input < 1 || input > 5)
        {
            cout << "Please enter a valid input.\n";
            printMenu();
            input = userInt();
        }

        switch (input)
        {
        case 1:
        {
            printMatrixInputMenu();

            input = userInt();
            while (input < 1 || input > 3)
            {
                cout << "Please enter a valid input.\n";
                printMatrixInputMenu();
                input = userInt();
            }
            if (input == 3) { break; }

            int height, width;
            getDimensions(&height, &width);

            if (input == 1) { matrixA = fillMatrix(height, width); }
            else { matrixB = fillMatrix(height, width); }

            break;
        }
        case 2:
        {
            printTransposeMenu();

            input = userInt();
            while (input < 1 || input > 3)
            {
                cout << "Please enter a valid input.\n";
                printTransposeMenu();
                input = userInt();
            }
            if (input == 3) { break; }

            if (input == 1) { matrixA = transposeMatrix(matrixA); }
            else  { matrixB = transposeMatrix(matrixB); }

            break;
        }
        case 3:
        {
            multiplyUserInput(matrixA, matrixB);
            break;
        }
        case 4:
        {
            printMatrixUserInput(matrixA, matrixB);
            break;
        }
        case 5:
            cout << "\nBye!\n";
            return 0;
        }
    }
}

/// Print the main menu of the program.
void printMenu()
{
    cout << "\n******************************\n";
    cout << "*   Linear Algebra Library   *\n";
    cout << "******************************\n";
    cout << "*  Please choose an option.  *\n";
    cout << "*                            *\n";
    cout << "*  1. Input matrix           *\n";
    cout << "*  2. Transpose matrix       *\n";
    cout << "*  3. Matrix multiplication  *\n";
    cout << "*  4. Print matrix           *\n";
    cout << "*  5. Quit                   *\n"; 
    cout << "******************************\n\n";
}

/// Print the matrix input menu.
void printMatrixInputMenu()
{
    cout << "\n******************************\n";
    cout << "*        Matrix Input        *\n";
    cout << "******************************\n";
    cout << "*   Please choose a matrix.  *\n";
    cout << "*                            *\n";
    cout << "*    1. Input matrix A       *\n";
    cout << "*    2. Input matrix B       *\n";
    cout << "*    3. Back                 *\n";
    cout << "******************************\n";
}

/// Print the matrix transposition menu.
void printTransposeMenu()
{
    cout << "\n******************************\n";
    cout << "*    Matrix Transposition    *\n";
    cout << "******************************\n";
    cout << "*   Please choose a matrix.  *\n";
    cout << "*                            *\n";
    cout << "*    1. Transpose matrix A   *\n";
    cout << "*    1. Transpose matrix B   *\n";
    cout << "*    3. Back                 *\n";
    cout << "******************************\n";
}

/// Print the matrix multiplication menu.
void printMultiplyMenu()
{
    cout << "\n******************************\n";
    cout << "*    Matrix Multiplication   *\n";
    cout << "******************************\n";
    cout << "*    Please choose order.    *\n";
    cout << "*                            *\n";
    cout << "*    1. A x B                *\n";
    cout << "*    2. B x A                *\n";
    cout << "*    3. Back                 *\n";
    cout << "******************************\n\n";
}

/// Print the print matrix menu.
void printMatrixMenu()
{
    cout << "\n******************************\n";
    cout << "*        Print Matrix        *\n";
    cout << "******************************\n";
    cout << "*   Please choose a matrix.  *\n";
    cout << "*                            *\n";
    cout << "*    1. Print matrix A       *\n";
    cout << "*    1. Print matrix B       *\n";
    cout << "*    3. Back                 *\n";
    cout << "******************************\n";
}

/**
 * @brief Set the dimensions of the matrix based on user
 * input, then fill with integers based on user input.
 *
 * Matrices are stored as a vector of int vectors, where one
 * vector<int> is a single row.
 *
 * @param height The number of rows in the matrix
 * @param width The number of cols in the matrix
 *
 * @return A 2D array that represents the matrix
 */
matrix fillMatrix(int height, int width)
{
    matrix toFill;

    cout << "\nPlease enter each row as " << width << " numbers separated by spaces.\n";

    // Fill the matrix one row at a time.
    for (int rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        matrixRow row;
        // Continually ask for user input until the current row is correctly filled with integers.
        while (row.empty())
        {
            cout << "Row " << rowIndex + 1 << ": ";
            row = fillRow(width);

            if (row.empty())
            {
                cout << "\nPlease enter valid inputs.\n";
            }
        }
        toFill.push_back(row);
    }
    return toFill;
}

/**
 * @brief Transpose the incoming matrix (by switching the rows
 * with the columns).
 * 
 * @param toTranspose The matrix to transpose
 * 
 * @return The transposed matrix
 */
matrix transposeMatrix(matrix toTranspose)
{
    matrix transpose;
    if (toTranspose.empty()) 
    { 
        cout << "Error: matrix has not been input.\n";
        return transpose; 
    }

    for (int row = 0; row < toTranspose[0].size(); ++row)
    {
        matrixRow newRow;
        for (int col = 0; col < toTranspose.size(); ++col)
        {
            newRow.push_back(toTranspose[col][row]);
        }
        transpose.push_back(newRow);
    }
    return transpose;
}

/**
 * @brief Multiply the two matrices together.
 * 
 * @param first The first matrix operand
 * @param second The second matrix operand
 * 
 * @return The product of the two matrices
 */
matrix multiplyMatrices(matrix first, matrix second)
{
    matrix product;
    matrix transposedSecond = transposeMatrix(second);

    // productHeight = firstHeight
    for (int row = 0; row < first.size(); ++row)
    {
        matrixRow newRow;
        // productWidth = secondWidth
        for (int col = 0; col < second[0].size(); ++col)
        {
            newRow.push_back(dotProduct(first[row], transposedSecond[col]));
        }
        product.push_back(newRow);
    }
    return product;
}

/**
 * @brief Print the incoming matrix. Print an error message
 * if the matrix is empty.
 * 
 * @param print The matrix to display
 */
void printMatrix(matrix print)
{
    if (print.empty())
    {
        cout << "Error: matrix has not been input.\n";
        return;
    }

    for (matrixRow row : print)
    {
        cout << "\t";
        for (int num : row)
        {
            cout << num << "\t";
        }
        cout << "\n";
    }
}

/**
 * @brief Get user input and check that all inputs are integers and that there is the
 * correct number of inputs.
 *
 * If input is valid, fill incoming int array with user input.
 *
 * @param maxIndex The width of the matrix
 *
 * @return An int array representing a single row of the matrix
 */
matrixRow fillRow(int maxIndex)
{
    string input;
    matrixRow newRow;

    // Clear any remaining whitespace from the input buffer.
    cin.clear();
    getline(cin, input);

    // Set tokenStart to the first number in input.
    char *tokenStart = strtok((char *)input.c_str(), " ");

    while (tokenStart != NULL)
    {
        // If input is not a number, return an empty vector<int>.
        if (!isNumber((string)tokenStart))
        {
            newRow.clear();
            return newRow;
        }

        newRow.push_back(stoi((string)tokenStart));
        tokenStart = strtok(NULL, " ");
    }

    // If there is the wrong number of inputs, return an empty vector<int>.
    if (newRow.size() != maxIndex) { newRow.clear(); }
    return newRow;
}

/**
 * @brief Decide order of matrix multiplication based on
 * user input, then print result of computation.
 * 
 * @param matrixA The first matrix operand
 * @param matrixB The second matrix operand
 */
void multiplyUserInput(matrix matrixA, matrix matrixB)
{
    printMultiplyMenu();

    int bBeforeA = userInt();
    while (bBeforeA < 1 || bBeforeA > 3)
    {
        cout << "Please enter a valid input.\n";
        printMultiplyMenu();
        bBeforeA = userInt();
    }
    if (bBeforeA == 3) { return; }

    --bBeforeA;
    if (!isMultiplicationValid(bBeforeA ? matrixB : matrixA, bBeforeA ? matrixA : matrixB))
    {
        cout << "Error: matrices are not compatible for multiplication.\n";
        return;
    }
    matrix product = multiplyMatrices(bBeforeA ? matrixB : matrixA, bBeforeA ? matrixA : matrixB);
    printMatrix(product);
}

/**
 * @brief Determine which matrix to print based on user input, then print
 * that matrix.
 * 
 * @param matrixA The first matrix currently stored
 * @param matrixB The second matrix currently stored
 */
void printMatrixUserInput(matrix matrixA, matrix matrixB)
{
    printMatrixMenu();

    int input = userInt();
    while (input < 1 || input > 3)
    {
        cout << "Please enter a valid input.\n";
        printMatrixMenu();
        input = userInt();
    }
    if (input == 3) { return; }

    printMatrix(input == 1 ? matrixA : matrixB);
}

/**
 * @brief Set the height and width of the matrix.
 *
 * @param[out] height A pointer to the integer representing the desired height of the matrix
 * @param[out] width A pointer to the integer representing the desired width of the matrix
 */
void getDimensions(int *height, int *width)
{
    cout << "\nHeight: ";
    *height = userInt();

    cout << "Width: ";
   *width = userInt();
}

/**
 * @brief Determine if the two incoming matrices can be 
 * multiplied together.
 * 
 * The width of the first matrix must equal the height of the
 * second.
 * 
 * @param first The first matrix to consider as an operand
 * @param second The second matrix to consider as an operand
 * @return true if the matrices can be multiplied, false otherwise
 */
bool isMultiplicationValid(matrix first, matrix second)
{
    return (first[0].size() == second.size());
}

/**
 * @brief Calculate the dot product of two incoming vectors.
 * 
 * @param rowA The first vector
 * @param rowB The second vector
 * @return The dot product of the two vectors
 */
int dotProduct(matrixRow rowA, matrixRow rowB)
{
    int product = 0;
    for (int i = 0; i < rowA.size(); ++i)
    {
        product += rowA[i] * rowB[i];
    }
    return product;
}

/**
 * @brief Return true if incoming string is an integer.
 * 
 * @param str The string to check
 * @return true if str is an int, false otherwise
 */
bool isNumber(string str)
{
    // Allow for negative numbers.
    if (str[0] == '-')
    {
        str = str.substr(1);
    }
    return (!str.empty() && find_if(str.begin(), str.end(), checkChar) == str.end());
}

/**
 * @brief Check if the incoming character is a digit.
 * 
 * @param c The char to check
 * @return true if c is an int, false otherwise
 */
bool checkChar(char c)
{
    return !isdigit(c);
}

/**
 * @brief Get and error check user input. If the input is not an int,
 * set output parameter to 0.
 *
 * @return The integer version of the user input
 */
int userInt()
{
    string input;

    cin >> input;

    // return if input is not an int
    if (!isNumber(input)) { return 0; }
    return stoi(input);
}