#include <stdio.h>

/*
Подсчёт среднего гармонического последовательности вещественных чисел
Написано 02.12.19 Акостеловым И.И.
Рефакторинг 28.08.20
*/

double harmseq(FILE *file);

int main()
{
	FILE *inFile = fopen("input.txt", "rt");
	double s = harmseq(inFile);
	fclose(inFile);

	FILE *outFile = fopen("output.txt", "wt");
	fprintf(outFile, "%lg\n", s);
	fclose(outFile);
	return 0;
}

double harmseq(FILE *file)
{
	double x, sum = 0;
	int length = 0;
	while (fscanf(file, "%lg", &x) == 1)
	{
		sum += (1 / x);
		++length;
	}
	sum = length / sum;
	return sum;
}