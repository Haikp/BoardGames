/*
revision ideas after:
nested structs per game?
1 player functionality, algo neede for each game tho...
make board universal, number rows, alphabet columns, make the board prettier
error checking
*/
#include <iostream>

class myBoard
{

public:
    myBoard();
    myBoard(const myBoard&);
    void generateBoard(int, int);
    bool boundCheck(int&, int&);
    void placeObject(char, int, int);
    char tileCheck(int, int);
    void printBoard();
    void operator=(myBoard);
    ~myBoard();

private:
    void setSize(int, int);
    char** board;
    int rows;
    int cols;
};

//default constructor
myBoard::myBoard()
{
    board = nullptr;
    rows = 0;
    cols = 0;
}

myBoard::myBoard(const myBoard& rhs)
{
    generateBoard(rhs.rows, rhs.cols);

    for (int i = 0; i < rhs.rows; i++)
    {
        for (int j = 0; j < rhs.cols; j++)
        {
            board[i][j] = rhs.board[i][j];
        }
    }
}

void myBoard::setSize(int rowSize, int colSize)
{
    rows = rowSize;
    cols = colSize;
}

//constructor
void myBoard::generateBoard(int rowSize, int colSize)
{
    setSize(rowSize, colSize);

    board = new char*[rows];
    for (int i = 0; i < rows; i++)
    {
        board[i] = new char[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            board[i][j] = ' ';
        }
    }
}

bool myBoard::boundCheck(int& rowInput, int& colInput)
{
    if ((rowInput < 1 || rowInput > rows) || (colInput < 1 || colInput > cols))
    {
        std::cout << "Invalid Input. Tile doesn't exist.\n";
        return false;
    }

    rowInput -= 1;
    colInput -= 1;

    return true;
}

void myBoard::printBoard()
{
    std::cout << "  ";
    for (int i = 0; i < rows + 10; i++)
    {
        std::cout << "-";
    }

    std::cout << '\n';

    for (int i = rows - 1; i >= 0; i--)
    {
        std::cout << i + 1 << " |";
        for (int j = 0; j < cols; j++)
        {
            std::cout << " " << board[i][j] << " |";
        }

        std::cout << '\n';
    }

    std::cout << "  ";
    for (int i = 0; i < rows + 10; i++)
    {
        std::cout << "-";
    }

    std::cout << "\n ";

    for (int i = 0; i < cols; i++)
    {
        char letter = i + 97;
        std::cout << "   " << letter;
    }

    std::cout << "\n";
}

char myBoard::tileCheck(int row, int col)
{
    return board[row][col];
}

void myBoard::placeObject(char object, int row, int col)
{
    board[row][col] = object;
}

myBoard::~myBoard()
{
    for (int i = 0; i < rows; i++)
    {
        delete board[i];
    }

    delete board;
}

void myBoard::operator=(myBoard rhs)
{
    // delete contents of board
    if(board != nullptr)
    {
        for (int i = 0; i < rows; i++)
        {
            delete board[i];
        }

        board = nullptr;
    }

   //regenerate board

    generateBoard(rhs.rows, rhs.cols);

    for (int i = 0; i < rhs.rows; i++)
    {
        for (int j = 0; j < rhs.cols; j++)
        {
            board[i][j] = rhs.board[i][j];
        }
    }
}