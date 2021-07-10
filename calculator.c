#include "headers.h"
#include "testFunctions.c"

#define MAXOP 100
#define NUMBER '0'
#define EXPONENT '1'
#define SIN '2'
#define EXP '3'

int getop(char []);
void push(double);
double pop(void);

int main(){
    int type;
    double op2, op1;
    char s[MAXOP];

    printf("Enter the calculation you'd like to make: ");
    while((type = getop(s)) != '\n'){
        switch(type){
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if(op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                op1 = pop();

                if(op2 == 0.0)
                    printf("error: zero divisor\n");
                else if(floor(op2) == op2 && floor(op1) == op1)
                    push((int)op1 % (int)op2);
                else
                    printf("error: can't use a modulus operator on a fractional number");
            case'\n':
                printf("Your result is: %.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    printf("Your result is: %.8g\n", pop());
    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f){
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void){
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

double peek(){
    if (sp > 0)
        return val[sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void duplicateTop(){
    if (sp < MAXVAL){
        val[sp + 1] = val[sp];
        sp++;
    } else
        printf("error, stack full, can't duplicate");
}

void clearStack(){
    for(int i = 0; i < MAXVAL; i++)
        val[i] = '\0';
}

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i = 0;
    int c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    
    if (!isdigit(c) && c != '.'){
        if(c == '-'){
            c = getch();
            if(isdigit(c)){
                while (isdigit(c)){
                    s[++i] = c;
                    c = getch();
                }
                s[++i] = '\0';
                if (c != EOF)
                    ungetch(c);
                return NUMBER;
            } else {
                ungetch(c);
                return '-';
            }
        }
        else
            return c;
    }

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}