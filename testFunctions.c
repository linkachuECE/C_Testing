#include "headers.h"

void reverseString(char fromS[], char toS[]);
int strrindex(char s[], char t[]);
int stringLength(char s[]);
int getch(void);
void ungetch(int c);

// Get the index of the rightmost position of a string, contained within another string
int strrindex(char s[], char t[]){
    char treverse[stringLength(t) + 1];
    reverseString(t, treverse);

    int i;

    for(i = stringLength(s); i >= 0; i--){
        if (s[i] == treverse[0]){
            for(int j = 0; i - j >= -1 ; j++){
                if (treverse[j] == '\0')
                    return i - j + 1;
                if (treverse[j] != s[i - j])
                    break;
            }
        } 
    }

    return -1;
}

// Take a string and put the reverse in the second string
void reverseString(char fromS[], char toS[]){
    int i;
    int j = stringLength(fromS);
    toS[j--] = '\0';

    for(i = 0; fromS[i] != '\0'; i++, j--){
        toS[j] = fromS[i];
    }
}

// Returns the total length of a string
int stringLength(char* s){
    int i;
    for(i = 0; s[i] != '\0'; i++)
        ;
    
    return i;
}

int stoi(char s[]){
    int i, n;
    n = 0;

    for(i = 0; s[i] >= '0' && s[i] <= '9'; i++){
        n = 10 * n + (s[i] - '0');
    }
    return n;
}

void titleCase(char s[]){
    enum inOrOut{OUT, IN} wordState = OUT;
    
    for(int i = 0; s[i] != '\0'; i++){
        
        if((s[i] >= 'A') && (s[i] <= 'z')){
            if (wordState == OUT){
                wordState = IN;
                if(s[i] >= 'a' && s[i] <= 'z')
                    s[i] = toupper(s[i]);
            }
        } else
            wordState = OUT;
    }
}

int htoi(char s[], int length){
    int stopPoint = 0;
    int i = length - 1;
    int total = 0;
    int currentVal;

    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        stopPoint = 2;

    for(i; i >= stopPoint; i--){
        currentVal = s[i];
        if(s[i] >= 'a' && s[i] <= 'f')
            currentVal = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            currentVal = s[i] - 'A' + 10;
        else
            currentVal = s[i] - '0';
        
        total += currentVal * pow(16, (length-1) - i);
    }

    return total;
}

void strSqueeze(char s1[], char s2[]){
    for (int i = 0; s2[i] != '\0'; i++){
        for(int j = 0; s1[j] != '\0'; j++){
            if (s2[i] == s1[j]){
                for (int k = j; s1[k] != '\0'; k++){
                    s1[k] = s1[k+1];
                }
                j--;
            }
        }
    }
}

int setbits(int x, int p, int n, int y){
    /*int xMask = ~(~0 << n) << p;
    int clearedX = x | (xMask);
    int yMask = ~(~0 << n);
    int yInvMasked = ~y & yMask;
    int yInvShifted = yInvMasked << p;
    int yShifted = ~yInvShifted;
    int result = yShifted & clearedX;*/

    int result = (~((~y & (~(~0 << n))) << p)) & (x | (~(~0 << n) << p));

    return result;
}

// DOESN'T WORK RIGHT NOW, PLEASE FIX
int invert(int x, int p, int n){
    int xshift = x >> p;
    int xMask = ~(~0 << n);
    int xImportantBitsInverted = ~((xshift & xMask) << p);
    int origMask = ~(xMask << p);
    int clearedX = x & origMask;
    int result = clearedX & xImportantBitsInverted;

    return result;
}

int binsearch(int x, int v[], int n){
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    while (low <= high){
        mid = (low+high)/2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int linsearch(int x, int v[], int n){
    for(int i = 0; i < n; i++){
        if (v[i] == x)
            return i;
    }
    return -1;
}

void escape(char s[], char t[]){
    int i = 0;
    int j = 0;

    while(s[i] != '\0'){
        switch(s[i]){
            case '\t':
                t[j++] = '\\';
                t[j] = 't';
                break;
            case '\n':
                t[j++] = '\\';
                t[j] = 'n';
                break;
            default:
                t[j] = s[i];
        }
        ++i;
        ++j;
    }

    t[j] = '\0';
}

void realChars(char s[], char t[]){
    int i = 0;
    int j = 0;

    while(s[i] != '\0'){
        if(s[i] == '\\'){
            switch(s[i+1]){
                case 't':
                    t[j] = '\t';
                    ++i;
                    break;
                case 'n':
                    t[j] = '\n';
                    ++i;
                    break;
            }
        } else
            t[j] = s[i];

        ++i;
        ++j;
    }

    t[j] = '\0';
}

double atof(char s[]){
    double val, power, expNum;
    double expPower = 1;
    int i, j, sign, expSign;
    char expNumS[100];

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++){
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E'){
        i++;
        expSign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        j = 0;
        while(isdigit(s[i]) || s[i] == '.'){
            expNumS[j++] = s[i++];
        }
        expNumS[j] = '\0';
        expNum = atof(expNumS);
        expPower = pow(10, (expSign*expNum));
    }

    double result = (sign * val/power) * expPower;

    return result;
}

int getint(int *pn){
    int c, sign;

    while (isspace(c = getch()))
        ;
    
    if(!isdigit(c) && c != '+' && c != '-'){
        ungetch(c); // It's not a number
        return 0;
    }

    sign = (c =='-') ? -1 : 1;

    if (c == '-' && !isdigit(c = getch())){
        ungetch(c);
        *pn = EOF;
        return 0;
    }
    ungetch(c);

    if ((c = getch()) =='+' || c == '-')
        c = getch();
    for (*pn = 0;  isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;

    if (c != EOF)
        ungetch(c);
    return c;
}

// Concatenates, at most, the first n characters of f to t
void stringcat(char* f, char* t, int n){
    t = t + stringLength(t);
    int i = 0;

    while((*t++ = *f++) && i < n - 1)
        i++;
    
    *t = '\0';
}

// Copies, at most, the first n characters of f to n
void stringcopy(char* f, char* t, int n){
    int i = 0;

    while((*t++ = *f++) && i < n - 1)
        i++;
    
    *t = '\0';
}

int stringend(char* s, char* t){
    int isMatch = 0;
    char* p = t;

    while(*s){
        if (!(*p == *s)){
            p = t;
            isMatch = 0;
        }

        if(*s == *p){
            isMatch = 1;
            p++;
        }

        s++;
    }
    if(*p)
        isMatch = 0;
    
    return isMatch;
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

#define UPPERCASE 0
#define LOWERCASE 1

// Takes a string and converts to UPPERCASE or LOWERCASE
void convertCase(char *s, int lCase){
    for (int i = 0; i < stringLength(s); i++){
        if(lCase == UPPERCASE && s[i] >= 'a' && s[i] <= 'z')
            s[i] = 'A' + s[i] - 'a';
        else if(lCase == LOWERCASE && s[i] >= 'A' && s[i] <= 'Z')
            s[i] = 'a' + s[i] - 'A';
    }
}