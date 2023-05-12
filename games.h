#include "board.h"
#include <vector>
#include <fstream>

class games
{
    public:
    class ticTacToe
    {
    public:
        void initialize();

    private:
        bool winCond(myBoard::grid, bool, int, int);
    };
    
    class monopoly
    {
        struct tiles
        {
            std::string abbrev;
            std::string name;
            int rent0 = 0;
            int rent1 = 0;
            int rent2 = 0;
            int rent3 = 0;
            int rent4 = 0;
            int rent5 = 0;
            int mortgage = 0;
            int houseCost = 0;
            int hotelCost = 0;
            std::string owner = "bank";
        };
    public:
        void initialize();
    private:
    };
};

std::string get_next(std::string&, const char); 

void games::ticTacToe::initialize()
{
    int rows = 3;
    int cols = 3;
    myBoard::grid ticTacToe;
    ticTacToe.generateBoard(rows, cols);

    std::cout << "\nBoard Generated: \n";
    ticTacToe.printBoard();
    std::cout << "Insert by entering a row, then column! \nex. 1 a\n\n";
    
    int row = 0;
    int col = 0;
    char colInput;

    int turns = 0;

    bool finished = 0;
    bool playerTurn = 0;
    while(!finished)
    {
        //check if location is vacant
        bool vacant = false;
        while (!vacant)
        {
            bool validInput = 0;
            while(!validInput){
                //assumes correct inputs only
                std::cout << "\nPlayer " << playerTurn + 1 << "'s Turn: ";
                std::cin >> row >> colInput;
                std::cin.ignore(40, '\n');

                col = (int)std::tolower(colInput) - 96; 
                validInput = ticTacToe.boundCheck(row, col);
            }

            if (ticTacToe.tileCheck(row, col) != ' ')
            {
                std::cout << "Invalid Input. Tile already taken.\n";
                continue;
            }

            vacant = true;
        }

        // 0 refers to player 1
        if (playerTurn == 0)
        {
            ticTacToe.placeObject('X', row, col);
            //didnt have to make copy constructor,
            //couldve just passed in the 2d array
            //consider it for fun
            myBoard::grid boardCopy(ticTacToe);
            finished = winCond(boardCopy, playerTurn, rows, cols);
        }
        else
        {
            ticTacToe.placeObject('O', row, col);
            myBoard::grid boardCopy(ticTacToe);
            finished = winCond(boardCopy, playerTurn, rows, cols);
        }

        playerTurn = !playerTurn;
        ticTacToe.printBoard();
        turns += 1;
        if (turns >= 9)
        {
            std::cout << "It's a draw!\n\n";
            return;
        }
    }

    if (playerTurn == 1)
    {
        std::cout << "Player 1 wins!\n\n\n";
    }
    else
    {
        std::cout << "Player 2 wins!\n\n\n";
    }
}

bool games::ticTacToe::winCond(myBoard::grid board, bool playerTurn, int rows, int cols)
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
            if (board.tileCheck(i, j) != object)
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
            if (board.tileCheck(j, i) != object)
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
            if (board.tileCheck(i, j) != object)
            {
                break;
            }

            winCond++;
        }

        if (winCond == 3)
        {
            return true;
        }

        break;
    }

    //diagonal check 2
    for (int i = rows - 1; i >= 0;)
    {
        int winCond = 0;
        for (int j = 0; j < cols; j++, i--)
        {
            if (board.tileCheck(i, j) != object)
            {
                break;
            }

            winCond++;
        }

        if (winCond == 3)
        {
            return true;
        }

        break;
    }

    return false;
}

void games::monopoly::initialize()
{
    std::vector<std::string> temp;
    myBoard::loop<tiles> monopoly;
    std::fstream inFile;
    inFile.open("monopoly.csv");

    while (true)
    {
        std::string tileInfo;
        monopoly::tiles tile;
        getline(inFile, tileInfo);
        
        if (inFile.eof())
        {
            break;
        }

        tile.abbrev = get_next(tileInfo, ',');
        temp.push_back(tile.abbrev);
        tile.name = get_next(tileInfo, ',');
        tile.rent0 = std::stoi(get_next(tileInfo, ','));
        tile.rent1 = std::stoi(get_next(tileInfo, ','));
        tile.rent2 = std::stoi(get_next(tileInfo, ','));
        tile.rent3 = std::stoi(get_next(tileInfo, ','));
        tile.rent4 = std::stoi(get_next(tileInfo, ','));
        tile.rent5 = std::stoi(get_next(tileInfo, ','));
        tile.mortgage = std::stoi(get_next(tileInfo, ','));
        tile.houseCost = std::stoi(get_next(tileInfo, ','));
        tile.hotelCost = std::stoi(get_next(tileInfo, ','));
        monopoly.populateBoard(tile);
    }

    myBoard::loop<tiles> copyBoard (monopoly);
    std::string* abbrev = new std::string[temp.size()];
    for (int i = 0; i < temp.size(); i++)
    {
        abbrev[i] = temp[i];
    }

    copyBoard.printBoard(abbrev, temp.size());
    
    delete[] abbrev;
}

std::string get_next(std::string& line, const char delimiter = ',')
{
    int index = line.find(delimiter);
    std::string substr = line.substr(0, index);
    line.erase(0, index + 1);
    return substr;
}
