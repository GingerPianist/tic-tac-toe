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
            // char temp;
            std::cin >> number;
            /* only 2-letter numbers
            temp = number[1];
            number = number[0];
            number = number + temp;
            */
            if (!board.check_input(number))
                continue;

            board.change_numbers(number, (player == 1) ? "O" : "X");
            player = (player % 2) + 1;
        }

        if (board.check_win()) {
            player = (player % 2) + 1;
            board.draw();
            std::cout << std::endl;
            std::cout << "\e[30;42mPlayer " << player << " won!" << std::endl;

        } else { // assume draw
            std::cout << std::endl;
            std::cout << "\e[30;42mIt's a draw!" << std::endl;
        }

        std::cout << "\033[0m";

        next = 'n';
        std::cout << "Start another game? y/n" << std::endl;
        std::cin >> next;
    }
}