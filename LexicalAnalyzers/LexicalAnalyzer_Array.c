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
            !strcmp(str, "switch") || !strcmp(str, "void") ||
            !strcmp(str, "printf") || !strcmp(str, "%d") ||
            !strcmp(str, "%s") || !strcmp(str, "%c")|| 
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

bool isSemicolon(char ch) {
    return (ch == ';');
}

bool isSeperator(char ch) {
    return (ch == ' ' || ch == ',' || ch == '(' || 
            ch == ')' || ch == '{' || ch == '}' || 
            ch == '[' || ch == ']' || ch == '\n' || 
            ch == '\t');
}

bool isStringLiteral(char ch) {
    return (ch == '"');
}

void lexical_analyzer(char* code) {
    int len = strlen(code);
    for (int i = 0; i < len; i++) 
    {
        if (isSeperator(code[i])) 
        {
            if (code[i] == ' ' || code[i] == '\n' || code[i] == '\t') 
            {
                continue;
            }
            printf("Seperator: %c\n", code[i]);
        } 
        else if (isStringLiteral(code[i])) 
        {
            int j = i + 1;
            while (j < len && !isStringLiteral(code[j])) 
            {
                j++;
            }
            if (j < len) 
            {
                char literal[100];
                strncpy(literal, code + i, j - i + 1);
                literal[j - i + 1] = '\0';
                printf("String Literal: %s\n", literal);
                i = j;
            }
        } 
        else if (isOperator(code[i])) 
        {
            printf("Operator: %c\n", code[i]);
        } 
        else if (isSemicolon(code[i])) 
        {
            printf("Semicolon/Separator: %c\n", code[i]);
        }
         else 
         {
            char token[100];
            int j = 0;
            while (i < len && !isSeperator(code[i]) && !isOperator(code[i]) && !isSemicolon(code[i])) 
            {
                token[j++] = code[i++];
            }
            token[j] = '\0';
            i--;

            if (isKeyword(token)) 
            {
                printf("Keyword: %s\n", token);
            }
             else if (isInteger(token)) 
            {
                printf("Integer: %s\n", token);
            }
            else if (isIdentifier(token)) 
            {
                printf("Identifier: %s\n", token);
            } 
            else {
                printf("Unknown: %s\n", token);
            }
        }
    }
}

int main() {
    char code[1000]="";
    FILE *fptr, *fptr1;
    fptr = fopen("C:\\Varshaa\\compiler design\\code1.txt", "w");
    if(fptr == NULL)
    {
        printf("Error");
        exit(1);
    }
    printf("Enter the code:");//give space between every token
    char line[200];
    while(true)
    {
        fgets(line,sizeof(line),stdin);
        if(strcmp(line,"\n")==0)
        {
            break;
        }
        fputs(line,fptr);
    }
    fclose(fptr);
    char code1[1000];
    fptr1 = fopen("C:\\Varshaa\\compiler design\\code1.txt", "r");
    if (fptr1 == NULL) {
        printf("Error opening the file\n");
        return 1;
    }
    size_t bytesRead = fread(code1, sizeof(char), sizeof(code1) - 1, fptr);
    code1[bytesRead] = '\0';
    fclose(fptr1);
    lexical_analyzer(code1);
    return 0;
}
