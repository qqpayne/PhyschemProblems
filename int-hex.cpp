#include <stdio.h>

const char * HEX_DIGITS = "0123456789ABCDEF";

int main(){
    int n;
    char hex[16];
    while (true) {
        printf("n:\n");
        if (scanf("%d", &n) < 1)
            break;
        for (int i = 7; i>=0; --i) {
            int d = (n & 0xf);
            n >>= 4;
            hex[i] = HEX_DIGITS[d];
       }
       hex[8] = 0;
       printf("hex(n): %s\n", hex);
    }
    return 0;
}   
