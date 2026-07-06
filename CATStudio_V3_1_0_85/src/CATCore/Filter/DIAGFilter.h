
#pragma once
#include "FilterBase.h"
#include "SignalsFilterManager.h"
#include "../Converter/CommandAndMessageStructures.h"
#include "MrvlCommon/CommonDefs.h"
#define SWAP_4_BYTES(dw) ((DWORD)((((DWORD)(dw)&0x000000FF)<<24) | (((DWORD)(dw)&0x0000FF00)<<8) | (((DWORD)(dw)&0x00FF0000)>>8) | (((DWORD)(dw)&0xFF000000)>>24)) )

class CDIAGFilter : public CFilterBase
{
public:
  CDIAGFilter(CAllFilters *pAllFilters, BOOL bOpenAll, int nDevice, BOOL bAppSide=false);
  virtual ~CDIAGFilter(void);
  
  virtual BOOL CreateDlg(CWnd *pParent);
  virtual CDialog * GetDlg();
  virtual BOOL IsPassFilter(CICATMessage *pMessage);
  virtual void RefreshFilterTree(){}
  virtual void RenewFilter();
  virtual void OpenEntireFilter();
  virtual void CloseEntireFilter();
  virtual void UpdateFilterTree(){}


  BYTE *       GetFilter(){return m_pFilter;};

  void        UpdateFilter(LPVOID lpCmdData, int nCmdDataLen);
  BOOL        IsPassFilterSeries(CICATMessage* pMessage);
  BOOL        SetPassFilter(const CString &strCat1, const CString &strCat2, const CString &strCat3, BYTE bPass);
private:
	int m_nDevice;
  UINT        m_MaxMessageID;
  BYTE *       m_pFilter;
  BOOL        m_bAppSide;

  //////////////////////////////////////////////////////////////////////////
  //Richard added for Download DiagFilter to UE  ---  Start		2011-10-13
private:
	static int m_nMaxMessageID;
	static UE_errCode_t DownloadFilterBuffer(int nDevice, BYTE* pBuffer, int nLength, eTargetType TargetType = UE_Comm_Side);
	static DWORD InitBytesArray(int nDevice, CDWordArray &dwBytesArray, const CDWordArray &dwBasesArray);
	static void InitBasesArray(int nDevice, CDWordArray &dwBasesArray);
	static WORD FindHighestSet(int nDevice);
	static DWORD GetNumBases(int nDevice);
public:
	//////////////////////////////////////////////////////////////////////////
	//CP begin
	static UE_errCode_t EnableAllCpDiagFilter(int nDevice);
	static UE_errCode_t DisableAllCpDiagFilter(int nDevice);
	static UE_errCode_t __declspec(dllexport) EnablePartCpDiagFilterToUE(int nDevice, CStringArray& strMsgArray, BOOL bDisableOther = FALSE);	
	static UE_errCode_t __declspec(dllexport) DisablePartCpDiagFilterToUE(int nDevice, CStringArray& strMsgArray, BOOL bEnableOther = FALSE);
	//CP end
	//////////////////////////////////////////////////////////////////////////
	//AP begin
	static UE_errCode_t EnableAllApDiagFilter(int nDevice);
	static UE_errCode_t DisableAllApDiagFilter(int nDevice);
	static UE_errCode_t EnablePartApDiagFilterToUE(int nDevice, CStringArray& strMsgArray, BOOL bDisableOther = FALSE);	
	static UE_errCode_t DisablePartApDiagFilterToUE(int nDevice, CStringArray& strMsgArray, BOOL bEnableOther = FALSE);
	//AP end
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//GKI begin
//	/*static */CSignalsFilterManager	* m_pSignalsFilterManager;
	static UE_errCode_t EnableAllGkiFilter(int nDevice);
	static UE_errCode_t DisableAllGkiFilter(int nDevice);
	//GKI end
	//////////////////////////////////////////////////////////////////////////

	static UE_errCode_t StopProtocolStack(int nDevice, int timeout = DEFAULT_TIMEOUT);					//通过发送AT+CFUN=0去关闭手机协议栈.
	static UE_errCode_t StartProtocolStack(int nDevice, int timeout = DEFAULT_TIMEOUT);					//通过发送AT+CFUN=1去开启手机协议栈.
  //Richard added for Download DiagFilter to UE  ---  End		2011-10-13
  //////////////////////////////////////////////////////////////////////////

};
