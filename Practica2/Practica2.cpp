#include <iostream>

void GetBytes(int* _iValue)
{
    char* pChar = reinterpret_cast<char*>(_iValue);
    for (int i = 0; i < 4; i++, pChar++)
    {
        printf("Byte %i: %u\n", i, *pChar);
    }
}

int GetHighestInt(int* _iTable, unsigned int _uTableSize)
{
    int iResult = INT_MIN;
    for (unsigned int i = 0; i < _uTableSize; i++, _iTable++)
    {
        if (*_iTable > iResult)
        {
            iResult = *_iTable;
        }
    }
    return iResult;
}

unsigned int GetHighestByte(int* _iTable, unsigned int _uTableSize)
{
    unsigned char* pChar = reinterpret_cast<unsigned char*>(_iTable);
    unsigned int iResult = 0u;
    for (unsigned int i = 0; i < _uTableSize * sizeof(unsigned int); i++)
    {
        if (*(pChar + i) > iResult)
        {
            iResult = *(pChar + i);
        }
    }
    return iResult;
}

void ReverseString(char* pString)
{
    unsigned int uStringSize = 0;
    while (*pString != '\0')
    {
        //printf("%c", *pString);
        ++uStringSize;
        pString++;
    }
    pString -= uStringSize;
    int iEndIndex = uStringSize - 1;
    char temp;
    for (unsigned int i = 0; i <= uStringSize / 2; i++)
    {
        // Basic array swapping
        temp = *(pString + i); // Store character in a temp variable
        *(pString + i) = *(pString + iEndIndex); // Set first character to the last character
        *(pString + iEndIndex) = temp; // Set last character to the stored value in temp
        iEndIndex--;
    }
}

int main()
{
    // #1 - Separate bytes
    int iValue = 0xEEDDCCBB;
    GetBytes(&iValue);

    // #2 - Get table max (int)
    int iTable[] = { 1, 3, 2, 5, 3, static_cast<int>(0xFFFFFFFF), 2 };
    const unsigned int uTableSize = sizeof(iTable) / sizeof(int);
    printf("Highest Value: %u\n", GetHighestInt(iTable, uTableSize));

    // #3 - Get table max (byte)
    printf("Highest Byte: %u\n", GetHighestByte(iTable, uTableSize));

    // #4 - Reverse String
    char string[] = "Hello!";
    ReverseString(string);
    printf("%s\n", string);

}