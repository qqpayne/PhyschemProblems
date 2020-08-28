#include <stdio.h>

/*
Нахождение НОД элементов последовательности целых чисел
Написано 02.12.19 Акостеловым И.И.
Рефакторинг 28.08.20
*/

int GCD(int a, int b);
int seqGCD(FILE *file);

int main()
{
	FILE *inFile = fopen("input.txt", "rt");
	int gcd = seqGCD(inFile);
	fclose(inFile);

	FILE *outFile = fopen("output.txt", "wt");
	fprintf(outFile, "%d\n", gcd);
	fclose(outFile);
	return 0;
}

int GCD(int a, int b)
{
	// Алгоритм Евклида вычитанием, можно и другой
	while (a != b)
	{
		if (a > b)
			a -= b;
		else
			b -= a;
	}
	return a;
}

int seqGCD(FILE *file)
{
	// НОД нескольких чисел можно найти вычислением НОДа между каждым новым элементом и НОДом всех прошлых элементов
	int x, prevGcd;
	fscanf(file, "%d", &prevGcd); // НОД одного элемента - сам элемент
	while (fscanf(file, "%d", &x) == 1)
	{
		// на каждом шаге вычисляем НОД старого НОДа и нового элемента
		prevGcd = GCD(prevGcd, x); 
	}
	return prevGcd;
}

