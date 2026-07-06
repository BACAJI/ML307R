
/*--------------------------------------------------------------------------------------*
| (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved		|
*--------------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////
/////generalDefs.h  - includes the necessary includes for the tests/
////////////////////////////////////////////////////////////////////



//////////////////////
/////include files////
//////////////////////
#ifndef  _GENERALDEFS 
#define  _GENERALDEFS
#include <Afxmt.h>
#include <afxtempl.h>
#include <math.h>
#include "..\..\..\APTController\APTControllerManager.h"
#include "..\..\FlashExplorer\FdiFile.h"
#include "..\Viewer.h"
#include "..\ViewerManager.h"
#include "..\..\Logger\LoggerManager.h"
#include "..\..\Converter\DBUtils.h"
#include "XmlConfig.h"
#include "ConfigFile.h"
#include "..\TestEngine.h"
#include "..\..\FlashExplorer\FlashExplorerData.h"
#include "..\..\Converter\ConverterManager.h"
#include "..\..\BasicComponents\StructureDefine.h"
#include "..\..\BasicComponents\ThreadLocalDataInterface.h"
#include "..\..\CommandAndControl\CommandAndControl.h"
#include "..\..\CommManager\CommunicationManager.h"
#include "..\..\..\MrvlCommon\CommInterface.h"

#define FULL_APPS_PATH(S) (AppPath().Left(AppPath().Find(_T("\\Exec"))) + _T("\\") + (S))
#define TLS_pTestEngine (((TestInterface *)CThreadLocalDataInterface::GetData())->m_pTestEngine)

#define AppCat123ToID                   APCat123ToID
// CCommandAndControl theCommandAndControl;
#define theCommandAndControl	TLS_pTestEngine->m_CommandAndControl
// 
#define ICAT_CmdAndCtrlInstance			theCommandAndControl.CmdAndCtrlInstance
#define ICAT_DeleteCmdAndCtrlInstance	theCommandAndControl.DeleteCmdAndCtrlInstance

#define ICAT_SendCommand				theCommandAndControl.SendCommand
#define ICAT_WaitForMessage				theCommandAndControl.WaitForMessage
#define ICAT_SendAndWait				theCommandAndControl.SendAndWait
//#define ICAT_SendAndWaitFrm				theCommandAndControl.SendAndWaitFrm
#define ICAT_SendExtCommand				theCommandAndControl.SendExtCommand
#define ICAT_WaitForExtMessage			theCommandAndControl.WaitForExtMessage
#define ICAT_SendExtAndWait				theCommandAndControl.SendExtAndWait
#define ICAT_SendAndWaitExt				theCommandAndControl.SendAndExtWait
#define ICAT_SendExtAndWaitExt			theCommandAndControl.SendExtAndWaitExt
#define ICAT_GetErrorMessage			theCommandAndControl.GetErrorMessage

#define ICAT_SendInternalServiceCommand			theCommandAndControl.SendInternalServiceCommand
#define ICAT_WaitForInternalServiceCommand		theCommandAndControl.WaitForInternalServiceCommand
#define ICAT_WaitForReturnService				ICAT_WaitForInternalServiceCommand
#define ICAT_SendInternalServiceCommandAndWait	theCommandAndControl.SendInternalServiceCommandAndWait
#define ICAT_SendInternalAndWaitReturn			ICAT_SendInternalServiceCommandAndWait

#define ICAT_SendIPCCommand				theCommandAndControl.SendIPCCommand
#define ICAT_SendIPCAndWait				theCommandAndControl.SendIPCAndWait
#define ICAT_SendIPCAndWaitExt			theCommandAndControl.SendIPCAndWaitExt
#define ICAT_SendIPCAndWaitMultipleExt	theCommandAndControl.SendIPCAndWaitMultipleExt

#define ICAT_SendATCommand			theCommandAndControl.SendATCommand
#define ICAT_WaitForATMessage		theCommandAndControl.WaitForATMessage
#define ICAT_SendATAndWait			theCommandAndControl.SendATAndWait

#define ICAT_SendGKISignal					theCommandAndControl.SendGKISignal
#define ICAT_WaitForGKISignal				theCommandAndControl.WaitForGKISignal
#define ICAT_SendGKICommand					theCommandAndControl.SendGKICommand
#define ICAT_SendGKISignalAndWaitGKISignal	theCommandAndControl.SendGKISignalAndWaitGKISignal
#define ICAT_SendGKICommandAndWaitGKISignal	theCommandAndControl.SendGKICommandAndWaitGKISignal
#define ICAT_GetGKITaskID					theCommandAndControl.GetGKITaskID


#define ICAT_WaitForMultipleMessage			theCommandAndControl.WaitForMultipleMessage
#define	ICAT_SendAndWaitMultiple			theCommandAndControl.SendAndWaitMultiple
#define	ICAT_WaitForMultipleExtMessage		theCommandAndControl.WaitForMultipleExtMessage
#define	ICAT_SendExtAndWaitMultipleExt		theCommandAndControl.SendExtAndWaitMultipleExt
#define	ICAT_WaitForMultipleATMessage		theCommandAndControl.WaitForMultipleATMessage
#define	ICAT_SendATAndWaitMultiple			theCommandAndControl.SendATAndWaitMultiple
#define	ICAT_WaitForSeveralATMessage		theCommandAndControl.WaitForSeveralATMessage
#define	ICAT_SendATAndWaitSeveral			theCommandAndControl.SendATAndWaitSeveral

#define ICAT_GetMessage				theCommandAndControl.GetCat123Message
#define ICAT_GetExtMessage			theCommandAndControl.GetExtMessage
#define ICAT_GetNextMessage			theCommandAndControl.GetNextMessage
#define ICAT_GetNextExtMessage		theCommandAndControl.GetNextExtMessage
#define ICAT_GetPrevMessage			theCommandAndControl.GetPrevMessage
#define ICAT_GetPreviousMessage		theCommandAndControl.GetPrevMessage
#define ICAT_GetPrevExtMessage		theCommandAndControl.GetPrevExtMessage
#define ICAT_GetGKISignal			theCommandAndControl.GetGKISignal
#define ICAT_GetNextGKISignal		theCommandAndControl.GetNextGKISignal
#define ICAT_GetPrevGKISignal		theCommandAndControl.GetPrevGKISignal
#define ICAT_DeleteMessage			theCommandAndControl.DeleteMessage
#define ICAT_ClearMessageFIFO		theCommandAndControl.ClearMessageFIFO
#define ICAT_StartFIFO				theCommandAndControl.StartFIFO
#define ICAT_StopFIFO				theCommandAndControl.StopFIFO
#define ICAT_SetFifoSize				theCommandAndControl.SetFifoSize
#define ICAT_RemoveMessagesFromFIFO		theCommandAndControl.RemoveMessagesFromFIFO
#define ICAT_RemoveExtMessagesFromFIFO	theCommandAndControl.RemoveExtMessagesFromFIFO
#define ICAT_RemoveGKISignalsFromFIFO	theCommandAndControl.RemoveGKISignalsFromFIFO
#define ICAT_ClearFIFOExcludingMessages	theCommandAndControl.ClearFIFOExcludingMessages
#define ICAT_ClearFIFOExcludingExtMessages	theCommandAndControl.ClearFIFOExcludingExtMessages
#define ICAT_ClearFIFOExcludingGKISignals	theCommandAndControl.ClearFIFOExcludingGKISignals


#define ICAT_GetATMessage				theCommandAndControl.GetATMessage
#define ICAT_GetNextATMessage			theCommandAndControl.GetNextATMessage
#define ICAT_GetPrevATMessage			theCommandAndControl.GetPrevATMessage

#define ICAT_GetEnumStrings				theCommandAndControl.GetEnumStrings
#define ICAT_GetEnumString				theCommandAndControl.GetEnumStrings
#define ICAT_GetAppEnumStrings			theCommandAndControl.GetAppEnumStrings
#define ICAT_GetAppEnumString			theCommandAndControl.GetAppEnumStrings
#define ICAT_ReportLineToEnumStrings	theCommandAndControl.ReportLineToEnumStrings
#define ICAT_AppReportLineToEnumStrings theCommandAndControl.AppReportLineToEnumStrings

#define ICAT_GoToEndOfFIFO				theCommandAndControl.GoToEndOfFIFO
#define ICAT_GoToBeginningOfFIFO		theCommandAndControl.GoToBeginningOfFIFO

#define ICAT_ShowIMEIOnTarget			theCommandAndControl.ShowIMEIOnTarget
#define ICAT_GetIMEIOnDevice			theCommandAndControl.GetIMEIOnDevice
#define ICAT_GetIMEI					theCommandAndControl.GetIMEI

#define ICAT_SendBoardTrackerInformation	theCommandAndControl.SendBoardTrackerInformation


#define ICAT_SetATCommandsMode			theCommandAndControl.SetATCommandsMode
#define ICAT_SetATCommandsOverDiag		theCommandAndControl.SetATCommandsOverDiag

#define SendICATMessage					TLS_pTestEngine->SaveAndSendMessage

#define ICAT_SendHugeCommand			theCommandAndControl.SendHugeCommand

#define ICAT_SetTraceFilter				theCommandAndControl.SetTraceFilter
#define ICAT_GetTraceFilter				theCommandAndControl.GetTraceFilter
#define ICAT_SetSignalFilter			theCommandAndControl.SetSignalFilter
#define ICAT_GetSignalFilter			theCommandAndControl.GetSignalFilter


extern CConfigFile				IniFile;


//void SendToLog(CString str, BOOL toFile = FALSE);

void InitializeParams(TestInterface *ti);
void UpdateIniFile();
UINT GetIntervalTime(SYSTEMTIME &first, SYSTEMTIME &second);


#define ICAT_AddNewViewer(s)					CViewerManager::Instance()->AddScriptViewer((s), TLS_pTestEngine)
#define ICAT_AddNewViewerInOfflineMode(s)		CViewerManager::Instance()->AddScriptViewer((s), TRUE, TLS_pTestEngine)
#define ICAT_CloseViewer						CViewerManager::Instance()->CloseScriptViewer
#define ICAT_SetDIAGMessageColor				CViewerManager::Instance()->SetDIAGMessageColor
#define ICAT_SetGKIMessageColor					CViewerManager::Instance()->SetGKIMessageColor
#define ICAT_SetDSPMessageColor					CViewerManager::Instance()->SetDSPMessageColor

#define ICAT_AddNewLogger						CLoggerManager::Instance()->AddNewLogger
#define ICAT_AddScriptLogger(fn, tr, st, pa)	CLoggerManager::Instance()->AddScriptLogger((fn), (tr), (st), (pa), TLS_pTestEngine)
#define ICAT_CloseLogger						CLoggerManager::Instance()->CloseLogger
#define ICAT_OpenNewLog							CLoggerManager::Instance()->OpenNewLog
#define ICAT_ExportLogFile						CLoggerManager::Instance()->ExportLogFile

#define ICAT_OpenDbTable		CDbViewerManager::Instance()->OpenDbTable


/////////////////////////////////////////////////////////////////////////

#define ICAT_GetScriptParameter					TLS_pTestEngine->GetScriptParameter
#define ICAT_SetScriptParameter					TLS_pTestEngine->SetScriptParameter
#define ICAT_GetBatchParameter					TLS_pTestEngine->GetBatchParameter
#define ICAT_SetBatchParameter					TLS_pTestEngine->SetBatchParameter
#define ICAT_GetEnvironmentParameter			TLS_pTestEngine->GetEnvironmentParameter
#define ICAT_SetEnvironmentParameter			TLS_pTestEngine->SetEnvironmentParameter
#define ICAT_GetMinStandard						TLS_pTestEngine->GetMinStandard
#define ICAT_SetScriptFailureReason				TLS_pTestEngine->SetScriptFailureReason
#define ICAT_GetScriptFailureReason				TLS_pTestEngine->GetScriptFailureReason
#define ICAT_SaveSubScriptResult				TLS_pTestEngine->SaveSubScriptResult
#define ICAT_SetSubScriptResultParameter		TLS_pTestEngine->SetSubScriptResultParameter
#define ICAT_CheckSubScriptResult				TLS_pTestEngine->CheckSubScriptResult
#define ICAT_GetPrimaryViSession				TLS_pTestEngine->GetPrimaryViSession
#define ICAT_GetSecondaryViSession				TLS_pTestEngine->GetSecondaryViSession
#define ICAT_GetDeviceAttenuation				TLS_pTestEngine->GetDeviceAttenuation
#define ICAT_SetDeviceAttenuation				TLS_pTestEngine->SetDeviceAttenuation
#define ICAT_GetUserInput						TLS_pTestEngine->GetUserInput
#define ICAT_PromptFileName						TLS_pTestEngine->PromptFileName
#define ICAT_GetCurrentHWConfig					TLS_pTestEngine->GetCurrentHWConfig
#define ICAT_GetXDEVConfigDevices				TLS_pTestEngine->GetXDEVConfigDevices
#define ICAT_GetXDEVConfigurationDeviceGroup	TLS_pTestEngine->GetXDEVConfigurationDeviceGroup
#define ICAT_XDEVImportDevOrCfg					TLS_pTestEngine->XDEVImportDevOrCfg
#define ICAT_GetCurrentScriptIteration			TLS_pTestEngine->GetCurrentScriptIteration
#define ICAT_IsLastScriptAndIterInBatch			TLS_pTestEngine->IsLastScriptAndIterInBatch
#define ICAT_GetCurrentScriptIndex				TLS_pTestEngine->GetCurrentScriptIndex
#define ICAT_GetCurrentBatchIteration			TLS_pTestEngine->GetCurrentBatchIteration
#define ICAT_GetTotalCurrentScriptIterations	TLS_pTestEngine->GetTotalCurrentScriptIterations
#define ICAT_GetTotalBatchIterations			TLS_pTestEngine->GetNumOfBatchIterations
#define ICAT_GetTestEngineWnd					TLS_pTestEngine->GetTestEngineWnd
#define ICAT_SetScriptParameterConst			TLS_pTestEngine->SetScriptParameterValue
#define ICAT_SetTargetDevice					theCommandAndControl.SetTargetDevice
#define ICAT_SetTargetDeviceFilter				theCommandAndControl.SetTargetDeviceFilter
#define ICAT_GetTargetDevice					theCommandAndControl.GetTargetDevice
#define ICAT_GetScriptFilters					theCommandAndControl.GetFilters
#define ICAT_GetNightMode						TLS_pTestEngine->GetNightMode
#define ICAT_Register							theCommandAndControl.Register
#define ICAT_Unregister							theCommandAndControl.Unregister
#define ICAT_StopBatchRunning					TLS_pTestEngine->UserStopBatchFromScript
#define ICAT_PauseBatchRunning					TLS_pTestEngine->UserPauseBatchFromScript

#define ICAT_GetLastTestBatchPath				CTestEngine::GetLastTestBatchPath
#define ICAT_GetCurrentTestBatchPath			TLS_pTestEngine->GetCurrentTestBatchPath
#define GetScriptKillEvent						TLS_pTestEngine->GetKillEvent
#define BeginCleanUpThread						TLS_pTestEngine->BeginCleanUpThread
#define SetCleanUpThread						TLS_pTestEngine->SetCleanUpThread
#define GetScriptPauseEvent						TLS_pTestEngine->GetPauseEvent
#define GetScriptResumeEvent					TLS_pTestEngine->GetResumeEvent

#define ICAT_SetProgressMaxNum					TLS_pTestEngine->SetProgressMaxNum
#define ICAT_SetProgressCurrentNum				TLS_pTestEngine->SetProgressCurrentNum
#define ICAT_SendScriptFileToCTSpector			TLS_pTestEngine->SendScriptFileToCTSpector

#define UE_UpdateCommandsDB						ICAT_UpdateCommandsDB
#define UE_UpdateNVMDB							ICAT_UpdateNVMDB
#define UE_UpdateDSPDB							ICAT_UpdateDSPDB
#define UE_ImportDBFromText						ICAT_ImportDBFromText

#define ICAT_UpdateCommandsDB					TLS_pTestEngine->UpdateCommandsDB
#define ICAT_UpdateNVMDB						TLS_pTestEngine->UpdateNVMDB
#define ICAT_UpdateDSPDB						TLS_pTestEngine->UpdateDSPDB
#define ICAT_ImportDBFromText					TLS_pTestEngine->ImportDBFromText

#define ICAT_InitSerial				CCommunicationManager::Instance()->InitSerial
#define ICAT_InitSocket				CCommunicationManager::Instance()->InitSocket
#define ICAT_InitSocketEx			CCommunicationManager::Instance()->InitSocketEx

#define ICAT_IsSerial				CCommunicationManager::Instance()->IsSerial
#define ICAT_InitUsb				CCommunicationManager::Instance()->InitUsb
#define ICAT_InitDevice				CCommunicationManager::Instance()->InitDevice
#define ICAT_CloseDevice			CCommunicationManager::Instance()->CloseDevice
#define ICAT_IsAlive				CCommunicationManager::Instance()->IsAlive
#define ICAT_IsDIAG					CCommunicationManager::Instance()->IsDIAG
#define ICAT_IsEMMI					CCommunicationManager::Instance()->IsEMMI
#define ICAT_IsRawData				CCommunicationManager::Instance()->IsRawData


#define ICAT_ConvertValueToEnum			theConverterManager(CCommInterface::Instance()->GetAliveDiagDeviceID())->GetEnumFromTable
#define ICAT_ConvertEnumToValue			CDatabaseAPI::GetEnumValue
#define ICAT_GetEnumSizeByName			theConverterManager(CCommInterface::Instance()->GetAliveDiagDeviceID())->GetEnumSizeByName
#define ConvertEnumNameToValue			theConverterManager(CCommInterface::Instance()->GetAliveDiagDeviceID())->GetEnumValueByName

#define ICAT_IsAsn1Message				theConverterManager(CCommInterface::Instance()->GetAliveDiagDeviceID())->IsAsn1Message
#define ICAT_GetASN1MessageName			theConverterManager(CCommInterface::Instance()->GetAliveDiagDeviceID())->GetASN1MessageName
#define ICAT_DecodeASN1Message			theConverterManager(CCommInterface::Instance()->GetAliveDiagDeviceID())->DecodeASN1Message
#define ICAT_GetASN1StructName			theConverterManager(CCommInterface::Instance()->GetAliveDiagDeviceID())->GetASN1StructName
#define ICAT_GetASN1MsgGroupDetails		theConverterManager(CCommInterface::Instance()->GetAliveDiagDeviceID())->GetASN1MsgGroupDetails
#define ICAT_GetAsn1SignalID			theConverterManager(CCommInterface::Instance()->GetAliveDiagDeviceID())->GetAsn1SignalID
#define ICAT_GetSignalID   theConverterManager(CCommInterface::Instance()->GetAliveDiagDeviceID())->GetSignalID

#define ICAT_Cat123ToID    theCommandAndControl.Cat123ToID

#define ICAT_GetOSType		CDBUtils::Instance(CCommInterface::Instance()->GetAliveDiagDeviceID())->GetOSType


#define ICAT_PlayMacro					theCommandAndControl.PlayMacro

#define ICAT_pCommandAndControlofFlashExplorer         CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->m_pCommandAndControl
#define ICAT_SetFlashExplorerDevice         CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->SetActiveDevice
#define ICAT_SaveFileToFlash				CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->WriteFile
#define ICAT_LoadFileFromFlash				CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->ReadFile
#define ICAT_ComparePcFileWithFlashFile		CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->ComparePcFileWithFlashFile
#define ICAT_RemoveFileFromFlash			CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->RemoveFile
#define ICAT_FormatFlash					CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->FormatFlash
#define ICAT_SetRTC							CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->SetRTC
#define ICAT_ResetBoard						CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->ResetBoard
#define ICAT_RenameFile						CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->RenameFile
#define ICAT_ChangeMode						CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->ChangeMode
#define ICAT_GetFlashFileNameList			CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->GetFlashFileNameList
#define ICAT_SetVolumeAndPath				CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->SetVolumeAndPath
#define ICAT_GetVolumeAndPath				CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->GetVolumeAndPath
#define ICAT_MakeDir						CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->MakeDir
#define ICAT_RemoveDir						CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->RemoveDir
#define ICAT_GetVolumeList					CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->GetVolumeList
#define ICAT_SetTargetType					CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->SetTargetType
#define ICAT_GetTargetType					CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->GetTargetType
#define ICAT_SetActiveDevice				CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->SetActiveDevice
#define ICAT_GetVolumeList					CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->GetVolumeList
#define ICAT_GetFdiVersion					CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->GetFdiVersion
#define	ICAT_QueryFdiVersion				CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->QueryFdiVersion
#define ICAT_UpdateAvailableSpace			CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->UpdateAvailableSpace
#define ICAT_SetCurrentDevice				CFlashExplorerData::Instance(TLS_pTestEngine->GetInstanceName())->SetCurrentDevice

// Download filters to target
#define ICAT_SetDIAGTargetFilterArray	theCommandAndControl.SetDIAGTargetFilterArray
#define ICAT_GetDIAGTargetFilterArray	theCommandAndControl.GetDIAGTargetFilterArray
#define ICAT_SetDIAGTargetFilterMessage	theCommandAndControl.SetDIAGTargetFilterMessage
#define ICAT_GetDIAGTargetFilterMessage	theCommandAndControl.GetDIAGTargetFilterMessage
#define ICAT_SetGKITargetFilterSignal	theCommandAndControl.SetGKITargetFilterSignal
#define ICAT_GetGKITargetFilterSignal	theCommandAndControl.GetGKITargetFilterSignal

#define ICAT_SetAppDIAGTargetFilterArray	theCommandAndControl.SetAppDIAGTargetFilterArray
#define ICAT_GetAppDIAGTargetFilterArray	theCommandAndControl.GetAppDIAGTargetFilterArray
#define ICAT_EnablePartCpDiagFilterToUE     CDIAGFilter::EnablePartCpDiagFilterToUE
#define ICAT_DisablePartCpDiagFilterToUE    CDIAGFilter::DisablePartCpDiagFilterToUE
#define ICAT_EnableAllCpDiagFilter          CDIAGFilter::EnableAllCpDiagFilter
#define ICAT_DisableAllCpDiagFilter         CDIAGFilter::DisableAllCpDiagFilter

#define ICAT_OpenEntireFilter				CViewer::OpenEntireFilter
#define ICAT_CloseEntireFilter				CViewer::CloseEntireFilter
#define ICAT_SetDIAGFilter					CViewer::SetDIAGFilter

// Definitions for Backward Compatibility:
//////////////////////////////////////////
#define UE_CmdAndCtrlInstance			ICAT_CmdAndCtrlInstance
#define UE_DeleteCmdAndCtrlInstance		ICAT_DeleteCmdAndCtrlInstance 

#define UE_SendCommand				ICAT_SendCommand
#define UE_WaitForMessage			ICAT_WaitForMessage
#define UE_SendAndWait				ICAT_SendAndWait
//#define SendAndWaitFrm			ICAT_SendAndWaitFrm
#define UE_SendExtCommand			ICAT_SendExtCommand
#define UE_WaitForExtMessage		ICAT_WaitForExtMessage
#define UE_SendExtAndWait			ICAT_SendExtAndWait
#define UE_SendAndWaitExt			ICAT_SendAndWaitExt
#define UE_SendExtAndWaitExt		ICAT_SendExtAndWaitExt
#define UE_GetErrorMessage			ICAT_GetErrorMessage

#define SendInternalServiceCommand	ICAT_SendInternalServiceCommand
#define WaitForReturnService		ICAT_WaitForReturnService
#define SendInternalAndWaitReturn	ICAT_SendInternalAndWaitReturn

#define SendIPCCommand				ICAT_SendIPCCommand
#define SendIPCAndWait				ICAT_SendIPCAndWait				
#define SendIPCAndWaitExt			ICAT_SendIPCAndWaitExt			
#define SendIPCAndWaitMultipleExt	ICAT_SendIPCAndWaitMultipleExt	

#define UE_SendATCommand			ICAT_SendATCommand
#define UE_WaitForATMessage		ICAT_WaitForATMessage
#define UE_SendATAndWait			ICAT_SendATAndWait

#define UE_SendGKISignal					ICAT_SendGKISignal
#define UE_WaitForGKISignal				ICAT_WaitForGKISignal
#define UE_SendGKICommand					ICAT_SendGKICommand
#define UE_SendGKISignalAndWaitGKISignal	ICAT_SendGKISignalAndWaitGKISignal
#define UE_SendGKICommandAndWaitGKISignal	ICAT_SendGKICommandAndWaitGKISignal
#define UE_GetGKITaskID					ICAT_GetGKITaskID

#define UE_WaitForMultipleMessage		ICAT_WaitForMultipleMessage
#define	UE_SendAndWaitMultiple			ICAT_SendAndWaitMultiple
#define	UE_WaitForMultipleExtMessage	ICAT_WaitForMultipleExtMessage
#define	UE_SendExtAndWaitMultipleExt	ICAT_SendExtAndWaitMultipleExt
#define	UE_WaitForMultipleATMessage	ICAT_WaitForMultipleATMessage
#define	UE_SendATAndWaitMultiple		ICAT_SendATAndWaitMultiple
#define	UE_WaitForSeveralATMessage		ICAT_WaitForSeveralATMessage
#define	UE_SendATAndWaitSeveral		ICAT_SendATAndWaitSeveral

#define UE_GetSignalID     ICAT_GetSignalID
#define UE_Cat123ToID      ICAT_Cat123ToID
#define UE_SendHugeCommand				ICAT_SendHugeCommand

#define UE_SetTraceFilter						ICAT_SetTraceFilter
#define UE_GetTraceFilter						ICAT_GetTraceFilter
#define UE_SetSignalFilter						ICAT_SetSignalFilter
#define UE_GetSignalFilter						ICAT_GetSignalFilter

#define	UE_GetOSType					ICAT_GetOSType

#define _GetMessage						ICAT_GetMessage
#define GetExtMessage					ICAT_GetExtMessage
//#define GetNextMessage					ICAT_GetNextMessage
//#define GetNextExtMessage				ICAT_GetNextExtMessage
#define GetPrevMessage					ICAT_GetPrevMessage
#define GetPreviousMessage				ICAT_GetPreviousMessage
#define GetPrevExtMessage				ICAT_GetPrevExtMessage
#define GetGKISignal					ICAT_GetGKISignal
#define GetNextGKISignal				ICAT_GetNextGKISignal
#define GetPrevGKISignal				ICAT_GetPrevGKISignal
//#define DeleteMessage					ICAT_DeleteMessage
#define ClearMsgFIFO				ICAT_ClearMessageFIFO
//#define StartFIFO						ICAT_StartFIFO
//#define StopFIFO						ICAT_StopFIFO
//#define SetFifoSize						ICAT_SetFifoSize
#define RemoveMessagesFromFIFO			ICAT_RemoveMessagesFromFIFO
#define RemoveExtMessagesFromFIFO		ICAT_RemoveExtMessagesFromFIFO
#define RemoveGKISignalsFromFIFO		ICAT_RemoveGKISignalsFromFIFO
#define ClearFIFOExcludingMessages		ICAT_ClearFIFOExcludingMessages
#define ClearFIFOExcludingExtMessages	ICAT_ClearFIFOExcludingExtMessages
#define ClearFIFOExcludingGKISignals	ICAT_ClearFIFOExcludingGKISignals

#define GetATMessage			ICAT_GetATMessage
//#define GetNextATMessage		ICAT_GetNextATMessage
#define GetPrevATMessage		ICAT_GetPrevATMessage
#define GetEnumStrings			ICAT_GetEnumStrings
#define GetEnumString			ICAT_GetEnumString
#define GetAppEnumStrings		ICAT_GetAppEnumStrings
#define GetAppEnumString		ICAT_GetAppEnumString
#define ReportLineToEnumStrings	ICAT_ReportLineToEnumStrings
#define AppReportLineToEnumStrings	ICAT_AppReportLineToEnumStrings

#define GoToEndOfFIFO			ICAT_GoToEndOfFIFO
#define GoToBeginningOfFIFO		ICAT_GoToBeginningOfFIFO

#define ShowIMEIOnTarget		ICAT_ShowIMEIOnTarget
#define GetIMEIOnDevice			ICAT_GetIMEIOnDevice
#define GetIMEI					ICAT_GetIMEI

#define SendBoardTrackerInformation	ICAT_SendBoardTrackerInformation

#define SetProductionLineMode	theCommandAndControl.SetProductionLineMode

#define SetATCommandsMode		ICAT_SetATCommandsMode
#define SetATCommandsOverDiag	ICAT_SetATCommandsOverDiag

#define SendSTX					ICAT_SendSTX
#define SendLV					ICAT_SendLV

#define AddNewViewer(s)					ICAT_AddNewViewer(s)
#define AddNewViewerInOfflineMode(s)	ICAT_AddNewViewerInOfflineMode(s)
#define CloseViewer						ICAT_CloseViewer
#define SetDIAGMessageColor				ICAT_SetDIAGMessageColor
#define SetGKIMessageColor				ICAT_SetGKIMessageColor
#define SetDSPMessageColor				ICAT_SetDSPMessageColor

#define AddNewLogger						ICAT_AddNewLogger
#define AddScriptLogger(fn, tr, st, pa)		ICAT_AddScriptLogger(fn, tr, st, pa)
#define CloseLogger							ICAT_CloseLogger
#define UE_OpenNewLog						ICAT_OpenNewLog
#define UE_ExportLogFile					ICAT_ExportLogFile

#define OpenDbTable							ICAT_OpenDbTable


#define GetScriptParameter			ICAT_GetScriptParameter
#define SetScriptParameter			ICAT_SetScriptParameter
#define GetBatchParameter			ICAT_GetBatchParameter
#define SetBatchParameter			ICAT_SetBatchParameter
#define GetEnvironmentParameter		ICAT_GetEnvironmentParameter
#define SetEnvironmentParameter		ICAT_SetEnvironmentParameter
#define GetMinStandard				ICAT_GetMinStandard
#define SetScriptFailureReason		ICAT_SetScriptFailureReason
#define GetScriptFailureReason		ICAT_GetScriptFailureReason
#define SaveSubScriptResult			ICAT_SaveSubScriptResult
#define SetSubScriptResultParameter ICAT_SetSubScriptResultParameter
#define CheckSubScriptResult		ICAT_CheckSubScriptResult
#define GetPrimaryViSession			ICAT_GetPrimaryViSession
#define GetSecondaryViSession		ICAT_GetSecondaryViSession
#define GetDeviceAttenuation		ICAT_GetDeviceAttenuation
#define SetDeviceAttenuation		ICAT_SetDeviceAttenuation
#define GetUserInput				ICAT_GetUserInput
#define PromptFileName				ICAT_PromptFileName
#define GetCurrentHWConfig			ICAT_GetCurrentHWConfig
#define GetXDEVConfigDevices		ICAT_GetXDEVConfigDevices
#define GetXDEVConfigurationDeviceGroup  ICAT_GetXDEVConfigurationDeviceGroup
#define XDEVImportDevOrCfg			ICAT_XDEVImportDevOrCfg
#define GetCurrentScriptIteration		 ICAT_GetCurrentScriptIteration
#define IsLastScriptAndIterInBatch		 ICAT_IsLastScriptAndIterInBatch
#define GetCurrentScriptIndex		 	 ICAT_GetCurrentScriptIndex
#define GetCurrentBatchIteration		 ICAT_GetCurrentBatchIteration
#define GetTotalCurrentScriptIterations  ICAT_GetTotalCurrentScriptIterations
#define GetTotalBatchIterations			 ICAT_GetTotalBatchIterations
#define GetTestEngineWnd			ICAT_GetTestEngineWnd
#define SetScriptParameterConst		ICAT_SetScriptParameterConst
#define UE_SetTargetDevice			ICAT_SetTargetDevice
#define UE_SetTargetDeviceFilter	ICAT_SetTargetDeviceFilter
#define UE_GetTargetDevice			ICAT_GetTargetDevice
#define GetScriptFilters			ICAT_GetScriptFilters
#define GetNightMode				ICAT_GetNightMode
#define UE_Register					ICAT_Register
#define UE_Unregister				ICAT_Unregister
#define PauseBatchRunning			ICAT_PauseBatchRunning
#define StopBatchRunning			ICAT_StopBatchRunning


#define GetLastTestBatchPath		ICAT_GetLastTestBatchPath
#define GetCurrentTestBatchPath		ICAT_GetCurrentTestBatchPath

#define SetProgressMaxNum			ICAT_SetProgressMaxNum
#define SetProgressCurrentNum		ICAT_SetProgressCurrentNum

#define SendScriptFileToCTSpector	ICAT_SendScriptFileToCTSpector

#define InitSerial				ICAT_InitSerial
#define InitSocket				ICAT_InitSocket
#define InitSocketEx			ICAT_InitSocketEx

#define IsSerial			ICAT_IsSerial
#define InitUsb				ICAT_InitUsb
#define InitDevice			ICAT_InitDevice
#define IsAlive				ICAT_IsAlive
#define IsDIAG				ICAT_IsDIAG
#define IsEMMI				ICAT_IsEMMI
#define IsRawData			ICAT_IsRawData

#define ConvertValueToEnum			ICAT_ConvertValueToEnum
#define ConvertEnumToValue			ICAT_ConvertEnumToValue
#define GetEnumSizeByName			ICAT_GetEnumSizeByName

#define IsAsn1Message				ICAT_IsAsn1Message
#define GetASN1MessageName			ICAT_GetASN1MessageName
#define DecodeASN1Message			ICAT_DecodeASN1Message
#define GetASN1StructName			ICAT_GetASN1StructName
#define GetASN1MsgGroupDetails		ICAT_GetASN1MsgGroupDetails
#define GetAsn1SignalID				ICAT_GetAsn1SignalID

#define PlayMacro					ICAT_PlayMacro

#define UE_SaveFileToFlash				ICAT_SaveFileToFlash
#define UE_LoadFileFromFlash			ICAT_LoadFileFromFlash
#define UE_ComparePcFileWithFlashFile	ICAT_ComparePcFileWithFlashFile
#define UE_RemoveFileFromFlash			ICAT_RemoveFileFromFlash
#define UE_FormatFlash					ICAT_FormatFlash
#define UE_SetRTC						ICAT_SetRTC
#define UE_ResetBoard					ICAT_ResetBoard
#define UE_RenameFile					ICAT_RenameFile
#define UE_ChangeMode					ICAT_ChangeMode
#define UE_GetFlashFileNameList			ICAT_GetFlashFileNameList
#define UE_SetVolumeAndPath				ICAT_SetVolumeAndPath
#define UE_GetVolumeAndPath				ICAT_GetVolumeAndPath
#define UE_MakeDir						ICAT_MakeDir
#define UE_RemoveDir					ICAT_RemoveDir
#define UE_GetVolumeList				ICAT_GetVolumeList
#define UE_SetTargetType				ICAT_SetTargetType
#define UE_GetTargetType				ICAT_GetTargetType
#define UE_SetActiveDevice				ICAT_SetActiveDevice
#define UE_SetCurrentDevice				ICAT_SetCurrentDevice
#define UE_GetFDIVersion				ICAT_GetFdiVersion
#define	UE_QueryFdiVersion				ICAT_QueryFdiVersion
#define UE_UpdateAvailableSpace			ICAT_UpdateAvailableSpace

// #define UE_SendCommand			SendCommand
// #define UE_WaitForMessage		WaitForMessage
// #define UE_SendAndWait			SendAndWait
//#define UE_SendAndWaitFrm		SendAndWaitFrm
// #define UE_SendExtCommand		SendExtCommand
// #define UE_WaitForExtMessage	WaitForExtMessage
// #define UE_SendExtAndWait		SendExtAndWait
// #define UE_SendAndWaitExt		SendAndWaitExt
// #define UE_SendExtAndWaitExt	SendExtAndWaitExt
#define UE_GetErrorMessage		ICAT_GetErrorMessage

#define UE_SendInternalServiceCommand	SendInternalServiceCommand
#define UE_WaitForReturnService			WaitForReturnService
#define UE_SendInternalAndWaitReturn	SendInternalAndWaitReturn

#define UE_SendIPCCommand				SendIPCCommand
#define UE_SendIPCAndWait				SendIPCAndWait
#define UE_SendIPCAndWaitExt			SendIPCAndWaitExt
#define UE_SendIPCAndWaitMultipleExt	SendIPCAndWaitMultipleExt


// #define UE_SendATCommand				SendATCommand
// #define UE_WaitForATMessage				WaitForATMessage
// #define UE_SendATAndWait				SendATAndWait
// 
// #define UE_SendGKISignal					SendGKISignal
// #define UE_WaitForGKISignal					WaitForGKISignal
// #define UE_SendGKICommand					SendGKICommand
// #define UE_SendGKISignalAndWaitGKISignal	SendGKISignalAndWaitGKISignal
// #define UE_SendGKICommandAndWaitGKISignal	SendGKICommandAndWaitGKISignal
// #define UE_GetGKITaskID						GetGKITaskID
// 
// #define UE_WaitForMultipleMessage		WaitForMultipleMessage
// #define	UE_SendAndWaitMultiple			SendAndWaitMultiple
// #define	UE_WaitForMultipleExtMessage	WaitForMultipleExtMessage
// #define	UE_SendExtAndWaitMultipleExt	SendExtAndWaitMultipleExt
// #define	UE_WaitForMultipleATMessage		WaitForMultipleATMessage
// #define	UE_SendATAndWaitMultiple		SendATAndWaitMultiple
// #define	UE_WaitForSeveralATMessage		WaitForSeveralATMessage
// #define	UE_SendATAndWaitSeveral			SendATAndWaitSeveral


#define UE_GetMessage				ICAT_GetMessage
#define UE_GetExtMessage			ICAT_GetExtMessage
#define UE_GetNextMessage			ICAT_GetNextMessage
#define UE_GetNextExtMessage		ICAT_GetNextExtMessage
#define UE_GetPrevMessage			ICAT_GetPrevMessage
#define UE_GetPreviousMessage		ICAT_GetPrevMessage
#define UE_GetPrevExtMessage		ICAT_GetPrevExtMessage
#define UE_GetGKISignal				ICAT_GetGKISignal
#define UE_GetNextGKISignal			ICAT_GetNextGKISignal
#define UE_GetPrevGKISignal			ICAT_GetPrevGKISignal
#define UE_DeleteMessage			ICAT_DeleteMessage
#define UE_DeleteMessageFromFIFO	ICAT_DeleteMessage
#define UE_ClearFIFO				ICAT_ClearMessageFIFO
#define UE_StartFIFO				ICAT_StartFIFO
#define UE_StopFIFO					ICAT_StopFIFO
#define UE_SetFIFOSize				ICAT_SetFifoSize
#define UE_RemoveMessagesFromFIFO		RemoveMessagesFromFIFO
#define UE_RemoveExtMessagesFromFIFO	RemoveExtMessagesFromFIFO
#define UE_RemoveGKISignalsFromFIFO		RemoveGKISignalsFromFIFO
#define UE_ClearFIFOExcludingMessages		ClearFIFOExcludingMessages
#define UE_ClearFIFOExcludingExtMessages	ClearFIFOExcludingExtMessages
#define UE_ClearFIFOExcludingGKISignals		ClearFIFOExcludingGKISignals

#define UE_SetATCommandsMode			SetATCommandsMode
#define UE_SetATCommandsOverDiag		SetATCommandsOverDiag

#define UE_ShowIMEIOnTarget			ShowIMEIOnTarget
#define UE_GetIMEIOnDevice			GetIMEIOnDevice
#define UE_GetIMEI					GetIMEI


#define UE_PauseFIFO				UE_StopFIFO
#define UE_ResumeFIFO				UE_StartFIFO
#define UE_ContinueFIFO				UE_StartFIFO

#define UE_SendDSPCommand			ICAT_SendExtCommand
#define UE_WaitForDSPMessage		ICAT_WaitForExtMessage
#define UE_SendDSPAndWait			ICAT_SendExtAndWait
#define UE_SendAndWaitDSP			ICAT_SendAndWaitExt
#define UE_SendDSPAndWaitDSP		ICAT_SendExtAndWaitExt
#define UE_GetDSPMessage			ICAT_GetExtMessage
#define UE_GetNextDSPMessage		ICAT_GetNextExtMessage
#define UE_GetPrevDSPMessage		ICAT_GetPrevExtMessage

#define UE_GetATMessage				ICAT_GetATMessage
#define UE_GetNextATMessage			ICAT_GetNextATMessage
#define UE_GetPrevATMessage			ICAT_GetPrevATMessage

#define UE_GoToEndOfFIFO			GoToEndOfFIFO
#define UE_GoToBeginningOfFIFO		GoToBeginningOfFIFO

#define UE_PlayMacro				PlayMacro

#define STX_Send					SendSTX
#define LV_Send						SendLV

#define Comm_InitSerial				InitSerial
#define Comm_InitSocket				InitSocket
#define Comm_InitSocketEx			InitSocketEx
#define Comm_InitUsb				InitUsb
#define Comm_InitDevice				InitDevice
#define Comm_CloseDevice			ICAT_CloseDevice
#define Comm_IsAlive				IsAlive
#define Comm_IsDIAG					IsDIAG
#define Comm_IsEMMI					IsEMMI
#define Comm_IsRawData				IsRawData

#define PlayCommandMacro			PlayMacro

// Download filters to target
#define SetDIAGTargetFilterArray	ICAT_SetDIAGTargetFilterArray
#define GetDIAGTargetFilterArray	ICAT_GetDIAGTargetFilterArray
#define SetDIAGTargetFilterMessage	ICAT_SetDIAGTargetFilterMessage
#define GetDIAGTargetFilterMessage	ICAT_GetDIAGTargetFilterMessage
#define SetGKITargetFilterSignal	ICAT_SetGKITargetFilterSignal
#define GetGKITargetFilterSignal	ICAT_GetGKITargetFilterSignal

#define SetAppDIAGTargetFilterArray		ICAT_SetAppDIAGTargetFilterArray
#define GetAppDIAGTargetFilterArray		ICAT_GetAppDIAGTargetFilterArray

#define UE_SetDIAGTargetFilterArray		SetDIAGTargetFilterArray
#define UE_GetDIAGTargetFilterArray		GetDIAGTargetFilterArray
#define UE_SetDIAGTargetFilterMessage	SetDIAGTargetFilterMessage
#define UE_GetDIAGTargetFilterMessage	GetDIAGTargetFilterMessage
#define UE_SetGKITargetFilterSignal		SetGKITargetFilterSignal
#define UE_GetGKITargetFilterSignal		GetGKITargetFilterSignal

#define UE_SetAppDIAGTargetFilterArray		SetAppDIAGTargetFilterArray
#define UE_GetAppDIAGTargetFilterArray		GetAppDIAGTargetFilterArray
#define EnablePartCpDiagFilterToUE          ICAT_EnablePartCpDiagFilterToUE
#define DisablePartCpDiagFilterToUE         ICAT_DisablePartCpDiagFilterToUE
#define EnableAllCpDiagFilter      ICAT_EnableAllCpDiagFilter      
#define DisableAllCpDiagFilter     ICAT_DisableAllCpDiagFilter   

#define UE_GetEnumStrings			GetEnumStrings
#define UE_GetEnumString			GetEnumString
#define UE_GetAppEnumStrings		GetAppEnumStrings
#define UE_GetAppEnumString			GetAppEnumString
#define UE_ReportLineToEnumStrings	ReportLineToEnumStrings
#define UE_AppReportLineToEnumStrings	AppReportLineToEnumStrings

#define OpenEntireViewerFilter		ICAT_OpenEntireFilter
#define CloseEntireViewerFilter		ICAT_CloseEntireFilter
#define SetDIAGViewerFilter			ICAT_SetDIAGFilter

#define CreateMessageSender			TLS_pTestEngine->CreateMessageSender
#define DeleteMessageSender			TLS_pTestEngine->DeleteMessageSender
#define CreateMessageReceiver		TLS_pTestEngine->CreateMessageReceiver
#define DeleteMessageReceiver		TLS_pTestEngine->DeleteMessageReceiver

// APT-Controller.
#define	 AptController_GetDeviceValue					CAPTControllerManager::Instance()->GetDeviceValue

#endif 
