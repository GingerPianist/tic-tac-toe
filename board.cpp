#include "classes.hpp"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>

#ifdef WINDOWS
#include <Windows.h>
#else
#include <unistd.h>
#endif

Board::Board() {
    size = 5;
    for (int i = 0; i <= 100; ++i)
        numbers[i] = std::to_string(i);
}

void Board::draw_floor() {
    for (int k = 0; k < size; ++k) {
        for (int i = 0; i < size; ++i)
            std::cout << "_";
        if (k < size - 1)
            std::cout << "|";
    }
    std::cout << std::endl;
}
void Board::draw_empty() {

    for (int k = 0; k < size; ++k) {

        for (int i = 0; i < size; ++i)
            std::cout << " ";
        if (k < size - 1)
            std::cout << "|";
    }
    std::cout << std::endl;
}
int Board::draw_number(int number) {
    int local_size = size - 1;
    if (size % 2 == 0)
        local_size -= 1;
    if (number > 10)
        local_size -= 1;

    for (int k = 0; k < size; ++k) { // each "box"

        for (int i = 0; i < size / 2; ++i)
            std::cout << " ";

        switch (numbers[number][0]) {
        case 'X':
            std::cout << "\e[1;96m" << numbers[number]; // << "\033[0m";
            break;
        case 'O':
            std::cout << "\e[1;31m" << numbers[number]; // << "\033[0m";
            break;
        default:
            std::cout << numbers[number];
            break;
        }
        std::cout << "\033[0m";
        // std::cout << numbers[number]; // << " " << local_size;
        for (int i = 0; i < local_size / 2; ++i)
            std::cout << " ";

        if (k < size - 1)
            std::cout << "|";
        ++number;
        if (number == 10)
            local_size -= 1;
    }

    std::cout << std::endl;
    return number;
}

void Board::draw() {

#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif

    std::cout << "   \e[30;42mConsole tic-tac-toe game" << std::endl;
    std::cout << "Player 1 <O> - - - Player 2 <X> \033[0m" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    int board_number = 1;

    for (int t = 0; t < size; ++t) {
        for (int k = 0; k < size / 2; ++k)
            draw_empty();
        board_number = draw_number(board_number);
        for (int k = 1; k < size / 2; ++k)
            draw_empty();
        if (t < size - 1)
            draw_floor();
    }
}

void Board::change_numbers(std::string number, std::string ch) {
    int integer_number = 0, base = 1;

    for (int i = 0; i < number.length(); ++i) {
        integer_number += ((int)number[number.length() - 1 - i] - 48) * base;
        base *= 10;
        if (i != 0)
            ch += ' ';
    }
    numbers[integer_number] = ch;
}

bool Board::check_win() {

    // horizontal combinations
    for (int i = 1; i <= 1 + (size * (size - 1)); i += size) {
        bool win = true;
        for (int j = i; j < i + size - 1; ++j)
            if (numbers[j] != numbers[j + 1]) {
                win = false;
                break;
            }
        if (win)
            return true;
    }

    // vertical combinations
    for (int i = 1; i <= size; ++i) {
        bool win = true;
        for (int j = i; j < i + (size * (size - 1)); j += size) {
            if (numbers[j][0] != numbers[j + size][0]) {
                win = false;
                break;
            }
        }
        if (win)
            return true;
    }

    // across combinations
    bool win = true;
    for (int i = 1; i < size * size; i = i + size + 1)
        if (numbers[i][0] != numbers[i + size + 1][0]) {
            win = false;
            break;
        }
    if (win)
        return true;

    win = true;
    for (int i = size; i < (size * size) - size + 1; i = i + size - 1)
        if (numbers[i][0] != numbers[i + size - 1][0]) {
            win = false;
            break;
        }
    if (win)
        return true;
    //

    return false;
}

bool Board::check_draw() {
    for (int i = 1; i <= size * size; ++i) {
        if (numbers[i][0] != 'X' && numbers[i][0] != 'O')
            return false;
    }
    return true;
}

bool Board::check_input(std::string number) {
    // make this function more contained!!!!!!!!
    if (number.length() > 2) {
        std::cout << "This number is not in range! Try another one!" << std::endl;
        sleep(1);
        return false;
    }

    if (number.length() == 2) {
        for (int i = 0; i < number.length(); ++i)
            if (number[i] < 48 || number[i] > 56) {
                std::cout << "This is not a number! Try another one!" << std::endl;
                sleep(1);
                return false;
            }

        int integer_number = ((int)number[0] - 48) * 10 + ((int)number[1] - 48);

        if (integer_number > size * size || integer_number <= 0) {
            std::cout << "This number is not in range! Try another one!" << std::endl;
            sleep(1);
            return false;
        }
        return true;
    }

    int integer_number = (int)number[0] - '0';

    if (integer_number < 1 || integer_number > 9 || integer_number <= 0) {
        std::cout << "This is not a number! Try another one!" << std::endl;
        sleep(1);
        return false;
    }
    if (numbers[integer_number][0] == 'O' || numbers[integer_number][0] == 'X') {
        std::cout << "This number is taken. Try another one!" << std::endl;
        sleep(1);
        return false;
    }

    return true;
}

void Board::set_size() {
    int board_size;
    std::cout << "\e[3mPlease enter the board size (number from 3 to 9): \033[0m";
    std::cin >> board_size;
    while (board_size > 9 || board_size < 3) {
        std::cout << "\e[101mThe size is not a number between 3 and 9! Try another one:\033[0m";
        std::cin >> board_size;
    }

    size = board_size;
}
