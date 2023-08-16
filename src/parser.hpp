#pragma once
#include <stack>
#include "data.hpp"
#include "file.hpp"
#include "error.hpp"
#include "token.hpp"
#include "command.hpp"
#include "template_string.hpp"

std::string parse_template(std::string text)
{
    line = 1, column = 1;
    
    for (size_t i = 0; i < text.size(); i++)
    {
        column++;

        if (text[i] == '\n')
        {
            line++;
            column = 1;
            continue;
        }

        if (text[i] == '{' && text[i+1] == '{')
        {
            int end = 0;

            for (size_t c = i+1; c < text.size(); c++)
            {
                if (text[c] == '{' && text[c+1] == '{')
                {
                    end = 0;
                    break;
                }
                else if (text[c] == '}' && text[c+1] == '}')
                {
                    end = c+1;
                    break;
                }
            }

            if (end == 0)
                error("end of template not found");

            std::vector<Token> tokens = get_tokens(text, i, end);
            std::stack<std::string> stack;

            for (size_t t = 0; t < tokens.size(); t++)
            {
                Token token = tokens[t];

                switch (token.type) 
                {
                    case TOKEN_STRING:
                        stack.push(token.value);
                        break;

                    case TOKEN_TEMPLATE_STRING:
                        stack.push(parse_template_string(token.value));
                        break;

                    case TOKEN_SHELL:
                    {
                        if (tokens[t+1].type == TOKEN_STRING)
                            stack.push(exec(tokens[t+1].value.c_str()));
                        else if (tokens[t+1].type == TOKEN_TEMPLATE_STRING)
                            stack.push(exec(parse_template_string(tokens[t+1].value).c_str()));
                        else if (tokens[t+1].type == TOKEN_WORD && variables.contains(tokens[t+1].value))
                            stack.push(exec(std::string(variables[tokens[t+1].value]).c_str()));
                        else
                            error("can only execute strings and variables");

                        t++;
                        break;
                    }
                    
                    case TOKEN_WORD:
                    {
                        if (variables.contains(token.value))
                            stack.push(variables[token.value]);
                        else if (components.count(token.value))
                        {
                            const size_t args = tokens.size();

                            for (size_t c = t+1; c < args; c++)
                            {
                                variables[std::to_string(c)] = tokens[c].value;
                                t++;
                            }

                            int org_line = line, org_col = column;
                            auto org_file = file;

                            file = components[token.value].file;

                            stack.push(parse_template(components[token.value].html));

                            line = org_line, column = org_col, file = org_file;

                            for (size_t c = 1; c <= args; c++)
                                variables.erase(std::to_string(c));
                        }
                        else
                            error("unknown word: '"+token.value+"'");

                        break;
                    }

                    default:
                        break;
                }
            }
            
            if (stack.size() > 1)
                error("too many values on stack!");
            
            for (auto ch : stack.top())
            {
                if (ch == '\n')
                    line--;
            }

            text.erase(i, end-i+1);
            text.insert(i, stack.top());
            column+=end-i+1-stack.top().length();
        }
    }

    return text;
}

std::string parse_page(const std::string& path)
{
    std::string text = read_file(path);
    file = path;

    return parse_template(text);
}