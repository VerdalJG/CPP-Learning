#include "String.h"
#include <iostream>

CString::CString(const char* str)
{

}

CString::CString(const CString& str)
{
	
}

CString::~CString()
{
	
}

bool CString::operator==(const CString& other) const
{
	return false;
}

bool CString::operator!=(const CString& other) const
{
	return false;
}

bool CString::operator>(const CString& other) const
{
	return false;
}

bool CString::operator<(const CString& other) const
{
	return false;
}

CString CString::operator+(const CString& other) const
{
	return CString();
}

CString CString::operator+(char c) const
{
	return CString();
}

CString& CString::operator=(const CString& other)
{
	return other;
}

CString& CString::operator=(char c)
{
	return c;
}

CString& CString::operator+=(const CString& other)
{
	return other;
}

CString& CString::operator+=(char c)
{
	return c;
}

