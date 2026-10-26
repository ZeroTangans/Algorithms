#include "Lab2CPP.h"

static bool check(const vector<string>& tokens) {
    bool token = false;
    int bracketCount = 0;
    for (size_t i = 0; i < tokens.size(); i++) {
        const string& t = tokens[i];
        if (isdigit(static_cast<unsigned char>(t[0]))) {
            if (token) return false;
            token = true;
        }
        else if(t == "+" || t == "-" || t == "*" || t == "/") {
            if (!token) return false;
            token = false;
        }
        else if (t == "(") {
            if (token) return false;
            bracketCount++;
        }
        else if (t == ")") {
            if (!token) return false;
            bracketCount--;
            if (bracketCount < 0) return false;
        }
        else return false;
    }

    return token && bracketCount == 0;
}

vector<string>* tokens_create_and_read(ifstream& input)
{
    vector<string> tokens;

    string expression;
    if (!getline(input, expression)) {
        return nullptr;
    }

    size_t i = 0;
    while (i < expression.size()) {
        char c = expression[i];

        if (isspace(static_cast<unsigned char>(c))) {
            i++;
            continue;
        }

        if (isdigit(static_cast<unsigned char>(c))) {
            string num;
            while (i < expression.size() && isdigit(static_cast<unsigned char>(expression[i]))) {
                num += expression[i];
                i++;
            }
            tokens.push_back(num);
        }
        else {
            tokens.push_back(string(1, c));
            i++;
        }
    }
    if (!check(tokens)) return nullptr;
    return new vector<string>(move(tokens));
}

