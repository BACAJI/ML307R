
#ifndef __ATCOMMANDSIGNALS_H__
#define __ATCOMMANDSIGNALS_H__


#define VGMUX_CHANNEL_COMMAND_1		0
#define VGMUX_CHANNEL_COMMAND_2		1
#define VGMUX_CHANNEL_COMMAND_3		2
#define VGMUX_CHANNEL_COMMAND_4		3
#define VGMUX_CHANNEL_UNSOLISITED	4
#define VGMUX_CHANNEL_GSM_DATA		5
#define VGMUX_CHANNEL_GPRS_DATA		6
#define VGMUX_CHANNEL_INVALID		7


//#define MAX_AT_COMMANDS_LENGTH	128
//#define MAX_AT_SEND_COMMANDS_LENGTH		200
#define MAX_AT_SEND_COMMANDS_LENGTH		   2000   //Modify by ZQQ to support MEP Command
#define MAX_AT_COMMANDS_LENGTH	           2000

struct VgmuxAtDataInd
{
	BYTE channelNumber;	// enum VgmuxChannelNumber
	BYTE length;
	BYTE/*TCHAR*/ data[MAX_AT_SEND_COMMANDS_LENGTH]; // unsigned ?
};

#ifndef _VGMUX_AT_DATA_REQ_
#define _VGMUX_AT_DATA_REQ_
struct VgmuxAtDataReq
{
	BYTE channelNumber;	// enum VgmuxChannelNumber
	BYTE length;
	BYTE/*TCHAR*/ data[MAX_AT_COMMANDS_LENGTH]; // unsigned ?	
};
#endif

#define RECEIVE_AT_COMMAND_SIGNAL_NAME	_T("vgmuxAtDataReq")
#define SEND_AT_COMMAND_SIGNAL_NAME		_T("vgmuxAtDataInd")

#define AT_COMMAND_SOURCE_TASK	_T("PASS_THRU_TASK_ID")
#define AT_COMMAND_TARGET_TASK	_T("VG_CI_TASK_ID")


#endif //__ATCOMMANDSIGNALS_H__