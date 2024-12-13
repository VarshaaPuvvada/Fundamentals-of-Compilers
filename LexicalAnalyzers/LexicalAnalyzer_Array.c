#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || 
            ch == '/' || ch == '>' || ch == '<' || 
            ch == '=');
}

bool isKeyword(char* str) {
    return (!strcmp(str, "if") || !strcmp(str, "else") || 
            !strcmp(str, "while") || !strcmp(str, "do") || 
            !strcmp(str, "break") || !strcmp(str, "continue") || 
            !strcmp(str, "int") || !strcmp(str, "double") || 
            !strcmp(str, "float") || !strcmp(str, "return") || 
            !strcmp(str, "char") || !strcmp(str, "case") || 
            !strcmp(str, "switch") || !strcmp(str, "void")||
            !strcmp(str, "printf") || !strcmp(str,"%d") ||
            !strcmp(str,"%s")||!strcmp(str,"%c")||
            !strcmp(str,"#include") || !strcmp(str,"<stdio.h>"));
}

bool isInteger(char* str) {
    int len = strlen(str);
    if (len == 0) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isIdentifier(char* str) {
    if (!isalpha(str[0]) && str[0] != '_') {
        return false;
    }
    for (int i = 1; i < strlen(str); i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return false;
        }
    }
    return true;
}

bool semicolan(char ch)
{
    return(ch==';');
}

bool isSeperator(char ch) {
    return (ch == ' ' || ch == ',' || ch == '(' || 
            ch == ')' || ch == '{' || ch == '}' || 
            ch == '[' || ch == ']' || ch == '\n' || 
            ch == '\t');
}

bool isStringLiteral(char ch)
{
    return (ch == '"');
}

void lexical_analyzer(char* code) {
    char* token = strtok(code, " ");
    while (token != NULL) {
        if (isKeyword(token)) 
        {
            printf("Keyword: %s\n", token);
        } 
        else if (isInteger(token)) 
        {
            printf("Integer: %s\n", token);
        } 
        else if (isOperator(token[0]) && strlen(token) == 1) 
        {
            printf("Operator: %s\n", token);
        } 
        else if (isIdentifier(token)) 
        {
            printf("Identifier: %s\n", token);
        }
        else if(semicolan(token[0]))
        {   
            printf("Semicolon/Seperator:%s\n",token);
        } 
        else if(isStringLiteral(token[0]))
        {
            char literal[100];
            strcpy(literal, token);
            token = strtok(NULL, "\"");
            if (token != NULL) 
            {
                strcat(literal, " ");
                strcat(literal, token);
                strcat(literal, "\"");
                printf("String Literal: %s\n", literal);
            }
        }
        else if(isSeperator(token[0]))
        {
            printf("Seperator:%s\n",token);
        }
        else {
            printf("Unknown: %s\n", token);
        }
        token = strtok(NULL, " ");
    }
}

int main() {
    char code[100];
    printf("Enter the code:");//give space between every token
    fgets(code,sizeof(code),stdin);
    lexical_analyzer(code);
    return 0;
}
