#include <stdio.h>

int n, adj[20][20], visited[20];


void dfs(int state) {
    visited[state] = 1;
    for (int i = 1; i <= n; i++) {
        if (adj[state][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int t, u, v;
    char sym;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (format: from_state symbol to_state):\n");
    for (int i = 0; i < t; i++) {
        scanf("%d %c %d", &u, &sym, &v);
    
        if (sym == 'e' || sym == 'E') {
            adj[u][v] = 1;
        }
    }

    printf("\n--- e-closure of states ---\n");
    for (int i = 1; i <= n; i++) {
      
        for (int j = 1; j <= n; j++) {
            visited[j] = 0;
        }

        dfs(i);

        printf("e-closure(q%d) = { ", i);
        for (int j = 1; j <= n; j++) {
            if (visited[j]) {
                printf("q%d ", j);
            }
        }
        printf("}\n");
    }

    return 0;
}