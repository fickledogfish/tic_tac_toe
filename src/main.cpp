#include <iostream>
#include <vector>
#include <sstream>
#include <cstdio>

#include "config.hpp"
#include "Board.hpp"
#include "text.hpp"

int main() {

    // Print the program name and version
    std::stringstream project_name;
    project_name << conf::PROJECT_NAME << " " << conf::VERSION_MAJOR << "." << conf::VERSION_MINOR;
    std::cout << txt::centerTextLine(project_name.str(), 80) << std::endl;

    // Get number of players and each's symbol
    std::cout << "Enter the number of players: ";
    unsigned int num_players = 0;
    while(!(std::cin >> num_players)) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << std::endl << "That was not helpfull... Try again: ";
    }

    std::vector<char> player_symbols(num_players);

    for (int i = 1; i <= num_players; i++) {
        std::cout << "Player " << i << " enter your symbol: ";
        char sym = 'a';

        while(!(std::cin >> sym)) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << std::endl << "That was not helpfull... Try again: ";
        }

        player_symbols[i-1] = sym;

        std::cout << "you entered " << sym << " " << player_symbols[i] << std::endl;
    }

    // Create the board
    std::cout << "Enter the size of the board: ";
    unsigned int size;
    while(!(std::cin >> size)) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << std::endl << "That was not helpfull... Try again: ";
    }

    Board board(size, player_symbols);

    while (board.checkBoard() == 0) {
        board.printBoard();

        std::cout << "Player '" << board.getPlayerSymbol(board.getTurn())
                  << "', enter your move:" << std::endl;
        int row = 0, col = 0;
        bool roll_again = true;

        // get input untill it is valid
        while (roll_again) {
            std::cout << "row: ";
            while (!(std::cin >> row)) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << std::endl << "That was not helpfull... Try again: ";
            }

            std::cout << "column: ";
            while (!(std::cin >> col)) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << std::endl << "That was not helpfull... Try again: ";
            }

            if (board.giveLand(row-1, col-1) != 0) {
                std::cout << "Invalid move!" << std::endl;
            }

            roll_again = false;
        }

        board.switchTurn();
    }

    std::cout << "Player " << board.checkBoard() << " won!" << std::endl;

    return 0;
}
