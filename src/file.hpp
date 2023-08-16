#pragma once
#include <fstream>
#include <filesystem>
#include "error.hpp"

const std::string read_file(const std::string& filePath)
{
    if (!std::filesystem::exists(filePath))
        error("file '"+filePath+"' does not exist", true);

    std::ifstream file(filePath);
    std::string output, content;

    if (file.peek() == std::ifstream::traits_type::eof())
    {
        warn('\''+filePath+"' is an empty file!", true);
        return "";
    }

    while (std::getline(file, output)) content+=output+'\n';
    content.pop_back();

    return content;
}

void write_file(const std::string& filePath, const std::string& text)
{
    std::ofstream file(filePath);
    file << text;
}

void append_file(const std::string& filePath, const std::string& text)
{
    std::ofstream file(filePath, std::ios_base::app);
    file << text;
}
