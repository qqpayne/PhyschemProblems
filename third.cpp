#include <stdio.h>

double harm(FILE *f);

int main(){
	FILE *f = fopen("input.txt","rt");
	double s = harm(f);
	fclose(f);
	FILE *g = fopen("output.txt", "wt");
	fprintf(g, "%lf", s);
	fclose(g);
	return 0;
}

double harm(FILE *f){
	double x, s = 0, n = 0, harm;
	while (fscanf(f, "%lf", &x) == 1){
		s+=(1/x);
		++n;
	}
	harm = 1/(s/n);
	return harm;
}
