#include <stdio.h> 

bool isrecur(FILE *f);

int main(){
    FILE *f = fopen("input.txt", "rt");
    bool r = isrecur(f);
    fclose(f);
    FILE *g = fopen("output.txt", "wt");
    if (r)
        fprintf(g, "yes\n");
    else
        fprintf(g, "no\n");
    fclose(g);
    return 0;
}


bool isrecur(FILE *f){
    int a, b, c, d, x, x1, x2, s, i = 0;
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