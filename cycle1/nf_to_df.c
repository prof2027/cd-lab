#include <stdio.h>

int n, noalpha, start_state, n_final;
int is_final[20];
char alpha[10];

int nfa[20][10][20];       
int dfa_states[20][20];    
int dfa_trans[20][10];     
int dfa_count = 0;


void print_set(int state_idx) {
    printf("{ ");
    for (int j = 1; j <= n; j++) {
        if (dfa_states[state_idx][j]) printf("q%d ", j);
    }
    printf("}");
}


int is_equal(int a[20], int b[20]) {
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int main() {
    int t;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of alphabets: ");
    scanf("%d", &noalpha);
    printf("Enter alphabets: ");
    for (int i = 0; i < noalpha; i++) {
        scanf(" %c", &alpha[i]);
    }

    printf("Enter start state: ");
    scanf("%d", &start_state);

    printf("Enter number of final states: ");
    scanf("%d", &n_final);
    printf("Enter final states: ");
    for (int i = 0; i < n_final; i++) {
        int f;
        scanf("%d", &f);
        is_final[f] = 1;
    }

    printf("Enter number of transitions: ");
    scanf("%d", &t);
    printf("Enter transitions (format: from symbol to):\n");
    for (int i = 0; i < t; i++) {
        int u, v;
        char sym;
        scanf("%d %c %d", &u, &sym, &v);
        for (int a = 0; a < noalpha; a++) {
            if (alpha[a] == sym) nfa[u][a][v] = 1;
        }
    }


    dfa_states[0][start_state] = 1;
    dfa_count = 1;

   
    for (int i = 0; i < dfa_count; i++) {
        for (int a = 0; a < noalpha; a++) {
            int next_set[20] = {0};

          
            for (int u = 1; u <= n; u++) {
                if (dfa_states[i][u]) {
                    for (int v = 1; v <= n; v++) {
                        if (nfa[u][a][v]) next_set[v] = 1;
                    }
                }
            }

        
            int is_empty = 1;
            for (int k = 1; k <= n; k++) {
                if (next_set[k]) { is_empty = 0; break; }
            }

            if (is_empty) {
                dfa_trans[i][a] = -1; 
                continue;
            }

        
            int existing_idx = -1;
            for (int k = 0; k < dfa_count; k++) {
                if (is_equal(dfa_states[k], next_set)) {
                    existing_idx = k;
                    break;
                }
            }

            if (existing_idx != -1) {
                dfa_trans[i][a] = existing_idx;
            } else {
               
                for (int k = 1; k <= n; k++) {
                    dfa_states[dfa_count][k] = next_set[k];
                }
                dfa_trans[i][a] = dfa_count;
                dfa_count++;
            }
        }
    }


    printf("\n--- DFA Transitions ---\n");
    for (int i = 0; i < dfa_count; i++) {
        for (int a = 0; a < noalpha; a++) {
            print_set(i);
            printf(" -- %c --> ", alpha[a]);
            if (dfa_trans[i][a] != -1) {
                print_set(dfa_trans[i][a]);
            } else {
                printf("phi");
            }
            printf("\n");
        }
    }


    printf("\nDFA Final States: ");
    for (int i = 0; i < dfa_count; i++) {
        for (int j = 1; j <= n; j++) {
            if (dfa_states[i][j] && is_final[j]) {
                print_set(i);
                printf(" ");
                break;
            }
        }
    }
    printf("\n");

    return 0;
}