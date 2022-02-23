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

using namespace std;

// Prototypes
void printMenu();
void userInt(int *);
void matrixInput(int *[], int *[]);
void userMatrixChoice(char *);
int ** fillMatrix();
void getDimensions(int *, int *);
int * fillRow(int);
void transposeMatrix();
void multiplyMatrices();
bool isNumber(string);
bool checkChar(char);

int main()
{
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
void userInt(int *intInput) // TODO: make this return an int instead of pointing to it
{
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

    if (matrix == 'A') 
    {
        matrixA = fillMatrix();
    } else
    {
        matrixB = fillMatrix();
    }
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
    string input;

    cin >> input;

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
 * @return A 2D array that represents the matrix
 */
int ** fillMatrix()
{
    int height, width;

    // Set dimensions of 2D array that represents the matrix.
    getDimensions(&height, &width);
    int **rows = (int **)malloc(sizeof(int *));

    cout << "\nPlease enter each row as " << width << " numbers separated by spaces.\n";

    // Fill the matrix one row at a time.
    for (int rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        *(rows + rowIndex) = (int *)malloc(sizeof(int));
        *(rows + rowIndex) = NULL;
        
        // Continually ask for user input until the current row is correctly filled with integers.
        while (*(rows + rowIndex) == NULL)
        {
            cout << "Row " << rowIndex + 1 << ": ";
            *(rows + rowIndex) = fillRow(width);
            if (*(rows + rowIndex) == NULL)
            {
                cout << "\nPlease enter valid inputs.\n";
            }
        }
    }
    // matrix = (int **)rows;
    return NULL;
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
    userInt(height);

    cout << "Width: ";
    userInt(width);
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
int * fillRow(int maxIndex)
{
    string input;
    int *newRow = (int *)malloc(sizeof(int));

    // Clear any remaining whitespace from the input buffer.
    cin.clear();
    getline(cin, input);

    cout << input << "\n";

    // Set tokenStart to the first number in input.
    char *tokenStart = strtok((char *)input.c_str(), " ");

    int i = 0;
    while (tokenStart != NULL)
    {
        // If input is not a number, free int array and return.
        if (!isNumber((string)tokenStart))
        {
            free(newRow);
            return NULL;
        }

        *(newRow + i) = stoi((string)tokenStart);
        ++i;
        tokenStart = strtok(NULL, " ");
    }

    // If there is the wrong number of inputs, free int array and return.
    if (i != maxIndex)
    {
        free(newRow);
        return NULL;
    }
    return newRow;
}

void transposeMatrix()
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