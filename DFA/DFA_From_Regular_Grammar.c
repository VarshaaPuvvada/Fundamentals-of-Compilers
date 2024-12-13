#include <stdio.h>
#include <string.h>

int findStateIndex(char states[][5], int n_states, char state[]) {
    for (int i = 0; i < n_states; i++) {
        if (strcmp(states[i], state) == 0) {
            return i;
        }
    }
    return -1;
}

int findSymbolIndex(char symbols[][2], int n_symbols, char symbol[]) {
    for (int i = 0; i < n_symbols; i++) {
        if (strcmp(symbols[i], symbol) == 0) {
            return i;
        }
    }
    return -1; 
}

int isFinalState(char final[][5], int n_final, char state[]) {
    for (int i = 0; i < n_final; i++) {
        if (strcmp(final[i], state) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int n_states;
    printf("Enter the no. of states:");
    scanf("%d",&n_states);
    char states[n_states][5];
    for(int i=0;i<n_states;i++)
    {
        printf("Enter the state %d:",i+1);
        scanf("%s",&states[i]);
    }
    int n_symbols;
    printf("Enter the number of symbols:");
    scanf("%d",&n_symbols);
    char symbols[n_symbols][2];
    for(int i=0;i<n_symbols;i++)
    {
        printf("Enter symbol %d:",i+1);
        scanf("%s",&symbols[i]);
    }
    char start[1][5];
    printf("Enter the start state:");
    scanf("%s",&start[0]);
    int n_final;
    printf("Enter the number of final states:");
    scanf("%d",&n_final);
    char final[n_final][5];
    for(int i=0;i<n_final;i++)
    {
        printf("Enter the final state %d:",i+1);
        scanf("%s",&final[i]);
    }
    char transitions[n_states][n_symbols][5]; 
    for(int i = 0; i < n_states; i++) {
        for(int j = 0; j < n_symbols; j++) {
            printf("D[%s , %s]: ", states[i], symbols[j]);
            scanf("%s", transitions[i][j]);
        }
    }
    printf("Transition table\n");
    for(int j = 0; j < n_symbols; j++) {
        printf("\t\t %s",symbols[j]);
    }
    printf("\n");
    for(int i = 0; i < n_states; i++) {
        printf("%s",states[i]);
        for(int j = 0; j < n_symbols; j++) {
            printf("\t\t %s",transitions[i][j]);
        }
        printf("\n");
    }
    char s[20];
    printf("Enter the string to be verified for the dfa:");
    scanf("%s",s);
    char current_state[5];
    strcpy(current_state, start[0]);
    for (int i = 0; i < strlen(s); i++) {
        char symbol[2] = {s[i],'\0'};
        int state_index = findStateIndex(states, n_states, current_state);
        int symbol_index = findSymbolIndex(symbols, n_symbols, symbol);
        
        if (state_index == -1 || symbol_index == -1) {
            printf("Invalid state or symbol.\n");
            return 1;
        }
        printf("(%s,%s)->",states[state_index],symbols[symbol_index]);
        strcpy(current_state, transitions[state_index][symbol_index]);
    }
    printf("(%s)\n", current_state);
    if (isFinalState(final, n_final, current_state)) {
        printf("The string is accepted by the DFA.\n");
    } else {
        
        printf("The string is not accepted by the DFA.\n");
    }

    return 0;
}
