#include <stdio.h>

/*
Перевод целого числа в шестнадцатеричную систему счисления (отрицательные числа через дополнительный код)
Работает на том, что шестнадцатеричная система использует те же самые биты из двоичной, сгрупированные в группы по четыре
Написано в конце 2019 Акостеловым И.И.
Переписано 28.08.20
*/

const char *HEX_DIGITS = "0123456789ABCDEF"; // массив доступных цифр в шестнадцатеричной системе счисления

void convert(char *arr, int number);
int findEmpty(char *arr);

int main()
{
    int intNumb;
    char hex[9]; // 8 битов в восьмеричной системе уже больше чем INT_MAX

    // работает, пока пользователь не Ctrl-C'шнется
    while (true)
    {
        printf("your integer number: ");
        if (scanf("%d", &intNumb) < 1)
            break;

        convert(hex, intNumb);

        char *hex_chopped = hex + findEmpty(hex);
        printf("your number in hexadecimal: %s\n", hex_chopped);
    }
    return 0;
}

void convert(char *arr, int number)
{
    // записывает шестнадцатеричное число в указанный массив символов (должен быть размера 10)
    for (int i = 8; i >= 0; --i)
    {
        // побитовое И между введеным числом и 1111 (F в восьмеричной системе)
        // возвращает то, чему в шестнадцатеричной системе равна первая цифра
        int d = (number & 0xf);
        number >>= 4; // сдвигаем на четыре бита (1111)
        arr[i] = HEX_DIGITS[d];
    }
}

int findEmpty(char *arr)
{
    // находит, на сколько позиций можно безопасно переместить указатель на начало массива (срезав бесполезные нули в начале)
    int counter = 0;
    for (int i = 0; i <= 8; ++i)
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
    return 8; // чтобы отображался ноль
}
