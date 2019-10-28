#include <stdio.h>
#include <limits.h>

int diffelem(FILE *f);

int main(){
	FILE *f = fopen("input.txt","rt");
	int s = diffelem(f);
	fclose(f);
	FILE *g = fopen("output.txt", "wt");
	fprintf(g, "%d\n", s);
	fclose(g);
	return 0;
}

int diffelem(FILE *f){
	int x, n = 0;
	int p = INT_MIN; 
	while (fscanf(f, "%d", &x) == 1){
		if (x>p)
			++n;
		p = x;
	}
	return n;
}
