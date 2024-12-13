#include <stdio.h>
#include <string.h>

int is_nt(char ele, char nt[][2], int n) {
    for (int i = 0; i < n; i++) {
        if (ele == nt[i][0]) {
            return 1;
        }
    }
    return 0;
}

int index_nt(char ele, char nt[][2], int n) {
    for (int i = 0; i < n; i++) {
        if (ele == nt[i][0]) {
            return i;
        }
    }
    return -1;
}

int index_st(char ele, char t[][2], int n) {
    for (int i = 0; i < n; i++) {
        if (ele == t[i][0]) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n_nt;
    printf("Enter the number of non-terminals: ");
    scanf("%d", &n_nt);
    
    char nt[n_nt][2]; 
    printf("Enter the non-terminals:\n");
    for (int i = 0; i < n_nt; i++) {
        printf("Non-terminal %d: ", i + 1);
        scanf(" %c", &nt[i][0]);  
        nt[i][1] = '\0';          
    }
    
    int n_t;
    printf("Enter the number of terminals: ");
    scanf("%d", &n_t);
    
    char t[n_t][2]; 
    printf("Enter the terminals:\n");
    for (int i = 0; i < n_t; i++) {
        printf("Terminal %d: ", i + 1);
        scanf(" %c", &t[i][0]);  
        t[i][1] = '\0';          
    }
    
    char parse_table[n_nt][n_t][10]; 
    printf("Enter the values of the parse table:\n");
    for (int i = 0; i < n_nt; i++) {
        printf("%c is the non-terminal\n", nt[i][0]);
        for (int j = 0; j < n_t; j++) {
            printf("For terminal %c -> production is: ", t[j][0]);
            scanf("%s", parse_table[i][j]);  
        }
    }

    printf("\nParse Table:\n");
    
    printf("\t");  
    for (int i = 0; i < n_t; i++) {
        printf("%c\t", t[i][0]); 
    }
    printf("\n");

    for (int j = 0; j < n_nt; j++) {
        printf("%c\t", nt[j][0]);  
        for (int k = 0; k < n_t; k++) {
            printf("%s\t", parse_table[j][k]);  
        }
        printf("\n");  
    }

    char input_string[20];
    printf("Enter the input string: ");
    scanf("%s", input_string);
    strcat(input_string,"$");
    char stack[20];
    int top = 0;
    stack[top++] = '$';   
    stack[top++] = nt[0][0];  
    
    int index = 0;  
    int length = strlen(input_string);
    
    printf("Stack\t\t\tInput\t\t\tOutput\n");

    while (top > 0) {
    for (int i = 0; i < top; i++) {
        printf("%c", stack[i]);
    }
    printf("\t\t\t");
    
    for (int j = index; j < length; j++) {
        printf("%c", input_string[j]);  
    }
    printf("\t\t\t");
    
    char stack_top = stack[--top];  
    
    if (stack_top == input_string[index]) {
        printf("Match %c\n", stack_top);
        index++;  
    } 
    else if (is_nt(stack_top, nt, n_nt) == 1) {
        int i = index_nt(stack_top, nt, n_nt);
        int s = index_st(input_string[index], t, n_t);
        
        if (s == -1 || strcmp(parse_table[i][s], "-") == 0) {
            printf("Error: No rule for %c on input %c\n", stack_top, input_string[index]);
            return 1;
        }
        
        char *rule = parse_table[i][s];
        int r = strlen(rule);
        
        if (strcmp(rule, "e") != 0) {  
            for (int k = r - 1; k > 2; k--) {
                stack[top++] = rule[k];  
            }
        }
        printf("Apply rule: %s\n", rule);
    } 
    else if (stack_top == 'e') {
        printf("Epsilon (e) encountered, removing from stack\n");
        continue;
    } 
    else {
        printf("Error: Mismatch at %c\n", input_string[index]);
        return 1;
    }
}
if (top==0 && index==length) {
    printf("Success: Input string is accepted by the grammar.\n");
} else {
    printf("Error: Input string is not fully consumed.\n");
}

    return 0;
}
