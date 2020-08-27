#include <stdio.h>

int gcd(int a, int b);
int gcdseq(FILE *f);

int main(){
	FILE *f = fopen("input.txt", "rt");
	int s = gcdseq(f);
	fclose(f);
	FILE *g = fopen("output.txt", "wt");
	fprintf(g, "%d\n", s);
	fclose(g);
	return 0;
}

int gcdseq(FILE *f){
	int x, p;
	fscanf(f, "%d", &p);
	while (fscanf(f, "%d", &x) == 1){
		p = gcd(p, x);
	}
	return p;
}

int gcd(int a, int b){
	while (a != b){
		if (a > b)
			a = a - b;
		else
			b = b - a;
	}
	return a;
}