/*
Author :
            Liqiang Zheng    --- 13354467
            Nan Zhang        --- 13354433
            Yiting Lin       --- 13331157
            Shuangquan Lyu   --- 13331188

Purpose:    Deal with the ".aql" file.
*/

#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <map> 
using namespace std;

class Tag{
public:
    //定义Token类型，为每一种Token分配唯一标识符
    static int const CREATE = 250, VIEW = 251, AS = 252, OUTPUT = 253,
    SELECT = 254, FROM = 255, EXTRACT = 256, REGEX = 257,
    ON = 258, RETURN = 259, AND = 260, TOKEN = 261, PATTERN = 262,
    ID = 263, NUM = 264, REG = 265, GROUP = 266, END = 267;
};

class Token{
public:
    int tag;
    int line, column;
    Token() {
        tag = line = column = 0;
    }
    //其他Token类型的基类
    //私有成员tag为Token类型的标识符，line、column为该Token所处的行和列
    //另外，也用于为‘(’ , ‘)’,‘{’,‘}’,‘<’,‘>’,‘,’,‘.’生成Token
    //这时tag是该符号的ASCII码
    Token(int t, int l, int c){
        tag = t;
        line = l;
        column = c;
    }
    //将int类型转换成string类型
    string intToString(int num){
        string s = "";
        while(num > 0){
            
            s = (char)(num % 10 + '0') + s;
            
            num /= 10;
        }
        if(s == "")  s = "0";
        return s;
    }
    //返回该Token的内容
    virtual string toString(){
        char c = tag;
        string str = ".";
        str[0] = c;
        return str;
    }
};


//Num类，继承于Token，用于整形数字
//int类型成员value，为该数字的数值
//重写了toString函数
class Num : public Token{
public:
    int value;
    Num(int v, int l, int c):Token(Tag::NUM, l, c){
        value = v;
    }
    string toString(){
        return intToString(value);
    }
};

//Word类，继承于Token，用于ID和保留字
//string类型成员lexeme，为该ID或保留字的内容
//重写了toString函数
class Word : public Token{
public:
    string lexeme = "";
    Word(string s, int tag, int l, int c):Token(tag, l, c){
        lexeme = s;
    }
    string toString(){
        return lexeme;
    }
    
};

//Regex类，继承于Token，用于正则表达式
//string类型成员lexeme，为正则表达式的内容，不含斜杠
//重写了toString函数
class Regex : public Token{
public:
    string content = "";
    Regex(string s, int tag, int l, int c): Token(tag, l, c){
        content = s;
    }
    string toString(){
        return content;
    }
};

//End类，继承于Token，用于文件的末尾，即EOF
class End : public Token {
public:
    End(int l, int c):Token(Tag::END, l, c){
    }
};

class Lexer{
public:

    Lexer();
    Lexer(string aqlFile);
    void reserve (Word* w);
    void readch();
    bool readch(char c);
    bool isLetter(char c);
    bool isDigit(char c);
    Token* scan();

private:
    FILE *file;
    int line = 1;
    int column = 0;
    char peek = ' ';
    //字符串表
    map<string, Word*> words;
};

#endif