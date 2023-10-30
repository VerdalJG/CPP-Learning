#include <iostream>
#include "CList.h"
#include "FileUtils.h"

int main()
{
    CList oList;
    oList.Push("First");
    oList.Push("Second");
    oList.Push("Third");
    oList.Push("Last");


    const char* pString = oList.First();
    while (pString != nullptr)
    {
        printf("%s\n", pString);
        pString = oList.Next();
    }
}

