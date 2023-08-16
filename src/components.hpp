#pragma once
#include "data.hpp"
#include "file.hpp"
#include "error.hpp"

void load_components()
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator("components"))
    {
        components[entry.path().stem()].file = entry.path();
        components[entry.path().stem()].html = read_file(entry.path());
    }
}