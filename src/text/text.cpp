#include "text.hpp"

#include <iostream>
#include <sstream>

std::string txt::centerTextLine(const std::string text_line, unsigned int field) {
    // copy the entered string
    std::string text_centered {text_line};

    /*
    add whitespace before the string.
     
    The number of whitespaces that need to me added can be calculate as:
     
                field          (f)
        |-------------------|
                 text          (n)
            |-----------|
        *********************
        |                   |
        |   laskdjflksad    |
        |   laksjdlkasjt    |
        |   alksdjlkasjn    |
        |                   |
        *********************
        |---|           |---|
          x               x
     
    If we consider `x` to be the number of whitespaces that needs to be
    added before each line of text, `n` is the number of characters in the
    text and `f` is the number of characters in the field, the equation
        
        f = 2.x + n
     
    is valid for each line of text. So
     
            f - n
        x = -----
              2
     
    calculates the needed whitespace for each line.
    */
    text_centered.insert(0, (field - text_line.size())/2, ' ');

    return text_centered;
}

void txt::printCentered(const std::string str, unsigned int field) {
    std::stringstream source_str {str};
    std::string tmp;

    // center each line and print it
    while (std::getline(source_str, tmp, '\n')) {
        std::cout << txt::centerTextLine(tmp, field) << std::endl;
    }
}
