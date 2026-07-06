// CATCore.h : main header file for the CATCore
//
#pragma once
#include <afxmt.h>
#include "../../MrvlCommon/CommonDefs.h"
#include "singletondestroyer.h"
#include "SmartShell.h"
#include "ICATMessage.h"
#include "FdiFile.h"
#include "ExportedStructures.h"
#include "../Converter/CommandAndMessageStructures.h"
#include <map>
#include "FlashExplorerSmartShell.h"

using std::map;

// 
#define FDI5    "FDI5"
#define FDI6    "FDI6"
#define FDI7    "FDI7"
#define FDI71   "FDI71"
#define FDI8    "FDI8"

class CFlashExplorerSmartShell;
class __declspec(dllexport) CFlashExplorerData
{
public:
    CFlashExplorerData(int nDevice);
    CFlashExplorerData(CStringA strInstanceName = "FlashExplorer Data");
    ~CFlashExplorerData(void);

private:
    int m_nDevice;
    static CSingletonDestroyer<CFlashExplorerData> m_Destroyer;
    static SmartShell<CFlashExplorerData> m_SmartShell;
	static CFlashExplorerSmartShell m_stringSmartShell;
    static CCriticalSection m_InstanceCreationLock;
    eTargetType m_eTargetType;
    BOOL m_bCancelFile;
    BOOL m_bModify;
    BOOL m_bExtendedFdi;
    int m_nRootPathLength;
    CString m_sFdiPath; // String which contains the current FDI file's path, include the Volume.
    CString m_strWriteFileName;
    CString m_sCommFdiVersion;      // String which indicates on the FDI SW version on the Comm. side.
    CString m_sAppFdiVersion;       // String which indicates on the FDI SW version on the App. side.
    CList<CFdiFile,const CFdiFile&>     m_olFileList;   //Every single file(CP or AP) item will be added to: m_olFileList;
    UINT32 m_nAvailableSpace;
    class CCommandChannel* m_pCommandAndControl;
    volatile HWND  m_hMainFrmWnd;
    CCriticalSection m_Lock;
public:
	CString m_sInstanceName;

public:
    static CFlashExplorerData* Instance(int nDevice);
#ifdef _UNICODE
    static CFlashExplorerData* Instance(CString strInstanceName);
#endif
	static CFlashExplorerData* Instance(CStringA strInstanceName);
    UE_errCode_t SetTargetType(eTargetType targetType);
    eTargetType  GetTargetType(){ return m_eTargetType;};
#ifdef _UNICODE
	UE_errCode_t ReadFile(eTargetType TargetType, const CString& a_sDstPcBinFileName, const CString& a_sSrcFlashFileName);
	UE_errCode_t RemoveFile(eTargetType TargetType, const CString& a_sFlashFileName);
	UE_errCode_t RemoveDir(eTargetType TargetType, const CString& a_sFlashDirName);
	UE_errCode_t SetVolumeAndPath(eTargetType TargetType, const CString &UserPath, BOOL DefaultPath = false);
    UE_errCode_t MakeDir(eTargetType TargetType, const CString &a_sDirName, short a_sMode, UINT32 &a_lMkDirErrCode);
    UE_errCode_t GetFlashFileNameList(eTargetType TargetType, CStringList &a_strFileNameList, const CString a_strWildCard = _T("*"));
	UE_errCode_t WriteFile(eTargetType TargetType, const CString& a_sDstFlashBinFileName,const CString& a_sSrcPcBinFilePath,BOOL a_bValidate = FALSE);
	UE_errCode_t CheckFileExist(eTargetType TargetType, const CString& a_sFileName, const CString& a_sFlashDirName = _T(""));
#endif
	UE_errCode_t ReadFile(eTargetType TargetType, const CStringA& a_sDstPcBinFileName, const CStringA& a_sSrcFlashFileName);
	UE_errCode_t ReadFile(const CStringW& a_sDstPcBinFileName, const CStringW& a_sSrcFlashFileName);
	UE_errCode_t WriteFile(eTargetType TargetType, const CStringA& a_sDstFlashBinFileName,const CStringA& a_sSrcPcBinFilePath,BOOL a_bValidate = FALSE);
    UE_errCode_t GetFileList(eTargetType TargetType, CList<CFdiFile,const CFdiFile&>*& a_plFileList, CString a_sWildCard, BOOL a_bForced );
    void LockFileList();
    void UnlockFileList();
    UE_errCode_t RenameFile(eTargetType TargetType, const CString& a_sCurFileName, const CString& a_sNewFileName);
	UE_errCode_t RemoveFile(eTargetType TargetType, const CStringA& a_sFlashFileName);
	UE_errCode_t RemoveDir(eTargetType TargetType, const CStringA& a_sFlashDirName);
    UE_errCode_t FormatFlash(eTargetType TargetType);
    UE_errCode_t FormatFlash(eTargetType TargetType, const CString &volName);
    UE_errCode_t GetFDVSize(eTargetType TargetType, UINT64& a_dwFdvFlashSize);
    UE_errCode_t GetFlashAvailableSize(eTargetType TargetType, UINT32& nFDVAvailableSpace);
    UE_errCode_t QueryAppSideFdiNVMPath(eTargetType TargetType, CString& strFdiNvmPath);
    BOOL         IsFdiVer(eTargetType TargetType, int a_nFdiVer);
    CFdiFile*    GetFileDataInfo(const CString& a_sFileName);
    static void  DeleteInstance(int nDevice);
	static void  DeleteInstance(CString strInstanceName);
    CString      GetErrorMessage(UE_errCode_t a_eErrCode);
    CString      GetVolumeAndPath();
    void         SetActiveDevice(CICATMessage::eDirection targetDev);
	void         SetCurrentDevice(int nDevice);
	UE_errCode_t MakeDir(eTargetType TargetType, const CStringA &a_sDirName, short a_sMode, UINT32 &a_lMkDirErrCode);
	UE_errCode_t GetFlashFileNameList(eTargetType TargetType, CStringList &a_strFileNameList, const CStringA a_strWildCard = "*");
	UE_errCode_t SetVolumeAndPath(eTargetType TargetType, const CStringA &UserPath, BOOL DefaultPath = false);
	//UE_errCode_t CheckFileExist(eTargetType TargetType, const CStringA &UserPath, BOOL DefaultPath = false);
	UE_errCode_t CheckFileExist(eTargetType TargetType, const CStringA& a_sFileName, const CStringA& a_sFlashDirName = "");
    CString     GetWriteFileName(){return m_strWriteFileName;}
    void        SetMainFrmWnd(HWND a_hMainFrmWnd);
    void        CancelFile(){m_bCancelFile = true;}
    unsigned int Adler32Checksum(unsigned char *data, int len);
private:
    UE_errCode_t GetMaxInputMessageBodyLength(eTargetType TargetType,UINT32& dwMaxMsgLen);
    UE_errCode_t GetMaxOutputMessageBodyLength(eTargetType TargetType, UINT32& dwMaxMsgLen);
    UE_errCode_t UpdateAvailableSpace(eTargetType TargetType, CString a_sVolName);
    UE_errCode_t QueryFdiVersion(eTargetType TargetType);
    UE_errCode_t InitVolumeAndPath(eTargetType TargetType);
    UE_errCode_t GetMaxFileNameLength(eTargetType TargetType, int& a_iMaxFileNameLength);
    UE_errCode_t UpdateFileInfoList(eTargetType TargetType, CString& a_sWildCard);
    UE_errCode_t CompareBinFiles(const CString& l_sDstBinFileName, const CString& l_sSrcBinFileName);
    UE_errCode_t PreConfig(eTargetType TargetType);
    BOOL    IsCAT123Exist(eTargetType TargetType, const CString& l_sCmdCAT123, BOOL isReport);
    CString GetFdiVersion(eTargetType TargetType);
    BOOL    IsValidFilePath(const CString& a_sPath);
    BOOL    GetPCFileSize(const CString& a_sFilePathnName, LONG& a_lPcFileSize);
    CString RetrieveFileName(const CString& a_sFilePath);
    CString RetrieveVolumeName(const CString& a_sFilePath);
    UINT32  GetFDVAvailableSpace();  
    BOOL    ParseFilePropList(eTargetType TargetType, CString &a_sFileListInfo, int a_iListLen, BOOL a_bOverwrite);
    BOOL    ConvertByteSizeToKorMstr(UINT32 a_nByteSize, CString &a_sFormatedSize, BOOL a_bRound = false);
    void    EmptyMessageList(); //clear the file list information in the parameter
    void    RandModifyFileName(CString& strFileName); //Random modify the file name

    UE_errCode_t _openFile(eTargetType TargetType,CString a_sFileName,CString a_sMode,UINT32 &a_nFileID,int &a_fdiErrCode);
    UE_errCode_t _closeFile(eTargetType TargetType,UINT32 a_nFileID);
    UE_errCode_t _readFile(eTargetType TargetType,UINT32 a_nFileID,const CString& a_sDstPcBinFileName,const CString& a_sSrcFlashFileName);
    UE_errCode_t _readFile2(eTargetType TargetType,UINT32 a_nFileID,const CString& a_sDstPcBinFileName,const CString& a_sSrcFlashFileName,DWORD dwFlashFileSize);
    UE_errCode_t _writeFile(eTargetType TargetType,UINT32 a_nFileID,const CString& a_sDstFlashBinFileName,const CString& a_sSrcPcBinFilePath, BOOL a_bValidate = FALSE);
    UE_errCode_t _fseek(eTargetType TargetType,UINT32 a_nFileID,int a_iOffset,int a_iWhereFrom);

	//FDI VER 8 functions
	UE_errCode_t _readFileFDI8(eTargetType TargetType,UINT32 a_nFileID,const CString& a_sDstPcBinFileName,const CString& a_sSrcFlashFileName,DWORD dwFlashFileSize);
	UE_errCode_t _writeFileFDI8(eTargetType TargetType,UINT32 a_nFileID,const CString& a_sDstFlashBinFileName,const CString& a_sSrcPcBinFilePath, BOOL a_bValidate = FALSE);
	UE_errCode_t SetFDIVersion(eTargetType TargetType,UINT32 FDIVersion);

private:
	int TargetDeviceToDeviceId(CICATMessage::eDirection eTargetDevice);
	CString GetFilelistCacheStr();
public:
	BOOL FileExist(eTargetType TargetType, const CString& strUeFileFullPath);


};

