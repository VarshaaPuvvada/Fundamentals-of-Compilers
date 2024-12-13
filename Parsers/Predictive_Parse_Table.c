#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SYMBOLS 100
#define MAX_PRODUCTIONS 10
#define MAX_TERMINALS 20
#define MAX_NONTERMINALS 20

typedef struct {
    char lhs;
    char rhs[MAX_PRODUCTIONS][MAX_SYMBOLS];
    int count;
} Production;

typedef struct {
    char terminal;
    char production[MAX_SYMBOLS];
} TerminalProduction;

typedef struct {
    char nonTerminal;
    TerminalProduction entries[MAX_TERMINALS];
    int count;
} ParseTableEntry;

Production productions[MAX_NONTERMINALS];
int productionCount = 0;
char terminals[MAX_TERMINALS];
int terminalCount = 0;
char nonTerminals[MAX_NONTERMINALS];
int nonTerminalCount = 0;
char firstSets[MAX_NONTERMINALS][MAX_SYMBOLS][MAX_SYMBOLS];
int firstCount[MAX_NONTERMINALS];
char followSets[MAX_NONTERMINALS][MAX_SYMBOLS][MAX_SYMBOLS];
int followCount[MAX_NONTERMINALS];
ParseTableEntry parseTable[MAX_NONTERMINALS];
int parseTableCount = 0;

int isNonTerminalChar(char c) {
    return isupper(c);
}

int containsString(char set[][MAX_SYMBOLS], int count, char *symbol) {
    for(int i = 0; i < count; i++) {
        if(strcmp(set[i], symbol) == 0)
            return 1;
    }
    return 0;
}

void addTerminal(char c) {
    if(!isNonTerminalChar(c) && c != 'e' && c != '$') {
        for(int i = 0; i < terminalCount; i++) {
            if(terminals[i] == c)
                return;
        }
        terminals[terminalCount++] = c;
    }
}

void addNonTerminal(char c) {
    for(int i = 0; i < nonTerminalCount; i++) {
        if(nonTerminals[i] == c)
            return;
    }
    nonTerminals[nonTerminalCount++] = c;
}

int findProductionIndex(char lhs) {
    for(int i = 0; i < productionCount; i++) {
        if(productions[i].lhs == lhs)
            return i;
    }
    return -1;
}

void addProduction(char lhs, const char *rhs) {
    int index = findProductionIndex(lhs);
    if(index == -1) {
        productions[productionCount].lhs = lhs;
        strcpy(productions[productionCount].rhs[productions[productionCount].count++], rhs);
        addNonTerminal(lhs);
        productionCount++;
    }
    else {
        strcpy(productions[index].rhs[productions[index].count++], rhs);
    }
}

void computeFirst(char symbol, char result[][MAX_SYMBOLS], int *resCount) {
    if(!isNonTerminalChar(symbol)) {
        char temp[2] = {symbol, '\0'};
        if(!containsString(result, *resCount, temp)) {
            strcpy(result[*resCount], temp);
            (*resCount)++;
        }
        return;
    }
    int index = findProductionIndex(symbol);
    if(index == -1) return;
    for(int i = 0; i < productions[index].count; i++) {
        char first = productions[index].rhs[i][0];
        if(first == 'e') {
            char temp[] = "e";
            if(!containsString(result, *resCount, temp)) {
                strcpy(result[*resCount], temp);
                (*resCount)++;
            }
        }
        else if(!isNonTerminalChar(first)) {
            char temp[2] = {first, '\0'};
            if(!containsString(result, *resCount, temp)) {
                strcpy(result[*resCount], temp);
                (*resCount)++;
            }
            addTerminal(first);
        }
        else {
            computeFirst(first, result, resCount);
        }
    }
}
void computeFirstSets() {
    for(int i = 0; i < nonTerminalCount; i++) {
        firstCount[i] = 0;
        computeFirst(nonTerminals[i], firstSets[i], &firstCount[i]);
    }
}
void computeFollow(char symbol, char result[][MAX_SYMBOLS], int *resCount) {
    if(symbol == productions[0].lhs) {
        char temp[] = "$";
        if(!containsString(result, *resCount, temp)) {
            strcpy(result[*resCount], temp);
            (*resCount)++;
        }
    }
    for(int i = 0; i < productionCount; i++) {
        for(int j = 0; j < productions[i].count; j++) {
            char *prod = productions[i].rhs[j];
            for(int k = 0; k < strlen(prod); k++) {
                if(prod[k] == symbol) {
                    if(k + 1 < strlen(prod)) {
                        char next = prod[k + 1];
                        if(next == 'e') {
                            computeFollow(productions[i].lhs, result, resCount);
                        }
                        else if(!isNonTerminalChar(next)) {
                            char temp[2] = {next, '\0'};
                            if(!containsString(result, *resCount, temp)) {
                                strcpy(result[*resCount], temp);
                                (*resCount)++;
                            }
                        }
                        else {
                            int nextIndex = findProductionIndex(next);
                            if(nextIndex != -1) {
                                for(int f = 0; f < firstCount[nextIndex]; f++) {
                                    if(strcmp(firstSets[nextIndex][f], "e") != 0) {
                                        if(!containsString(result, *resCount, firstSets[nextIndex][f])) {
                                            strcpy(result[*resCount], firstSets[nextIndex][f]);
                                            (*resCount)++;
                                        }
                                    }
                                }
                                int contains_e = 0;
                                for(int f = 0; f < firstCount[nextIndex]; f++) {
                                    if(strcmp(firstSets[nextIndex][f], "e") == 0) {
                                        contains_e = 1;
                                        break;
                                    }
                                }
                                if(contains_e) {
                                    int lhsIndex = findProductionIndex(productions[i].lhs);
                                    if(lhsIndex != -1) {
                                        for(int f = 0; f < followCount[lhsIndex]; f++) {
                                            if(!containsString(result, *resCount, followSets[lhsIndex][f])) {
                                                strcpy(result[*resCount], followSets[lhsIndex][f]);
                                                (*resCount)++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else {
                        int lhsIndex = findProductionIndex(productions[i].lhs);
                        if(lhsIndex != -1) {
                            for(int f = 0; f < followCount[lhsIndex]; f++) {
                                if(!containsString(result, *resCount, followSets[lhsIndex][f])) {
                                    strcpy(result[*resCount], followSets[lhsIndex][f]);
                                    (*resCount)++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void computeFollowSets() {
    for(int i = 0; i < nonTerminalCount; i++) {
        followCount[i] = 0;
    }
    int changed = 1;
    while(changed) {
        changed = 0;
        for(int i = 0; i < nonTerminalCount; i++) {
            char current = nonTerminals[i];
            char tempSet[MAX_SYMBOLS][MAX_SYMBOLS];
            int tempCount = 0;
            computeFollow(current, tempSet, &tempCount);
            for(int j = 0; j < tempCount; j++) {
                if(!containsString(followSets[i], followCount[i], tempSet[j])) {
                    strcpy(followSets[i][followCount[i]++], tempSet[j]);
                    changed = 1;
                }
            }
        }
    }
}

void computeParseTable() {
    for(int i = 0; i < nonTerminalCount; i++) {
        parseTable[i].nonTerminal = nonTerminals[i];
        parseTable[i].count = 0;
    }
    for(int i = 0; i < productionCount; i++) {
        char lhs = productions[i].lhs;
        int lhsIndex = -1;
        for(int nt = 0; nt < nonTerminalCount; nt++) {
            if(nonTerminals[nt] == lhs) {
                lhsIndex = nt;
                break;
            }
        }
        if(lhsIndex == -1) continue;
        for(int p = 0; p < productions[i].count; p++) {
            char *prod = productions[i].rhs[p];
            if(prod[0] == 'e') {
                for(int f = 0; f < followCount[lhsIndex]; f++) {
                    parseTable[lhsIndex].entries[parseTable[lhsIndex].count].terminal = followSets[lhsIndex][f][0];
                    strcpy(parseTable[lhsIndex].entries[parseTable[lhsIndex].count].production, "e");
                    parseTable[lhsIndex].count++;
                }
            }
            else {
                char first = prod[0];
                if(!isNonTerminalChar(first)) {
                    parseTable[lhsIndex].entries[parseTable[lhsIndex].count].terminal = first;
                    strcpy(parseTable[lhsIndex].entries[parseTable[lhsIndex].count].production, prod);
                    parseTable[lhsIndex].count++;
                    addTerminal(first);
                }
                else {
                    int firstIndex = findProductionIndex(first);
                    if(firstIndex != -1) {
                        for(int f = 0; f < firstCount[firstIndex]; f++) {
                            if(strcmp(firstSets[firstIndex][f], "e") != 0) {
                                parseTable[lhsIndex].entries[parseTable[lhsIndex].count].terminal = firstSets[firstIndex][f][0];
                                strcpy(parseTable[lhsIndex].entries[parseTable[lhsIndex].count].production, prod);
                                parseTable[lhsIndex].count++;
                            }
                        }
                        int contains_e = 0;
                        for(int f = 0; f < firstCount[firstIndex]; f++) {
                            if(strcmp(firstSets[firstIndex][f], "e") == 0) {
                                contains_e = 1;
                                break;
                            }
                        }
                        if(contains_e) {
                            for(int f = 0; f < followCount[lhsIndex]; f++) {
                                parseTable[lhsIndex].entries[parseTable[lhsIndex].count].terminal = followSets[lhsIndex][f][0];
                                strcpy(parseTable[lhsIndex].entries[parseTable[lhsIndex].count].production, prod);
                                parseTable[lhsIndex].count++;
                            }
                        }
                    }
                }
            }
        }
    }
}

void displayFirstSets() {
    printf("\nFIRST Sets:\n");
    for(int i = 0; i < nonTerminalCount; i++) {
        printf("FIRST(%c) = { ", nonTerminals[i]);
        for(int j = 0; j < firstCount[i]; j++) {
            printf("%s ", firstSets[i][j]);
        }
        printf("}\n");
    }
}

void displayFollowSets() {
    printf("\nFOLLOW Sets:\n");
    for(int i = 0; i < nonTerminalCount; i++) {
        printf("FOLLOW(%c) = { ", nonTerminals[i]);
        for(int j = 0; j < followCount[i]; j++) {
            printf("%s ", followSets[i][j]);
        }
        printf("}\n");
    }
}

void displayParseTable() {
    printf("\nParse Table:\n");
    printf("NT\tTerminal\tProduction\n");
    for(int i = 0; i < nonTerminalCount; i++) {
        for(int j = 0; j < parseTable[i].count; j++) {
            printf("%c\t%c\t\t%c->%s\n", parseTable[i].nonTerminal, parseTable[i].entries[j].terminal, parseTable[i].nonTerminal, parseTable[i].entries[j].production);
        }
    }
}

void predictiveParse(char input_string[], ParseTableEntry parse_table[], int rule_count) {
    char stack[MAX_SYMBOLS];
    int top = 0;
    stack[top++] = '$';  // Stack initialized with end marker
    stack[top++] = productions[0].lhs;  // Start symbol of the grammar
    strcat(input_string, "$");  // Append end marker to input string
    int ptr = 0;  // Pointer for the input string

    printf("\nStack\t\tInput\t\tAction\n");

    while (top > 0) {
        stack[top] = '\0';  // Null-terminate stack for printing
        printf("%s\t\t%s\t\t", stack, &input_string[ptr]);

        char topSymbol = stack[--top];  // Pop the top of the stack
        char current = input_string[ptr];

        if (topSymbol == current) {
            // Match terminal; move input pointer
            printf("Match %c\n", current);
            ptr++;
        } else if (isNonTerminalChar(topSymbol)) {
            // Look up production in parse table
            int found = 0;
            for (int i = 0; i < nonTerminalCount; i++) {
                if (parse_table[i].nonTerminal == topSymbol) {
                    for (int j = 0; j < parse_table[i].count; j++) {
                        if (parse_table[i].entries[j].terminal == current) {
                            // Apply production and push RHS in reverse order
                            char *production = parse_table[i].entries[j].production;
                            printf("%c->%s\n", topSymbol, production);
                            int len = strlen(production);
                            for (int k = len - 1; k >= 0; k--) {
                                if (production[k] != 'e') {  // Ignore epsilon
                                    stack[top++] = production[k];
                                }
                            }
                            found = 1;
                            break;
                        }
                    }
                    break;
                }
            }
            if (!found) {
                // No valid production found; reject string
                printf("Error: No matching rule for %c with %c\n", topSymbol, current);
                printf("String rejected.\n");
                return;
            }
        } else {
            // Mismatched terminal symbol; reject string
            printf("Error: Unexpected terminal %c\n", current);
            printf("String rejected.\n");
            return;
        }
    }
    printf("String accepted");
    
}

int main() {
    addProduction('E', "TA");
    addProduction('A', "+TA");
    addProduction('A', "e");
    addProduction('T', "FB");
    addProduction('B', "*FB");
    addProduction('B', "e");
    addProduction('F', "(E)");
    addProduction('F', "a");
    
    // addProduction('S', "(L)");
    // addProduction('S', "a");
    // addProduction('L', "SA");
    // addProduction('A', ",SA");
    // addProduction('A', "e");

    computeFirstSets();

    computeFollowSets();

    computeParseTable();

    displayFirstSets();

    displayFollowSets();

    displayParseTable();

    char input_string[] = "a+a*a"; // Example input string
    predictiveParse(input_string, parseTable, parseTableCount);
    return 0;
}
