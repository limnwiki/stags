#pragma once
#include <string>
#include <unordered_map>
#include "json.hpp"

#define CONFIG_FILE "stags.config.json"

using json = nlohmann::json;

struct Component
{
    std::string html, file;
};

json variables;
std::unordered_map<std::string, Component> components;

// used for debug info
int line = 1, column = 1; 
std::string file;