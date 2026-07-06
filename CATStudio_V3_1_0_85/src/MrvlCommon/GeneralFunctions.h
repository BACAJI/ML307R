#pragma once

CString  GetACATVersionString();
UINT  GetACATVersionNumber();
CString  GetDumpFolderPath();


#define DECLARE_NO_COPY(class_name)					\
	private:										\
	class_name(const class_name&);				\
	class_name& operator= (const class_name&);	
