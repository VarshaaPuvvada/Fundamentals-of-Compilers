#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <ctype.h>

#define MAX_LINES 100
#define MAX_LENGTH 50
 
int isNumber(char *str) {
for (int i = 0; str[i] != '\0'; i++) {
if (!isdigit(str[i])) return 0;
}
return 1;
}

void optimizeCode(char code[MAX_LINES][MAX_LENGTH], int lineCount) {
char temp[MAX_LENGTH];

for (int i = 0; i < lineCount; i++) {
char *op = strstr(code[i], " = ");

if (op != NULL) {
char result[MAX_LENGTH], operand1[MAX_LENGTH], operand2[MAX_LENGTH], operator;

sscanf(code[i], "%s = %s %c %s", result, operand1, &operator, operand2); 
if (isNumber(operand1) && isNumber(operand2)) {
    int op1 = atoi(operand1); 
    int op2 = atoi(operand2); 
    int foldedResult;
    switch (operator) {
        case '+': foldedResult = op1 + op2; 
        break; 
        case '-': foldedResult = op1 - op2; 
        break; 
        case '*': foldedResult = op1 * op2; 
        break;
        case '/': if (op2 != 0) foldedResult = op1 / op2; else continue; break; default: continue;
    }

    sprintf(code[i], "%s = %d", result, foldedResult);
}
else if (operator == '*' && strcmp(operand2, "2") == 0) {
sprintf(code[i], "%s = %s + %s", result, operand1, operand1);
}
else if (operator == '*' && strcmp(operand2, "0") == 0) { sprintf(code[i], "%s = 0", result);
}

else if ((operator == '+' && strcmp(operand2, "0") == 0) ||
(operator == '-' && strcmp(operand2, "0") == 0)) { sprintf(code[i], "%s = %s", result, operand1);
}
else if (operator == '*' && strcmp(operand2, "1") == 0) { sprintf(code[i], "%s = %s", result, operand1);
}
}
}
 
}

int main() {
char code[MAX_LINES][MAX_LENGTH];
int lineCount = 0;

printf("Enter three-address code lines (end input with 'end'):\n"); while (1) {
fgets(code[lineCount], MAX_LENGTH, stdin);
code[lineCount][strcspn(code[lineCount], "\n")] = 0; // Remove newline
if (strcmp(code[lineCount], "end") == 0) break;
lineCount++;
}
optimizeCode(code, lineCount);

printf("\nOptimized code:\n"); for (int i = 0; i < lineCount; i++) {
printf("%s\n", code[i]);
}

return 0;
}
