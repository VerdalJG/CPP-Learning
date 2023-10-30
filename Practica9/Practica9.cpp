#include <iostream>
#include "TList.h"
#include "FileUtils.h"

TList GetReverseList(TList _list);

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
    GetReverseList(oList);
}

TList GetReverseList(TList _list)
{
    TList result;
    const char* pString = _list.First();

    while (pString != nullptr)
    {
        printf("%s\n", pString);
        pString = result.Next();
    }

    return result;
}

