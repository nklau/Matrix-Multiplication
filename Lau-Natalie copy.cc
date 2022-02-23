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

// TODO LIST: change matrices to pointers to 2d arrays
// store as 2d arrays, pass as pointers to those objects

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
void transposeMatrix(matrix);
void multiplyMatrices();
bool isNumber(string);
bool checkChar(char);
void printMatrix(matrix);

int main()
{
    int input = 0;
    matrix matrixA, matrixB;

    printMenu();
    // Continually ask for user input until input is an int from 1 to 4 (inclusive)
    while (input < 1 || input > 4)
    {
        input = userInt();
        if (input < 1 || input > 4)
        {
            cout << "Please enter a valid input.\n";
            printMenu();
        }
    }

    switch (input)
    {
    case 1:
    {
        char matrixChoice = userMatrixChoice();
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
        char matrixChoice = userMatrixChoice();
        // matrixA.empty() returns 1 if empty
        transposeMatrix(matrixChoice == 'A' ? matrixA : matrixB);
        break;
    }
    case 3:
        multiplyMatrices();
        break;
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
        cout << "\nWould you like to input matrix A or B?\n";
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

    cout << input << "\n";  // TODO: delete

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

void transposeMatrix(matrix toTranspose)
{
    cout << "Matrix Transposition\n";
}

void multiplyMatrices()
{
    cout << "Matrix Multiplication\n";
}

bool isNumber(string str)
{
    return (!str.empty() && find_if(str.begin(), str.end(), checkChar) == str.end());
}

bool checkChar(char c)
{
    return !isdigit(c);
}

void printMatrix(matrix print)
{
    if (print.empty())
    {
        cout << "Error: matrix has not been input.\n";
        return;
    }

    for (vector<int> row : print)
    {
        for (int num : row)
        {
            cout << num << " ";
        }
    }
}