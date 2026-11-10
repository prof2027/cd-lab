
#include <stdio.h>
#include <string.h>

char stack[30], input[30];
int top = -1, i = 0;

void check()
{
    int reduced = 1;

    while (reduced)
    {
        reduced = 0;

        
        if (top >= 1 &&
            stack[top - 1] == 'i' &&
            stack[top] == 'd')
        {
            stack[top - 1] = 'E';
            top--;
            stack[top + 1] = '\0';

            printf("\nREDUCE E -> id");
            reduced = 1;
        }

        
        else if (top >= 2 &&
                 stack[top - 2] == '(' &&
                 stack[top - 1] == 'E' &&
                 stack[top] == ')')
        {
            stack[top - 2] = 'E';
            top -= 2;
            stack[top + 1] = '\0';

            printf("\nREDUCE E -> (E)");
            reduced = 1;
        }

        
        else if (top >= 2 &&
                 stack[top - 2] == 'E' &&   
                 stack[top - 1] == '+' &&
                 stack[top] == 'E')
        {
            stack[top - 2] = 'E';
            top -= 2;
            stack[top + 1] = '\0';

            printf("\nREDUCE E -> E+E");
            reduced = 1;
        }

        
        else if (top >= 2 &&
                 stack[top - 2] == 'E' &&
                 stack[top - 1] == '*' &&
                 stack[top] == 'E')
        {
            stack[top - 2] = 'E';
            top -= 2;
            stack[top + 1] = '\0';

            printf("\nREDUCE E -> E*E");
            reduced = 1;
        }
    }
}

int main()
{
    printf("GRAMMAR:\n");
    printf("E -> E+E\n");
    printf("E -> E*E\n");
    printf("E -> (E)\n");
    printf("E -> id\n");

    printf("\nEnter input string: ");
    scanf("%29s", input);

    printf("\nSTACK\t\tINPUT\t\tACTION\n");

    while (input[i] != '\0')
    {
       
        stack[++top] = input[i++];
        stack[top + 1] = '\0';

        printf("\n%-16s %-16s SHIFT", stack, input + i);

        
        check();

        printf("\n%-16s %-16s REDUCE", stack, input + i);
    }

    if (top == 0 && stack[0] == 'E')
        printf("\n\nString ACCEPTED!\n");
    else
        printf("\n\nString REJECTED!\n");

    return 0;
}
