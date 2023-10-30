#include <iostream>
#include "FileUtils.h"

int FindRepetitions(FileUtils::CFile _oFile, char* _pString)
{
    unsigned int result = 0;

    char sBuffer[128];
    unsigned int uNumReads = _oFile.ReadFile(sBuffer, 128);
    sBuffer[uNumReads] = '\0';

    char* pBuffer = sBuffer;

    unsigned int uIndex1 = 0;
    unsigned int uIndex2;

    while (*(pBuffer + uIndex1) != '\0')
    {
        uIndex2 = 0;
        while (*(pBuffer + uIndex1 + uIndex2) == *(_pString + uIndex2))
        {
            if (*(_pString + uIndex2 + 1) == '\0')
            {
                result++;
                uIndex1 += uIndex2;
                break;
            }
            uIndex2++;
        }
        uIndex1++;
    }
    return result;
}

int AddNumbersInFile(FileUtils::CFile _oFile)
{
    unsigned int result = 0;

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
            uIndexToAdvance = 0;
            result += std::atoi(pBuffer + uIndex);
            /*while (std::atoi(pBuffer + uIndex + uIndexToAdvance) != 0)
            {
                uIndexToAdvance++;
            }*/
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

int main()
{
    // Practica 5 - Open, Read, Write, Close

    FileUtils::CFile oFile1;

    if (oFile1.OpenFile("filetest.txt", "r+"))
    {
        printf("File opened!\n");
    }
    else
    {
        printf("Failed to open file!\n");
    }

    char sBuffer[128];
    unsigned int uNumReads = oFile1.ReadFile(sBuffer, 128);
    sBuffer[uNumReads] = '\0';

    // Writing functionality, can uncomment, works fine

    //char sToWrite[] = "YAY";
    //WriteFile(sToWrite, sizeof(sToWrite), pFile);

    printf("%s\n", sBuffer);

    if (oFile1.CloseFile())
    {
        printf("Successfully closed file\n");
    }
    else 
    {
        printf("Failed to close file\n");
    }

    // Practica 6: part 1 - String repetitions in file
    FileUtils::CFile oFile2;
    oFile2.OpenFile("filetest.txt", "r+");
    char sToCheck[] = "idkc";
    printf("Amount of repetitions of 'idkc': %i\n", FindRepetitions(oFile2, sToCheck));
    oFile2.CloseFile();

    // Practica 6: part 2 - Add integers in file
    FileUtils::CFile oFile3;
    oFile3.OpenFile("filetest.txt", "r+");
    printf("Sum of all numbers: %i\n", AddNumbersInFile(oFile3));
    oFile3.CloseFile();

  

    
}


