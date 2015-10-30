/*
This file defines the Board class.

=== Data Definitions ===

Player: Natural,
        Player > 0
    Name (ID) of one of the Players currently on the board.

    ID 0 is special for the free lands.

Players: Natural,
         Players > 2
    Number of players of the game. There is _always_ the player zero (see Player
    above), so there is, at the bare minimum, one player. However, this would't
    be much of a game with only one player and the free lands. So, to ensure a
    game, at least tree Players are required.

Turn: Player
    Marks which player owns the current turn.

PlayerSymbols: VectorOf(Char),
               PlayerSymbols.size() > 2,
               PlayerSymbols.size() == Players - 1
    Hold the symbols that represent each player. Since Player0 is special, this
    vector is expected to store information only for the other players.

GameBoard: VectorOf(VectorOf(Player)),
           GameBoard.size() > 0,
           GameBoard.size() == GameBoard[i].size() for all i
    Describes the current state of the board, where every spot is _always_ owned
    by a Player. Notice the board is always NxN.
*/

#pragma once

#include <vector>
#include <string>

class Board {

public:
    typedef unsigned int Player;                                 // Data::Player
    typedef std::vector<std::vector<Board::Player>> BoardMatrix; // Data::GameBoard

private:
    std::vector<char> _player_symbols; // Data::PlayerSymbols
    Board::BoardMatrix _board;         // the actual data for the GameBoard
    unsigned int _turn;                // Data::Turn

public:
    Board(unsigned int size, std::vector<char> player_symbols, char free_lands_symbol = '0');

    void resize(unsigned int new_size);

    void resetBoard();

    /**
    If the current land is free, asign it to player; else, do nothing.

    Returned values are:
        *  0: the block was free, and now belongs to `player`;
        * -1: invalid data;
        * -2: the block was not free, and nothing was done.
    */
    int giveLand(int row, int col);

    /**
    Converts the current board to a plain string.
    */
    std::string str();

    /**
    Transforms lines into columns.
    */
    Board::BoardMatrix transpose();

    /**
    Checks the board for any winners. Returns the winning player, if one is
    found; if not, returns the player 0.
    */
    Board::Player checkBoard();

    /**
    Switches the current turn for the next player.
    */
    void switchTurn();

    // === Getters ===

    /**
    Number of usable players current on the game.

    The free lands are not usable players.
    */
    unsigned int getNumPlayers() { return _player_symbols.size() - 1; };

    /**
    Gets the symbol used by player on the current board.
    */
    char getPlayerSymbol(Player player);

    /**
    Transforms the board into a nice, printable string.
    */
    std::string getBoard(bool use_symbols);

    /**
    Size of the current board.

    Remember that the board is always a square matrix.
    */
    unsigned int getSize() { return Board::_board.size(); };

    /**
    Current player to play.
    */
    unsigned int getTurn() { return Board::_turn; };

    // === Printers ===

    void printPlayerSymbols();

    void printBoard(bool use_symbols = true);

private:

    /**
    Checks if inputed player is valid in the current board.
    */
    bool verifyPlayer(Board::Player player);

    /**
    Transforms the board into a human-readble string.
    */
    std::string rawBoard();

    void printRawMatrix(Board::BoardMatrix vec);

    /**
    Transforms a matrix into a string, with newlines at the end of each row.
    */
    std::string to_string(Board::BoardMatrix board);

    /**
    Primary and secondary diagonals of the current board.
    */
    Board::BoardMatrix getDiagonals();

};
