#include <iostream>

/*
Пирамидальная сортировка

Входной массив преобразуется в двоичную кучу, где у каждого элемента (индекс i) есть два сына 
с индексами 2i + 1 и 2i + 2. Сортирует как max-heap, ставя root-ом в каждое поддереве наибольший элемент

Для понимания: первоначальное построение пирамиды гарантирует то, что наибольший элемент 
будет находиться в корне в начале работы и сыновья любого элемента будут меньше него самого

Написано 06.05.20 Акостеловым И.И.
Переписано 29.08.20
*/

void heapSort(double *arr, int length);
void heapify(double *arr, int length, int m);
void swap(double *a, double *b);

int main()
{
	// при желании можно вводить массив каким угодно способом
	// для простоты - hardcode
	double arr[] = {12, 11, 13, 5, 6, 7, 7, 11, 2};
	int length = sizeof(arr) / sizeof(arr[0]);

	heapSort(arr, length);

	for (int i = 0; i < length; ++i)
		std::cout << arr[i] << " ";
	std::cout << "\n";
}

void heapSort(double *arr, int length)
{
	// строим пирамиду снизу вверх,
	// начиная с самого правого элемента предпоследнего слоя
	for (int i = length / 2 - 1; i >= 0; i--)
		heapify(arr, length, i);
	
	// один за другим извлекаем элементы из кучи и перемещаем их в конец
	for (int i = length - 1; i >= 0; i--)
	{
		// перемещаем текущий корень (наибольший элемент) в конец и больше его не трогаем
		swap(&arr[0], &arr[i]);

		// просеиваем наибольший элемент вверх на уменьшенной куче
		heapify(arr, i, 0);
	}
}

// просеять i-ый элемент, переместив на i-ую позицию наибольший из его потомков
void heapify(double *arr, int length, int i)
{
	while (true)
	{
		int max = i;
		int leftSon = 2 * i + 1;
		int rightSon = 2 * i + 2;

		// находим наибольший из сыновей
		if (leftSon < length && arr[leftSon] > arr[max])
			max = leftSon;
		if (rightSon < length && arr[rightSon] > arr[max])
			max = rightSon;

		if (max != i)
			swap(&arr[i], &arr[max]);
		else
			break;

		/* 
		если мы переместили какой-то из дочерних элементов, то 
		просеиваем и то поддерево, в котором он был root-ом, 
		применяя к нему ту же процедуру
		*/
		i = max;
	}
}

// поменять местами переменные a и b
void swap(double *a, double *b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}