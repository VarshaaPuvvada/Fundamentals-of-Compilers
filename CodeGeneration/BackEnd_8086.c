#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VAR_SIZE 50
#define MAX_LINE_SIZE 100

void generate_assignment(const char* lhs, const char* rhs, FILE* out_file) {
    fprintf(out_file, "MOV AX, [%s]\n", rhs);  // Load rhs into AX
    fprintf(out_file, "MOV [%s], AX\n", lhs);  // Store AX into lhs
}

void generate_operation(const char* lhs, const char* operand1, const char* op, const char* operand2, FILE* out_file) {
    fprintf(out_file, "MOV AX, [%s]\n", operand1);  // Load operand1 into AX

    if (strcmp(op, "+") == 0) {
        fprintf(out_file, "ADD AX, [%s]\n", operand2);  // AX = AX + operand2
    } else if (strcmp(op, "-") == 0) {
        fprintf(out_file, "SUB AX, [%s]\n", operand2);  // AX = AX - operand2
    } else if (strcmp(op, "*") == 0) {
        fprintf(out_file, "MOV BX, [%s]\n", operand2);  // Load operand2 into BX
        fprintf(out_file, "MUL BX\n");  // AX = AX * BX
    } else if (strcmp(op, "/") == 0) {
        fprintf(out_file, "MOV BX, [%s]\n", operand2);  // Load operand2 into BX
        fprintf(out_file, "DIV BX\n");  // AX = AX / BX
    }

    fprintf(out_file, "MOV [%s], AX\n", lhs);  // Store the result in lhs
}

void parse_line(const char* line, FILE* out_file) {
    char lhs[MAX_VAR_SIZE], op[MAX_VAR_SIZE];
    char operand1[MAX_VAR_SIZE], operand2[MAX_VAR_SIZE];

    if (strstr(line, "=")) {
        sscanf(line, "%s = %s %s %s", lhs, operand1, op, operand2);

        if (strlen(op) > 0) {
            generate_operation(lhs, operand1, op, operand2, out_file);
        } else {
            generate_assignment(lhs, operand1, out_file);
        }
    } else {
        fprintf(out_file, "; Unrecognized line: %s\n", line);
    }
}

int main() {
    FILE* out_file = fopen("output.asm", "w");
    if (!out_file) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    printf("Enter TAC lines (press Enter twice to finish):\n");
    char line[MAX_LINE_SIZE];

    while (1) {
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            break;
        }

        parse_line(line, out_file);
    }

    fclose(out_file);
    printf("Generated Assembly Code in output.asm\n");

    return 0;
}
