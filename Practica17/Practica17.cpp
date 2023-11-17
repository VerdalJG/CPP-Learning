#include <iostream>
#include <string>



#define DECLARE_ENUM_VALUE(_VALUE) \
    _VALUE,

#define DECLARE_ENUM(_NAME, _VALUES) \
struct _NAME \
{ \
    enum Enum \
    { \
        _VALUES(DECLARE_ENUM_VALUE) \
        Count, \
        Invalid \
    }; \
};

#define ENUM_COLORS(_CALL) \
    _CALL(Red) \
    _CALL(Orange) \
    _CALL(Yellow)

DECLARE_ENUM(EColor, ENUM_COLORS)

    /*static const char* ToString(Enum _enum)
    {
#define REG_MACRO(_VALUE) \
    if (_enum == _VALUE) return #_VALUE;
        ENUM_CREATOR
#undef REG_MACRO
        return "Invalid";
    }

    static Enum ToEnum(const char* _string)
    {
#define REG_MACRO(_VALUE) \
    if (strcmp(#_VALUE, _string) == 0) return _VALUE;
        ENUM_CREATOR
#undef REG_MACRO
        return Invalid;
    }*/



int main()
{
    SEnum::Enum test1 = SEnum::Red;
    SEnum::Enum test2 = SEnum::Orange;
    SEnum::Enum test3 = SEnum::Yellow;

    printf("There are %d entries in enum\n", static_cast<int>(SEnum::Count));
    //printf("The variable test1 is: %s\n", SEnum::ToString(test1));
    //printf("The variable test2 is: %s\n", SEnum::ToString(test2));
    //printf("The variable test3 is: %s\n", SEnum::ToString(test3));
}
