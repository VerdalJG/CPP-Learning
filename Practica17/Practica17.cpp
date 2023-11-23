#include <iostream>
#include <string>

#include "Enum.h"

#define ENUM_COLORS(_CALL) \
    _CALL(Red) \
    _CALL(Orange) \
    _CALL(Yellow)

DECLARE_ENUM(EColor, ENUM_COLORS)

int main()
{
    EColor::Enum test1 = EColor::Enum::Red;
    EColor::Enum test2 = EColor::Enum::Orange;
    EColor::Enum test3 = EColor::Enum::Yellow;

    printf("There are %d entries in enum\n", static_cast<int>(EColor::Enum::Count));
    printf("The variable test1 is: %s\n", EColor::ToString(test1));
    printf("The variable test2 is: %s\n", EColor::ToString(test2));
    printf("The variable test3 is: %s\n", EColor::ToString(test3));
}
