#include <iostream>
#include "TList.h"
#include "FileUtils.h"

TList GetNumbersInFile(FileUtils::CFile _oFile);

int main()
{
    // Practica 10

    // 1 - Get numbers in file

    FileUtils::CFile oFile;
    oFile.OpenFile("filetest.txt", "r+");

    TList numbersList;
    numbersList = GetNumbersInFile(oFile);

    // 2 - Print numbers in file

    const char* numListPtr = numbersList.First();
    while (numListPtr != nullptr)
    {
        printf("%s\n", numListPtr);
        numListPtr = numbersList.Next();
    }

    // Practica 11

    // 1 - Copy Constructor call + check for copy

    TList oList;
    oList.Push("First");
    oList.Push("Second");
    oList.Push("Third");
    oList.Push("Last");

    TList list2 = oList;

    const char* pString = list2.First();
    while (pString != nullptr)
    {
        printf("%s\n", pString);
        pString = list2.Next();
    }


    // 2 - Reverse List 
    TList reversedList;

    reversedList = reversedList.GetReverseList(oList);

    const char* pString2 = reversedList.First();
    while (pString2 != nullptr)
    {
        printf("%s\n", pString2);
        pString2 = reversedList.Next();
    }

    const char* pString3 = oList.First();
    while (pString3 != nullptr)
    {
        printf("%s\n", pString3);
        pString3 = oList.Next();
    }

}

TList GetNumbersInFile(FileUtils::CFile _oFile)
{
    TList result;
    char sBuffer[128];
    unsigned int uNumReads = _oFile.ReadFile(sBuffer, 128);
    sBuffer[uNumReads] = '\0';

    char* pBuffer = sBuffer;
    unsigned int uIndex = 0;
    unsigned int uIndexToAdvance;

    while (*(pBuffer + uIndex) != '\0')
    {
        if (std::atoi(pBuffer + uIndex) != 0) // if it is a number
        {
            int numberFound = std::atoi(pBuffer + uIndex);
            char* buffer = new char; // CANNOT DECLARE WITH [] because it puts it on the stack. Must be on heap.
            result.Push(_itoa(numberFound, buffer, 10));

            uIndexToAdvance = 0;

            while (*(pBuffer + uIndex + uIndexToAdvance) != ',')
            {
                if (*(pBuffer + uIndex + uIndexToAdvance) == '\0') break;
                uIndexToAdvance++; // Find comma before looking for next number
            }

            uIndex += uIndexToAdvance;
        }

        else
        {
            uIndex++;
        }
    }

    return result;
}
