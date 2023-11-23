#pragma once

#define DECLARE_ENUM_VALUE(_VALUE) \
    _VALUE,

#define DECLARE_ENUM_TO_STRING(_VALUE) \
    if(_enum == Enum::_VALUE) return #_VALUE;

#define DECLARE_STRING_TO_ENUM(_VALUE) \
    if(strcmp(#_VALUE, _string) == 0) return Enum::_VALUE;

#define DECLARE_ENUM(_NAME, _VALUES) \
struct _NAME \
{ \
    enum class Enum \
    { \
        _VALUES(DECLARE_ENUM_VALUE) \
        Count, \
        Invalid \
    }; \
    static const char* ToString(Enum _enum) \
    { \
        _VALUES(DECLARE_ENUM_TO_STRING) \
        return "Invalid"; \
    } \
    static Enum ToEnum(const char* _string) \
    { \
        _VALUES(DECLARE_STRING_TO_ENUM) \
        return Enum::Invalid; \
    } \
};