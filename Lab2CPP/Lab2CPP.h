#ifndef LAB2CPP
#define LAB2CPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <utility>

using namespace std;

using Tokens = vector<string>;

Tokens* tokens_create_and_read(ifstream& input);

#endif