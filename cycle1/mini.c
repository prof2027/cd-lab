#include <stdio.h>

int n, noalpha, n_final;
int trans[20][10];       
int group[20], new_group[20];
int is_final[20];

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of alphabets: ");
    scanf("%d", &noalpha);

    printf("Enter number of final states: ");
    scanf("%d", &n_final);
    printf("Enter final states: ");
    for (int i = 0; i < n_final; i++) {
        int f;
        scanf("%d", &f);
        is_final[f] = 1;
    }

    printf("Enter transition table (target state for each symbol):\n");
    for (int i = 0; i < n; i++) {
        for (int a = 0; a < noalpha; a++) {
            printf("q%d on symbol %d -> ", i, a);
            scanf("%d", &trans[i][a]);
        }
    }

    
    for (int i = 0; i < n; i++) {
        group[i] = is_final[i];
    }

   
    while (1) {
        int g_count = 0;
        for (int i = 0; i < n; i++) new_group[i] = -1;

        for (int i = 0; i < n; i++) {
            if (new_group[i] != -1) continue; 
            new_group[i] = g_count;

            for (int j = i + 1; j < n; j++) {
                
                if (group[i] == group[j]) {
                    int same = 1;
                    
                    for (int a = 0; a < noalpha; a++) {
                        if (group[trans[i][a]] != group[trans[j][a]]) {
                            same = 0;
                            break;
                        }
                    }
                    if (same) new_group[j] = g_count;
                }
            }
            g_count++;
        }

      
        int changed = 0;
        for (int i = 0; i < n; i++) {
            if (group[i] != new_group[i]) {
                changed = 1;
                group[i] = new_group[i];
            }
        }

        if (!changed) break;
    }

    
    int num_groups = 0;
    for (int i = 0; i < n; i++) {
        if (group[i] > num_groups) num_groups = group[i];
    }
    num_groups++;

    printf("\n--- Minimized DFA States ---\n");
    for (int g = 0; g < num_groups; g++) {
        printf("Group G%d = { ", g);
        for (int i = 0; i < n; i++) {
            if (group[i] == g) printf("q%d ", i);
        }
        printf("}\n");
    }

   
    printf("\n--- Minimized Transition Table ---\n");
    for (int g = 0; g < num_groups; g++) {
        int rep = -1; 
        for (int i = 0; i < n; i++) {
            if (group[i] == g) { rep = i; break; }
        }

        for (int a = 0; a < noalpha; a++) {
            printf("G%d -- sym %d --> G%d\n", g, a, group[trans[rep][a]]);
        }
    }

    return 0;
}