/**
 * @file Lau-Natalie.cc
 *
 * @author Natalie Lau
 * Contact: nklau2016@gmail.com
 *
 * @brief Computes matrix multiplication and matrix transposes
 * of MxN matrices.
 *
 * Matrices are stored as std::vector<std::vector<int> >
 * 
 * Compile using 'g++ -std=c++11 Lau-Natalie.cc'
 *
 * @date 2022-02-18
 *
 */

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// A matrix is represented by a vector of integer vectors.
typedef vector<int> matrixRow;
typedef vector<matrixRow> matrix;

#define INPUT_MATRIX 1
#define TRANSPOSE_MATRIX 2
#define MULTIPLY_MATRIX 3
#define RETURN_TO_MAIN_MENU 3
#define PRINT_MATRIX 4
#define QUIT_PROGRAM 5

struct MatrixDimensions
{
    int height;
    int width;
};

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
matrixRow fillRow(int);
int dotProduct(matrixRow, matrixRow);
bool isMultiplicationValid(matrix, matrix);
bool isNumber(string);
bool intInRange(int, int, int);

// User input
void multiplyUserInput(matrix, matrix);
void printMatrixUserInput(matrix, matrix);
int getIntFromStdin();
int getLineFromStdin();
MatrixDimensions getDimensionsFromStdin();

int main()
{
    int menuOption;
    matrix matrixA, matrixB;

    while (true)
    {
        printMenu();
        menuOption = getIntFromStdin();
        // Continually ask for user input until input is an int from 1 to 5 (inclusive)
        while (!intInRange(menuOption, 1, 5))
        {
            cout << "Please enter a valid input.\n";
            printMenu();
            menuOption = getIntFromStdin();
        }

        switch (menuOption)
        {
        case INPUT_MATRIX:
        {
            printMatrixInputMenu();

            menuOption = getIntFromStdin();
            while (!intInRange(menuOption, 1, 3))
            {
                cout << "Please enter a valid input.\n";
                printMatrixInputMenu();
                menuOption = getIntFromStdin();
            }
            if (menuOption == RETURN_TO_MAIN_MENU) { break; }

            MatrixDimensions dimensions = getDimensionsFromStdin();

            if (menuOption == 1) { matrixA = fillMatrix(dimensions.height, dimensions.width); }
            else { matrixB = fillMatrix(dimensions.height, dimensions.width); }

            break;
        }
        case TRANSPOSE_MATRIX:
        {
            printTransposeMenu();

            menuOption = getIntFromStdin();
            while (!intInRange(menuOption, 1, 3))
            {
                cout << "Please enter a valid input.\n";
                printTransposeMenu();
                menuOption = getIntFromStdin();
            }
            if (menuOption == RETURN_TO_MAIN_MENU) { break; }

            if (menuOption == 1) { matrixA = transposeMatrix(matrixA); }
            else  { matrixB = transposeMatrix(matrixB); }

            break;
        }
        case MULTIPLY_MATRIX:
            multiplyUserInput(matrixA, matrixB);
            break;
        case PRINT_MATRIX:
            printMatrixUserInput(matrixA, matrixB);
            break;
        case QUIT_PROGRAM:
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
    cout << "*    2. Transpose matrix B   *\n";
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
    cout << "*    2. Print matrix B       *\n";
    cout << "*    3. Back                 *\n";
    cout << "******************************\n";
}

/**
 * @brief Create a new matrix of the incoming dimensions,
 * then fill with integers based on user input.
 *
 * Matrices are stored as a vector of int vectors, where one
 * vector<int> is a single row.
 *
 * @param height The number of rows in the matrix
 * @param width The number of cols in the matrix
 *
 * @return A vector of vector<int>s that represents the matrix
 */
matrix fillMatrix(int height, int width)
{
    matrix toFill;

    cout << "\nPlease enter each row as " << width << " number";
    if (width > 1) { cout << "s"; }
    cout << " separated by spaces.\n";

    // Fill the matrix one row at a time.
    for (int rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        cout << "Row " << rowIndex + 1 << ": ";

        matrixRow row = fillRow(width);
        // Continually ask for user input until the current row is correctly filled with integers.
        while (row.empty())
        {
            cout << "\nPlease enter valid inputs.\n";
            cout << "Row " << rowIndex + 1 << ": ";
            row = fillRow(width);
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
 * If input is valid, return a vector<int> filled with user input.
 *
 * @param maxIndex The width of the matrix
 *
 * @return An vector<int> representing a single row of the matrix
 */
matrixRow fillRow(int maxIndex)
{
    string input;
    matrixRow newRow;

    getline(cin, input);
    istringstream iss(input);

    string token;

    // Split the string at each space character.
    while (getline(iss, token, ' '))
    {
        // If input is not a number, return an empty vector<int>.
        if (!isNumber((string)token))
        {
            newRow.clear();
            return newRow;
        }

        newRow.push_back(stoi((string)token));
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

    int bBeforeA = getIntFromStdin();
    while (!intInRange(bBeforeA, 1, 3))
    {
        cout << "Please enter a valid input.\n";
        printMultiplyMenu();
        bBeforeA = getIntFromStdin();
    }
    if (bBeforeA == RETURN_TO_MAIN_MENU) { return; }

    // Decrement so only possible values are 1 or 0 (true or false).
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

    int menuOption = getIntFromStdin();
    while (!intInRange(menuOption, 1, 3))
    {
        cout << "Please enter a valid input.\n";
        printMatrixMenu();
        menuOption = getIntFromStdin();
    }
    if (menuOption == RETURN_TO_MAIN_MENU) { return; }

    printMatrix(menuOption == 1 ? matrixA : matrixB);
}

/**
 * @brief Get the desired height and width of the matrix from
 * cin.
 *
 * @return A MatrixDimensions struct
 */
MatrixDimensions getDimensionsFromStdin()
{
    MatrixDimensions dimensions;

    cout << "\nHeight: ";
    // Clear the new line char from previous inputs.
    cin.ignore(1, '\n');

    int height = getLineFromStdin();
    while (height <= 0)
    {
        cout << "\nError: Please enter a single positive number.\nHeight: ";
        height = getLineFromStdin();
    }
    dimensions.height = height;

    cout << "Width: ";
    int width = getLineFromStdin();
    while (width <= 0)
    {
        cout << "\nError: Please enter a single positive number.\nWidth: ";
        width = getLineFromStdin();
    }
    dimensions.width = width;
    
    return dimensions;
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
 * 
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
 * 
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
 * 
 * @return true if str is an int, false otherwise
 */
bool isNumber(string str)
{
    // Allow for negative numbers.
    if (str[0] == '-')
    {
        str = str.substr(1);
    }

    return (!str.empty() && find_if(str.begin(), str.end(), [](char c) { return !isdigit(c); }) == str.end());
}

/**
 * @brief Get and error check user input. If the input is not an int,
 * return 0.
 *
 * @return The integer version of the user input
 */
int getIntFromStdin()
{
    string input;

    cin >> input;

    // return if input is not an int
    if (!isNumber(input)) { return 0; }
    return stoi(input);
}

/**
 * @brief Get and error check user input. If the input is not a 
 * single integer, return 0.
 * 
 * @return The integer version of the user input.
 */
int getLineFromStdin()
{
    string input;

    // Get entire line in case user includes whitespace in answer.
    getline(cin, input);

    if (!isNumber(input)) { return 0; }
    return stoi(input);
}

/**
 * @brief Return whether the incoming int toCheck is within the range
 * of [min, max] (inclusive).
 * 
 * @param toCheck The int to check
 * @param min The minimum value of the range
 * @param max The maximum value of the range
 * @return true if toCheck is between min and max (inclusive), false otherwise
 */
bool intInRange(int toCheck, int min, int max)
{
    return (min <= toCheck && max >= toCheck);
}