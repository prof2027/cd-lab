#include <stdio.h>
#include <ctype.h>

int n;                      
char a[30][30];            
int first[256][256];        
int follow[256][256];       


int merge(int dst[], int src[]) {
    int grew = 0;
    for (int t = 0; t < 256; t++)
        if (src[t] && !dst[t]) dst[t] = grew = 1;
    return grew;
}


int firstOfString(char *s, int out[]) {
    for (; *s; s++) {
        if (*s == '$') continue;                  
        if (!isupper(*s)) { out[(int)*s] = 1; return 0; }  
        merge(out, first[(int)*s]);              
        if (!first[(int)*s]['$']) return 0;       
    }
    return 1;
}

int main(void) {
    char c, ch;
    int z;

    printf("Enter the no of productions:\n");
    scanf("%d", &n);
    printf("Enter the productions (e.g. S=ABC, use $ for epsilon):\n");
    for (int i = 0; i < n; i++)
        scanf("%s%c", a[i], &ch);

   
    for (int changed = 1; changed;) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            int tmp[256] = {0};
            if (firstOfString(a[i] + 2, tmp)) tmp['$'] = 1;
            changed |= merge(first[(int)a[i][0]], tmp);
        }
    }

  
    follow[(int)a[0][0]]['$'] = 1;
    for (int changed = 1; changed;) {
        changed = 0;
        for (int i = 0; i < n; i++)
            for (int j = 2; a[i][j]; j++) {
                if (!isupper(a[i][j])) continue;
                int *b = follow[(int)a[i][j]];
                int tmp[256] = {0};
                int rest = firstOfString(a[i] + j + 1, tmp);
                changed |= merge(b, tmp);
                if (rest) changed |= merge(b, follow[(int)a[i][0]]);
            }
    }

    do {
        printf("Enter the element whose first & follow is to be found: ");
        scanf(" %c", &c);

        printf("First(%c)={", c);
        if (!isupper(c)) printf("%c", c);
        else for (int t = 0; t < 256; t++) if (first[(int)c][t]) printf("%c", t);
        printf("}\n");

        if (isupper(c)) {
            printf("Follow(%c)={", c);
            for (int t = 0; t < 256; t++) if (follow[(int)c][t]) printf("%c", t);
            printf("}\n");
        }

        printf("Continue(0/1)? ");
        scanf("%d%c", &z, &ch);
    } while (z == 1);

    return 0;
}