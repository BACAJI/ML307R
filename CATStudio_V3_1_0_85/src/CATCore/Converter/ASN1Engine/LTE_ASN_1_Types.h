#pragma once

typedef enum
{
	NON_LTE_MSG_TYPE = -1,
	ERRDEBUGAIRINTERFACETXIND_MSG_TYPE,
	ERRDEBUGAIRINTERFACERXIND_MSG_TYPE,
	EMMDEBUGAIRINTERFACETXIND_MSG_TYPE,
	EMMDEBUGAIRINTERFACERXIND_MSG_TYPE
}eLTEMsgtype;

typedef enum
{
	LTE_NAS_Type_MMDOWNLINK,
	LTE_NAS_Type_MMUPLINK,
	LTE_NAS_Type_SMDOWNLINK,
	LTE_NAS_Type_SMUPLINK,
	LTE_NAS_Type_SS2UE,
	LTE_NAS_Type_UE2SS
}eLTE_NAS_Type;

#define ERR_MAX_AIR_INTERFACE_DEBUG_OCTETS 512
#define EMM_MAX_AIR_INTERFACE_DEBUG_OCTETS 256

/** Describes the Logical Channel Type.
*/
typedef enum EutraLogicalChannelTypeTag
{
	EUTRA_BCCH = 0,	/**< BCCH Logical Channel */
	EUTRA_PCCH,		/**< PCCH Logical Channel */
	EUTRA_CCCH,		/**< CCCH Logical Channel */
	EUTRA_DCCH,		/**< DCCH Logical Channel */
	EUTRA_DTCH, 	/**< DTCH Logical Channel */
	EUTRA_MAX_LOGICAL_CHANNEL_TYPES
}
EutraLogicalChannelTypeEnum;
typedef UINT8 EutraLogicalChannelType;

typedef enum EutraRlcModeTag
{
	EUTRA_RLC_TM = 0,	/**< RLC transparent mode (TM) */
	EUTRA_RLC_UM,		/**< RLC unacknowledged mode (UM) */
	EUTRA_RLC_AM,		/**< RLC acknowledged mode (AM) */
}
EutraRlcModeEnum;
typedef UINT8 EutraRlcMode;

typedef enum EutraSrbIdTag
{
	EUTRA_SRB_0 = 0,	/**< SRB 0 (SRB ID starts at 0) */
	EUTRA_SRB_1,		/**< SRB 1 */
	EUTRA_SRB_2			/**< SRB 2 */
} EutraSrbIdEnum;
typedef UINT8 EutraSrbId;

typedef unsigned long Earfcn;
typedef UINT16  /* 0 to 503 */ EPhysCellId_t;


/**
 * Debug Signal send from ERRC to log Tx Air Interface signal.
 * The Signal is send encoded and should be decoded by the PC tool.
 */
typedef struct ErrDebugAirInterfaceTxIndTag
{
	EutraLogicalChannelType              logicalChannelType;        /**< logical channel type for Tx message */
	EutraRlcMode                         rlcMode;              /**< rlc mode for Tx message */
	EutraSrbId                           srbId;                    /**< srb Id for Tx message */
	Earfcn                               dlEarfcn;             /**< Earfcn for Tx message */    
	EPhysCellId_t                        pci;                       /**< pci for Tx message */
	short                                dataLength;        /**< encoded data length in bytes */
	BYTE                                 data [ERR_MAX_AIR_INTERFACE_DEBUG_OCTETS];        /**< encoded data */
	/* Do NOT add fields here! data field must be last! */
}
ErrDebugAirInterfaceTxInd;

/**
 * Debug Signal send from ERRC to log Rx Air Interface signal.
 * The Signal is send encoded and should be decoded by the PC tool.
 */
typedef struct ErrDebugAirInterfaceRxIndTag
{
	EutraSrbId              srbId;		/**< srb Id for Rx message */
	EutraLogicalChannelType	logicalChannelType;	/**< logical channel type for Rx message */	
	EutraRlcMode			rlcMode;	/**< rlc mode for Rx message */	
	
	Earfcn					dlEarfcn;	/**< Earfcn for Rx message */	
	EPhysCellId_t				pci;			/**< pci for Rx message */
	
	short					dataLength;	/**< encoded data length in bytes */
	BYTE					data [ERR_MAX_AIR_INTERFACE_DEBUG_OCTETS];/**< encoded data */
}
ErrDebugAirInterfaceRxInd;

/**
* Debug Signal send from EMM to log TX Air Interface signal.
* The Signal is sent encoded and is decoded by the Pas-thru task.
*/
typedef struct EmmDebugAirInterfaceTxIndTag
{
	short dataLength;        /**< encoded data length in bytes */
	char  data [EMM_MAX_AIR_INTERFACE_DEBUG_OCTETS];    /**< encoded data */
}
EmmDebugAirInterfaceTxInd;

/**
* Debug Signal send from EMM to log RX Air Interface signal.
* The Signal is sent encoded and is decoded by the Pas-thru task.
*/
typedef struct EmmDebugAirInterfaceRxIndTag
{
	short dataLength;        /**< encoded data length in bytes */
	char  data [EMM_MAX_AIR_INTERFACE_DEBUG_OCTETS];/**< encoded data */
}
EmmDebugAirInterfaceRxInd;

