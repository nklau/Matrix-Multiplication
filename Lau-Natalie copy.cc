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
 * @version 0.1
 *
 * @date 2022-02-18
 *
 */

#include <iostream>
#include <vector>

using namespace std;

// A matrix is represented by a vector of integer vectors.
typedef vector<vector<int> > matrix;

// Prototypes
void printMenu();
int userInt();
void matrixInput(int **, int **);
char userMatrixChoice();
matrix fillMatrix(int, int);
void getDimensions(int *, int *);
vector<int> fillRow(int);
void transposeMatrix(matrix *);
int determineOrder(matrix, matrix);
void multiplyMatrices(matrix, matrix);
bool isNumber(string);
bool checkChar(char);
void printMatrix(matrix);

int main()
{
    int input;
    matrix matrixA, matrixB;
    char matrixChoice;

    while (1)
    {
        input = 0;
        printMenu();
        // Continually ask for user input until input is an int from 1 to 5 (inclusive)
        while (input < 1 || input > 5)
        {
            input = userInt();
            if (input < 1 || input > 5)
            {
                cout << "Please enter a valid input.\n";
                printMenu();
            }
        }

        switch (input)
        {
        case 1:
        {
            matrixChoice = userMatrixChoice();
            int height, width;
            getDimensions(&height, &width);

            if (matrixChoice == 'A')
            {
                matrixA = fillMatrix(height, width);
            }
            else
            {
                matrixB = fillMatrix(height, width);
            }
            break;
        }
        case 2:
        {
            matrixChoice = userMatrixChoice();
            transposeMatrix(matrixChoice == 'A' ? &matrixA : &matrixB);
            break;
        }
        case 3:
        {
            if (matrixA.empty() || matrixB.empty())
            {
                cout << "Error: please input both matrices.\n";
                break;
            }
            int aBeforeB = determineOrder(matrixA, matrixB);
            if (aBeforeB == 0)
            {
                cout << "Error: matrices are not compatible for multiplication.\n";
                break;
            }
            multiplyMatrices(aBeforeB ? matrixA : matrixB, aBeforeB ? matrixB : matrixA);
            break;
        }
        case 4:
        {
            char matrixChoice = userMatrixChoice();
            printMatrix(matrixChoice == 'A' ? matrixA : matrixB);
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
    cout << "*  1. Input matrix           *\n";
    cout << "*  2. Transpose matrix       *\n";
    cout << "*  3. Matrix multiplication  *\n"; // TODO: ask order, store?
    cout << "*  4. Print matrix           *\n";
    cout << "*  5. Quit                   *\n"; 
    cout << "******************************\n\n";
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

/**
 * @brief Get and error check user input. If the input is not
 * either the character 'A' or 'B', return NULL character.
 *
 * @return The user input character, NULL char if input is invalid
 */
char userChar()
{
    string input;

    cin >> input;

    // Return null char if input is not 1 char long OR is not a valid character.
    if (input.length() != 1 || toupper(input[0]) != 'A' && toupper(input[0]) != 'B')
    {
        return '\0';
    }

    return toupper(input[0]);
}

/**
 * @brief Return whether user wants to fill matrix A or matrix B.
 *
 * @return 'A' for matrixA, 'B' for matrixB
 */
char userMatrixChoice()
{
    char matrixChoice = '\0';

    // Continually ask for user input until a valid input is given.
    // A valid input is one of the following: 'A', 'a', 'B', 'b'
    while (matrixChoice == '\0')
    {
        cout << "\nPlease choose matrix A or B.\n";
        matrixChoice = userChar();

        if (matrixChoice == '\0')
        {
            cout << "Please enter a valid input.\n";
        }
    }

    return matrixChoice;
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
        vector<int> row;
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
 * @brief Get user input and check that all inputs are integers and that there is the
 * correct number of inputs.
 *
 * If input is valid, fill incoming int array with user input.
 *
 * @param maxIndex The width of the matrix
 *
 * @return An int array representing a single row of the matrix
 */
vector<int> fillRow(int maxIndex)
{
    string input;
    vector<int> newRow;

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
 * @brief Transpose the incoming matrix (by switching the rows
 * with the columns).
 * 
 * @param[out] toTranspose The matrix to transpose
 */
void transposeMatrix(matrix *toTranspose)
{
    if ((*toTranspose).empty())
    {
        return;
    }
    matrix transpose;
    for (int row = 0; row < (*toTranspose)[0].size(); ++row)
    {
        vector<int> newRow;
        for (int col = 0; col < (*toTranspose).size(); ++col)
        {
            newRow.push_back((*toTranspose)[col][row]); // TODO: found seg fault
        }
        transpose.push_back(newRow);
    }
    *toTranspose = transpose;
}

/**
 * @brief Determine which order of the two matrices would result in
 * a valid order for matrix multiplication.
 * 
 * The width of the first matrix must equal the height of the
 * second, and the height of the first must equal the width of the
 * second.
 * 
 * If multiplication order is first x second, return 1.
 * If multiplication order is second x first, return -1.
 * If neither is valid, return 0.
 * 
 * @param first The first matrix to consider as an operand
 * @param second The second matrix to consider as an operand
 * @return an int from -1 to 1 (inclusive)
 */
int determineOrder(matrix first, matrix second)
{
    int firstHeight = first.size(), firstWidth = first[0].size();
    int secondHeight = second.size(), secondWidth = second[0].size();

    if (firstWidth == secondHeight && firstHeight == secondWidth)
    {
        return 1;
    }

    if (secondWidth == firstHeight && secondHeight == firstWidth)
    {
        return -1;
    }

    return 0;
}

/**
 * @brief Multiply the two matrices together in whichever order is
 * valid. 
 * 
 * @param first The first matrix operand
 * @param second The second matrix operand
 */
void multiplyMatrices(matrix first, matrix second)
{
    cout << "Matrix Multiplication\n";
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

    for (vector<int> row : print)
    {
        cout << "\t";
        for (int num : row)
        {
            cout << num << "\t";
        }
        cout << "\n";
    }
}