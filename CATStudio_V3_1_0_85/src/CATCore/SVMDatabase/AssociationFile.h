// AssociationFile.h: interface for the CAssociationFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSOCIATIONFILE_H__8AA97B31_F1F7_4396_BFF4_BAADEC7E29F0__INCLUDED_)
#define AFX_ASSOCIATIONFILE_H__8AA97B31_F1F7_4396_BFF4_BAADEC7E29F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAssociationFile : public CStdioFile  
{
public:
	CAssociationFile();
	virtual ~CAssociationFile();

	void CacheTable(CMapStringToOb &StrRuleMap);

private:
	BOOL OpenAssocFile();

};

#endif // !defined(AFX_ASSOCIATIONFILE_H__8AA97B31_F1F7_4396_BFF4_BAADEC7E29F0__INCLUDED_)
