#pragma once

#include <string>
typedef unsigned int   uint;
typedef char  int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef __int64  int64;
typedef unsigned __int64 uint64;
typedef std::wstring  string16;
typedef wchar_t  char16;


#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif