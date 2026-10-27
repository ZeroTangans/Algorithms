#include "Lab2CPP.h"

Tokens* tokens_create_and_read(ifstream& input)
{
    Tokens tokens;

    string expression;
    if (!getline(input, expression)) {
        return nullptr;
    }

    size_t i = 0;
    bool token = false;
    int bracketCount = 0;
    while (i < expression.size()) {
        char c = expression[i];

        if (isspace(static_cast<unsigned char>(c))) {
            i++;
            continue;
        }

        if (isdigit(static_cast<unsigned char>(c))) {
            if (token) return nullptr;
            token = true;
            string num;
            while (i < expression.size() && isdigit(static_cast<unsigned char>(expression[i]))) {
                num += expression[i];
                i++;
            }
            tokens.push_back(num);
        }
        else {
            if (c == '+' || c == '-' || c == '*' || c == '/') {
                if (!token) return nullptr;
                token = false;
            }
            else if (c == '(') {
                if (token) return nullptr;
                bracketCount++;
            }
            else if (c == ')') {
                if (!token) return nullptr;
                bracketCount--;
                if (bracketCount < 0) return nullptr;
            }
            else return nullptr;
            tokens.push_back(string(1, c));
            i++;
        }
    }
    if (!token || bracketCount != 0) return nullptr;
    return new Tokens(move(tokens));
}

