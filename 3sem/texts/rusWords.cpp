#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include "utf8/utf8.h"

using namespace std;

/*
Программа, позволяющая найти пары слов в тексте на русском языке и отсортировать их по частоте (с одинаковой частотой - лексикографически).
Два соседних слова образуют пару, если между ними нет знаков препинания и других символов, кроме пробелов, переводов строк и дефисов.
Т.к не было явно обозначено, считаем что пара 'яблоко-банан' и 'яблоко банан' - одинаковые пары. Поэтому в финальном выводе разделитель не фигурирует
Пары вида 'яблоко банан' и 'банан яблоко' - разные пары.
Написано 06.12.20 Акостеловым И.И.
*/

typedef int UnicodeChar;
typedef basic_string<UnicodeChar> UnicodeString;
typedef pair<UnicodeString, UnicodeString> pairOfWords;

char allowedPunctuation[] = {' ', '\n', '\r', '\t', '-'}; // символы, нахождение которых между двумя словами не мешает им быть парой

void extractPairs(map<pairOfWords, int> &words);
bool allowedPunc(UnicodeChar c);
bool comparePairs(
    const pair<pairOfWords, int> &i0,
    const pair<pairOfWords, int> &i1);
bool comparePairOfUnicodeStrings(const pairOfWords &s0, const pairOfWords &s1);
bool compareUnicodeStrings(const UnicodeString &s0, const UnicodeString &s1);
std::ostream &operator<<(std::ostream &stream, const pairOfWords &pair);

int main()
{
    map<pairOfWords, int> words;
    extractPairs(words);

    // Вывести пары слов, отсортированные по частоте вхождения и лексикографически
    vector<pair<pairOfWords, int>> wordFreq;
    for (auto i = words.cbegin(); i != words.cend(); ++i)
    {
        wordFreq.push_back(*i);
    }
    cout << "Число различных пар слов в тексте: " << wordFreq.size() << endl;

    stable_sort(wordFreq.begin(), wordFreq.end(), comparePairs);

    int counter = 0;
    for (auto i = wordFreq.cbegin(); i != wordFreq.cend() && counter <= 500; ++i)
    {
        cout << i->second << "\t" << i->first << endl;
        ++counter;
    }

    return 0;
}

// Finite-state machine для корректного добавлени пар слов
// Немного монструозно, но зато легче проектировать и находить ошибки
void extractPairs(map<pairOfWords, int> &words)
{
    pairOfWords wordPair;

    enum State
    {
        zeroWord,
        oneWord,
        twoWords
    };

    State state = zeroWord;

    while (true)
    {
        bool readFail, punctuation;

        if (state == twoWords)
        {
            if (words.count(wordPair) == 0) // пары слов нет в словаре - добавляем их
                words[wordPair] = 1;
            else // пара слов есть в словаре - повышаем число вхождений
                ++(words[wordPair]);

            wordPair.first = wordPair.second; // сохраняем только что прочтенное слово в буфер
            wordPair.second.clear();          // чистим место для нового слова

            if (punctuation)
            {
                // если нашли 'запрещенный' разделитель, то считаем, что пара слов кончилась, и отбрасываем буффер
                wordPair.first.clear();
                state = zeroWord;
                punctuation = false;
            }
            else
            {
                // иначе сохраняем буффер и ищем следующее слово
                state = oneWord;
            }

            continue;
        }

        UnicodeChar c = get_utf8_code_point(cin, readFail);
        if (readFail)
        {
            if (!cin.good())
                break;
        }

        if (state == zeroWord)
        {
            if (isRussianLetter(c)) // записываем слово по буквам
            {
                c = toLowerLetter(c);
                wordPair.first += c;
            }
            else if (allowedPunc(c) && (wordPair.first.length() > 0))
            {
                // если нашли какой либо из 'разрёшенных' разделителей, считаем что слово кончилось и переходим к следующему
                state = oneWord;
            }
            else
            {
                // если нашли 'запрещенный' разделитель, то считаем слово кончилось (и т.к оно всего
                // одно), отбрасываем его
                wordPair.first.clear();
            }
        }
        else if (state == oneWord)
        {
            if (isRussianLetter(c)) // записываем слово по буквам
            {
                c = toLowerLetter(c);
                wordPair.second += c;
            }
            else if (allowedPunc(c) && wordPair.second.length() > 0)
            {
                // если нашли какой либо из 'разрёшенных' разделителей, считаем что слово кончилось
                state = twoWords;
            }
            else
            {
                if (wordPair.second.length() == 0)
                {
                    // если так случилось, что 'запрещенный' разделитель передался еще до первых букв нового слова, то откатываемся к zeroWord
                    wordPair.first.clear();
                    state = zeroWord;
                }
                else
                {
                    // если нашли 'запрещенный' разделитель, то считаем, что слово кончилось и передаем флаг punctuation (см. twoWords)
                    state = twoWords;
                    punctuation = true;
                }
            }
        }
    }
}

bool allowedPunc(UnicodeChar c)
{
    return (find(begin(allowedPunctuation), end(allowedPunctuation), c) != end(allowedPunctuation));
}

bool comparePairs(
    const pair<pairOfWords, int> &i0,
    const pair<pairOfWords, int> &i1)
{
    return (
        i0.second > i1.second ||
        (i0.second == i1.second &&
         comparePairOfUnicodeStrings(i0.first, i1.first) < 0));
}

bool comparePairOfUnicodeStrings(
    const pairOfWords &s0, const pairOfWords &s1)
{
    bool firstWord = compareUnicodeStrings(s0.first, s1.first);
    if (firstWord < 0)
    {
        return firstWord;
    }
    else
    {
        return compareUnicodeStrings(s0.second, s1.second);
    }
}

bool compareUnicodeStrings(
    const UnicodeString &s0, const UnicodeString &s1)
{
    int len0 = s0.length();
    int len1 = s1.length();
    for (int i = 0; i < len0; ++i)
    {
        if (i >= len1)
            return false;
        int c = compareRussianLetters(s0[i], s1[i]);
        if (c < 0)
            return true;
        else if (c > 0)
            return false;
    }
    return (len0 < len1);
}

std::ostream &operator<<(std::ostream &stream, const pairOfWords &pair)
{
    UnicodeString str;

    str = pair.first;
    for (size_t i = 0; i < str.length(); ++i)
    {
        output_utf8(stream, str[i]);
    }

    stream << " ";

    str = pair.second;
    for (size_t i = 0; i < str.length(); ++i)
    {
        output_utf8(stream, str[i]);
    }

    return stream;
}
