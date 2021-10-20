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

int main(int argc, char* argv[]){

    // Does nothing if there are no arguments passed
    if(argc == 1){
        printf("No arguments passed");
        return 0;
    }

    int type;
    double op2, op1;
    char s[MAXOP];
    double result;

    // Checks for the operator of each argument successively
    for(int i = 1; i < argc; i++){

        type = getop(argv[i]);

        switch(type){
            case NUMBER:
                result = atof(argv[i]);
                push(result);
                break;
            case '+':
                result = pop() + pop();
                push(result);
                break;
            case '*':
                result = pop() * pop();
                push(result);
                break;
            case '-':
                op2 = pop();
                result = pop() - op2;
                push(result);
                break;
            case '/':
                op2 = pop();
                if(op2 != 0.0){
                    result = pop() / op2;
                    push(result);
                }
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
                break;
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
                return 0;
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

// Takes the pointer to an array of chars from a command line argument and 
// interprets what operator it represents
int getop(char* s)
{
    int i = 0;
    int c = s[i];
    char check = c;
    int thisCharType;
    
    if(isalpha(c)){
        thisCharType = checkChar(s, c);
        return thisCharType;
    }

    // If the first character is not a digit, check to see if it's a negative number,
    // a minus, or any other operator
    if (!isdigit(c)){
        if(c == '-'){
            c = s[++i];
            // Check for a negative number
            if(isdigit(c)){
                while (isdigit(c))
                    c = s[++i];
                
                // Send an error if the negative sign is followed by anything but a number
                if(!c)
                    return NUMBER;
                else
                    return ERROR;

            } else if (!c)
                return '-';
            else
                return ERROR;
        }

        // Check if the character is an operator. If it is, but is followed by anything else, return an error.
        else if (c == '/' || c == '*' || c == '+' || c == '%'){
            c = s[++i];
            if(!c)
                return s[0];
            else
                return ERROR;
        }
        else
            return ERROR;
    }

    // If the first character is a digit, the rest must also be digits, otherwise return an error
    while (isdigit(c))
            c = s[++i];

    if(!c)
        return NUMBER;
    else
        return ERROR;
}

int checkChar(char* s, int c){
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