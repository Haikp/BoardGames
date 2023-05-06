# BoardGames
Intent of this project was to experiment in developing reusable code

#main.cpp
Menu option to for user to select a board game to play

#board.h
Only "games.h" has access to this header file
Board has control over the general aspects of board games, such as the size of the board, viewing the board, or placing "objects (pieces)" on the board
No rules for a particular game is established within this header file

#games.h
Only "main.cpp" has access to this header file
games are to be developed in here, setting the rules and such for a particular board game
A potential change that can occur in this header file is better organization when developing another board game
  - perhaps a headerfile for each game implemented? mostlikely excessive

#Interesting aspects to this project:
- dynamically allocated 2D arrays for the board (pointer to pointer)
  - proper deallocation no mem leaks
  - copy constructor
  - operator overloading
- header file organization
  - reusable code to develop/replicate other board games
  - multiple classes made with public and private functions/variables
- consideration of flexibility
  - there are no set "objects" or defined rules when creating the board
  - how pieces interact are entirely up to the development aspects "games.h"
    - "board.h" only tells you if there is a collision, and what the object is colliding with
- potential board games features involve:
  - On collision/occupying a specific tile (monopoly community/chance tiles)
  - tile randomizer, having different effects when landing on them
        
#Potential aspects to implement
- circular boards 
  - linked list board (games like monopoly)
- multiple "objects" occupying the same tile 
  - 3d arrays? having rows and columns be the 2D part, and the last dimension being the number of players
- implementation of tile types
  - struct, assignment effects
