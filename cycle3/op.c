
#include <stdio.h>
#include <string.h>

char ter[11], opt[10][10], stack[100];
int n, top;

const char *rhs[] = { "E+E", "E*E", "(E)", "i" };


int idx(char c)
{
    for (int k = 0; k < n; k++)
        if (ter[k] == c) return k;
    return -1;
}


int term_at(int j)
{
    while (j >= 0 && stack[j] == 'E') j--;
    return j;
}


int reduce(void)
{
    int a = term_at(top), b;

    for (;;) {                       
        b = term_at(a - 1);
        if (b < 0) return 0;
        if (opt[idx(stack[b])][idx(stack[a])] == '<') break;
        a = b;
    }

    int len = top - b;              
    for (int k = 0; k < 4; k++) {
        if ((int)strlen(rhs[k]) == len && strncmp(stack + b + 1, rhs[k], len) == 0) {
            top = b + 1;
            stack[top] = 'E';
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    char ip[50], tmp[16];
    int i, j, t, a, r;

    printf("Enter the no. of terminals (max 10, including $): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 10) return 1;

    printf("Enter the terminals (no spaces, include $): ");
    if (scanf("%10s", ter) != 1 || (int)strlen(ter) != n) return 1;

    printf("Enter table values (<, =, > or any other char for error/accept):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            printf("  %c %c: ", ter[i], ter[j]);
            if (scanf("%15s", tmp) != 1) return 1;
            opt[i][j] = tmp[0];
        }

    printf("\nEnter the input string (must end with $): ");
    if (scanf("%49s", ip) != 1) return 1;

    printf("\nSTACK\t\tINPUT\t\tACTION\n");
    stack[0] = '$';
    top = 0;
    i = 0;

    for (;;) {
        stack[top + 1] = '\0';
        printf("%s\t\t%s\t\t", stack, ip + i);

        t = term_at(top);
        a = idx(stack[t]);
        r = idx(ip[i]);

        if (r < 0) { printf("Invalid symbol - rejected\n"); break; }

        if (stack[t] == '$' && ip[i] == '$') {
            printf(top == 1 ? "Accepted\n" : "Rejected\n"); 
            break;
        }

        char rel = opt[a][r];

        if (rel == '<' || rel == '=') {
            stack[++top] = ip[i++];
            printf("Shift\n");
        } else if (rel == '>' && reduce()) {
            printf("Reduce\n");
        } else {
            printf("Rejected\n");
            break;
        }
    }
    return 0;
}