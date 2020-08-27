#include <stdio.h>

double harmseq(FILE *f);

int main(){
	FILE *f = fopen("input.txt", "rt");
	double s = harmseq(f);
	fclose(f);
	FILE *g = fopen("output.txt", "wt");
	fprintf(g, "%lg\n", s);
	fclose(g);
	return 0;
}

double harmseq(FILE *f){
	double x, s = 0;
	int n = 0;
	while (fscanf(f, "%lg", &x) == 1){
		s+=(1/x);
		++n;
	}
	s = n/s;
	return s;
}