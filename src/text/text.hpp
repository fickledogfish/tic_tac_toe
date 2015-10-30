/**
Functions that relate to manipulating text
*/

#pragma once

#include <string>

namespace txt {
    /**
    Centers a line of text in a field of `field` characters.
    */
    std::string centerTextLine(const std::string text_line, unsigned int field);

    void printCentered(const std::string str, unsigned int field);
}
