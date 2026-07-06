/*------------------------------------------------------------------------------------------*
 |(C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved				|
 *------------------------------------------------------------------------------------------*/


/******************************************************
*                         ErrorCodes.h
*
* Project : APTController                 Ver : 1.0
* Programmer : Maya Shtern        Date : 03/10/2003
* Language : VC 6.0                Target : Win32
* Purpose :	Error codes definitions
*****************************************************/

#define	ERROR_CODE											 int

#ifndef __APTCONTROLLERAPIFUNCTIONS_H__
#define __APTCONTROLLERAPIFUNCTIONS_H__


#define	SUCCESS_											   0
#define	INVALID_DEVICE_VALUE_								-100
#define	INVALID_DEVICE_NAME_								-101
#define DEVICE_WAS_NOT_CONFIGURED							-102
#define DEVICE_CONFIGURATION_DONT_MATCH_PURPOSE				-103

#define	INVALID_DATABASE_									-200
#define	MODULE_TYPE_NOT_FOUND_								-201
#define	ERROR_IN_TB_SIMULATION_STATION_COMMANDS_CONVERTER_	-202
#define	ERROR_IN_TB_AT_COMMANDS_							-203
#define	ERROR_IN_TB_DIAG_COMMANDS_CONVERTER_				-204
#define	ERROR_IN_TB_DIAG_MESSAGES_CAPTURING_				-205
#define	ERROR_IN_TB_DIAG_MESSAGES_HANDLING_					-206
#define	ERROR_IN_TB_DIAG_RESPONSE_AUTOMATA_					-207
#define	ERROR_IN_TB_DLL_SCRIPTS_COMMANDS_					-208
#define	ERROR_IN_TB_DLL_SCRIPTS_PARAMETERS_CONFIGURATION_	-209
#define	ERROR_IN_TB_MODULE_TYPE_							-210
#define	ERROR_IN_TB_SIM_SIMULATOR_COMMANDS_					-211
#define	ERROR_IN_TB_TESTQUEST_SCRIPS_						-212

#define INVALID_TIMER_APPLICATION_TYPE_						-300
#define INVALID_TIMER_APPLICATION_PATH_						-301
#define INVALID_TIMER_DLL_EXPORTED_FUNCTION_				-302
#define INVALID_TIMER_TIMEOUT_DURATION_						-303

#define	INVALID_XDEV_CONFIGURATION_							-400
#define IDENTICAL_SEQUENTIAL_AND_PARALLEL_CONFIGURATIONS_	-401

#define APT_CONTROLLER_ACTIVATED_							1
#define APT_CONTROLLER_DISABLED_							0

#endif //__APTCONTROLLERAPIFUNCTIONS_H__