#include <stdio.h>

/*
Перевод целого числа в восьмеричную систему счисления (отрицательные числа через дополнительный код)
Работает на том, что восьмеричная система использует те же самые биты из двоичной, сгрупированные в группы по три
Написано в конце 2019 Акостеловым И.И.
Переписано 28.08.20
*/

const char *OCT_DIGITS = "01234567"; // массив доступных цифр в восьмеричной системе

void convert(char *arr, int number);
int findEmpty(char *arr);

int main()
{
    int intNumb;
    char oct[12]; // 11 битов в восьмеричной системе уже больше чем INT_MAX

    // работает, пока пользователь не Ctrl-C'шнется
    while (true)
    {
        printf("your integer number: ");
        if (scanf("%d", &intNumb) < 1)
            break;

        convert(oct, intNumb);

        char *oct_chopped = oct + findEmpty(oct);
        printf("your number in octal: %s\n", oct_chopped);
    }
    return 0;
}

void convert(char *arr, int number)
{
    // записывает восьмеричное число в указанный массив символов (должен быть размера 12)
    for (int i = 11; i >= 0; --i)
    {
        // побитовое И между введеным числом и 111 (7 в восьмеричной системе)
        // возвращает то, чему в восьмеричной системе равна первая цифра
        int d = (number & 07);
        number >>= 3; // сдвигаем на три бита (111)
        arr[i] = OCT_DIGITS[d];
    }
}

int findEmpty(char *arr)
{
    // находит, на сколько позиций можно безопасно переместить указатель на начало массива (срезав бесполезные нули в начале)
    int counter = 0;
    for (int i = 0; i <= 11; ++i)
    {
        if (arr[i] != '0')
        {
            return counter + 1;
        }
        else if (arr[i] == '0')
        {
            counter = i;
        }
    }
    return 11; // чтобы отображался ноль
}