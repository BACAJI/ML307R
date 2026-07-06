// DiagMessage.cpp: implementation of the CDiagMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiagMessage.h"
#include "ICATMessage.h"
#include "..\CATCore\Converter\CommandAndMessageStructures.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ALIGN(counter, align) ((counter) += ((UINT)(counter) % (align)) ? ((align)-(((UINT)(counter)) % (align))) : 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiagMessage::CDiagMessage() : m_pData(NULL), m_pMessage(NULL), m_bFromTarget(false), m_bApp(false), m_bFrame2Exist(false)
{
}

CDiagMessage::~CDiagMessage()
{
}

CStringMessage::CStringMessage()
{
}

CStringMessage::~CStringMessage()
{
}

CDiag1Message::CDiag1Message()
{
}

CDiag1Message::~CDiag1Message()
{
}

CDiag1MessageDiag::CDiag1MessageDiag()
{
}

CDiag1MessageDiag::~CDiag1MessageDiag()
{
}

CDiag1MessageIS::CDiag1MessageIS()
{
}

CDiag1MessageIS::~CDiag1MessageIS()
{
}

CDiag1MessageGKI::CDiag1MessageGKI()
{
}

CDiag1MessageGKI::~CDiag1MessageGKI()
{
	
}

CDumyMessage::CDumyMessage()
{
}

CDumyMessage::~CDumyMessage()
{
}

const CSystemTime&	CDumyMessage::GetPCTimeStamp()
{
	static CSystemTime temp;
	return temp;
}


////////////////////////////////////////////////////////////////////////

CStringMessage::CStringMessage(CICATMessage* pMessage) : CDiagMessage(pMessage)
{
}

////////////////////////////////////////////////////////////////////////
CDiagMessage::CDiagMessage(CICATMessage* pMessage) : m_pMessage(pMessage), m_bFrame2Exist(false)
{
	m_pData = m_pMessage->m_pData;
	m_DataLen = (WORD)m_pMessage->m_DataLen;
	m_bFromTarget = (m_pMessage->m_ModuleID == 1); // MODULE_COMMUNICATION
}

////////////////////////////////////////////////////////////////////////


CDiag1Message::CDiag1Message(CICATMessage* pMessage) : CDiagMessage(pMessage)
{
	if (m_bFromTarget)
	{
		m_bApp = ( ((WORD*)m_pData)[diag1From_SAP] & APP_SIDE_MASK_FOR_RECEIVING) > 0;
		m_bFrame2Exist =  ( ((WORD*)m_pData)[diag1From_SAP] & SECOND_FRAME_MASK) > 0;
	}
	else
	{
		m_bApp = (m_pData[diag1To_SAP] & APP_SIDE_MASK_FOR_SENDING) > 0;
	}
}

CDiag1MessageDiag::CDiag1MessageDiag(CICATMessage* pMessage) : CDiag1Message(pMessage)
{
}

CDiag1MessageIS::CDiag1MessageIS(CICATMessage* pMessage) : CDiag1Message(pMessage)
{
}

CDiag1MessageGKI::CDiag1MessageGKI(CICATMessage* pMessage) : CDiag1Message(pMessage)
{
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

int CDiag1MessageDiag::BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination /*=0*/, bool bFixup /*=false*/)
{
	pData[0] = 
		  (nDestination > 0) ? COMMAND_SERVER | APP_SIDE_MASK_FOR_SENDING
		: (bFixup)			 ? FIXUPS_COMMAND_SERVER
		:					   COMMAND_SERVER;
	pData[1] = 0;
	memcpy(&pData[2], &nModule, sizeof(USHORT));
	memcpy(&pData[4], &nId, sizeof(DWORD));
	memset(&pData[8], 0, sizeof(DWORD));

	return 12;
}


int CDiag1MessageIS::BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination /*=0*/, bool bFixup /*=false*/)
{
	pData[0] = 
		(nDestination > 0) ? INTERNAL_SERVICE | APP_SIDE_MASK_FOR_SENDING
		:					 INTERNAL_SERVICE;
	pData[1] = nId;
	USHORT moduleID = 0xFFFF;
	memcpy(&pData[2], &moduleID, sizeof(USHORT));
	DWORD commandID = 0;
	memcpy(&pData[4], &commandID, sizeof(DWORD));
	memset(&pData[8], 0, sizeof(DWORD));

	return 12;
}

int CDiag1MessageGKI::BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination /*=0*/, bool bFixup /*=false*/)
{
	pData[0] = 
		(nDestination > 0) ? DIAG_MI_SIGNAL | APP_SIDE_MASK_FOR_SENDING
		:				     DIAG_MI_SIGNAL;
	pData[1] = 0;
	memset(&pData[2], 0, sizeof(USHORT));
	memset(&pData[4], 0, sizeof(DWORD));
	memset(&pData[8], 0, sizeof(DWORD));

	return 12;
}

int CDiag1MessageDiag::BuildTargetHeader(LPBYTE pData, int nBufLen, stDiagHeaderParams & param )
{
	if (12 > nBufLen)
		return 0;

	WORD wSap = APPLICATION_REPORT;
	if (param.nSource > 0)
		wSap |= APP_SIDE_MASK_FOR_RECEIVING;
	if (param.bFrame2)
	{
		wSap |= SECOND_FRAME_MASK;

		wSap |= (param.nFrame2 & 0x00FF) << 4;
	}

	*((WORD*)(&(pData[0]))) = wSap;

	if (param.bFrame)
	{
		memcpy(&pData[2], &param.nFrame, sizeof(USHORT));			// frame
		if (param.bFrame2)
		{
			pData[4] = (param.nFrame2 >> 8) & 0x0FF;
			pData[5] = ((param.nFrame2 >> 16) << 4) + (param.nFrame >> 16);
		}
		else
		{
			pData[5] = (param.nFrame >> 16);
			pData[4] = param.nModulId;
		}
	}
	else
	{
		memcpy(&pData[2], &param.nMsgCount, sizeof(USHORT));	//diag count
		if (param.bFrame2)
		{
			pData[4] = (param.nFrame2 >> 8) & 0x0FF;
			pData[5] = ((param.nFrame2 >> 16) << 4);
		}
		else
			memcpy(&pData[4], &param.nModulId, sizeof(USHORT));	//Module Id
	}

	memcpy(&pData[6], &param.nId, sizeof(WORD));			//Message Id
	memset(&pData[8], param.TimeStamp, sizeof(DWORD));		//Time Stamp

	return 12;
}


int CDiag1MessageIS::BuildTargetHeader(LPBYTE pData, int nBufLen, stDiagHeaderParams & param )
{
	if (12 > nBufLen)
		return 0;

	*((WORD*)(&(pData[0]))) = 
		(param.nSource > 0) ? RETURN_SERVICE | APP_SIDE_MASK_FOR_RECEIVING
		:					 RETURN_SERVICE;

	memcpy(&pData[6], &param.nId, sizeof(USHORT));	// service
	pData[2] = 0;
	pData[3] = 0;
	pData[4] = 0xFF;
	pData[5] = 0;
	memset(&pData[8], param.TimeStamp, sizeof(DWORD));	//Time Stamp

	return 12;
}

int CDiag1MessageGKI::BuildTargetHeader(LPBYTE pData, int nBufLen, stDiagHeaderParams & param )
{
	if (8 > nBufLen)
		return 0;

	*((WORD*)(&(pData[0]))) = 
		(param.nSource > 0) ? DIAG_MI_LOGGED_SIGNAL | APP_SIDE_MASK_FOR_RECEIVING
		:				     DIAG_MI_LOGGED_SIGNAL;

	memset(&pData[2], 0, sizeof(USHORT));
	memset(&pData[4], param.TimeStamp, sizeof(DWORD));		//Time Stamp


	return 8;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

LPBYTE	CDiagMessage::GetDataBuffer()
{
	return m_pData;
}

WORD	CDiagMessage::GetDataBufferLen()
{
	return m_DataLen;
}

LPBYTE CDiagMessage::GetData(UINT nIdx)
{
	int index = GetHeaderLen() + nIdx;
	if (index >= m_DataLen)
		return NULL;
	return (LPBYTE)&m_pData[index];
}

WORD CDiagMessage::GetDataLen()
{
	return (m_DataLen > GetHeaderLen()) ? (m_DataLen - GetHeaderLen()) : 0;
}

bool CDiagMessage::IsValidMessage()
{
	return ((m_pMessage->m_Error == kNoError) && (m_pData != NULL) && (GetHeaderLen() <= m_pMessage->m_DataLen));
}

WORD CDiagMessage::GetFullDiagSap()
{
	WORD wSap = GetDiagSap();

	if (m_bApp)
	{
		if (m_bFromTarget)
			wSap |= APP_SIDE_MASK_FOR_RECEIVING;
		else
			wSap |= APP_SIDE_MASK_FOR_SENDING;
	}
	return wSap;
}

int CDiagMessage::GetDevice()
{
	if (m_bFromTarget)
	{
		return m_pMessage->m_InstanceID;
	}
	else
	{
		if ( m_pMessage->m_Direction == CICATMessage::MessageIN /*||  m_pMessage->m_Direction == CICATMessage::MessageOUT_ALL */)
			return -1;

		//As to command message, its direction was initialized with value of "MessageOUT_ALL" 
		//Parsing this type message with ConverterManager(0).
		if (m_pMessage->m_Direction == CICATMessage::MessageOUT 
		||  m_pMessage->m_Direction == CICATMessage::MessageOUT_ALL )
		{
			return 0;
		}
		

		int direction = (int)m_pMessage->m_Direction;
		direction >>= 1;

		int index = 0;
		while ( direction && !(direction & 1) )
		{
			direction >>= 1;
			index++;
		}
		return index;

	}
}

UINT64 CDiagMessage::GetMessageNumber()
{
	return m_pMessage->m_MessageNumber;
}

const CSystemTime&	CDiagMessage::GetPCTimeStamp()
{
	return m_pMessage->m_Time;
}

bool CDiagMessage::IsPrintMessage()
{
	return (m_pMessage->m_ModuleID != 1 && m_pMessage->m_ModuleID != 3) || (GetDevice() == -1);
}

bool CDiagMessage::GetUserRemark( CString &UserRemark )
{
	UserRemark.Empty();
	return !UserRemark.IsEmpty();
}

////////////////////////////////////////////////////////
/*
bool CDiag1Message::IsValidMessage()
{
	return (CDiagMessage::IsValidMessage() && GetHeaderLen() >= PDU_HEADER_LEN);
}
*/
BYTE CDiag1Message::GetDiagSap()
{
	return (m_pData[diag1To_SAP] & 0x0F);
}

BYTE CDiag1Message::GetModuleID(bool bFromData/*= false*/)
{
// 	if ((!bFromData) || (IsFrame2Exist()))
// 	{
// 		return GetClientID();
// 	}
// 	else
	{	
		if (m_bFromTarget)
			return m_pData[diag1From_moduleID];
		else
			return m_pData[diag1To_moduleID];
	}
}


BYTE CDiag1Message::GetMsgType()
{
	BYTE	Type = 0xFF;

	if (m_bFromTarget)
	{
		switch (GetDiagSap())
		{
		case APPLICATION_REPORT:
		case APPLICATION_REPORT_ALIGNED:
				Type = 0x80;
				break;
		case RETURN_SERVICE:
				Type = GetService();
				break;
		case DIAG_MI_LOGGED_SIGNAL:
		case DIAG_MI_SPECIAL_LOGGED_SIGNAL:
				Type = 0x82;
				break;
		}
	}
	else
	{
		switch(GetDiagSap())
		{
		case INTERNAL_SERVICE:
			Type = GetService();
			break;
		case COMMAND_SERVER:
		case FIXUPS_COMMAND_SERVER:
			Type = 0x30;
			break;
		case DIAG_MI_SIGNAL:
			Type = 0x31;
			break;
		}
	}

	return Type;	
}

BYTE CDiag1Message::GetHeaderLen_DW()
{
	return PDU_HEADER_LEN / sizeof(DWORD);	
}

BYTE CDiag1Message::GetChannel()
{
	return 0;	
}

BYTE CDiag1Message::GetSrcId()
{
	if (m_bFromTarget)
	{
		if (m_bApp)
			return diag_entity_App;
		else		   
			return diag_entity_Comm;
	}
	else
		return diag_entity_Acat;
}

BYTE CDiag1Message::GetDstId()
{
	if (m_bFromTarget)
		return diag_entity_Acat;
	else
	{
		if (m_bApp)
			return diag_entity_App;
		else
			return diag_entity_Comm;
	}
}

DWORD CDiag1Message::GetTargetTs()
{
	if (m_bFromTarget)
		return *(LPDWORD)&m_pData[diag1From_TimeStamp];
	else
		return 0;
}

WORD CDiag1Message::GetMsgId()
{
	if (m_bFromTarget)
		return *(LPWORD)&m_pData[diag1From_commandID];
	else
		return *(LPWORD)&m_pData[diag1To_commandID];
}

WORD CDiag1Message::GetMsgCtr()
{
	WORD wCounter = 0;
	if (m_bFromTarget)
	{
		wCounter = *((WORD *)(&m_pData[diag1From_MsgCount]));				
	}
	return wCounter;
}

DWORD CDiag1Message::GetFrameNum()
{
	DWORD dwFrame = 0;
	if (m_bFromTarget)
	{
		dwFrame = MAKELONG(*((WORD *)(&m_pData[diag1From_Frame])), (m_pData[diag1From_FrameHigh] & 0x0F) );				
	}
	return dwFrame;
}


WORD CDiag1Message::GetHeaderLen()
{
	return (m_DataLen >= PDU_HEADER_LEN) ? PDU_HEADER_LEN : m_DataLen;	
}

BYTE CDiag1Message::GetClientID()
{
	if (IsApp())
		return 1;
	else
		return 0;
}

WORD CDiag1Message::GetExtraData()
{
	WORD wDiagIndex = 0;
	if (!IsFromTarget() || !m_pMessage->m_pData || m_pMessage->m_DataLen < 4)
	{
		return wDiagIndex;
	}

	BYTE bFlag = *((BYTE*)(&m_pMessage->m_pData[m_pMessage->m_DataLen - 1]));

	if (bFlag == 0x9D)
	{
		BYTE bExType = *((BYTE*)(&m_pMessage->m_pData[m_pMessage->m_DataLen - 2]));
		//Diag Index
		if ( bExType == 0x55)
		{
			wDiagIndex =  *((WORD *)(&m_pMessage->m_pData[m_pMessage->m_DataLen - 4]));
		}
	}

	return wDiagIndex;
}

DWORD CDiag1MessageGKI::GetTargetTs()
{
	if (m_bFromTarget)
		return *(LPDWORD)&m_pData[diag1GKIFrom_TimeStamp];
	else
		return 0;
}

bool CDiag1MessageDiag::IsAligned()
{
	return (m_bFromTarget && (GetDiagSap() == APPLICATION_REPORT_ALIGNED));
}

WORD CDiag1MessageDiag::GetDspOpCode()
{
	WORD* pW = ((WORD*)(GetData(0)));
	if (pW == NULL)
		return 0;
	return (*pW) & 0x03FF;	// Mask bits 10-15.
}

DWORD CDiag1MessageDiag::GetFrame2Num()
{
	DWORD dwFrame = 0;
	if (m_bFromTarget && m_bFrame2Exist)
	{
		dwFrame = (((*((WORD *)(&m_pData[0]))) >> 4) & 0x00FF) +
					((DWORD)m_pData[4] << 8) +
					(((DWORD)(m_pData[5] & 0xF0)) << 12);
	}
	return dwFrame;
}

WORD CDiag1MessageDiag::GetEntireDspOpCode()
{
	WORD* pW = ((WORD*)(GetData(0)));
	if (pW == NULL)
		return 0;
	return (*pW) & 0xE3FF;	// Mask bits 10-12 as they are being used as counter.
}


WORD CDiag1MessageGKI::GetHeaderLen()
{
	if (m_bFromTarget)
		return (2 * sizeof(DWORD));
	else
		return CDiag1Message::GetHeaderLen();
}

BYTE CDiag1MessageIS::GetService()
{
	if (m_bFromTarget)
		return m_pData[diag1From_serviceID];
	else
		return m_pData[diag1To_serviceID];
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

CHeaderBuilder::CHeaderBuilder( int nType) : m_pDiagMessage(NULL)
{
	switch (nType)
	{
	case DIAG_MESSAGE_DIAG:
		m_pDiagMessage = new CDiag1MessageDiag;
		break;
	case DIAG_MESSAGE_IS:
		m_pDiagMessage = new CDiag1MessageIS;
		break;
	case DIAG_MESSAGE_GKI:
		m_pDiagMessage = new CDiag1MessageGKI;
		break;
	}
}

CHeaderBuilder::~CHeaderBuilder()
{
	if (m_pDiagMessage)
		delete m_pDiagMessage;
}

int CHeaderBuilder::BuildHeader(LPBYTE pData, int nBufLen, int nId, int nModule, DWORD dwDBVersion, int nDestination /*=0*/, bool bFixup /*=false*/)
{
	return m_pDiagMessage->BuildHeader(pData,nBufLen, nId, nModule, dwDBVersion, nDestination, bFixup);
}

int CHeaderBuilder::BuildTargetHeader( LPBYTE pData, int nBufLen, stDiagHeaderParams & param )
{
	return m_pDiagMessage->BuildTargetHeader(pData, nBufLen, param);
}

////////////////////////////////////////////////////////////////////////

CDiagMessage* CTmpDiagMessage::CreateDiagMsg()
{
	return (CDiagMessage*)m_pMessage->CreateDiagMsg();
}

CTmpDiagMessage::CTmpDiagMessage( CICATMessage* pMessage )//Chaim - Don't call it's parent because it isn't initialized 
{
	m_pMessage = pMessage;
}

LPBYTE CTmpDiagMessage::GetDataBuffer()
{
	return m_pMessage->m_pData;
}

WORD CTmpDiagMessage::GetDataBufferLen()
{
	return m_pMessage->m_DataLen;
}

//////////////////////////////////////////////////////////////////////////