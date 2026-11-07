#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char keywords[5][10] = {"int", "float", "if", "else", "while"};

int isKeyword(char buffer[]) {
    for (int i = 0; i < 5; i++) {
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char ch, buffer[20];
    FILE *fp = fopen("input.txt", "r");
    int j = 0;

    if (fp == NULL) {
        printf("Error opening file\n");
        exit(0);
    }

    while ((ch = fgetc(fp)) != EOF) {
     
        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        
        if (isalpha(ch) || ch =='_') {
            buffer[j++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_')) {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            ungetc(ch, fp); 
            j = 0;

            if (isKeyword(buffer))
                printf("%s : Keyword\n", buffer);
            else
                printf("%s : Identifier\n", buffer);
        }
    
        else if (isdigit(ch)) {
            buffer[j++] = ch;
            int has_dot = 0;

            while ((ch = fgetc(fp)) != EOF && (isdigit(ch) || (ch == '.' && !has_dot))) {
                if (ch == '.') has_dot = 1;
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            ungetc(ch, fp);
            j = 0;

            printf("%s : Number\n", buffer);
        }
       
        else if (strchr("+-*/%=<>!", ch)) {
            char next = fgetc(fp);

            if (ch == '>' && next == '=')      printf(">= : Operator\n");
            else if (ch == '<' && next == '=') printf("<= : Operator\n");
            else if (ch == '=' && next == '=') printf("== : Operator\n");
            else if (ch == '!' && next == '=') printf("!= : Operator\n");
            else {
                ungetc(next, fp); 
                printf("%c : Operator\n", ch);
            }
        }
        
        else if (strchr(";,(){}", ch)) {
            printf("%c : Delimiter\n", ch);
        }
    }

    fclose(fp);
    return 0;
}