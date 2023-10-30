#include <iostream>

const char* tStrings[] =
{
    "First",
    "Second",
    "Another one",
    "HAHA"
};
int size = sizeof(tStrings) / sizeof(tStrings[0]);

const char* GetString(int _index)
{
    return tStrings[_index];
}

const char* GetStringReversed(int _index)
{
    const char* sBaseString = GetString(_index);
    size_t uStringSize = std::strlen(sBaseString);
    char* sReversedString = new char[uStringSize + 1];

    for (unsigned int i = 0; i < uStringSize; i++)
    {
        sReversedString[i] = sBaseString[uStringSize - i - 1];
    }
    sReversedString[uStringSize] = '\0';
    
    return sReversedString;
}

int main()
{
    printf("Size of string array: %d\n", size);

    int iIndex = 2;
    if (iIndex < size)
    {
        // #1 - Get string from array based on index
        printf("%s\n", GetString(iIndex));

        // #2 - Get string from array based on index and reverse it
        printf("%s\n", GetStringReversed(iIndex));
    }
}
