#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int n, m = 0, p;                
char a[10][10], f[10];
int inFollow = 0;                
char vis[256];                 

void follow(char c);
void first(char c);

void addf(char c) {             
    int k;
    for (k = 0; k < m; k++)
        if (f[k] == c) return;
    f[m++] = c;
}

int main() {
    int i, z;
    char c, ch;

    printf("Enter the no of productions:\n");
    scanf("%d", &n);

    printf("Enter the productions:\n");
    for (i = 0; i < n; i++)
        scanf("%s%c", a[i], &ch);

    do {
        m = 0;
        printf("Enter the elements whose first & follow is to be found: ");
        scanf(" %c", &c);

        inFollow = 0;            
        first(c);
        printf("First(%c)={", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");

        m = 0;                   
        memset(vis, 0, sizeof vis);   
        follow(c);
        printf("Follow(%c)={", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");

        printf("Continue(0/1)? ");
        scanf("%d%c", &z, &ch);
    } while (z == 1);

    return 0;
}

void first(char c) {
    int k;
    if (!isupper(c)) {        
        addf(c);
        return;
    }
    for (k = 0; k < n; k++) {
        if (a[k][0] == c) {
            if (a[k][2] == '$') {
                if (!inFollow)   
                    addf('$');
            }
            else if (a[k][2] != c)   
                first(a[k][2]);      
        }
    }
}

void follow(char c) {
    int i, j, k;                
    if (vis[(unsigned char)c]) return;   
    vis[(unsigned char)c] = 1;

    if (a[0][0] == c)
        addf('$');               
    for (i = 0; i < n; i++) {
        for (j = 2; j < strlen(a[i]); j++) {
            if (a[i][j] == c) {
                if (a[i][j + 1] != '\0') {
                    char nx = a[i][j + 1];
                    int nul = 0;
                    inFollow = 1;       
                    first(nx);
                    inFollow = 0;       
                    
                    for (k = 0; k < n; k++)
                        if (a[k][0] == nx && a[k][2] == '$') nul = 1;
                    if (nul && a[i][0] != c)
                        follow(a[i][0]);
                }
                else if (c != a[i][0])
                    follow(a[i][0]);
            }
        }
    }
}