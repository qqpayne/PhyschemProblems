
#include <stdio.h>

const char * OCT_DIGITS = "01234567";

int main(){
    int n;
    char oct[12];
    while (true) {
        printf("n: ");
        if (scanf("%d", &n) < 1)
            break;
        for (int i = 10; i>=0; --i) {
            int d = (n & 07);
            n >>= 3;
            if ((i == 0) and (d>3)){
            	d = d-4; // removing last bit
            }
            oct[i] = OCT_DIGITS[d];
        }
       oct[12] = 0;
       printf("oct(n): %s\n", oct);
    }
    return 0;
}   