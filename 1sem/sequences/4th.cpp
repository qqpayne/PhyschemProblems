#include <stdio.h>

int biggerelem(FILE *f);

int main(){
	FILE *f = fopen("input.txt", "rt");
	int s = biggerelem(f);
	fclose(f);
	FILE *g = fopen("output.txt", "wt");
	fprintf(g, "%d\n", s);
	fclose(g);
	return 0;
}

int biggerelem(FILE *f){
	double x, p;
	int n = 0;
	fscanf(f, "%lg", &p);
	while (fscanf(f, "%lg", &x) == 1){
		if (x>p)
			++n;
		p = x;
	}
	return n;
}