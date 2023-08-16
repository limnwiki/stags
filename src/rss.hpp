#pragma once
#include "data.hpp"
#include "html.hpp"
#include "error.hpp"
#include "config.hpp"

std::string get_feed(const json& feed, const std::string& value)
{
    if (feed.contains(value))
        return feed[value];
    else
        error("rss feed does not contain required item '"+value+'\'', true);

    return "";
}

void generate_rss_feeds()
{
    auto feeds = get_config("rss_feeds");

    for (const auto& feed : feeds)
    {
        const std::string& file = get_feed(feed, "file"), url = variables["site_url"], source = get_feed(feed, "source");

        write_file(file, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<rss version=\"2.0\">\n\n<channel>\n"); // creates file and adds rss and xml info
        append_file(file, "<title>"+get_feed(feed, "title")+"</title>\n"); // add title
        append_file(file, "<description>"+get_feed(feed, "description")+"</description>\n"); // add site url
        append_file(file, "<link>"+url+"</link>\n"); // add site url

        if (std::filesystem::exists("public/"+source))
        {
            for (const auto& entry : std::filesystem::recursive_directory_iterator("public/"+source))
            {
                if (!entry.is_regular_file() || entry.path().extension() != ".html")
                    continue;

                if (entry.path().filename() == "index.html" && (!feed.contains("include_index") || !feed["include_index"]))
                    continue;

                const std::string& html = read_file(entry.path());
                const std::string& title = get_tag("title", html);
                const std::string& content = get_tag(get_feed(feed, "content_tag"), html);
                const std::string& date = get_meta_attr("date", html);

                append_file(file, "<item>\n");
                append_file(file, "<title>"+title+"</title>\n"); // add title

                std::string location;

                if (!source.empty())
                    location = '/';

                if (get_config("auto_routes"))
                {
                    location+=entry.path().stem().string();

                    if (entry.path().stem().string() == "index")
                        location+=".html";
                }
                else
                    location+=entry.path().filename().string();
                
                append_file(file, "<link>"+url+source+location+"</link>\n"); // add site url
                append_file(file, "<pubDate>"+date+"</pubDate>\n"); // add date                
                append_file(file, "<description>"+content+"</description>\n"); // add title
                append_file(file, "</item>\n");
            }
        }
        else
            error("can not find rss source: 'public/"+source+'\'');

        append_file(file, "</channel>\n</rss>");
    }
}