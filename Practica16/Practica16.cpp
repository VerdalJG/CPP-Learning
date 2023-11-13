#include <iostream>
#include "TList.h"

int main()
{
    class CData : public IData
    {
    public:
        CData(const char* string) : m_string(string) {}
        virtual void Print() const
        {
            printf("%s\n", m_string);
        }
        const char* m_string;
    };

    CData data1("First");
    CData data2("Second");
    CData data3("Third");
    CData data4("Last");

    TList myList;
    myList.Push(&data1);
    myList.Push(&data2);
    myList.Push(&data3);
    myList.Push(&data4);

    const IData* dataPtr = myList.First();
    while (dataPtr != nullptr)
    {
        dataPtr->Print();
        dataPtr = myList.Next();
    }
}
