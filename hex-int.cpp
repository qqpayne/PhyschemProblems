#include <stdio.h>
#include <string.h>

int main(){
    int n;
    printf("Hex number:\n");
    scanf("%8s", hex);
    len = strlen(hex);
    
    for (int i = len-1; i>=0; --i){
        char d = hex[i];
        int k;
        if ('0' <=d && d <= '9')
            k = d - '0';
        else if ('A' <= d && d <= 'F')
            k = d - 'A';
        else if ('a' <= d && d <= 'f')
            k = d - 'a';
        else
            break;
            
        n |= (k << ( 
        
    }
    printf("%d", n);
