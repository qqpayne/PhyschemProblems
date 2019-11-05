#include <stdio.h>
#include <math.h>

int convert(int a, int basis); // this program works only for basis <= 10

int main(){
    int x;
    scanf("%d", &x);
    printf("%d", convert(x, 16));
}

int convert(int a, int basis){
    int x = a, result = 0, len = 1;
    while (x >= pow(basis, len)){ // getting length of number in basis
        ++len;
    }
    int* numbers = new int[len]; 
    
    for(int i = 0; x!=0; ++i){ // getting digits
        numbers[i] = x % basis;
        x /= basis;
    }
    
    for (int i = (len-1); i>(-1); --i){ // transforming it into a number
        result += pow(10, i)*numbers[i]; // it's better to inverse array and return it
    }
    return result;
}
