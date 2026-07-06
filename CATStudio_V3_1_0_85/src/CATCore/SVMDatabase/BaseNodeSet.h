
#pragma once
// BaseNodeSet.h : header file
//

#include "../../CATCore/Converter/DB/AdoRecordsetEx.h"
#include "SvmDatabase.h"
#include "CacheStrTable.h"

class DLL_EXPORT CBaseNodeSet : public CADORecordsetEx 
{
public:
	CBaseNodeSet(int nDeviceIndex,int nStrType,CADODatabase* pDatabase = NULL);	

	virtual void MoveFirst();
	virtual void MoveNext();
	virtual void MoveLast();
	virtual void MovePrev() { MovePrevious(); }	// For DAO Compatibility
	virtual void MovePrevious();	// For DAO Compatibility
	virtual void Move(long nMove);
		
	virtual long GetAbsolutePosition();
	virtual void SetAbsolutePosition(int nPosition);
	virtual bool IsEOF();
	virtual bool IsBOF();

	virtual CString GetDefaultDBName();
	virtual void SetDBName(const CString& strDBFile, const int nFileType);

	virtual void ParseTxtRec(CString strTempRec, int strType = CSvmDb::kNone)=0;
	virtual int GetStrType(){ return m_nStrType; }

	virtual int GetDeviceIndex(){return m_nDeviceIndex;};
protected:
	CString m_strDBFile;
	int		m_nFileType;
	int		m_nDeviceIndex;
	CCacheStrTable/*CStdioFile*/ m_fTxtFile;
	int m_nStrType;
};
