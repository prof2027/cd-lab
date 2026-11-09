#include <stdio.h>

#define MAX 10

int eps[MAX][MAX];        // epsilon closure: eps[i][j] = 1 if j reachable from i via epsilons
int trans[MAX][MAX][MAX]; // trans[q][a][p] = 1 if q --a--> p in the input e-NFA
int newt[MAX][MAX][MAX];  // transitions of the resulting NFA
int fin[MAX], newfin[MAX];
char sym[MAX];

int main() {
    int n, m, nf, t, i, j, k, q, a, r, p, s;

    printf("Number of states (0..n-1): ");
    scanf("%d", &n);

    printf("Number of input symbols: ");
    scanf("%d", &m);
    printf("Enter the symbols: ");
    for (i = 0; i < m; i++) scanf(" %c", &sym[i]);

    printf("Number of final states: ");
    scanf("%d", &nf);
    printf("Enter final states: ");
    for (i = 0; i < nf; i++) { scanf("%d", &j); fin[j] = 1; }

    printf("Number of transitions: ");
    scanf("%d", &t);
    printf("Enter transitions as: from symbol to   (use 'e' for epsilon)\n");
    for (i = 0; i < t; i++) {
        int from, to; char c;
        scanf("%d %c %d", &from, &c, &to);
        if (c == 'e') eps[from][to] = 1;
        else
            for (a = 0; a < m; a++)
                if (sym[a] == c) trans[from][a][to] = 1;
    }

    // Epsilon closure (every state reaches itself, then Warshall)
    for (i = 0; i < n; i++) eps[i][i] = 1;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (eps[i][k] && eps[k][j]) eps[i][j] = 1;

    // New transition: q =eps*=> r --a--> p =eps*=> s
    for (q = 0; q < n; q++)
        for (a = 0; a < m; a++)
            for (r = 0; r < n; r++) if (eps[q][r])
                for (p = 0; p < n; p++) if (trans[r][a][p])
                    for (s = 0; s < n; s++) if (eps[p][s])
                        newt[q][a][s] = 1;

    // q is final if its epsilon closure contains a final state
    for (q = 0; q < n; q++)
        for (r = 0; r < n; r++)
            if (eps[q][r] && fin[r]) newfin[q] = 1;

    printf("\nNFA transitions:\n");
    for (q = 0; q < n; q++)
        for (a = 0; a < m; a++) {
            printf("d(q%d, %c) = { ", q, sym[a]);
            for (s = 0; s < n; s++) if (newt[q][a][s]) printf("q%d ", s);
            printf("}\n");
        }

    printf("\nFinal states: ");
    for (q = 0; q < n; q++) if (newfin[q]) printf("q%d ", q);
    printf("\n");
    return 0;
}