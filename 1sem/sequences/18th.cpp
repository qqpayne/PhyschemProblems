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
    int x, p, n = 0, i = 1;
    fscanf(f, "%d", &p);
    while (fscanf(f, "%d", &x) == 1){
        if (x>p)
            ++i;
        else {
            if (i>1)
                ++n;
            i = 1;
        }
        p = x;
    }
    return n;
}