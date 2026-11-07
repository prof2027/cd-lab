%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char data[20];
    struct node *left;
    struct node *right;
};

struct node *createNode(char *data, struct node *left, struct node *right);
void preorder(struct node *root);
void postorder(struct node *root);

int yylex();
void yyerror(char *s);
%}

%union {
    char *str;
    struct node *node;
}

%token <str> ID
%type <node> E T F

%%
start:
      E '\n'
      {
          printf("\nAbstract Syntax Tree Traversal:\n");
          printf("Preorder  : ");
          preorder($1);
          printf("\nPostorder : ");
          postorder($1);
          printf("\n");
          exit(0);
      }
    ;

E:
      E '+' T   { $$ = createNode("+", $1, $3); }
    | E '-' T   { $$ = createNode("-", $1, $3); }
    | T         { $$ = $1; }
    ;

T:
      T '*' F   { $$ = createNode("*", $1, $3); }
    | T '/' F   { $$ = createNode("/", $1, $3); }
    | F         { $$ = $1; }
    ;

F:
      '(' E ')' { $$ = $2; }
    | ID        { $$ = createNode($1, NULL, NULL); }
    ;
%%

struct node *createNode(char *data, struct node *left, struct node *right)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    strcpy(newnode->data, data);
    newnode->left = left;
    newnode->right = right;
    return newnode;
}

void preorder(struct node *root)
{
    if (root != NULL) {
        printf("%s ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node *root)
{
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%s ", root->data);
    }
}

int main()
{
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    printf("Invalid Expression\n");
    exit(0);
}