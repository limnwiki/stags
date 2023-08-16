#pragma once
#include "data.hpp"
#include "error.hpp"

std::string parse_template_string(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '{')
        {
            int start = i;

            i++;
            std::string var;

            while (str[i] != '}') 
            {
                if (i == str.length())
                    error("end of template string value not found");

                if (str[i] != ' ') var+=str[i];
                i++;
            }

            str.erase(start, i-start+1);
            
            if (variables.contains(var))
                str.insert(start, variables[var]);
            else
                error("variable '"+var+"' not found!");
        }
    }

    return str;
}