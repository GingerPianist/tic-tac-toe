#include "classes.hpp"
#include <iostream>

int main() {

    char next = 'y';
    while (next == 'y') {
        Board board;
        int board_size;

        board.set_size();

        int player = 1;

        while (!board.check_win() && !board.check_draw()) {

            board.draw();
            std::cout << "Player " << player << " choose the number: ";

            std::string number;
            std::cin >> number;
            if (!board.check_input(number))
                continue;

            board.change_numbers(number, (player == 1) ? "O" : "X");
            player = (player % 2) + 1;
        }

        if (board.check_win()) {
            player = (player % 2) + 1;
            board.draw();
            std::cout << "Player " << player << " won!" << std::endl;

        } else // assume draw
            std::cout << "It's a draw!" << std::endl;

        next = 'n';
        std::cout << "Start another game? y/n" << std::endl;
        std::cin >> next;
    }
}