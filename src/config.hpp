#pragma once
#include "data.hpp"
#include "file.hpp"
#include "error.hpp"

json config;

json get_config(const std::string& value)
{
    if (config.contains(value))
        return config[value];
    else
        error("config value '"+value+"' not found", true);

    return NULL;
}

void load_config(const char* path)
{
    config = json::parse(read_file(path));
    variables = get_config("variables");
}