#ifndef XMLDATA_H
#define XMLDATA_H

#include <list>
#include <vector>
#include <map>
#include <set>
#include <algorithm> 

using namespace std;
#include <atlbase.h>


#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <string>
#include <TCHAR.H>

#ifdef UNICODE
#define _tstring	wstring
#define _ttoupper	towupper
#define _ttolower	tolower
#else
#define _tstring	string
#define _ttoupper	toupper
#define _ttolower	towlower
#endif

std::_tstring w2T(const wchar_t* str);
std::wstring T2w(const TCHAR* str);


bool FileExist(const TCHAR* path);

class CXmlNodeData{
	private:
		enum TYPE{ROOT,CHILD,SUPPER};
		TYPE type;
		_tstring src;
	public:
		CXmlNodeData* pParentNode;
		_tstring id;
		_tstring name;
		_tstring value;
		map<_tstring,_tstring> attributes;
		list<CXmlNodeData*> childNodes;
		map<_tstring,CXmlNodeData*> childNodesIdMap;
	private:
		CXmlNodeData(IXMLDOMNode* pIXMLDOMNode,CXmlNodeData* _pParentNode,TYPE _type,_tstring _src);
		CXmlNodeData(const TCHAR* rootName);
		CXmlNodeData(CXmlNodeData* _pParentNode,TYPE _type,_tstring _src,_tstring id,_tstring name,_tstring value);
		bool SaveToDom(IXMLDOMDocument* pDoc,IXMLDOMElement* pParent,int level);
	public:
		~CXmlNodeData();
		static CXmlNodeData* LoadData(const TCHAR* filePath);
		static CXmlNodeData* LoadData(list<_tstring> filePathList,const TCHAR* rootName);
		static CXmlNodeData* LoadDataByString(const TCHAR* str);
		static CXmlNodeData* LoadDataByUrl(const TCHAR* url);
		static CXmlNodeData* LoadDataByData(BYTE* pData,DWORD dataLength);
		static CXmlNodeData* NewDocument(const TCHAR* filePath,_tstring id,_tstring _name,_tstring _value=_T(""));
		static bool CreateDocumentObject(IXMLDOMDocument** ppXMLDOMDocument,const TCHAR* rootName,list<CXmlNodeData*>& childNodes);
		static bool GetDocumentObjectData(IXMLDOMDocument* pXMLDOMDocument,vector<BYTE>* pData);
	public:
		CXmlNodeData* AddChild(_tstring id,_tstring name,_tstring value=_T(""));
		void SetAttribute(const TCHAR* attributeName,const TCHAR* attributeValue);
		void SetAttributeInt(const TCHAR* attributeName,int attributeValue);
		void SetAttributeLong(const TCHAR* attributeName,long attributeValue);
		void SetAttributeDouble(const TCHAR* attributeName,double attributeValue);
		void SetAttributeBool(const TCHAR* attributeName,bool attributeValue);
		bool GetChildBool(const TCHAR* szChildName);
		double GetChildDouble(const TCHAR* szChildName);
		_tstring GetChildText(const TCHAR* szChildName);
		long GetChildLong(const TCHAR* szChildName);
		int GetChildInt(const TCHAR* szChildName);
		void RemoveAttribute(const TCHAR* attributeName);
		void Remove();
		CXmlNodeData* FindChild(const TCHAR* path);
		CXmlNodeData* FindChildById(const TCHAR* path);
		_tstring GetAttributeValue(const TCHAR* attributeName,bool* pResult=NULL);
		_tstring GetAttributeText(const TCHAR* attributeName,_tstring defValue=_T(""),bool* pResult=NULL);
		int GetAttributeInt(const TCHAR* attributeName,int defValue=0,bool* pResult=NULL);
		long GetAttributeLong(const TCHAR* attributeName,long defValue=0,bool* pResult=NULL);
		double GetAttributeDouble(const TCHAR* attributeName,double defValue=0,bool* pResult=NULL);
		bool GetAttributeBool(const TCHAR* attributeName,bool defValue=false,bool* pResult=NULL);
		bool Save();
		bool SaveTo(const TCHAR* filePath);
		bool GetTextData(vector<BYTE>* pData);
		_tstring GetText();
		CXmlNodeData* GetRoot();
		_tstring GetPath();
		_tstring GetSrc();
	private:
		bool GetDocumentObject(IXMLDOMDocument** ppXMLDOMDocument);
		bool DoSaveTo(const TCHAR* filePath);
		bool DoGetTextData(vector<BYTE>* pData);
		_tstring DoGetText();

};


#endif