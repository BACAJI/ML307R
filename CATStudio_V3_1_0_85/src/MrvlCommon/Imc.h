#pragma once
#include "MessageDefs.h"
#include "imc/ImcListener.h"
#include "imc/MessageReceiver.h"
#include "imc/MessageLoop.h"
#include "MrvlCommon/UEInfo.h"


#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

// CImc(CImcSender)类只有函数成员没有数据成员，因此适合作为函数局部对象来使用。
class DLL_EXPORT CImc
{
public:
   CImc();
   ~CImc();
   
   //! 获得Device的通信状态
   /**
   	@param iDevice
   	@param eConnectionStatus
   	@param eProtocol
   	@param eCommType
   	@return 
      @note 
   **/
   BOOL GetCommInfo(int iDevice, int& eConnectionStatus, int& eProtocol, int& eCommType);

   //! 在线模式下，获取一个已关闭icl文件的文件名
   /**
   	@param strFilename 
   	@param iFileIndex 指定文件的索引号。程序启动后保存的第一个icl文件的索引号是0，以此递增。
   	@return 成功获取到文件名返回TRUE，否则返回FALSE
      @note iFileIndex是输入输出参数，当该值为-1时，表示取最近保存的文件名，如果函数成功返回，
      @该值输出获取到的文件的索引号。
   **/
   BOOL GetLogFileName(CString& strFilename, __inout int& iFileIndex);

   //! 在线模式下，通过Index查询文件名
   /**
   	@param uMessageIndex 
   	@param strFilename 返回的文件名
   	@return 查询到对应的文件返回TRUE，否则返回FALSE
   **/
   BOOL GetLogFileNameByIndex(UINT64 uMesageIndex, CString& strFilename, int* pFileIndex=NULL, UINT64* pFirstIndex=NULL, UINT64* pLastIndex=NULL);

   //! 在线模式下，获取一个或多个已关闭icl文件的文件名
   /**
   	@param num 需要获取的文件名个数
   	@param fileArray 返回文件名的数组
   	@param iFileIndex 指定文件的索引值。以该索引值开始取后面的共num个文件。
   	@return 获取到至少一个文件名返回TRUE，否则返回FALSE
      @note 当iFileIndex不为-1时，fileArray中的文件对应的索引号依次为iFileIndex，iFileIndex+1，iFileIndex+2。。。
      @如果iFileIndex传入-1，则只取最近保存的num个文件名。
      @当程序成功返回后，iFileIndex输出fileArray中第一个文件的索引号。
   **/
   BOOL GetLogFilesName(int num, CStringArray& fileArray, int& iFileIndex);
  
   
   //! 离线模式下，获得已经载入的log信息
   /**
   	@param LogInf 返回的log信息，结构定义参见MessageDefs.h
   	@param lpszCallFrom 可选参数，用于写debuglog，主调模块的名称，比如_T("GraphViewer").
   	@return 如果取到了文件信息返回TRUE，否则返回FALSE（包括没有文件被载入的清空）。
      @note CMsgNewLogLoaded 是派生自CMessage，因此当函数返回后（无论成功或失败），需要调用DecRef()来释放。
   **/
   BOOL GetLoadedLogInf(CMsgGetLoadedLogInf& LogInf, LPCTSTR lpszCallFrom=_T("Null"));

   //! 双击跳转
   /**
   	@param uIndex 被双击的消息的MessageNumber
   	@param strSendingModuleName 被双击的View所属的模块的名称
   	@param iSendingModuleInstance 被双击的View的InstanceID（一个DLL可能有多个View的实例）
   	@return 
       @note 
   **/
   void ShowMessage(UINT64 uIndex, CString strSendingModuleName, int iSendingModuleInstance );
   void ShowMessage(UINT64 uIndex, CString strSendingModuleName, int iSendingModuleInstance, UINT8 uSimIndex);
   //! 
   /**
   	@param CString strFileName
   	@param int iDevice
   	@param int targetType
   	@return 
      @note 
   **/
   void OpenNvmEditor(CString strFileName, CString strStructname, int iDevice, int targetType, CString strSendingModule);

   //! 获得html log的目录
   /**
   	@return 
   	@note 
   **/
   CString GetLoggingPath();

   /** @brief 在线模式下关闭当前正在写的icl文件，同时打开一个新的icl文件。
    * 
    * 
    * @return 成功返回TRUE，失败返回FALSE
    * @see 
    * @note 
    */
   BOOL CloseOnlineLogFile();

   //! 
   /**
   	@param int iDevice
   	@param DWORD dwCpVerOld
   	@param DWORD dwApVerOld
   	@param DWORD dwCpVerOld
   	@param DWORD dwApVerOld
   	@return 
   	@note 
   **/
   void PostMsgDatabaseChanged(int iDevice, DWORD dwCpVerOld, DWORD dwApVerOld,  DWORD dwCpVerNew, DWORD dwApVerNew, DWORD dwCpNvmVerOld, DWORD dwApNvmVerOld, DWORD dwCpNvmVerNew, DWORD dwApNvmVerNew);

   //! 
   /**
   	@param int iDevice
   	@param int iNewStatus
   	@param int iProtocol
   	@return 
   	@note 
   **/
   void PostMsgDeviceChanged(int iDevice, int iNewStatus, int iProtocol);

   /** @brief 
    * 
    * 
    * @param  iDevice 
    * @return 
    * @see 
    * @note 
    */
   bool IsDatabaseLoaded(int iDevice);


   /** @brief 
    * 
    * 
    * @param  lpszSendingModule The name of the module which originally generated this messsage.
    * @param  bToModules Pass false to it if sending this message to Mainframe only.
    * @return 
    * @see 
    * @note 
    */
   void Start(LPCTSTR lpszSendingModule, bool bToModules=false);

   void Pause(LPCTSTR lpszSendingModule, bool bToModules=false);

   void Stop(LPCTSTR lpszSendingModule, bool bToModules=false);

   void Clear(LPCTSTR lpszSendingModule, bool bToModules=false);

   EPlayState GetPlayState();

   DWORD GetUECpVersion(int iDevice);
   DWORD GetUEApVersion(int iDevice);

   bool  GetUeCpInfo(int iDevice, CUeCpInfo& oUeCpInfo, CString strSendingModule=_T(""));

   bool  IsAutoUpdateDBEnabled();

   void  OpenOnlineNewLog(const CString & strLogName=_T(""));

   void  OnlineLogClosed(CString strLogPathName);

   void  ExportExtractedLog(CString strLogPathName);

   CString GetBinLogsPath(CString strSendingModule=_T(""));

   CView* GetActiveView();

	void OpenEntireFilter(int nDevice = -1);
	void CloseEntireFilter(int nDevice = -1);
	void SetDiagFilter(int nDevice, USHORT MessagId, int TargetType, bool bPass);
	void SetDiagFilter(int nDevice, const CString & strCat1, const CString & strCat2, const CString & strCat3, int TargetType, bool bPass);
	void SetDspFilter(int nDevice, int type, USHORT opCode, bool bPass);
	void SetDspFilter(int nDevice, int type, const CString & name, bool bPass);
	void SetGkiFilter(int nDevice, DWORD dwSigId, bool bPass);
	void SetGkiFilter(int nDevice, const CString & name, bool bPass);
	void OpenViewer(const CString & name, int type = 0);
	void CloseCurrentViewer(int type = 0);
	CString GetLogName();
	CString GetLogFullPathName();
	CString GetCurrentLogName();
	UINT64  GetLastLogMsgIdx();
	void InformLoggerUpdateDb();
	void EnableLogOperations();
	void DisableLogOperations();
	void ChangeDeviceState(int device, bool deviceEnabled, CCommSettings* commSettings);
};

typedef CMessageReceiver   CImcReceiver;
typedef CImc               CImcSender;