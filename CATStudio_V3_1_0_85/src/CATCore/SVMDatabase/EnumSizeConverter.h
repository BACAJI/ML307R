/******************************************************
*                       EnumSizeConverter.h
*
* Project : Logger                        Ver : 1.0
* Programmer : Ohad Peled        Date : 03/05/2003  10:48:46 AM
* Language : VC 6.0              Target : Win32
* Purpose :
*****************************************************/


#if !defined(AFX_ENUMSIZECONVERTER_H__7278B950_C46A_4D39_8A2A_9A15E9C9824F__INCLUDED_)
#define AFX_ENUMSIZECONVERTER_H__7278B950_C46A_4D39_8A2A_9A15E9C9824F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>
#include "SvmNode.h"

#define ENUMSIZECONVERTER_MAX_SIGNAL_BUFFER_LENGTH	(100*1024)

class CSvmNode;

// typedef BOOL(LP_DBLOADER_FUNC)(int, CWnd*, BOOL, BOOL);
// typedef int(LP_UPDATE_STRUCT_FUNC)(int, const CString&, CObList&, LPBYTE, int&, BOOL, BOOL);


class CEnumSizeConverter : public CObject  
{
public:
	CEnumSizeConverter();
	virtual ~CEnumSizeConverter();
	BOOL ConvertEnumSize(DWORD nID,int m_nDeviceIndex,BYTE* pBufIn,int nBufInSize,BYTE** ppRetBufOut,int& nBufOutSize,int nHeaderSize);
	BOOL ConvertEnumSizeFromGKIToIcl(DWORD nID,int m_nDeviceIndex, BYTE* pBufIn,int nBufInSize,BYTE** ppRetBufOut,int& nBufOutSize,int nHeaderSize);
	void EmptySignalsMap();
	CString GetLastError(){return m_strLastError;}
	void SetDbLoadedFalse();

private:
	bool ConvertEnums(CSvmObject* pParentNode, int nIdx, BYTE *pBufIn, BYTE *pBufOut, int &nInIndex, int &nOutIndex, CList<CSvmObject*> *pObList, CList<CSvmObject*> *pObList4B);
	bool ConvertEnumsFromGKIToIcl(CSvmObject* pParentNode, int nIdx, BYTE *pBufIn, BYTE *pBufOut, int &nInIndex, int &nOutIndex, CList<CSvmObject*> *pObList, CList<CSvmObject*> *pObList4B);
	
	BYTE m_BufOut[ENUMSIZECONVERTER_MAX_SIGNAL_BUFFER_LENGTH];

	CString m_strLastError;
	int m_nMaxBufferSize;
	int m_nMaxInBufferSize;
	int m_nBufInSize;

	CMap<CString,LPCTSTR,CSvmNode*,CSvmNode*> m_mapSignalToStruct4BAligned;
	CMap<CString,LPCTSTR,CSvmNode*,CSvmNode*> m_mapSignalToStructMinAligned;

	CCriticalSection		m_EnumConvertCriticalSection;
	int						m_nDeviceIndex;

	BOOL m_bLoaded;

// 	LP_DBLOADER_FUNC *m_pDBLoaderFunc;
// 	LP_UPDATE_STRUCT_FUNC *m_pUpdateStructureFunc;
	
};

#endif // !defined(AFX_ENUMSIZECONVERTER_H__7278B950_C46A_4D39_8A2A_9A15E9C9824F__INCLUDED_)
