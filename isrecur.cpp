#include <stdio.h> 

/*
This function determines if sequence elems satisfy a(x(i)) + b(x(i+1)) + c(x(i+2)) = d. 
Written October 19, 2019
*/

bool isrecur(FILE *f){
    int a, b, c, d, x, x1, x2, i = 0;
    int result = true;
    fscanf(f, "%d", &a);
    fscanf(f, "%d", &b);
    fscanf(f, "%d", &c);
    fscanf(f, "%d", &d);
    while (fscanf(f, "%d", &x2) == 1){
        s=(a*x+b*x1+c*x2);
        if ((s != d) and (i>1)){
            result = false;
            break;
        }
        x=x1;
        x1=x2;
        ++i;
    }
    return result;
}
