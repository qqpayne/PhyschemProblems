#include <stdio.h> 

int growing(FILE *f);

int main(){
    FILE *f = fopen("input.txt", "rt");
    int r = growing(f);
    fclose(f);
    FILE *g = fopen("output.txt", "wt");
    fprintf(g, "%d\n", r);
    fclose(g);
    return 0;
}


int growing(FILE *f){
    int x, p, n = 0;
    bool maybe = false;
    fscanf(f, "%d", &p);
    while (fscanf(f, "%d", &x) == 1){
        if ((x<=p) and maybe)
            ++n; 
        if (x>=p)
            maybe = true;
        else
            maybe = false;
        p = x;
    }
    return n;
}