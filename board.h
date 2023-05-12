#include <iostream>
#include "LL.h"

class myBoard
{
public:
    class grid
    {
    public:
        grid();
        grid(const myBoard::grid &);
        void generateBoard(int, int);
        bool boundCheck(int &, int &);
        void placeObject(char, int, int);
        char tileCheck(int, int);
        void printBoard();
        void operator=(myBoard::grid);
        ~grid();

    private:
        void setSize(int, int);
        char **board;
        int rows;
        int cols;
    };

    //uses linked list header file
    template <typename T>
    class loop
    {
    public:
        loop();
        loop(const myBoard::loop<T> &);
        void populateBoard(T);
        T tileCheck(int);
        void playerCount(int);
        void movePlayer(int, int);
        bool looped(int);
        void printBoard(std::string*, int);
        ~loop();

    private:
        LL<T> board;
        typename LL<T>::Iterator *player;
    };
private:
};

// default constructor
myBoard::grid::grid()
{
    board = nullptr;
    rows = 0;
    cols = 0;
}

// copy constructor
myBoard::grid::grid(const myBoard::grid &rhs)
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

// constructor
void myBoard::grid::generateBoard(int rowSize, int colSize)
{
    setSize(rowSize, colSize);

    board = new char *[rows];
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

bool myBoard::grid::boundCheck(int &rowInput, int &colInput)
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

void myBoard::grid::placeObject(char object, int row, int col)
{
    board[row][col] = object;
}

char myBoard::grid::tileCheck(int row, int col)
{
    return board[row][col];
}

void myBoard::grid::printBoard()
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

myBoard::grid::~grid()
{
    for (int i = 0; i < rows; i++)
    {
        delete board[i];
    }

    delete board;
}

void myBoard::grid::operator=(myBoard::grid rhs)
{
    // delete contents of board
    if (board != nullptr)
    {
        for (int i = 0; i < rows; i++)
        {
            delete board[i];
        }

        board = nullptr;
    }

    // regenerate board

    generateBoard(rhs.rows, rhs.cols);

    for (int i = 0; i < rhs.rows; i++)
    {
        for (int j = 0; j < rhs.cols; j++)
        {
            board[i][j] = rhs.board[i][j];
        }
    }
}

void myBoard::grid::setSize(int rowSize, int colSize)
{
    rows = rowSize;
    cols = colSize;
}

//default constructor
template <typename T>
myBoard::loop<T>::loop()
{
    //empty, private class loop already has data structure initialized
}

//copy constructor
template <typename T>
myBoard::loop<T>::loop(const myBoard::loop<T>& rhs)
{
    board = rhs.board;
}

//have a .txt file of tiles for it to insert
template <typename T>
void myBoard::loop<T>::populateBoard(T tile)
{
    //will be reading in a csv from games.h, populate called multiple times, tail insert btw
    board.tailInsert(tile);
}

template <typename T>
T myBoard::loop<T>::tileCheck(int idLocation)
{
    //will have to be done with iterators, per player
    return *player[idLocation];
}

template <typename T>
void myBoard::loop<T>::playerCount(int count)
{
    player = new typename LL<T>::Iterator [count];

    for (int i = 0; i < count; i++)
    {
        //end is considered the starting location after completing a loop
        player[i] = board.end();
    }
}

//recursive function
template <typename T>
void myBoard::loop<T>::movePlayer(int id, int amount)
{
    if (amount > 0)
    {
        for (int i = 0; i < amount; i++)
        {
            player[id]++;
        }
    }
    else if (amount < 0)
    {
        for (int i = 0; i > amount; i--)
        {
            player[id]--;
        }
    }
}

template <typename T>
bool myBoard::loop<T>::looped(int id)
{
    if (player[id] == board.begin())
    {
        return true;
    }

    return false;
}

template <typename T>
void myBoard::loop<T>::printBoard(std::string* board, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << board[i] << std::endl; 
    }
}

template <typename T>
myBoard::loop<T>::~loop()
{
    //LL is deallocated through LL.h library, just need to deallocate players
    //delete[] player;
    //std::cout << "is it here\n";
    //it was btw, munmap_chunk(): invalid pointer
}
