/**
 * @file Lau-Natalie.cc
 *
 * @author Natalie Lau
 * Contact: nklau2016@gmail.com
 *
 * @brief Computes matrix multiplication and matrix transposes
 * of MxN matrices.
 *
 * @version 0.1
 *
 * @date 2022-02-18
 *
 */

// TODO LIST: change matrices to pointers to 2d arrays
// store as 2d arrays, pass as pointers to those objects

#include <iostream>
#include <ctype.h>
#include <limits>
#include <vector>

using std::string;

// Prototypes
void printMenu();
void userInt(int *);
void matrixInput(int *[], int *[]);
void userMatrixChoice(char *);
void fillMatrix(int *[]);
void getDimensions(int *, int *);
void fillRow(int [], int);
void transposeMatrix();
void multiplyMatrices();
bool isNumber(string);
bool checkChar(char);

int main()
{
    using std::cout;

    int input = 0;
    int **matrixA, **matrixB; // TODO: change

    printMenu();
    // Continually ask for user input until input is an int from 1 to 4 (inclusive)
    while (input < 1 || input > 4)
    {
        userInt(&input);
        if (input < 1 || input > 4)
        {
            cout << "Please enter a valid input.\n";
            printMenu();
        }
    }

    switch (input)
    {
    case 1:
        matrixInput(matrixA, matrixB);
        break;
    case 2:
        transposeMatrix();
        break;
    case 3:
        multiplyMatrices();
        break;
    case 4:
        cout << "\nBye!\n";
        return 0;
    }
    // free(matrixA);
    // free(matrixB);
}

/// Print the main menu of the program.
void printMenu()
{
    using std::cout;

    cout << "\n******************************\n";
    cout << "*   Linear Algebra Library   *\n";
    cout << "******************************\n";
    cout << "*  Please choose an option.  *\n";
    cout << "*  1. Input matrix           *\n";
    cout << "*  2. Transpose matrix       *\n";
    cout << "*  3. Matrix multiplication  *\n"; // TODO: ask order, store?
    cout << "*  4. Quit                   *\n";
    cout << "******************************\n\n";
}

/**
 * @brief Get and error check user input. If the input is not an int,
 * set output parameter to 0.
 *
 * @param[out] intInput A pointer to the integer version of the user input
 */
void userInt(int *intInput)
{
    using std::cin;
    using std::stoi;

    string input;

    cin >> input;

    // return if input is not an int
    if (!isNumber(input))
    {
        *intInput = 0;
        return;
    }
    *intInput = stoi(input);
}

/**
 * @brief Ask if user wants to fill matrix A or matrix B, then fill
 * the corresponding matrix.
 * 
 * Matrices are stored as pointers to an int array, where one int array
 * is a single row.
 * 
 * @param matrixA A pointer to matrix A
 * @param matrixB A pointer to matrix B
 */
void matrixInput(int *matrixA[], int *matrixB[])
{
    using std::cout;

    char matrix = '\0';
    
    // Continually ask for user input until a valid input is given.
    // A valid input is one of the following: 'A', 'a', 'B', 'b'
    while (matrix == '\0')
    {
        cout << "\nWould you like to input matrix A or B?\n";
        userMatrixChoice(&matrix);
        if (matrix == '\0')
        {
            cout << "Please enter a valid input.\n";
        }
    }

    fillMatrix(matrix == 'A' ? matrixA : matrixB);
}

/**
 * @brief Get and error check user input. If the input is not
 * either the character 'A' or 'B', set the output parameter 
 * to the NULL character.
 * 
 * @param[out] inputChar A pointer to the user input character
 */
void userMatrixChoice(char *inputChar)
{
    using std::cin;

    string input;

    cin >> input;
    // cin.ignore();

    // return if input is not 1 char long OR is not a valid character
    if (input.length() != 1 || toupper(input[0]) != 'A' && toupper(input[0]) != 'B')
    {
        *inputChar = '\0';
        return;
    }

    *inputChar = toupper(input[0]);
}

/**
 * @brief Set the dimensions of the matrix based on user
 * input, then fill with integers based on user input.
 * 
 * @param[out] matrix A pointer to the matrix
 */
void fillMatrix(int *matrix[])
{
    using std::cout;

    int height, width;

    getDimensions(&height, &width);
    cout << "\nPlease enter each row as " << width << " numbers separated by spaces.\n";

    // Fill the matrix one row at a time.
    for (int row = 0; row < height; ++row)
    {
        // Continually ask for user input until the current row is filled with integers.
        while (*(matrix + row) == NULL) 
        {
            cout << "Row " << row + 1 << ": ";
            fillRow(*(matrix + row), width);
            if (*(matrix + row) == NULL) 
            {
                cout << "\nPlease enter valid inputs.\n";
            }
        }
    }
}

/**
 * @brief Set the height and width of the matrix.
 * 
 * @param[out] height A pointer to the integer representing the desired height of the matrix
 * @param[out] width A pointer to the integer representing the desired width of the matrix
 */
void getDimensions(int *height, int *width)
{
    using std::cout;

    cout << "\nHeight: ";
    userInt(height);

    cout << "Width: ";
    userInt(width);
}

/**
 * @brief Get user input and check that all inputs are integers and that there is the
 * correct number of inputs. 
 * 
 * @param[out] row The int array to fill
 * @param maxIndex The width of the matrix
 */
void fillRow(int row[], int maxIndex) 
{
    using std::cin;
    using std::cout; // TODO: delete
    using std::vector;

    string input;
    vector<int> tokens;

    // Clear any remaining whitespace from the input buffer.
    cin.ignore();
    getline(cin, input);

    // Set tokenStart to the first number in input.
    char *tokenStart = strtok((char *)input.c_str(), " ");

    for (int i = 0; i < maxIndex; ++i)
    {
        // If input is not a number, set row to NULL and return.
        if (!isNumber((string)tokenStart))
        {
            row = NULL;
            return;
        }
        // Otherwise, set element in row to int version of input.
        row[i] = stoi((string)tokenStart);
    }

    // If there are not enough numbers in input, set row to NULL and return.
    if (row[maxIndex - 1] == NULL)
    {
        row = NULL;
        return;
    }

    // for (char *tokenStart = strtok((char *)input.c_str(), " "); tokenStart != NULL; tokenStart = strtok(NULL, " "))
    // {
    //     if (!isNumber((string)tokenStart))
    //     {
    //         row = NULL;
    //         return;
    //     }
    //     tokens.push_back(stoi((string)tokenStart));
    // }
}

void transposeMatrix()
{
    using std::cout;

    cout << "Matrix Transposition\n";
}

void multiplyMatrices()
{
    using std::cout;

    cout << "Matrix Multiplication\n";
}

bool isNumber(string str) 
{
    using std::find_if;

    return (!str.empty() && find_if(str.begin(), str.end(), checkChar) == str.end());
}

bool checkChar(char c) 
{
    return !isdigit(c);
}