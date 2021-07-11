#include "headers.h"
#include "testFunctions.c"

#define MAXOP 100
#define NUMBER '0'
#define SIN '1'
#define SEC '2'
#define TAN '3'
#define COS '4'
#define CSC '5'
#define COT '6'
#define VAR '7'
#define ERROR '8'

int getop(char []);
void push(double);
double pop(void);
int checkChar(char s[], int c);

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
            case SIN:
                push(sin(pop()));
                break;
            case SEC:
                push(1/(cos(pop())));
                break;
            case TAN:
                push(tan(pop()));
                break;
            case COS:
                push(cos(pop()));
                break;
            case CSC:
                push(1/(sin(pop())));
                break;
            case COT:
                push(1/(tan(pop())));
                break;
            case'\n':
                printf("Your result is: %.8g\n", pop());
                break;
            case ERROR:       // Catches bad input
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
    int thisCharType;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    
    if(isalpha(c)){
        thisCharType = checkChar(s, c);
        return thisCharType;
    }

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

int checkChar(char s[], int c){
    int thisCharType;
    int error = 0;
    int test;

    // Initial test to see if the character is a variable
    if (isspace(test = getch())){
        thisCharType = VAR;
        return thisCharType;
    }
    ungetch(test);

    switch(c){
        // Case for SIN and SEC
        case 'S':
        case 's':
            if ((c = getch()) == 'i' || c == 'I'){
                if ((c = getch()) == 'n' || c == 'N'){
                    thisCharType = SIN;
                } else {
                    thisCharType = ERROR;
                }
            } else if (c == 'e' || c == 'E'){
                if ((c = getch()) == 'c' || c == 'C'){
                    thisCharType = SEC;
                } else {
                    thisCharType = ERROR;
                }
            } else 
                thisCharType = ERROR;

            break;
        
        // Case for TAN
        case 'T':
        case 't':
            if ((c = getch()) == 'a' || c == 'A'){
                if ((c = getch()) == 'n' || c == 'N'){
                    thisCharType = TAN;
                } else {
                    thisCharType = ERROR;
                }
            } else
                thisCharType = ERROR;

            break;
        
        // Case for COS, CSC, and COT
        case 'C':
        case 'c':
            if ((c = getch()) == 'o' || c == 'O'){
                if ((c = getch()) == 's' || c == 'S'){
                    thisCharType = COS;
                } else if (c == 't' || c == 'T'){
                    thisCharType = COT;
                } else {
                    thisCharType = ERROR;
                }
            } else if (c == 's' || c == 'S'){
                if ((c = getch()) == 'c' || c == 'C'){
                    thisCharType = SEC;
                } else {
                    thisCharType = ERROR;
                }
            } else 
                thisCharType = ERROR;

            break;
        
        }
    return thisCharType;
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