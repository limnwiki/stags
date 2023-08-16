#pragma once
#include <iostream>
#include <filesystem>
#include "json.hpp"
#include "file.hpp"

void create_site(const std::string& path)
{
    if (!std::filesystem::exists(path))
        std::filesystem::create_directories(path);

    std::filesystem::current_path(path);

    std::filesystem::create_directory("data");
    std::filesystem::create_directory("pages");
    std::filesystem::create_directory("assets");
    std::filesystem::create_directory("public");
    std::filesystem::create_directory("components");

    write_file(CONFIG_FILE,
    "{\n"
    "\t\"url\": \"https://www.example.com/\",\n"
    "\t\"testing_url\": \"http://localhost:8000/\",\n"
    "\t\"data_processing_command\": \"\",\n"
    "\t\"variables\": {},\n"
    "\t\"rss_feeds\": [],\n"
    "\t\"auto_routes\": true,\n"
    "\t\"clear_public_directory\": true\n"
    "}"
    );
}