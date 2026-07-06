#pragma once
#include "afx.h"
class CMemMapFile :
	public CStdioFile
{
public:
	CMemMapFile(void);
	CMemMapFile(LPCTSTR lpszFileName, UINT nOpenFlags);
	virtual ~CMemMapFile(void);

	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError = NULL);

	virtual ULONGLONG GetPosition() const;
	virtual ULONGLONG Seek(LONGLONG lOff, UINT nFrom);

	virtual UINT Read(void* lpBuf, UINT nCount);
	virtual void Write(const void* lpBuf, UINT nCount);

	virtual void Abort();
	virtual void Flush();

	virtual void Close();
	virtual ULONGLONG GetLength() const;

	virtual BOOL ReadString(CString& rString);
	virtual LPTSTR ReadString(_Out_z_cap_(nMax) LPTSTR lpsz, _In_ UINT nMax);
	virtual void WriteString(LPCTSTR lpsz);

	// Unsupported APIs
	virtual CFile* Duplicate() const;
	virtual void LockRange(ULONGLONG dwPos, ULONGLONG dwCount);
	virtual void UnlockRange(ULONGLONG dwPos, ULONGLONG dwCount);
	virtual void SetLength(ULONGLONG dwNewLen);

protected:
	void CommonInit(void);
	UINT   m_nOpenFlags;
	HANDLE m_hMapping;
	LPBYTE m_base;
	LPBYTE m_current;
	LARGE_INTEGER m_liSize;
};

