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

using std::string;

// Prototypes
void printMenu();
void userInt(int *);
void matrixInput(int *[], int *[]);
void userMatrixChoice(char *);
void fillMatrix(int *[]);
void getDimensions(int *, int *);
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
    // ask for user input while not an int from 1 to 4 (inclusive)
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
        cout << input;
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
    cout << "*  1. Input matrix           *\n"; // TODO: ask A or B
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
 * Matrices are stored as 2D arrays of integers.
 * 
 * @param matrixA A pointer to matrix A
 * @param matrixB A pointer to matrix B
 */
void matrixInput(int *matrixA[], int *matrixB[])
{
    using std::cout;

    char matrix = '\0';
    
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
    cin.ignore();

    // return if input is not 1 char long OR is not a valid character
    if (input.length() != 1 || toupper(input[0]) != 'A' && toupper(input[0]) != 'B')
    {
        *inputChar = '\0';
        return;
    }

    *inputChar = toupper(input[0]);
}

/**
 * @brief 
 * 
 * @param matrix 
 */
void fillMatrix(int *matrix[])
{
    using std::cout;

    int height, width;
    getDimensions(&height, &width);
    
    cout << height;
    cout << "\n";
    cout << width;
}

void getDimensions(int *height, int *width)
{
    using std::cout;

    cout << "\nHeight: ";
    userInt(height);

    cout << "\nWidth: ";
    userInt(width);

    // return if 
    // if (!isdigit(input))
    // {
    //     free(input);
    //     *inputChar = '\0';
    //     return;
    // }

    // free(input);
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