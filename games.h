/*
revision ideas after:
nested structs per game?
1 player functionality, algo neede for each game tho...
make board universal, number rows, alphabet columns, make the board prettier
error checking
*/
#include <iostream>

class boardGame
{
public:
    int menuSelect();

private:
    void ticTacToe();
    bool tTTWinCond(char**&, bool, int, int);
    void printBoard(char**&, int, int);
    void placeObject(char**&, char, int, int);
};

int boardGame::menuSelect()
{
    int gameSelect = 0;
    std::string exit;
    //prompt
    while (true){
        std::cout << "Please select a board game to play (input the number): " << std::endl;
        std::cout << "1. Tic-Tac-Toe\n";
        // std::cout << "2. Checkers\n";
        std::cout << "10. Exit\n";
        std::cin >> gameSelect;
        std::cin.ignore(40, '\n');
        switch (gameSelect)
        {
            case 1:
                std::cout << "Loading Tic-Tac-Toe...\n";
                boardGame::ticTacToe();
                break;
            case 10:
                while(true){
                    std::cout << "Are you sure? (Y/N): ";
                    std::cin >> exit;
                    std::cin.ignore(40, '\n');
                    if (exit == "Y" || exit == "y")
                        return 0;
                    if (exit == "N" || exit == "n")
                        continue;
                    else
                        std::cout << "Invalid Input. Try Again.\n";
                }
                break;
            default:
                std::cout << "Invalid Input. Try Again.\n";
        }
    }
}

void boardGame::ticTacToe()
{
    int rows = 3, cols = 3;
    //generate 3x3 board for tic tac toe dynamically
    char** board = new char*[rows];
    for (int i = 0; i < rows; i++)
    {
        board[i] = new char[cols];
    }

    //populate board
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            board[i][j] = ' ';
        }
    }

    std::cout << "\nBoard Generated: \n";
    boardGame::printBoard(board, rows, cols);
    std::cout << "Insert by entering a row, then column! \nex. 1 a\n\n";
    
    int row = 0;
    int col = 0;
    char colInput;

    bool finished = 0;
    bool playerTurn = 0;
    while(!finished)
    {
        //assumes correct inputs only
        std::cout << "Player " << playerTurn + 1 << "'s Turn: ";
        std::cin >> row >> colInput;
        std::cin.ignore(40, '\n');

        col = (int)std::tolower(colInput) - 97;

        // 0 refers to player 1
        if (playerTurn == 0)
        {
            placeObject(board, 'X', row, col);
            playerTurn = 1;
        }
        else
        {
            placeObject(board, 'O', row, col);
            playerTurn = 0;
        }

        finished = boardGame::tTTWinCond(board, playerTurn, rows, cols);

        boardGame::printBoard(board, rows, cols);
    }
}

bool boardGame::tTTWinCond(char**& board, bool playerTurn, int rows, int cols)
{
    char object;
    if (playerTurn == 0)
    {
        object = 'X';
    }
    else
    {
        object = 'O';
    }
    //potential optimization, see where they placed their object, and have a table of all possible viable solutions, any solutions with that location will be checked
    //brute force checking, its a small board
    //horizontal check
    for (int i = 0; i < rows; i++)
    {
        int winCond = 0;
        for (int j = 0; j < cols; j++)
        {
            if (board[i][j] != object)
            {
                break;
            }
            
            winCond++;
        }
        if (winCond == 3)
        {
            return true;
        }
    }

    //vertical check
    for (int i = 0; i < cols; i++)
    {
        int winCond = 0;
        for (int j = 0; j < rows; j++)
        {
            if (board[j][i] != object)
            {
                break;
            }
            
            winCond++;
        }
        if (winCond == 3)
        {
            return true;
        }
    }

    //diagonal check
    for (int i = 0; i < rows;)
    {
        int winCond = 0;
        for (int j = 0; j < cols; j++, i++)
        {
            if (board[i][j] != object)
            {
                break;
            }
        }

        if (winCond == 3)
        {
            return true;
        }
    }

    //diagonal check 2
    for (int i = rows - 1; i >= 0;)
    {
        int winCond = 0;
        for (int j = 0; j < cols; j++, i--)
        {
            if (board[i][j] != object)
            {
                break;
            }
        }

        if (winCond == 3)
        {
            return true;
        }
    }

    return false;
}

void boardGame::printBoard(char**& board, int rows, int cols)
{
    std::cout << rows << " " << cols << std::endl;

    for (int i = 0; i < rows + 10; i++)
    {
        std::cout << "_";
    }

    std::cout << '\n';

    for (int i = 0; i < rows; i++)
    {
        std::cout << "|";
        for (int j = 0; j < cols; j++)
        {
            std::cout << " " << board[i][j] << " |";
        }

        std::cout << '\n';
    }

    for (int i = 0; i < rows + 10; i++)
    {
        std::cout << "-";
    }

    std::cout << '\n';
}

void boardGame::placeObject(char**& board, char object, int row, int col)
{

}