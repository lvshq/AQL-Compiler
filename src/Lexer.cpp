/*
Author :
            Liqiang Zheng    --- 13354467
            Nan Zhang        --- 13354433
            Yiting Lin       --- 13331157
            Shuangquan Lyu   --- 13331188

Purpose:    Deal with the ".aql" file.
*/

#include "Lexer.h"
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <stdlib.h>
using namespace std;


Lexer::Lexer(){
    reserve(new Word("create", Tag::CREATE, 0, 0));
    reserve(new Word("view", Tag::VIEW, 0, 0));
    reserve(new Word("as", Tag::AS, 0, 0));
    reserve(new Word("output", Tag::OUTPUT, 0, 0));
    reserve(new Word("select", Tag::SELECT, 0, 0));
    reserve(new Word("from", Tag::FROM, 0, 0));
    reserve(new Word("extract", Tag::EXTRACT, 0, 0));
    reserve(new Word("regex", Tag::REGEX, 0, 0));
    reserve(new Word("on", Tag::ON, 0, 0));
    reserve(new Word("return", Tag::RETURN, 0, 0));
    reserve(new Word("and", Tag::AND, 0, 0));
    reserve(new Word("Token", Tag::TOKEN, 0, 0));
    reserve(new Word("pattern", Tag::PATTERN, 0, 0));
    reserve(new Word("group", Tag::GROUP, 0, 0));
}

Lexer::Lexer(string aqlFile) {

	file = fopen(aqlFile.c_str(), "r");

    //将关键字放入字符串表中
    reserve(new Word("create", Tag::CREATE, 0, 0));
    reserve(new Word("view", Tag::VIEW, 0, 0));
    reserve(new Word("as", Tag::AS, 0, 0));
    reserve(new Word("output", Tag::OUTPUT, 0, 0));
    reserve(new Word("select", Tag::SELECT, 0, 0));
    reserve(new Word("from", Tag::FROM, 0, 0));
    reserve(new Word("extract", Tag::EXTRACT, 0, 0));
    reserve(new Word("regex", Tag::REGEX, 0, 0));
    reserve(new Word("on", Tag::ON, 0, 0));
    reserve(new Word("return", Tag::RETURN, 0, 0));
    reserve(new Word("and", Tag::AND, 0, 0));
    reserve(new Word("Token", Tag::TOKEN, 0, 0));
    reserve(new Word("pattern", Tag::PATTERN, 0, 0));
    reserve(new Word("group", Tag::GROUP, 0, 0));
}

//功能：将World*类型的w放入字符串表中，即将ID或关键字对应的Token放入表中
void Lexer::reserve (Word* w){
    words[w->lexeme] = w;
}
    
//读取下一个字符    
void Lexer::readch(){
    column++;
    peek = fgetc(file);
}
    
//读取下一个字符，并匹配是否为c
bool Lexer::readch(char c){
    readch();
    if(peek != c) return false;
    peek = ' ';
    return true;
}
    
//判断c是否为字母    
bool Lexer::isLetter(char c){
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        return true;
    }
    return false;
}

//判断c是否为数字
bool Lexer::isDigit(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}
   

//功能：读取一个Token
//返回类型：Token*    
Token* Lexer::scan(){

    //剔除空白
    for(;;readch()){
        if(peek == ' ' || peek == '\t') continue;
        else if (peek == '\n'){
            line ++;
            column = 0;
            }
        else break;
    }

    //如果是文件结尾，则返回一个END的Token
    if (peek == EOF) {
        return new End(0, 0);
    }
    
    //返回NUM类型的Token
    if(isDigit(peek)){
        int v = 0;
        do{
            v = 10*v + (peek - '0');
            readch();
        }while(isDigit(peek));
        return new Num(v, line, column);
    }

    //返回REG类型的Token
    if(peek == '/'){
        string buffer = "";
        readch();
        while(peek != '/'){
            buffer += peek;
            readch();
        }
        readch();
        string s = buffer;
        return new Regex(s, Tag::REG, line, column);
    }
    
    //返回ID类型或关键字的Token
    //若字符串已经在字符表中，则返回字符表中的Token
    //否则放回一个新建ID类型的Token，并把它放在字符表中
    if( isLetter(peek) ){
        string buffer = "";
        do{
            buffer += peek;
            readch();
        } while(isLetter(peek) || isDigit(peek));
        
        string s = buffer;
        if(words.count(s) == 0){
            Word* w = new Word(s, Tag::ID, line, column);
            words[s] = w;
            return w;
        }
        else{
            return new Word(words[s]->lexeme, words[s]->tag, line, column);
        }
    }
    Token* tok = new Token(peek, line, column); peek = ' ';
    return tok;
}
