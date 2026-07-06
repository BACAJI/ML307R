#pragma once
#include <psapi.h>
#include "../GeneralMacroDefine.h"

#pragma comment(lib, "psapi.lib")
class CATCORE_DLLEXPORT CSystemInfo 
{
private:
  CSystemInfo();
  CString m_strOsVer;
public:
  static CSystemInfo* Instance();
  
  ~CSystemInfo();

  // Return the number of logical processors/cores on the current machine.
  int NumberOfProcessors();

  // Return the number of logical processors/cores on the current machine.
  CString NumberOfProcessorString();

  // Return the number of bytes of physical memory on the current machine.
  __int64 PhysicalMemory();

  // Return the number of megabytes of physical memory on the current machine.
  int PhysicalMemoryMB() {
    return static_cast<int>(PhysicalMemory() / 1024 / 1024);
  }

  // Return the number of megabytes of physical memory on the current machine.
  __int64 AvailableMemory();

  // Return the number of megabytes of physical memory on the current machine.
  int AvailableMemoryMB() {
    return static_cast<int>(AvailableMemory() / 1024 / 1024);
  }

  // Return the available disk space in bytes on the volume containing |path|,
  // or -1 on failure.
  static __int64 GetFreeDiskSpace(LPCTSTR path);

  // Return the available disk space in giga bytes on the volume containing |path|,
  static float   GetFreeDiskSpaceGB(LPCTSTR path=NULL);

  // Returns the name of the host operating system.
  CString OSName();

  // Returns the version of the host operating system.
  CString OSVersion();

  // Returns the CPU architecture of the system. Exact return value may differ
  // across platforms.
  CString CPUArchitecture();

  // Returns whether the process is running under WOW64; if true, CPUArchitecture() returns x86 under WOW64
  BOOL IsWow64() { return m_bWow64; }

  // Return the smallest amount of memory (in bytes) which the VM system will
  // allocate.
  DWORD VMAllocationGranularity();


  // Return the system time string.
  CString SystemTime();

  // Return build number of operating system.
  CString OSBuildNumberString();

  // Return build number of operating system.
  DWORD   OSBuildNumber();

 /* typedef struct _PROCESS_MEMORY_COUNTERS {
    DWORD  cb;
    DWORD  PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
  } PROCESS_MEMORY_COUNTERS, *PPROCESS_MEMORY_COUNTERS;*/

  // The number of page faults.
  static DWORD PageFaultCount();

  // The peak working set size, in bytes.
  static SIZE_T WorkingSetSize();

  static SIZE_T WorkingSetSizeMB();

  // The peak working set size, in bytes.
  static SIZE_T PeakWorkingSetSize();

  static SIZE_T CommitSize();

  // 
  static LONGLONG GetFrequency(DWORD sleepTime);

  //
  static int GetCPUFrequencyMHz(DWORD sleepTime){
     return (int)(GetFrequency(sleepTime)/1000/1000);
  }
   
  static int GetCPUPerformance(DWORD sleepTime){
     int nCPU = CSystemInfo::Instance()->NumberOfProcessors();
     int nMHz = GetCPUFrequencyMHz(sleepTime);
     float fMHz = (float)(nMHz/1000.0);
     fMHz = (fMHz*fMHz)/9; //0.5 ~ 1.0
     int nPerf = (int)(fMHz * 50 * nCPU);
     return nPerf;
  }

  /*
  // The current working set size, in bytes.
  SIZE_T QuotaPeakPagedPoolUsage();
    The peak paged pool usage, in bytes.
    QuotaPagedPoolUsage
    The current paged pool usage, in bytes.
    QuotaPeakNonPagedPoolUsage
    The peak nonpaged pool usage, in bytes.
    QuotaNonPagedPoolUsage
    The current nonpaged pool usage, in bytes.
    PagefileUsage
    The Commit Charge value in bytes for this process. Commit Charge is the total amount of memory that the memory manager has committed for a running process.
    PeakPagefileUsage
    The peak value in bytes of the Commit Charge during the lifetime of this process.
  */

private:
  SYSTEM_INFO m_sysinf;
  OSVERSIONINFOEX m_versionInfEx;
  BOOL m_bWow64;
};
