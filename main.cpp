//tic-tac-toe
//determine if a board is a draw

/*
current plan:
2 header files, board.h and games.h
    - board will control the construction and manip of the board
    - games will contain the games
    - main will only have access the games.h
    - board will only be able to be manip thru games.h
*/
#include <iostream>
#include "games.h"

int main()
{
    int gameSelect = 0;
    std::string exit;
    //prompt
    while (true){
        std::cout << "==========================================================\n";
        std::cout << "Welcome to the Board Game Development Project!\n";
        std::cout << "==========================================================\n\n";
        std::cout << "Menu\n";
        std::cout << "------------\n";
        std::cout << "1. Tic-Tac-Toe\n";
        std::cout << "2. Monopoly (WIP)\n";
        // std::cout << "2. Checkers\n";
        std::cout << "10. Exit\n";
        std::cout << "Please select a board game to play (input the number): ";
        std::cin >> gameSelect;
        std::cin.ignore(40, '\n');
        switch (gameSelect)
        {
            case 1:
                std::cout << "\nLoading Tic-Tac-Toe...\n";
                games::ticTacToe tTT;
                tTT.initialize();
                break;
            case 2:
                std:: cout << "\nLoading Monopoly...\n";
                games::monopoly monopoly;
                monopoly.initialize();
                break;
            case 10:
                while(true){
                    std::cout << "Are you sure? (Y/n): ";
                    std::cin >> exit;
                    std::cin.ignore(40, '\n');
                    if (exit == "Y" || exit == "y")
                        return 0;
                    if (exit == "N" || exit == "n")
                    {
                        std::cout << '\n';
                        break;
                    }
                    else
                        std::cout << "Invalid Input. Try Again.\n";
                }
                break;
            default:
                std::cout << "Invalid Input. Try Again.\n";
        }
    }
}
