// ASN1Wrapper.h: wrapping definitions for the CASN1Engine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ASN1WRAPPER_H)
#define ASN1WRAPPER_H

#include <afxtempl.h>
#include "MrvlCommon/SingletonDestroyer.h"

#include "LTE_ASN_1_Types.h"

typedef enum 
{
    AM_RLC_MODE = 0,
    UM_RLC_MODE = 1,
    TM_RLC_MODE = 2,
	RLC_MODE_INVALID = 0xFF
}
DlRlcMode;


typedef enum 
{
	/* CCCH */
    RBID_CCCH = 0,  

	/* DCCH */
    RBID_DCCH1 = 1,  

    /* DCCH */
    RBID_DCCH2 = 2,  
    
	/* DCCH */
    RBID_DCCH3 = 3,  

    /* DCCH */
    RBID_DCCH4 = 4,  

    RBID_MCCH = 5,

    /* BCCH */
    RBID_BCCH = 33,

	/* PCCH */
    RBID_PCCH = 34,
    
    RBID_NUM_BEARERS  = 36,

    /* RB_INVALID is used by MAC to indicate a transport block whose CRC was
     * ok, but couldn't be parsed
     */
    RBID_INVALID      = 0xFF
}RadioBearer,
RadioBearerId;

#ifndef _TRAFFICDIRECTION_
#define _TRAFFICDIRECTION_
typedef enum 
{
	NEUTRAL = 0,
	DOWNLINK = 1,
	UPLINK = 2
}
TrafficDirection;
#endif

typedef enum 
{
    TC_BCH = 0,
    TC_PCH = 1,
    TC_FACH = 2,
    TC_DCH = 3,
    TC_DSCH = 4,
    TC_RACH = 5,
	TC_INVALID = 0xFF
}
TransportChannel;


#define ASN1_WRAPPER	(CASN1Wrapper::Instance())


typedef enum UrrSirSibTypeExtExt2{
	SIB_TypeExt_systemInfoType11bis = 0,
	SIB_TypeExt_systemInfoType15bis = 1,
	SIB_TypeExt_systemInfoType15_1bis = 2,
	SIB_TypeExt_systemInfoType15_2bis = 3,
	SIB_TypeExt_systemInfoType15_3bis = 4,
	SIB_TypeExt_systemInfoType15_6 = 5,
	SIB_TypeExt_systemInfoType15_7 = 6,
	SIB_TypeExt_systemInfoType15_8 = 7,
	SIB_TypeExt2_systemInfoType19 = 8,
	SIB_TypeExt2_systemInfoType15_2ter = 9,
	SIB_TypeExt2_systemInfoType20 = 10,
	SIB_TypeExt2_spare5 = 11,
	SIB_TypeExt2_spare4 = 12,
	SIB_TypeExt2_spare3 = 13,
	SIB_TypeExt2_spare2 = 14,
	SIB_TypeExt2_spare1 = 15
}UrrSirSibTypeExtExt2;


class CASN1Wrapper
{
public:
	static CASN1Wrapper *Instance();

	BOOL	GetRlcModeName (DlRlcMode rlcMode, CString& strRlc);
	BOOL	GetRadioBearerName (RadioBearerId rb, CString& strRb);
	BOOL	GetTrafficDirectionName (TrafficDirection direction, CString& strDirection);
	BOOL	GetTransportChannelName (TransportChannel trCh, CString& strTrCh);

private:
	CASN1Wrapper ();
	virtual ~CASN1Wrapper ();

	void LoadRlcModeNameMap ();
	void LoadRadoiBearerNameMap ();
	void LoadTrafficDirectionNameMap ();
	void LoadTransportChannelNameMap ();

	static CASN1Wrapper *m_pThis;
	static CSingletonDestroyer<CASN1Wrapper> m_Destroyer;
	friend class CSingletonDestroyer<CASN1Wrapper>;

#ifdef UNICODE
	CMap<DlRlcMode, DlRlcMode, CString, LPCWSTR> m_RlcModeMap;
	CMap<RadioBearerId, RadioBearerId, CString, LPCWSTR> m_RadioBearerMap;
	CMap<TrafficDirection, TrafficDirection, CString, LPCWSTR> m_TrafficDirectionMap;
	CMap<TransportChannel, TransportChannel, CString, LPCWSTR> m_TransportChannelMap;
#else
	CMap<DlRlcMode, DlRlcMode, CString, LPCSTR> m_RlcModeMap;
	CMap<RadioBearerId, RadioBearerId, CString, LPCSTR> m_RadioBearerMap;
	CMap<TrafficDirection, TrafficDirection, CString, LPCSTR> m_TrafficDirectionMap;
	CMap<TransportChannel, TransportChannel, CString, LPCSTR> m_TransportChannelMap;
#endif
	
};

#endif