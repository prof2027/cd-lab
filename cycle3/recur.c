
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char input[100];
int pos = 0;

void E();
void E_prime();
void T();
void T_prime();
void F();

void advance()
{
    pos++;
}

// E -> TE'
void E()
{
    printf("E -> TE'\n");

    T();
    E_prime();
}

// E' -> +TE' | e
void E_prime()
{
    if (input[pos] == '+')
    {
        printf("E' -> +TE'\n");

        advance();
        T();
        E_prime();
    }
    else
    {
        printf("E' -> e\n");
    }
}

// T -> FT'
void T()
{
    printf("T -> FT'\n");

    F();
    T_prime();
}

// T' -> *FT' | e
void T_prime()
{
    if (input[pos] == '*')
    {
        printf("T' -> *FT'\n");

        advance();
        F();
        T_prime();
    }
    else
    {
        printf("T' -> e\n");
    }
}

// F -> (E) | i
void F()
{
    if (input[pos] == 'i' || input[pos] == 'I')
    {
        printf("F -> i\n");
        advance();
    }
    else if (input[pos] == '(')
    {
        printf("F -> (E)\n");

        advance();
        E();

        if (input[pos] == ')')
        {
            advance();
        }
        else
        {
            printf("Syntax Error: Missing closing parenthesis\n");
            exit(1);
        }
    }
    else
    {
        printf("Syntax Error at position %d\n", pos);
        exit(1);
    }
}

int main()
{
    printf("\nGRAMMAR:\n");
    printf("E  -> TE'\n");
    printf("E' -> +TE' | e\n");
    printf("T  -> FT'\n");
    printf("T' -> *FT' | e\n");
    printf("F  -> (E) | i\n");

    printf("\nEnter the input expression: ");
    scanf("%99s", input);

    printf("\nPRODUCTION RULES:\n");

    E();

    if (input[pos] == '\0')
    {
        printf("\nString ACCEPTED!\n");
    }
    else
    {
        printf("\nSyntax Error: Unexpected symbol '%c' at position %d\n",
               input[pos], pos);
        printf("String REJECTED!\n");
    }

    return 0;
}
