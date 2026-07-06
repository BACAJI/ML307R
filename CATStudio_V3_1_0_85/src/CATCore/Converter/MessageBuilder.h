/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

 


// MessageBuilder.h: interface for the CMessageBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEBUILDER_H__E670B688_2611_4FDC_9FEF_4716AE6941D9__INCLUDED_)
#define AFX_MESSAGEBUILDER_H__E670B688_2611_4FDC_9FEF_4716AE6941D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommandAndMessageStructures.h"
#include "ConverterManager.h"

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
class DLL_EXPORT CMessageBuilder  
{
public:
	CMessageBuilder();
	virtual ~CMessageBuilder();

	int BuildGKISignalHeader(int nDevice, BYTE *pBuffer, GKI_Signal &signal, BOOL bSide=kComm);
	int BuildGKICommandHeader(int nDevice, BYTE *pBuffer, GKI_Command &command, BOOL bSide=kComm);


	//Modified,  Add a length
	DWORD FindGKISignalID_DIAG(int nDevice, WORD diagSap, BYTE *pBuffer,int iLength);
	
	DWORD FindGKISignalID(int nDevice, BYTE *pBuffer, int iLength,BOOL bSide=kComm);
	DWORD FindGKILoggedSignalID(int nDevice, BYTE *pBuffer,int iLength,BOOL bSide=kComm);
	DWORD FindGKISpecialLoggedSignalID(int nDevice, BYTE *pBuffer,int iLength,BOOL bSide=kComm);
	

	DWORD FindGKISignalID_EMMI(int nDevice, BYTE signalType, BYTE *pBuffer,int iLength);
	BYTE  FindGKICommandID(BYTE *pBuffer);

	int BufferToGKISignalHeader_EMMI(int nDevice, BYTE signalType, BYTE *pBuffer, GKI_Signal &signal);
	int BufferToGKISignalHeader_DIAG(int nDevice, WORD diagSap, BYTE *pBuffer, GKI_Signal &signal);
	int BufferToGKISpecialLoggedSignalHeader(int nDevice, BYTE *pBuffer, GKI_Signal &signal, BOOL bSide=kComm);
	int BufferToGKILoggedSignalHeader(int nDevice, BYTE *pBuffer, GKI_Signal &signal, BOOL bSide=kComm);
	int BufferToGKISignalHeader(int nDevice, BYTE *pBuffer, GKI_Signal &signal, BOOL bSide=kComm);

};

#endif // !defined(AFX_MESSAGEBUILDER_H__E670B688_2611_4FDC_9FEF_4716AE6941D9__INCLUDED_)
