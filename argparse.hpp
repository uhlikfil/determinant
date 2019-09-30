//
// Created by uhlikf on 1/19/2019.
//

#ifndef DETERMINANT_ARGPARSE_HPP
#define DETERMINANT_ARGPARSE_HPP

#include "handler.hpp"


enum argument { HELP, SINGLE, MULTI, CUSTOM, INVALID };

int str_to_int(std::string const &str) {
    std::size_t pos;
    int res = std::stoi(str, &pos);
    if (pos != str.size())
        throw std::invalid_argument("numeric string ends with garbage");
    // and still, std::stod (and its underlying C implementation, strtod)
    // does one more extra thing nobody asked it to: skip (optional) leading
    // whitespace ... damn the stupid library functions
    return res;
}

argument parse_arguments(int &num_of_args, char* arguments[]) {
    if (num_of_args == 2 && strcmp(arguments[1], "--help") == 0) {
        return HELP;
    } else if (num_of_args == 2 && strcmp(arguments[1], "custom") == 0) {
        return CUSTOM;
    } else if (num_of_args == 4 && strcmp(arguments[3], "0") == 0) {
        str_to_int(arguments[2]);
        str_to_int(arguments[3]);

        return SINGLE;
    } else if (num_of_args == 4 && strcmp(arguments[3], "1") == 0) {
        str_to_int(arguments[2]);
        str_to_int(arguments[3]);

        return MULTI;
    } else {
        return INVALID;
    }
}
#endif //DETERMINANT_ARGPARSE_HPP
