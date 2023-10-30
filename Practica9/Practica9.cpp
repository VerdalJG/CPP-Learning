#include <iostream>
#include "TList.h"
#include "FileUtils.h"

int main()
{
    TList oList;
    oList.Push("First");
    oList.Push("Second");
    oList.Push("Third");
    oList.Push("Last");

    // 1 - Copy Constructor call + check for copy
    TList list2 = oList;

    const char* pString = list2.First();
    while (pString != nullptr)
    {
        printf("%s\n", pString);
        pString = list2.Next();
    }

}

