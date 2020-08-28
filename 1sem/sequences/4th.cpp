#include <stdio.h>

/*
Подсчёт числа элементов последовательности вещественных чисел, больших предыдущих
Написано 02.12.19 Акостеловым И.И.
Рефакторинг 28.08.20
*/

int biggerelem(FILE *file);

int main()
{
	FILE *inFile = fopen("input.txt", "rt");
	int numb = biggerelem(inFile);
	fclose(inFile);

	FILE *outFile = fopen("output.txt", "wt");
	fprintf(outFile, "%d\n", numb);
	fclose(outFile);
	return 0;
}

int biggerelem(FILE *file)
{
	double x, prev;
	int numb = 0;
	fscanf(file, "%lg", &prev); 
	while (fscanf(file, "%lg", &x) == 1)
	{
		if (x > prev) ++numb;
		prev = x;
	}
	return numb;
}