#include <iostream>
#include <string>

class Board {
  private:
    int size;
    std::string numbers[101];

  public:
    Board();
    void draw();
    void draw_empty();
    void draw_floor();
    int draw_number(int number);
    void change_numbers(std::string number, std::string ch);
    void set_size();
    bool check_win();
    bool check_draw();
    bool check_input(std::string number);
};
