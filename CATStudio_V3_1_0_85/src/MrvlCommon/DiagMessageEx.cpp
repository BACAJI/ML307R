// DiagMessageEx.cpp: implementation of the CDiagMessageEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiagMessageEx.h"
//#include "UE_Rec.h"
//#include "ApplicationINI.h"

//lee add
#include "ICATMessage.h"
#include "..\CATCore\Converter\ConverterManager.h"
#include "..\CATCore\Converter\DSPRecord.h"
#include "CommInterface.h"
#include "XmlConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#pragma comment(lib, "catcore.lib")

/////////////////////////////////////////////////////////////////////////////
///  GKI Data reader 
/////////////////////////////////////////////////////////////////////////////

CGKIExData::CGKIExData(CICATMessage * pIcatMessage)
	: m_pIcatMessage(pIcatMessage)
	, m_iFrameNumberIndex(0)
	, m_iFrameTicksIndex(0)
	, m_iSkipSize(0)
	, m_dwSkipSize(0)
{
	m_iDataIndex = 0;
	int nCurrentDevice = m_pIcatMessage->GetDevice();

	m_taskIDSize			= theConverterManager(nCurrentDevice)->GetGKITaskIDSize();
	m_nSignalIDSize			= theConverterManager(nCurrentDevice)->GetGKISignalIDSize();
	EEnumSize tmpEnumSize	= theConverterManager(nCurrentDevice)->GetEnumerationSize(eTargetDBTypeCom);
	int structAlign			= ((theConverterManager(nCurrentDevice)->GetStructureAlignment(eTargetDBTypeCom)) == eAlignMinimum) ?  sizeof(short) : eAlign4Bytes; 

	if (pIcatMessage->IsFromTarget())
	{
		switch(pIcatMessage->GetDiagSap())
		{
		default:
		case DIAG_MI_LOGGED_SIGNAL:
			m_iSourceTaskIDIndex = 0;	 
			m_iTargetTaskIDIndex = m_taskIDSize;

			m_iFrameNumberIndex = m_iTargetTaskIDIndex + m_taskIDSize;
			if (tmpEnumSize == eEnumSizeAsNeeded && m_taskIDSize == 1)
				m_iFrameNumberIndex += 2;

			m_iFrameTicksIndex = m_iFrameNumberIndex + sizeof(DWORD);

			m_iSignalIDIndex = (m_iFrameTicksIndex + sizeof(DWORD) + sizeof(USHORT));
			m_iSignalLengthIndex = (m_iFrameTicksIndex + sizeof(DWORD));
			ALIGN(m_iSignalIDIndex, m_nSignalIDSize);

			m_iDataIndex = m_iSignalIDIndex + m_nSignalIDSize;
			ALIGN(m_iSignalIDIndex, MAX_ALIGN_STRUCT);

			break;
		case DIAG_MI_SIGNAL:
			m_iSourceTaskIDIndex = 0;
			m_iTargetTaskIDIndex = m_taskIDSize;

			m_iSignalIDIndex = m_iTargetTaskIDIndex + m_taskIDSize;
			ALIGN(m_iSignalIDIndex, structAlign);
			m_iSignalLengthIndex = m_iSignalIDIndex;
			m_iSignalIDIndex += sizeof(USHORT); /*Jump over the Signal-Length*/
			ALIGN(m_iSignalIDIndex, m_nSignalIDSize);

			m_iDataIndex = m_iSignalIDIndex + m_nSignalIDSize;
			ALIGN(m_iSignalIDIndex, MAX_ALIGN_STRUCT);

			break;
		case DIAG_MI_SPECIAL_LOGGED_SIGNAL:
			m_iFrameNumberIndex = 0;
			m_iFrameTicksIndex = m_iFrameNumberIndex + sizeof(DWORD);
			m_iSkipSize = m_iFrameTicksIndex + sizeof(DWORD);

			if((m_iSkipSize > pIcatMessage->GetDataLen()) || (pIcatMessage->GetData(m_iSkipSize) == NULL) || (m_dwSkipSize = *((DWORD *)(pIcatMessage->GetData(m_iSkipSize)))) > pIcatMessage->GetDataLen())  
			{
				m_dwSkipSize = 0;
				m_iSourceTaskIDIndex = 0;
				m_iTargetTaskIDIndex = 0;
				m_iSignalIDIndex = 0;
				m_iDataIndex = 0;
				return;
			}
		
			m_iSourceTaskIDIndex = m_iSkipSize + sizeof(DWORD) + m_dwSkipSize;
			ALIGN(m_iSourceTaskIDIndex, ((tmpEnumSize == eEnumSize4Bytes) ? 4 : 2));
			ALIGN(m_iSourceTaskIDIndex, m_taskIDSize);

			m_iTargetTaskIDIndex = m_iSourceTaskIDIndex + m_taskIDSize;

			m_iSignalIDIndex = m_iTargetTaskIDIndex + m_taskIDSize;
			ALIGN(m_iSignalIDIndex, structAlign);
			m_iSignalLengthIndex = m_iSignalIDIndex;
			m_iSignalIDIndex += sizeof(USHORT); /*Jump over the Signal-Length*/
			ALIGN(m_iSignalIDIndex, m_nSignalIDSize);

			m_iDataIndex = m_iSignalIDIndex + m_nSignalIDSize;
			ALIGN(m_iSignalIDIndex, MAX_ALIGN_STRUCT);

			break;
		}
	}
	else /* command and control message */
	{
		m_iSourceTaskIDIndex = 0;
		m_iTargetTaskIDIndex = m_taskIDSize;

		m_iSignalIDIndex = m_iTargetTaskIDIndex + m_taskIDSize;
		ALIGN(m_iSignalIDIndex, structAlign);
		m_iSignalLengthIndex = m_iSignalIDIndex;
		m_iSignalIDIndex += sizeof(USHORT);/*Jump over the Signal-Length*/
		ALIGN(m_iSignalIDIndex, m_nSignalIDSize);

		m_iDataIndex = m_iSignalIDIndex + m_nSignalIDSize;
		ALIGN(m_iSignalIDIndex, MAX_ALIGN_STRUCT);
	}
}

DWORD CGKIExData::GetFrameNum()
{
	// only when from target
	DWORD dwFrame = 0;
	if (m_iFrameNumberIndex)
	{
		BYTE * pData = m_pIcatMessage->GetData(m_iFrameNumberIndex);
		if (pData == NULL)
			return 0;
		dwFrame = *((DWORD *)pData); 
	}
	return dwFrame;
}


WORD CGKIExData::GetSourceTaskId()
{
	BYTE * pData = m_pIcatMessage->GetData(m_iSourceTaskIDIndex);
	if (pData == NULL)
		return 0; 
	WORD wSourceTaskID;
	if (m_taskIDSize == 1)
		wSourceTaskID = *pData;
	else
		wSourceTaskID = *((WORD *)pData);
	return wSourceTaskID;
}

WORD CGKIExData::GetTargetTaskId()
{
	BYTE * pData = m_pIcatMessage->GetData(m_iTargetTaskIDIndex);
	if (pData == NULL)
		return 0;

	WORD wTargetTaskID;
	if (m_taskIDSize == 1)
		wTargetTaskID = *pData;
	else
		wTargetTaskID = *((WORD *)pData);
	return wTargetTaskID;
}

DWORD CGKIExData::GetSignalId()
{
	DWORD dwSignalID;
	BYTE * pData = (m_pIcatMessage->GetData(m_iSignalIDIndex));
	if (pData == NULL)
		return 0;

	if (m_nSignalIDSize == 2)
		dwSignalID = *((WORD *)pData);
	else
		dwSignalID = *((DWORD *)pData); 
	return dwSignalID;
}

DWORD CGKIExData::GetFrameTicks()
{
	BYTE * pData = m_pIcatMessage->GetData(m_iFrameTicksIndex);
	if (pData == NULL)
		return 0;
	DWORD dwTmp = *((DWORD *)pData);
	return dwTmp;
}

WORD CGKIExData::GetSignalLength()
{
	BYTE * pData = (m_pIcatMessage->GetData(m_iSignalLengthIndex));
	if (pData == NULL)
		return 0;
		
	return *((WORD *)pData);
}

////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

CString strCopyTypes[3] = { _T("NO COPY"), _T("KNOWN"), _T("UNKNOWN") };

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringMessageEx::CStringMessageEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage) : CDiagMessageEx(pMessageReaderEx, pIcatMessage)
{
}

////////////////////////////////////////////////////////////////////////
CDiagMessageEx::CDiagMessageEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage) : m_pIcatMessage(pIcatMessage), m_pMessageReaderEx(pMessageReaderEx),
	m_pMessageConversionData(NULL)
{
	m_strCurrentRawData.Empty();
}

void CDiagMessageEx::SetMessageConversionData(MessageConversionData * pMessageConversionData)
{
	m_pMessageConversionData = pMessageConversionData;
	m_pMessageConversionData->strStruct.Empty();
}

////////////////////////////////////////////////////////////////////////


CDiagMessageDiagEx::CDiagMessageDiagEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage, EnumValsRecord * pRec) : CDiagMessageEx(pMessageReaderEx, pIcatMessage), m_pRec(pRec)
{
}

CDiagMessageISEx::CDiagMessageISEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage) : CDiagMessageEx(pMessageReaderEx, pIcatMessage)
{
}

CDiagMessageGKIEx::CDiagMessageGKIEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage) : CDiagMessageEx(pMessageReaderEx, pIcatMessage), m_pExData(NULL)
{

}

CDiagMessageGKIEx::~CDiagMessageGKIEx()
{
	delete m_pExData;
}


void CDiagMessageGKIEx::SetMessageConversionData( MessageConversionData * pMessageConversionData )
{
	__super::SetMessageConversionData(pMessageConversionData);

	if (IsFromTarget())
	{
		m_pMessageConversionData->dwSourceTaskID = GetSourceTaskId();
		m_pMessageConversionData->dwTargetTaskID = GetTargetTaskId();
	}
}


CDiagMessageDspEx::CDiagMessageDspEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage, EnumValsRecord * pRec) : CDiagMessageDiagEx(pMessageReaderEx, pIcatMessage, pRec)
{
}

CDiagMessageDiagErrorEx::CDiagMessageDiagErrorEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage) : CDiagMessageDiagEx(pMessageReaderEx, pIcatMessage, NULL)
{
}

CdumyMessageEx::CdumyMessageEx(CMessageReaderEx * pMessageReaderEx) : CDiagMessageEx(pMessageReaderEx, NULL)
{
}

CDiagMessageHexEx::CDiagMessageHexEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage ) : CStringMessageEx(pMessageReaderEx, pIcatMessage)
{
}

CErrorMessageEx::CErrorMessageEx(CMessageReaderEx * pMessageReaderEx, CICATMessage * pIcatMessage ) : CStringMessageEx(pMessageReaderEx, pIcatMessage)
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


DWORD CDiagMessageEx::GetAppTS()
{
	if (IsApp())
		return GetTargetTs();
	else
		return 0;
}

DWORD CDiagMessageEx::GetCommTS()
{
	if (!IsApp())
		return GetTargetTs();
	else
		return 0;
}

CGKIExData * CDiagMessageGKIEx::GetGKIExData()
{
	if ( m_pExData == NULL )
	{
		CSingleLock sLock(&m_CritSec, TRUE);
		
		// Double Lock Check !!!!
		if ( m_pExData == NULL )	
			m_pExData = new CGKIExData(m_pIcatMessage);
	}

	return m_pExData;
}


DWORD CDiagMessageGKIEx::GetFrameNum()
{
	if (IsFromTarget())
	{
		if (m_pIcatMessage->GetDiagId() < 2)
			return GetGKIExData()->GetFrameNum();
	}

	return CDiagMessageEx::GetFrameNum();
}


//////////////////

bool CDiagMessageEx::GetTargetTSStr(CString & strtemp)
{
	if (IsFromTarget())
	{
		DWORD dwUE_TimeStamp = GetTargetTs();
		FormatTimeStamp(dwUE_TimeStamp, strtemp);	
		return true;
	}

	strtemp.Empty();
	return false;
}

bool CDiagMessageEx::GetAppTSStr(CString & strtemp)
{
	if (IsApp())
		return GetTargetTSStr(strtemp);

	strtemp.Empty();
	return false;
}

bool CDiagMessageEx::GetCommTSStr(CString & strtemp)
{
	if (!IsApp())
		return GetTargetTSStr(strtemp);

	strtemp.Empty();
	return false;
}

bool CDiagMessageEx::GetChannelStr(CString & strtemp)
{
// 	if (IsFromTarget())
// 	{
// 		strtemp.Format(_T("%d"),m_pIcatMessage->GetChannel());
// 		return true;
// 	}

	strtemp.Empty();
	return false;
}

bool CDiagMessageEx::GetMessageNumberStr(CString & strtemp)
{	
	strtemp.Format(_T("%I64u"), m_pIcatMessage->GetMessageNumber());

	return true;
}

bool CDiagMessageEx::GetDeviceStr(CString & strtemp)
{
	int nDevice = m_pIcatMessage->GetDevice();
	if (nDevice < 0)
		strtemp = _T("N/A");
	else
		strtemp.Format(_T("Device %d"), nDevice);

	return true;
}

bool CDiagMessageEx::GetDataStr(CString & strtemp)
{
	bool bRet;
	if (IsFromTarget())
		bRet = ConvertString(strtemp);
	else
		bRet = ConvertCCString(strtemp);
	if (!bRet)
		strtemp = _T("Error in Data");
	return true;
}

bool CDiagMessageEx::GetFullDiagSapStr(CString & strtemp)
{
// 	if (m_pIcatMessage->GetDiagId() > 1)
// 	{
// 		return GetDiagIdStr(strtemp);
// 	}

	strtemp.Format(_T("%d"),m_pIcatMessage->GetFullDiagSap());
	return true;
}

bool CDiagMessageEx::GetModuleIDStr(CString & strtemp)
{
	WORD module_ID = m_pIcatMessage->GetModuleID(true);
	strtemp.Format(_T("%d"), module_ID);
	return true;
}

bool CDiagMessageEx::GetPCTimeStampStr(CString & strtemp)
{
	const CSystemTime& time = m_pIcatMessage->GetPCTimeStamp();
	strtemp.Format(_T("%2.2u-%2.2u-%2.2u %2.2u:%2.2u:%2.2u.%3.3u"), time.wYear%100, time.wMonth, time.wDay, time.wHour, time.wMinute, 
		time.wSecond, time.wMilliseconds); 
	return true;
}

bool CDiagMessageEx::GetSrcIdStr(CString & strtemp)
{
	int nSrcId = m_pIcatMessage->GetSrcId();
	strtemp.Format(_T("0x%02X"), nSrcId);
	return true;
}

bool CDiagMessageEx::GetDstIdStr(CString & strtemp)
{
	int nDstId = m_pIcatMessage->GetDstId();
	strtemp.Format(_T("0x%02X"), nDstId);
	return true;
}

bool CDiagMessageEx::GetSrcNameStr(CString & strtemp)
{
	int nSrcId = m_pIcatMessage->GetSrcId();
	return GetClientName(nSrcId, strtemp);
}

bool CDiagMessageEx::GetDstNameStr(CString & strtemp)
{
	int nDstId = m_pIcatMessage->GetDstId();
	return GetClientName(nDstId, strtemp);
}

bool CDiagMessageEx::GetDiagIdStr(CString & strtemp)
{
	int nDiagId = m_pIcatMessage->GetDiagId();
	strtemp.Format(_T("DIAG %d"), nDiagId);
	return true;
}

bool CDiagMessageEx::GetMsgTypeStr(CString & strtemp)
{
	if (m_pIcatMessage->GetDiagId() < 2)
	{
		return GetDiagIdStr(strtemp);
	}

	int nMsgType = m_pIcatMessage->GetMsgType();
	strtemp.Format(_T("0x%02X"), nMsgType);
	return true;
}

bool CDiagMessageEx::GetUserRemarkStr( CString & strtemp )
{
	return m_pIcatMessage->GetUserRemark(strtemp);
}

bool CDiagMessageEx::GetDataExLenStr( CString & strtemp )
{
	int dataLength = GetDataExLen();
	strtemp.Format(_T("%d"),dataLength);
	return true;
}

bool CDiagMessageEx::GetDataLenStr( CString & strtemp )
{
	int dataLength = GetDataBufferLen();
	strtemp.Format(_T("%d"),dataLength);
	return true;
}

bool CDiagMessageEx::GetDataHexStr( CString & strtemp )
{
	strtemp.Empty();
	BYTE * pData = GetDataBuffer();
	if (pData == NULL)
		return false;

	FormatData(pData, GetDataBufferLen(), strtemp);
	return true;
}

////////////////////////////////

bool CDiagMessageDiagErrorEx::GetDataStr(CString & strtemp)
{
	//if (IsFromTarget())
	//{
	//	strtemp.Format(_T("Report not found in DB - FileID = %d, MessageID = %d, TimeStamp = %u"), 
	//		(int)m_pIcatMessage->GetModuleID(true), (int)m_pIcatMessage->GetMsgId(), m_pIcatMessage->GetTargetTs());				
	//}
	//else
	//{
	//	strtemp.Format(_T("Command not found in DB - FileID = %d, MessageID = %d"), 
	//		(int)m_pIcatMessage->GetModuleID(true), (int)m_pIcatMessage->GetMsgId());				
	//}
	//return true;

	BYTE* pData = GetDataBuffer();
	if (pData == NULL)
	{
		return false;
	}

	FormatData(pData, GetDataBufferLen(), strtemp);

	return true;
}

bool CDiagMessageDiagErrorEx::GetCat1Str(CString & strtemp)
{
	return CDiagMessageEx::GetCat1Str(strtemp);
}

bool CDiagMessageDiagErrorEx::GetCat2Str(CString & strtemp)
{
	return CDiagMessageEx::GetCat2Str(strtemp);
}

bool CDiagMessageDiagErrorEx::GetCat3Str(CString & strtemp)
{
	return CDiagMessageEx::GetCat3Str(strtemp);
}


bool CDiagMessageDiagEx::GetCat1Str(CString & strtemp)
{
	strtemp = m_pRec->m_Cat1;
	return true;
}

bool CDiagMessageDiagEx::GetCat2Str(CString & strtemp)
{
	strtemp = m_pRec->m_Cat2;
	return true;
}

bool CDiagMessageDiagEx::GetCat3Str(CString & strtemp)
{
	strtemp = m_pRec->m_Cat3;
	return true;
}

bool CDiagMessageDiagEx::GetMsgCtrStr(CString & strtemp)
{
	if (IsFromTarget())
	{
		DWORD diagCounter = m_pIcatMessage->GetMsgCtr();
		strtemp.Format(_T("%d"),diagCounter);
		return true;
	}
	else
	{
		strtemp.Empty(); 
		return false;
	}
}

bool CDiagMessageDiagEx::GetFrameNumStr(CString & strtemp)
{
	if ( (m_pIcatMessage->GetDiagId() == 1 && !m_pIcatMessage->IsApp()) || m_pIcatMessage->GetMsgType() == DM_RX_TRACE_AND_FN)
	{
		DWORD dwTmp = m_pIcatMessage->GetFrameNum();
		if(m_pMessageReaderEx->GetFrameNumberFormat() == FRAME_NUMBER_DATA_PRES_DEC)
			strtemp.Format(_T("%u"), dwTmp);
		else
			strtemp.Format(_T("0x%4.4lx"), dwTmp);
		return true;
	}
	else
	{
		strtemp.Empty(); 
		return false;
	}
}

bool CDiagMessageDiagEx::GetSFNStr(CString & strtemp)
{
	if (IsFromTarget())
	{
		DWORD diagCounter = m_pIcatMessage->GetMsgCtr();
		strtemp.Format(_T("%4.4x"),diagCounter);
		return true;
	}
	else
	{
		strtemp.Empty(); 
		return false;
	}
}

// bool CDiagMessageDiagEx::GetFrame2NumStr(CString & strtemp)
// {
// 	if ( m_pIcatMessage->IsFrame2Exist()) 
// 	{
// 		DWORD dwTmp = m_pIcatMessage->GetFrame2Num();
// 		strtemp.Format(_T("%u"), dwTmp,dwTmp);
// 		return true;
// 	}
// 	else
// 		return CDiagMessageEx::GetFrame2NumStr(strtemp);
// }

bool CDiagMessageDiagEx::GetMsgIdStr(CString & strtemp)
{
	WORD message_ID = m_pIcatMessage->GetMsgId();
	strtemp.Format(_T("%d"), message_ID);
	return true;
}

bool CDiagMessageDiagEx::GetExtraDataStr( CString & strtemp )
{
	int wDiagIndex;
	if (wDiagIndex = m_pIcatMessage->GetExtraData() > 0)
	{
		strtemp.Format(_T("DIAG Counter=%d."), wDiagIndex);
	}

	strtemp.Empty();
	return false;
}


//////////////////////////

bool CDiagMessageGKIEx::GetMsgCtrStr(CString & strtemp)
{
	if (IsFromTarget())
	{
		DWORD diagCounter = m_pIcatMessage->GetMsgCtr();
		strtemp.Format(_T("%d"),diagCounter);
		return true;
	}
	else
		return CDiagMessageEx::GetMsgCtrStr(strtemp);
}

bool CDiagMessageGKIEx::GetFrameNumStr(CString & strtemp)
{
	if (IsFromTarget())
	{
		WORD wDiagSap = m_pIcatMessage->GetDiagSap();
		switch(wDiagSap)
		{
		case DIAG_MI_LOGGED_SIGNAL:
		case DIAG_MI_SPECIAL_LOGGED_SIGNAL:
			{
				DWORD dwTmp = GetFrameNum();
				if(m_pMessageReaderEx->GetFrameNumberFormat() == FRAME_NUMBER_DATA_PRES_DEC)
					strtemp.Format(_T("%u"), dwTmp);
				else
					strtemp.Format(_T("0x%4.4lx"), dwTmp);
				return true;
			}
			
		}
	}

	return CDiagMessageEx::GetFrameNumStr(strtemp);
}

bool CDiagMessageGKIEx::GetSFNStr(CString & strtemp)
{
	if (IsFromTarget())
	{
		DWORD diagCounter = m_pIcatMessage->GetMsgCtr();
		strtemp.Format(_T("%4.4x"),diagCounter);
		return true;
	}
	else
	{
		strtemp.Empty(); 
		return false;
	}
}

bool CDiagMessageGKIEx::GetFrameTicksStr(CString & strtemp)
{
	if (IsFromTarget())
	{
		WORD wDiagSap = m_pIcatMessage->GetDiagSap();
		switch(wDiagSap)
		{
		case DIAG_MI_LOGGED_SIGNAL:
		case DIAG_MI_SPECIAL_LOGGED_SIGNAL:
			{
				DWORD dwTmp = GetFrameTicks();
				strtemp.Format(_T("%lu"), dwTmp);
				return true;
			}
		}
	}
	
	return CDiagMessageEx::GetFrameTicksStr(strtemp);
}

bool CDiagMessageGKIEx::GetSignalGroupStr(CString & strtemp)
{
	CString strSignalName, strSignalGroup;
	DWORD signalID = GetSignalId();
	if ( theConverterManager(m_pIcatMessage->GetDevice())->LookupSignal(signalID, strSignalName, strSignalGroup) )
	{
		strtemp = strSignalGroup;
	}
	else
	{
		strtemp = "Unknown Signal";
	}
	return true;
}

bool CDiagMessageGKIEx::GetSourceTaskIdStr(CString & strtemp, BOOL bWithID /*TRUE*/)
{
	WORD wSourceTaskID = GetSourceTaskId();
	
	BOOL bLookupGKITaskID = theConverterManager(m_pIcatMessage->GetDevice())->LookupGKITaskID(wSourceTaskID, strtemp);
	
	if ( !bLookupGKITaskID )
		strtemp.Format(_T("Unrecognized TaskID - %d"), wSourceTaskID);
	else if (bWithID)
	{
		CString strNum;
		strNum.Format(_T(" [%d]"), wSourceTaskID);
		strtemp += strNum;
	}
	return true;
}

bool CDiagMessageGKIEx::GetTargetTaskIdStr(CString & strtemp, BOOL bWithID /*TRUE*/)
{
	WORD wTargetTaskID = GetTargetTaskId();

	BOOL bLookupGKITaskID = theConverterManager(m_pIcatMessage->GetDevice())->LookupGKITaskID(wTargetTaskID, strtemp);
	
	if ( !bLookupGKITaskID )
		strtemp.Format(_T("Unrecognized TaskID - %d"), wTargetTaskID);
	else if (bWithID)
	{
		CString strNum;
		strNum.Format(_T(" [%d]"), wTargetTaskID);
		strtemp += strNum;
	}
	return true;
}

////////////////////////////

LPBYTE	CDiagMessageDspEx::GetDataEx(UINT nIdx)
{
	return GetData(nIdx + 4);
}

WORD	CDiagMessageDspEx::GetDataExLen()
{
	return GetDataLen() - 4;
}

BYTE CDiagMessageDspEx::GetCopyType()
{
	if (GetDataLen() <= 7)
		return 0;
	return *(GetData(7));
}

BYTE * CDiagMessageDspEx::GetDataPacket()
{
	return GetData(4 + (GetDspDataLen() * 2));
}

WORD CDiagMessageDspEx::GetDataPacketLen()
{
	 return (GetDataLen() - (4 + (GetDspDataLen() * 2)));
}

WORD CDiagMessageDspEx::GetDspOpCode()
{
	WORD* pW = ((WORD*)(GetData(0)));
	if (pW == NULL)
		return 0;
	return (*pW) & 0x03FF;	// Mask bits 10-15.
}

WORD CDiagMessageDspEx::GetEntireDspOpCode()
{
	WORD* pW = ((WORD*)(GetData(0)));
	if (pW == NULL)
		return 0;
	return (*pW) & 0xE3FF;	// Mask bits 10-12 as they are being used as counter.
}

WORD CDiagMessageDspEx::GetDspDataLen()
{
	WORD * pW = ((WORD *)(GetData(2)));
	if (pW == NULL)
		return 0;
	return *pW;
}

WORD CDiagMessageDspEx::GetDspSetId()
{
	WORD vSetID = (GetDspOpCode() & 0x03C0) >> 6;
	return vSetID;
}

WORD CDiagMessageDspEx::GetDspSubOpCode()
{
	WORD wSubOpcode = GetDspOpCode() & 0x003F;
	return wSubOpcode;
}

bool CDiagMessageDspEx::GetCopyTypeStr(CString & strtemp)
{
	if (IsFromTarget())
		return CDiagMessageEx::GetCopyTypeStr(strtemp);

	unsigned int nType = GetCopyType();
	if (nType < 3)
		strtemp = strCopyTypes[nType];
	else
		strtemp.Empty();
	return true;
}

bool CDiagMessageDspEx::GetDataPacketStr(CString & strtemp)
{
	if (IsFromTarget())
		return CDiagMessageEx::GetCopyTypeStr(strtemp);

	WORD extLen = GetDspDataLen();
	FormatData(GetData(4) + (extLen * 2), GetDataLen() - (4 + (extLen * 2)), strtemp);
	return true;
}

bool CDiagMessageDspEx::GetDspOpCodeStr(CString & strtemp)
{
	WORD opCode = GetEntireDspOpCode();
	WORD extLen = GetDspDataLen();
	
	strtemp.Format(_T("0x%4.4x [Len = %d]"), opCode, extLen);
	return true;
}

bool CDiagMessageDspEx::GetDspSetIdStr(CString & strtemp)
{
	WORD wSetID		= GetDspSetId();
	WORD wSubOpcode	= GetDspSubOpCode();
	
	CDSPRecord rec;
	WORD wKey = (wSetID << 8) | wSubOpcode;
	
	bool bCommand;
	if (IsFromTarget())
		bCommand = ( m_pRec->m_Cat1 == _T("HAL") && m_pRec->m_Cat2 == _T("IPC") && m_pRec->m_Cat3 == _T("IPC_SEND") );
	else
		bCommand = ((m_pRec->m_bIsExtCommand) == TRUE);


	if ( bCommand )
		theConverterManager(m_pIcatMessage->GetDevice())->LookupDSPCommand(wKey, rec);
	else
		theConverterManager(m_pIcatMessage->GetDevice())->LookupDSPReport(wKey, rec);
	
	strtemp.Format(_T("%s [0x%X]"), rec[0], wSetID);
	return true;
}

bool CDiagMessageDspEx::GetDspSubOpCodeStr(CString & strtemp)
{
	WORD extLen = GetDspDataLen();
	
	WORD wSetID		= GetDspSetId();
	WORD wSubOpcode	= GetDspSubOpCode();
	
	CDSPRecord rec;
	WORD wKey = (wSetID << 8) | wSubOpcode;
	
	bool bCommand;
	if (IsFromTarget())
		bCommand = ( m_pRec->m_Cat1 == _T("HAL") && m_pRec->m_Cat2 == _T("IPC") && m_pRec->m_Cat3 == _T("IPC_SEND") );
	else
		bCommand = ((m_pRec->m_bIsExtCommand) == TRUE);
	
	
	if ( bCommand )
		theConverterManager(m_pIcatMessage->GetDevice())->LookupDSPCommand(wKey, rec);
	else
		theConverterManager(m_pIcatMessage->GetDevice())->LookupDSPReport(wKey, rec);
	
	strtemp.Format(_T("%s [0x%X] [Len = %d]"), rec[1], wSubOpcode, extLen);
	return true;
}

bool CDiagMessageDspEx::IsDSPReport()
{
	return (m_pRec->m_bIsExtReport == TRUE);
}

bool CDiagMessageDspEx::IsPLPMsg()
{
	return m_pRec->m_bIsPLP;
}

////////////////////////////

bool CDiagMessageISEx::GetServiceStr(CString & strtemp)
{
	BYTE bServiceID = GetService();
	strtemp.Format(_T("%d"), bServiceID);
	return true;
}
////////////////////////////////////////////////////////////////////////////////
//	CMessageReaderEx
////////////////////////////////////////////////////////////////////////////////

CMessageReaderEx::CMessageReaderEx()
{
	InitParams();
	m_pDiagMessageEx = new CdumyMessageEx(this);
}

CMessageReaderEx::CMessageReaderEx(MessageConversionData * pMessageConversionData)
{
	InitParams();
	SetMessage(pMessageConversionData);
}

CMessageReaderEx::CMessageReaderEx(CICATMessage* pMessage)
{
	InitParams();
	SetMessage(pMessage);
}

void CMessageReaderEx::InitParams()
{
	m_pMessage = NULL;
	m_pDiagMessageEx = NULL;
	m_dwPrevAppTimeStamp = 0; 
	m_dwPrevCommTimeStamp = 0;
	m_bIsOffline = FALSE;

	m_TimeStampFormat = TIME_STAMP_FORMAT_TICKS; 
	m_TimeStampTextFormat = TIME_STAMP_TEXT_FORMAT_MINUTES;
	m_RawFormat = RAW_DATA_FORMAT_BYTE; 
	m_RawPres = RAW_DATA_PRES_HEX;
	m_StructPres = STRUCT_PRES_NAME; 
	m_bLeadingZeros = TRUE;
	m_RawMessagePresentation = RAW_MESSAGE_PRES_ASCII;
	m_bFrameNumberFormatDec = FRAME_NUMBER_DATA_PRES_DEC;
	m_bIsHexDisplayMode = false;
}

void CMessageReaderEx::InitParamsFromIni()
{
	CXmlConfig *pAppXML = AppXml();

	m_RawFormat					= pAppXML->GetAttributeInt(_T("LogViewer\\DataFormat\\RawDataFor"), RAW_DATA_FORMAT_BYTE);
	m_RawPres					= pAppXML->GetAttributeInt(_T("LogViewer\\DataFormat\\RawDataPresentation"), RAW_DATA_PRES_HEX);
	m_TimeStampFormat			= pAppXML->GetAttributeInt(_T("LogViewer\\DataFormat\\TimeStampFormat"), TIME_STAMP_FORMAT_WHITESAIL_SLOW);
	m_RawMessagePresentation	= pAppXML->GetAttributeInt(_T("LogViewer\\DataFormat\\RawMsgPresentation"), RAW_MESSAGE_PRES_ASCII);
	m_StructPres				= pAppXML->GetAttributeInt(_T("LogViewer\\DataFormat\\StrucruePresentaion"), STRUCT_PRES_NAME);
	m_bLeadingZeros				= pAppXML->GetAttributeBool(_T("LogViewer\\DataFormat\\LeadingZeros"), true);
	m_TimeStampTextFormat		= pAppXML->GetAttributeInt(_T("LogViewer\\DataFormat\\TimeStampTxtFormat"), TIME_STAMP_TEXT_FORMAT_MINUTES);
}

void CMessageReaderEx::SetMessage(CICATMessage* pMessage)
{
	m_pMessage = pMessage;

	//first we initialize pMessage
	m_pMessage->CreateDiagMsg();
	
	if (m_pDiagMessageEx)
	{
		delete m_pDiagMessageEx;
		m_pDiagMessageEx = NULL;
	}

	if (m_bIsHexDisplayMode)
	{
		m_pDiagMessageEx = new CDiagMessageHexEx(this, pMessage);
		return;
	}

	if (pMessage->m_Error != kNoError)
	{
		m_pDiagMessageEx = new CErrorMessageEx(this, pMessage);
		return;
	}

	switch (GetDiagMessageType())
	{
	case DIAG_MESSAGE_DIAG:
		{
			EnumValsRecord * pRec;
			if (IsFromTarget())
				pRec= theConverterManager(m_pMessage->GetDevice())->GetReportRecord(GetModuleID(), GetMsgId(), m_pMessage->IsApp());
			else
				pRec= theConverterManager(m_pMessage->GetDevice())->GetCommandRecord(GetModuleID(), GetMsgId(), m_pMessage->IsApp());

			if (!pRec)
				m_pDiagMessageEx = new CDiagMessageDiagErrorEx(this, pMessage);
			else
			{
				if (pRec->m_bIsExtCommand || pRec->m_bIsExtReport)
					m_pDiagMessageEx = new CDiagMessageDspEx(this, pMessage, pRec);
				else
					m_pDiagMessageEx = new CDiagMessageDiagEx(this, pMessage, pRec);
			}
		}
		break;
	case DIAG_MESSAGE_IS:
		m_pDiagMessageEx = new CDiagMessageISEx(this, pMessage);
		break;
	case DIAG_MESSAGE_GKI:
		m_pDiagMessageEx = new CDiagMessageGKIEx(this, pMessage);
		break;
	case DIAG_MESSAGE_STRING:
		m_pDiagMessageEx = new CStringMessageEx(this, pMessage);
		break;
	default:
		m_pDiagMessageEx = new CdumyMessageEx(this);

	}
}
void CMessageReaderEx::SetMessage(MessageConversionData * pMessageConversionData)
{
	SetMessage(pMessageConversionData->pMessage);
	m_pDiagMessageEx->SetMessageConversionData(pMessageConversionData);
	m_bIsOffline = pMessageConversionData->bIsOffline;
}

CMessageReaderEx::~CMessageReaderEx()
{
	if (m_pDiagMessageEx)
		delete m_pDiagMessageEx;
}

/////////////////////////////////////////////////////


DWORD	CMessageReaderEx::GetDifTargetTS()
{
	DWORD dwUE_TimeStamp = GetTargetTs();
	
	if (IsApp())
	{
		dwUE_TimeStamp -= m_dwPrevAppTimeStamp;
		m_dwPrevAppTimeStamp += dwUE_TimeStamp;
	}
	else
	{
		dwUE_TimeStamp -= m_dwPrevCommTimeStamp;
		m_dwPrevCommTimeStamp += dwUE_TimeStamp;
	}
#if 0
	return dwUE_TimeStamp;
#else
	return abs((int) dwUE_TimeStamp);
#endif
}

DWORD	CMessageReaderEx::GetAppTS()
{
	return m_pDiagMessageEx->GetAppTS();
}

DWORD	CMessageReaderEx::GetCommTS()
{
	return m_pDiagMessageEx->GetCommTS();
}

DWORD	CMessageReaderEx::GetDifAppTS()
{
	if (IsApp())
		return GetDifTargetTS();
	else
		return 0;
}

DWORD	CMessageReaderEx::GetDifCommTS()
{
	if (!IsApp())
		return GetDifTargetTS();
	else
		return 0;
}

/////////////////////

BYTE	CMessageReaderEx::GetCopyType()
{
	return m_pDiagMessageEx->GetCopyType();
}

BYTE	* CMessageReaderEx::GetDataPacket()
{
	return m_pDiagMessageEx->GetDataPacket();
}

WORD	CMessageReaderEx::GetDataPacketLen()
{
	return m_pDiagMessageEx->GetDataPacketLen();
}

WORD	CMessageReaderEx::GetDspOpCode()
{
	return m_pDiagMessageEx->GetDspOpCode();
}

WORD CMessageReaderEx::GetEntireDspOpCode()
{
	return m_pDiagMessageEx->GetEntireDspOpCode();
}

WORD	CMessageReaderEx::GetDspDataLen()
{
	return m_pDiagMessageEx->GetDspDataLen();
}

WORD	CMessageReaderEx::GetDspSetId()
{
	return m_pDiagMessageEx->GetDspSetId();
}

WORD	CMessageReaderEx::GetDspSubOpCode()
{
	return m_pDiagMessageEx->GetDspSubOpCode();
}
///////////////////////////////////

LPBYTE CMessageReaderEx::GetDataEx(UINT nIdx)
{
	return m_pDiagMessageEx->GetDataEx(nIdx);	
}

WORD CMessageReaderEx::GetDataExLen()
{
	return m_pDiagMessageEx->GetDataExLen();	
}

DWORD CMessageReaderEx::GetFrameNum()
{
	return m_pDiagMessageEx->GetFrameNum();	
}

DWORD CMessageReaderEx::GetFrame2Num()
{
	return m_pDiagMessageEx->GetFrame2Num();	
}

DWORD CMessageReaderEx::GetFrameTicks()
{
	return m_pDiagMessageEx->GetFrameTicks();	
}

WORD CMessageReaderEx::GetSourceTaskId()
{
	return m_pDiagMessageEx->GetSourceTaskId();	
}

WORD CMessageReaderEx::GetTargetTaskId()
{
	return m_pDiagMessageEx->GetTargetTaskId();	
}

DWORD CMessageReaderEx::GetSignalId()
{
	return m_pDiagMessageEx->GetSignalId();	
}

WORD CMessageReaderEx::GetSignalLength()
{
	return m_pDiagMessageEx->GetSignalLength();	
}
///////////////////////////////////

bool CMessageReaderEx::GetTargetTSStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetTargetTSStr(strtemp);
}

bool CMessageReaderEx::GetDifTargetTSStr(CString & strtemp)
{
	if (IsFromTarget())
	{
		DWORD dwUE_TimeStamp = GetDifTargetTS();
		m_pDiagMessageEx->FormatTimeStamp(dwUE_TimeStamp, strtemp);
		return true;
	}
	strtemp.Empty();
	return false;
}

bool CMessageReaderEx::GetAppTSStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetAppTSStr(strtemp);
}

bool CMessageReaderEx::GetCommTSStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetCommTSStr(strtemp);
}

bool CMessageReaderEx::GetDifAppTSStr(CString & strtemp)
{
	if (IsApp())
		return GetDifTargetTSStr(strtemp);

	strtemp.Empty();
	return false;
}

bool CMessageReaderEx::GetDifCommTSStr(CString & strtemp)
{
	if (!IsApp())
		return GetDifTargetTSStr(strtemp);

	strtemp.Empty();
	return false;
}

bool CMessageReaderEx::GetCat1Str(CString & strtemp)
{
	return m_pDiagMessageEx->GetCat1Str(strtemp);
}

bool CMessageReaderEx::GetCat2Str(CString & strtemp)
{
	return m_pDiagMessageEx->GetCat2Str(strtemp);
}

bool CMessageReaderEx::GetCat3Str(CString & strtemp)
{
	return m_pDiagMessageEx->GetCat3Str(strtemp);
}

bool CMessageReaderEx::GetCat123Str(CString & strtemp, bool bAddClientName/*=false*/)
{
	CString cat1,cat2,cat3;
	bool ret = m_pDiagMessageEx->GetCat1Str(cat1) && m_pDiagMessageEx->GetCat2Str(cat2) && m_pDiagMessageEx->GetCat3Str(cat3);

	if ( bAddClientName )
	{
		CDiagMessageEx::GetClientName(GetClientID(), strtemp);
		strtemp += "__";
	}

	strtemp += cat1+"__"+cat2+"__"+cat3; 

	return ret;
}

bool CMessageReaderEx::GetChannelStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetChannelStr(strtemp);
}

bool CMessageReaderEx::GetMessageNumberStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetMessageNumberStr(strtemp);
}

bool CMessageReaderEx::GetDeviceStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetDeviceStr(strtemp);
}

bool CMessageReaderEx::GetCopyTypeStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetCopyTypeStr(strtemp);
}

bool CMessageReaderEx::GetDataStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetDataStr(strtemp);
}

bool CMessageReaderEx::GetDataPacketStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetDataPacketStr(strtemp);
}

bool CMessageReaderEx::GetMsgCtrStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetMsgCtrStr(strtemp);
}

bool CMessageReaderEx::GetFullDiagSapStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetFullDiagSapStr(strtemp);
}

bool CMessageReaderEx::GetDspOpCodeStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetDspOpCodeStr(strtemp);
}

bool CMessageReaderEx::GetFrameNumStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetFrameNumStr(strtemp);
}

bool CMessageReaderEx::GetSFNStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetSFNStr(strtemp);
}

// bool CMessageReaderEx::GetFrame2NumStr(CString & strtemp)
// {
// 	return m_pDiagMessageEx->GetFrame2NumStr(strtemp);
// }

bool CMessageReaderEx::GetFrameTicksStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetFrameTicksStr(strtemp);
}

bool CMessageReaderEx::GetMsgIdStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetMsgIdStr(strtemp);
}

bool CMessageReaderEx::GetModuleIDStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetModuleIDStr(strtemp);
}

bool CMessageReaderEx::GetPCTimeStampStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetPCTimeStampStr(strtemp);
}

bool CMessageReaderEx::GetServiceStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetServiceStr(strtemp);
}

bool CMessageReaderEx::GetDspSetIdStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetDspSetIdStr(strtemp);
}

bool CMessageReaderEx::GetSignalGroupStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetSignalGroupStr(strtemp);
}

bool CMessageReaderEx::GetSourceTaskIdStr(CString & strtemp, BOOL bWithID /*TRUE*/)
{
	return m_pDiagMessageEx->GetSourceTaskIdStr(strtemp, bWithID);
}

bool CMessageReaderEx::GetTargetTaskIdStr(CString & strtemp, BOOL bWithID /*TRUE*/)
{
	return m_pDiagMessageEx->GetTargetTaskIdStr(strtemp, bWithID);
}

bool CMessageReaderEx::GetDspSubOpCodeStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetDspSubOpCodeStr(strtemp);
}

bool CMessageReaderEx::GetUserDataStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetUserDataStr(strtemp);
}

bool CMessageReaderEx::GetUserRemarkStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetUserRemarkStr(strtemp);
}

bool CMessageReaderEx::GetSrcIdStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetSrcIdStr(strtemp);
}

bool CMessageReaderEx::GetDstIdStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetDstIdStr(strtemp);
}

bool CMessageReaderEx::GetSrcNameStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetSrcNameStr(strtemp);
}

bool CMessageReaderEx::GetDstNameStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetDstNameStr(strtemp);
}

bool CMessageReaderEx::GetDiagIdStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetDiagIdStr(strtemp);
}

bool CMessageReaderEx::GetMsgTypeStr(CString & strtemp)
{
	return m_pDiagMessageEx->GetMsgTypeStr(strtemp);
}

bool CMessageReaderEx::IsMessageTypeDSP()
{
	return m_pDiagMessageEx->IsMessageTypeDSP();
}

bool CMessageReaderEx::IsDSPReport()
{
	return m_pDiagMessageEx->IsDSPReport();
}

bool CMessageReaderEx::IsPLPMsg()
{
	return m_pDiagMessageEx->IsPLPMsg();
}


void CMessageReaderEx::FormatData( BYTE *pData, int len, CString &retStr )
{
	m_pDiagMessageEx->FormatData(pData,len,retStr);
}

void CMessageReaderEx::GetCurrentRawData(CString &str)
{
	m_pDiagMessageEx->GetCurrentRawData(str);
}

bool CMessageReaderEx::GetExtraDataStr( CString & str )
{
	return m_pDiagMessageEx->GetExtraDataStr(str);
}

bool CMessageReaderEx::GetDataExLenStr( CString & str )
{
	return m_pDiagMessageEx->GetDataExLenStr(str);
}

bool CMessageReaderEx::GetDataLenStr( CString & str )
{
	return m_pDiagMessageEx->GetDataLenStr(str);
}

bool CMessageReaderEx::GetDataHexStr( CString & str )
{
	return m_pDiagMessageEx->GetDataHexStr(str);
}

///////////////////////////////////////////////

CHeaderBuilderEx::CHeaderBuilderEx(int nType) : CHeaderBuilder(nType), m_nType(nType)
{
}

CHeaderBuilderEx::~CHeaderBuilderEx()
{
}

int CHeaderBuilderEx::BuildTargetHeader( LPBYTE pData, int nBufLen, stDiagHeaderParams & param )
{
	int size = CHeaderBuilder::BuildTargetHeader(pData, nBufLen, param);

	switch (m_nType)
	{
	case DIAG_MESSAGE_DIAG:
		break;
	case DIAG_MESSAGE_IS:
		break;
	case DIAG_MESSAGE_GKI:
		if (param.bExGKI)
		{
			if ((size + 16) > nBufLen)
				return 0;

			int nCurrentDevice = CCommInterface::Instance()->GetAliveDiagDeviceID();

			int taskIDSize			= theConverterManager(nCurrentDevice)->GetGKITaskIDSize();
			int nSignalIDSize		= theConverterManager(nCurrentDevice)->GetGKISignalIDSize();
			EEnumSize tmpEnumSize	= theConverterManager(nCurrentDevice)->GetEnumerationSize(0);
			//int structAlign			= (theConverterManager(nCurrentDevice)->GetStructureAlignment() == eAlignMinimum) ?  sizeof(short) : eAlign4Bytes; 

			*((WORD*)(pData + size)) = param.SourceTaskId;
			size += taskIDSize;
			*((WORD*)(pData + size)) = param.TargetTaskId;
			size += taskIDSize;

			if (tmpEnumSize == eEnumSizeAsNeeded && taskIDSize == 1)
				size += 2;

			*((DWORD*)(pData + size)) = param.nFrame;
			size += sizeof(DWORD);
			*((DWORD*)(pData + size)) = param.FrameTicks;
			size += sizeof(DWORD);
			size += sizeof(USHORT);
			ALIGN(size, nSignalIDSize);

			*((DWORD*)(pData + size)) = param.SignalId;
			size += nSignalIDSize;
		}

		break;
	}
	return size;
}

