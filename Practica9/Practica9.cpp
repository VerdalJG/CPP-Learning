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



