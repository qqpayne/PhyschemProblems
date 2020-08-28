#include <stdio.h>
#include <math.h>

/* 
Конвертирует данное целое число в любую систему счисления до 36-ичной включительно.
Написано 7.11.19 Акостеловым И.И.
*/

void convert(int num, int basis);
int basislen(int num, int basis);
void getdigits(int *arr, int num, int basis);
void invert(int *arr, int len);

int main()
{
	int x, basis;
	printf("What number do you want to convert?: ");
	scanf("%d", &x);
	while (true)
	{
		printf("To what number system base?: ");
		scanf("%d", &basis);
		if (basis < 2)
			printf("No cheating! Try again. \n");
		else
			break;
	}
	convert(x, basis);
}

void convert(int num, int basis)
{
	int len = basislen(num, basis);
	int *digits = new int[len];
	getdigits(digits, num, basis);
	invert(digits, len);

	// printing array out
	printf("%d in %d system is: ", num, basis);
	for (int i = 0; i < len; ++i)
	{
		if (digits[i] > 9)
			printf("%c", ('A' + digits[i] - 10));
		else
			printf("%d", digits[i]);
	}
	printf("\n");
}

int basislen(int num, int basis)
{
	// Returns length of given number in given basis
	int len = 1;
	while (num >= pow(basis, len))
	{
		++len;
	}
	return len;
}

void getdigits(int *arr, int num, int basis)
{
	// Fills array with digits of given number in given basis (in reversed order!)
	for (int i = 0; num != 0; ++i)
	{
		arr[i] = num % basis;
		num /= basis;
	}
}

void invert(int *arr, int len)
{
	// Inverts array in-place
	int tmp, k = 0;
	for (int i = (len - 1); i >= (len / 2); --i)
	{
		tmp = arr[k];
		arr[k] = arr[i];
		arr[i] = tmp;
		k++;
	}
}
