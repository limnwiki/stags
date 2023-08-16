#pragma once
#include <cstdlib>
#include <filesystem>
#include "rss.hpp"
#include "data.hpp"
#include "file.hpp"
#include "config.hpp"
#include "parser.hpp"

void build_site()
{
    if (get_config("clear_public_directory"))
        for (const auto& entry : std::filesystem::directory_iterator("public")) 
            std::filesystem::remove_all(entry.path());

    for (const auto& entry : std::filesystem::recursive_directory_iterator("pages"))
    {
        if (entry.is_directory()) 
            continue;

        const std::filesystem::path& path = entry.path().string().substr(5);

        if (path.has_parent_path())
            std::filesystem::create_directories("public"+path.parent_path().string());

        write_file("public"+path.string(), parse_page(entry.path()));
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator("assets"))
    {
        if (entry.is_directory()) 
            continue;

        const std::filesystem::path& path = entry.path().string().substr(6);

        if (path.has_parent_path())
            std::filesystem::create_directories("public"+path.parent_path().string());

        std::filesystem::copy_file(entry, "public/"+path.string());
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator("data"))
    {
        if (entry.is_directory()) 
            continue;

        const std::filesystem::path& path = entry.path().string().substr(4);

        if (path.has_parent_path())
            std::filesystem::create_directories("public"+path.parent_path().string());

        const std::string& cmd = get_config("data_processing_command");

        variables["file"] = std::filesystem::absolute(entry.path().string());
        variables["dest"] = "public"+path.parent_path().string()+'/'+path.stem().string()+".html";

        system(parse_template_string(cmd).c_str());

        if (std::filesystem::exists(variables["dest"]))
            write_file(variables["dest"], parse_page(variables["dest"]));
    }

    if (config.contains("rss_feeds"))
        generate_rss_feeds();

    if (get_config("auto_routes"))
    {
        for (const auto& entry : std::filesystem::recursive_directory_iterator("public"))
        {
            if (!entry.is_regular_file() || entry.path().extension() != ".html" || entry.path().filename() == "index.html")
                continue;

            const std::filesystem::path& path = entry.path();
            const std::string& new_dir = path.parent_path().string()+'/'+path.stem().string();

            std::filesystem::create_directory(new_dir);
            std::filesystem::rename(entry, new_dir+"/index.html"); // move file
        }
    }
}