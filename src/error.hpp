#pragma once
#include <iostream>
#include "data.hpp"

void warn(const std::string& msg)
{
    std::cerr << file << ':' << line << ':' << column << ": \033[1;33mwarning:\033[0m " << msg << '\n';
}

void warn(const std::string& msg, bool no_file_info) // bool added to create function overload
{
    std::cerr << "\033[1;33mwarning:\033[0m " << msg << '\n';
}

void error(const std::string& msg)
{
    std::cerr << file << ':' << line << ':' << column << ": \033[1;31merror:\033[0m " << msg << '\n';
    exit(1);
}

void error(const std::string& msg, bool no_file_info)
{
    std::cerr << "\033[1;31merror:\033[0m " << msg << '\n';
    exit(1);
}