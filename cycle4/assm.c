#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generate_8086(char *line) {
    char lhs[10], arg1[10], op[5], arg2[10];
    int count = sscanf(line, "%s = %s %s %s", lhs, arg1, op, arg2);

    // Simple assignment: x = a
    if (count == 2) {
        printf("    MOV AX, %s\n", arg1);
        printf("    MOV %s, AX\n", lhs);
        return;
    }

    // Binary operations: x = a op b
    if (count == 4) {
        // Load first argument into AX register
        printf("    MOV AX, %s\n", arg1);

        if (strcmp(op, "+") == 0) {
            printf("    ADD AX, %s\n", arg2);
        } else if (strcmp(op, "-") == 0) {
            printf("    SUB AX, %s\n", arg2);
        } else if (strcmp(op, "*") == 0) {
            printf("    MOV BX, %s\n", arg2);
            printf("    MUL BX\n"); // AX = AX * BX
        } else if (strcmp(op, "/") == 0) {
            printf("    MOV BX, %s\n", arg2);
            printf("    XOR DX, DX\n"); // Clear DX for 16-bit division
            printf("    DIV BX\n");     // AX = AX / BX
        }

        // Store result from AX into LHS target variable
        printf("    MOV %s, AX\n", lhs);
    }
}

int main() {
    char icode[10][50];
    int n = 0;

    printf("Enter the Three-Address Code (type 'exit' to terminate):\n");
    while (1) {
        fgets(icode[n], sizeof(icode[n]), stdin);
        icode[n][strcspn(icode[n], "\n")] = 0; // Remove newline
        if (strcmp(icode[n], "exit") == 0) break;
        n++;
    }

    printf("\n--- Generated 8086 Assembly Code ---\n");
    printf(".CODE\n");
    printf("MAIN PROC\n");

    for (int i = 0; i < n; i++) {
        if (strlen(icode[i]) > 0) {
            printf("; 3AC: %s\n", icode[i]);
            generate_8086(icode[i]);
        }
    }

    printf("    MOV AH, 4CH\n");
    printf("    INT 21H\n");
    printf("MAIN ENDP\n");
    printf("END MAIN\n");

    return 0;
}