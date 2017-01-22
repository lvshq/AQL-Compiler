/*
Author :
            Liqiang Zheng    --- 13354467
            Nan Zhang        --- 13354433
            Yiting Lin       --- 13331157
            Shuangquan Lyu   --- 13331188

Purpose:    Extract Tokens for Lexer and Parser.
*/

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TextToken {
    string textToken;
    int start;
    int end;
    TextToken(string t, int s, int e) {
        textToken = t;
        start = s;
        end = e;
    }
};

class Tokenizer {
private:
    string file_path;
    string content;
    vector<TextToken> textTokens;
    bool isDigit(const char c);
    bool isLetter(const char c);
public:
    Tokenizer();
    Tokenizer(string file_path);
    ~Tokenizer();
    void run();
    void setFilePath(string file_path);
    string getFilePath();
    string getLocationPath();
    string getContent();
    vector<TextToken> getTextTokens();
};

#endif