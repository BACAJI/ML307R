#ifndef _CSN1MSGNAMEANDSTRUCT_H_
#define _CSN1MSGNAMEANDSTRUCT_H_


typedef enum
{
	STYPE_RR,
	STYPE_RR_PLEN,
	STYPE_RR_SPD,
	STYPE_RR_RR_SPD,
	STYPE_RR_RR_SPD_PLEN,
	STYPE_RR_L3,
	STYPE_RLC_MAC,
	STYPE_L3,
	STYPE_RR_CHNL_REQ,

	STYPE_INVALIDE
}SignalsType_Enum;

typedef enum
{
	DIR_UL,
	DIR_DL,

	DIR_INVALIDE
}SignalsDirection_Enum;

typedef struct CCSN1MsgDetails 
{
	CString m_strSignalName;
	SignalsType_Enum m_enmSignalType;
	SignalsDirection_Enum m_enmSignalDir;
	CString m_strParamPath;
	CString m_strLengthPath;

	CCSN1MsgDetails()
	{
		m_enmSignalType = STYPE_INVALIDE;
		m_enmSignalDir  = DIR_INVALIDE;
		m_strLengthPath = "";
	};

}CCSN1MsgDetails;

#endif //_CSN1MSGNAMEANDSTRUCT_H_