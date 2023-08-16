#pragma once
#include <vector>
#include "error.hpp"

enum TokenType
{
    TOKEN_WORD,
    TOKEN_STRING,
    TOKEN_TEMPLATE_STRING,
    TOKEN_SHELL,
};

struct Token
{
    TokenType type;
    std::string value;
};

std::vector<Token> get_tokens(std::string text, int start, int end)
{
    std::vector<Token> tokens;
    std::string word;

    for (int i = start+2; i < end-1; i++)
    {
        if (text[i] == '"')
        {
            i++;

            while (text[i] != '"') 
            {
                if (text[i] == '\\' && text[i+1] == '"')
                    i++;

                word+=text[i];
                i++;
            }
            tokens.push_back({TOKEN_STRING, word});
            word.clear();
            i++;
            continue;
        }
        else if (text[i] == '\'')
        {
            i++;
            while (text[i] != '\'') 
            {
                if (text[i] == '\\' && text[i+1] == '\'')
                    i++;

                word+=text[i];
                i++;
            }
            tokens.push_back({TOKEN_TEMPLATE_STRING, word});
            word.clear();
            i++;
            continue;
        }
        else if (text[i] == ' ' && !word.empty())
        {
            tokens.push_back({TOKEN_WORD, word});
            word.clear();
        }
        else if (text[i] == '$') 
        {
            if (!word.empty())
                error("can not execute shell script in word");
            tokens.push_back({TOKEN_SHELL, ""});
        }
        else if (text[i] != ' ')
            word+=text[i];
    }

    return tokens;
}