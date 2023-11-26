#include <iostream>
#include "List.h"

int main()
{
    int a = 2;
    int* aPtr = &a;
    List<int> intList;
    intList.Push(a);
    intList.Push(3);
    intList.Push(5);
    int* b = intList.First();

    int* intPtr = intList.First();
    while (intPtr != nullptr)
    {
        printf("%d\n", *intPtr);
        intPtr = intList.Next();
    }

    char c = 70;
    List<char> stringList;
    stringList.Push(c);
    stringList.Push(71);
    stringList.Push(72);

    const char* stringPtr = stringList.First();
    while (stringPtr != nullptr)
    {
        printf("%c\n", *stringPtr);
        stringPtr = stringList.Next();
    }
}
