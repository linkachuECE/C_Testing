#include "headers.h"

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