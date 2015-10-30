#include "Board.hpp"

#include <iostream>
#include <sstream>
#include "random.hpp"
#include "text.hpp"

Board::Board(unsigned int size, std::vector<char> player_symbols, char free_lands_symbol)
    : _player_symbols{player_symbols} {
    _player_symbols.insert(_player_symbols.begin(), free_lands_symbol);

    // randomize the first turn
    _turn = rnd::random_int(1, _player_symbols.size()-1);

    // resize the board to desired size and sets every point free
    Board::resize(size);
}

void Board::resize(unsigned int new_size) {
    Board::_board.resize(new_size);
    for (Board::BoardMatrix::size_type i = 0; i < Board::_board.size(); i++)
        Board::_board[i].resize(new_size);

    // make sure averything is initialized
    Board::resetBoard();
}

void Board::resetBoard() {
    for (Board::BoardMatrix::size_type row = 0; row < Board::getSize(); row++)
        for (std::vector<Board::Player>::size_type col = 0; col < Board::getSize(); col++)
            Board::_board[row][col] = 0;
}

std::string Board::to_string(Board::BoardMatrix board) {
    std::stringstream board_str;

    for (auto &row : board) {
        for (auto &col : row)
            board_str << col;
        board_str << std::endl; // add a newline after every row of the matrix
    }

    return board_str.str();
}

std::string Board::str() {
    return Board::to_string(Board::_board);
}

Board::BoardMatrix Board::transpose() {
    // copy the board
    Board::BoardMatrix transposed_board {Board::_board};

    for (Board::BoardMatrix::size_type row = 0; row < Board::getSize(); row++)
        for (std::vector<Board::Player>::size_type col = 0; col < Board::getSize(); col++)
            transposed_board[row][col] = Board::_board[col][row];

    return transposed_board;
}

Board::BoardMatrix Board::getDiagonals() {

    /*
    This is a little tricky... Lets go with a 3x3 board:

        (0,0) | (0,1) | (0,2)
        ------|-------|------
        (1.0) | (1,1) | (1,2)
        ------|-------|------
        (2,0) | (2,1) | (2,2)

    The fist diagonal is the easiest one, needing only a simple condition:

        row == col

    The second, though, is a little tricky.

        col == size - row - 1

    */

    Board::BoardMatrix diagonals;

    diagonals.resize(2); // no matter the size, there are alays two diagonals

    for (Board::BoardMatrix::size_type i = 0; i < diagonals.size(); i++)
        diagonals[i].resize(Board::getSize()); // the size of the diagonal is always equal to the board's

    // primary diagonal
    for (Board::BoardMatrix::size_type row = 0; row < Board::getSize(); row++)
        for (std::vector<Board::Player>::size_type col = 0; col < Board::getSize(); col++)
            if (row == col)
                diagonals[0][row] = Board::_board[row][col];

    // secondary diagonal
    for (Board::BoardMatrix::size_type row = 0; row < Board::getSize(); row++)
        for (std::vector<Board::Player>::size_type col = 0; col < Board::getSize(); col++)
            if (col == (Board::getSize() - row - 1))
                diagonals[1][row] = Board::_board[row][col];

    return diagonals;
}

Board::Player Board::checkBoard() {
    unsigned int found_player = 0;        // value to be returned
    std::string board_str = Board::str(); // board translated to a string

    // do this for every registered player
    for (unsigned int player = 1; player < Board::getSize(); player++) {
        // build the string to be searched
        std::stringstream search_sstr;

        // include as many player data as the current size of the board
        for (int i = 0; i < Board::getSize(); i++)
            search_sstr << player;

        std::string search_str = search_sstr.str();

        // check for rows
        if (board_str.find(search_str) != std::string::npos) {
            found_player = player;
            break;
        }

        // check for cols
        if (Board::to_string(Board::transpose()).find(search_str) != std::string::npos) {
            found_player = player;
            break;
        }

        // check for diagonals
        if (Board::to_string(Board::getDiagonals()).find(search_str) != std::string::npos) {
            found_player = player;
            break;
        }
    }

    // if nothing was found, return 0
    return found_player;
}

void Board::printPlayerSymbols() {
    for (std::vector<char>::size_type i = 1; i < Board::_player_symbols.size(); i++)
        std::cout << "Player " << i << ": " << Board::_player_symbols[i] << std::endl;
}

char Board::getPlayerSymbol(Board::Player player) {
    return Board::_player_symbols[player];
}

bool Board::verifyPlayer(Board::Player player) {
    if (player <= Board::_player_symbols.size())
        return true;
    else
        return false;
}

int Board::giveLand(int row, int col) {

    // validate data
    if (row < 0 || col < 0)
        return -1;

    if (Board::_board[row][col] == 0) {
        Board::_board[row][col] = Board::_turn;
        return 0;
    } else {
        return -2; // the current land was not free, so cannot be given
    }
}

std::string Board::rawBoard() {
    std::string board_str;

    for (Board::BoardMatrix::size_type row = 0; row < Board::_board.size(); row++) {
        for (std::vector<Board::Player>::size_type col = 0; col < Board::_board.size(); col++)
            board_str += Board::_board[row][col];
        board_str += "\n";
    }

    return board_str;
}

std::string Board::getBoard(bool use_symbols) {
    std::string board_str = "";
    unsigned int board_str_line_size = 0;

    for (Board::BoardMatrix::size_type row = 0; row < Board::_board.size(); row++) {
        for (std::vector<Board::Player>::size_type col = 0; col < Board::_board.size(); col++) {
            board_str += "| ";
            if (use_symbols)
                board_str += Board::getPlayerSymbol(Board::_board[row][col]);
            else
                board_str += Board::_board[row][col];
            board_str += " ";
        }
        board_str += "|\n";

        if (row == 0)
            board_str_line_size = board_str.size();

        board_str.insert(board_str.end(), board_str_line_size - 1, '-');
        board_str += '\n';
    }

    // insert extra line in the beginning of the string
    board_str.insert(board_str.begin(), board_str_line_size - 1, '-');
    board_str.insert(board_str_line_size - 1, 1, '\n');

    return board_str;
}

void Board::printBoard(bool use_symbols) {
    txt::printCentered(Board::getBoard(use_symbols), 80);
}

void Board::printRawMatrix(Board::BoardMatrix vec) {
    for (Board::BoardMatrix::size_type row = 0; row < vec.size(); row++) {
        for (Board::BoardMatrix::size_type col = 0; col < vec[row].size(); col++)
            std::cout << vec[row][col];
        std::cout << std::endl;
    }
}

void Board::switchTurn() {
    /*
    While the current player ID is less than the number of players, simply
    add one to get the next turn owner.

    When we hit the last player, restart the cycle.
    */
    if (Board::_turn < (Board::getNumPlayers()))
        Board::_turn++;
    else
        Board::_turn = 1;
}
