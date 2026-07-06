// CSN1Handler.h: interface for the CCSN1Handler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSN1HANDLER_H__64C3669E_4453_4506_B013_94BABF0D3388__INCLUDED_)
#define AFX_CSN1HANDLER_H__64C3669E_4453_4506_B013_94BABF0D3388__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CSN1MsgNameAndStruct.h"


typedef int(SVM_SET_GET_CONTENT_PTR)(int, LPCTSTR, LPBYTE, int);

class CCSN1Engin;

class CCSN1Handler  
{
public:
	CCSN1Handler();
	virtual ~CCSN1Handler();

	void Init(CMap<CString, LPCTSTR, DWORD, DWORD> *SignalNameToSignalIDMap);
	void ReloadSignalsIds();
	
	BOOL IsCSN1Msg(DWORD dwSigId);
	BOOL GetCSN1MsgName(DWORD dwSigId, BYTE* pData, CString& strCSN1Name);
	BOOL GetCSN1MsgDetails(int nDevice, DWORD dwSigId, BYTE* pData, CString& strCSN1Details);
	BOOL GetCSN1MsgDirection(DWORD dwSigId, int &direction);
	DWORD GetCSN1SignalID (const CString &strCsn1MsgName);
	BOOL DecodeCSN1Message(int nDevice,DWORD dwSigId,BYTE *pDataBuffer,int bufferLen,CString &strDecodedMsg);
	CStringList * GetGKISignalsForCSN1();
   void SetNvmDbPath(CString strCpNvmDbPath, CString strApNvmDbPath, int nCpType, int nApType, int nUnionVer );
private:

	//Members
	CMap<DWORD,DWORD&,int,int&>					m_mapSignalIdToDetailsIndex;
	CMap<CString, LPCTSTR, DWORD, DWORD>			*m_SignalNameToSignalIDMap;
	CArray<CCSN1MsgDetails, CCSN1MsgDetails&>	m_arrSinalsDetails;
	CMap<DWORD, DWORD, int, int>			m_SignalIDToIndex;
	CMap<CString, LPCTSTR, int, int>			m_SignalNameToIndex;
	CStringList									*m_strCSN1SignalsNames;
	HMODULE										m_hCSN1EngineDll;
	CCSN1Engin*									m_pCSN1Engine;
   CString                             m_strCpNvmDbPath;
   CString                             m_strApNvmDbPath;
   int	m_nCpType;
   int  m_nApType;
   int  m_nUnionVer;

	typedef	 CCSN1Engin* (*LPFUNC_CSN1INST)();
	typedef	 void (*LPFUNC_CSN1FREE)(CCSN1Engin*);
#if 0 // _MSC_VER > 1200
	typedef	 BOOL (*LPFUNC_CSN1ENGINEAPI)(const char *, int, CStringA&);
#else
	typedef	 BOOL (*LPFUNC_CSN1ENGINEAPI)(const char *, int, CString&);
#endif
   typedef   LPFUNC_CSN1ENGINEAPI LPFUNC_CSN1API;
	
	//Functions
	void LoadToSignalsMap();
	int GetDataIndexForRLCMAC(const unsigned char *pDataBuffer);
	void SetSVMFuncsPtr();
	bool NeedToDecode(const unsigned char *pDataBuffer,const CCSN1MsgDetails tmpDetails);
	
	SVM_SET_GET_CONTENT_PTR	*pSetNvmContentFunc;
	SVM_SET_GET_CONTENT_PTR	*pGetNvmContentFunc;

	HINSTANCE				hSVMLib;
	BOOL m_bLoaded;

	CString getDownLinkMsgType(unsigned char nType);
	CString getUpLinkMsgType(unsigned char nType);
	CString getAccStratumMessageType(unsigned char nType);
	CString getSystemInformation(unsigned char nType);

};

#endif // !defined(AFX_CSN1HANDLER_H__64C3669E_4453_4506_B013_94BABF0D3388__INCLUDED_)
