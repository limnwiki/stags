#pragma once
#include <cctype>
#include <boost/regex.hpp>

std::string get_tag(const std::string& tag, const std::string& html)
{
    boost::regex tag_regex("<"+tag+".*?>(.*?)</"+tag+">");

    auto content_begin = boost::sregex_iterator(html.begin(), html.end(), tag_regex);
    auto content_end = boost::sregex_iterator();

    for (boost::sregex_iterator i = content_begin; i != content_end; i++) 
    {
        boost::smatch match = *i;
        return match.str(1);
    }

    return "";
}

std::string get_meta_attr(const std::string& name, const std::string& html)
{
    boost::regex attr_regex("<meta.*?name=\""+name+"\".*?content=\"(.*?)\".*?>|<meta.*?content=\"(.*?)\".*?name=\""+name+"\".*?>");

    auto content_begin = boost::sregex_iterator(html.begin(), html.end(), attr_regex);
    auto content_end = boost::sregex_iterator();

    for (boost::sregex_iterator i = content_begin; i != content_end; i++) 
    {
        boost::smatch match = *i;
        return match.str(1);
    }

    return "";
}