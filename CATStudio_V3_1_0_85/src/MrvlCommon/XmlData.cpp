#include "stdafx.h"
#include "XmlData.h"
/*#include "func.h"*/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void ReplaceAll(_tstring &base,const _tstring &needle, const _tstring &s){
	unsigned long lastpos = 0, thispos;
	while ((thispos = base.find(needle, lastpos)) != _tstring::npos){
		base.replace(thispos, needle.length(), s);
		lastpos = thispos+s.length() ;
	}
}
void TrimFilePath(_tstring & fp){
	ReplaceAll(fp,_T("/"),_T("\\"));
	while(_tcsstr(fp.c_str(),_T("\\\\"))){
		ReplaceAll(fp,_T("\\\\"),_T("\\"));
	}
}
_tstring GetFileDir(const TCHAR* filePath){
	_tstring fp=filePath;
	TrimFilePath(fp);
	int i=fp.rfind(_T("\\"));
	if(i!=_tstring::npos){
		return fp.substr(0,i);
	}
	else{
		return fp;
	}
}
//VectorÅúÁ¿Ìí¼Ó
void VectorAddBYTE(vector<BYTE>& vec,BYTE* data,int size){
	if( size <= 0 )
	{
		return;
	}

	size_t CurSize = vec.size();
	vec.resize( CurSize + size );
	memcpy( &(vec[CurSize]), data, size );
}

CXmlNodeData* CXmlNodeData::FindChild(const TCHAR* path){
	_tstring allPath=path;
	ReplaceAll(allPath,_T("/"),_T("\\"));
	while(allPath.find(_T("\\\\"))!=_tstring::npos){
		ReplaceAll(allPath,_T("\\\\"),_T("\\"));
	}
	//transform(allPath.begin(),allPath.end(),allPath.begin(),_ttolower);

	size_t i=allPath.find(_T("\\"));
	_tstring currentPath=_T("");
	_tstring nextPath=_T("");

	if(i==_tstring::npos) currentPath=allPath;
	else{
		currentPath=allPath.substr(0,i);
		nextPath=allPath.substr(i+1);
	}

	list<CXmlNodeData*>::iterator it;
	for(it=childNodes.begin();it!=childNodes.end();it++){
		if((*it)->name==currentPath){
			if(nextPath==_T("")) return (*it);
			else return (*it)->FindChild(nextPath.c_str());
		}
	}
	return NULL;
}

CXmlNodeData* CXmlNodeData::FindChildById(const TCHAR* path){
	_tstring allPath=path;
	ReplaceAll(allPath,_T("/"),_T("\\"));
	while(allPath.find(_T("\\\\"))!=_tstring::npos){
		ReplaceAll(allPath,_T("\\\\"),_T("\\"));
	}

	size_t i=allPath.find(_T("\\"));
	_tstring currentPath=_T("");
	_tstring nextPath=_T("");

	if(i==_tstring::npos) currentPath=allPath;
	else{
		currentPath=allPath.substr(0,i);
		nextPath=allPath.substr(i+1);
	}

	map<_tstring,CXmlNodeData*>::iterator it=childNodesIdMap.find(currentPath);
	if(it!=childNodesIdMap.end()){
		if(nextPath==_T("")) return it->second;
		else return (it->second)->FindChildById(nextPath.c_str());
	}
	else{
		return NULL;
	}
}
bool FileExist(const TCHAR* path){
	return (GetFileAttributes(path)!=0xFFFFFFFF);
}

std::wstring T2w(const TCHAR* str){
#ifdef UNICODE
	return str;
#else
	return a2w(str);
#endif
}
std::_tstring w2T(const wchar_t* str){
#ifdef UNICODE
	return str;
#else
	return w2a(str);
#endif
}
CXmlNodeData* CXmlNodeData::LoadData(const TCHAR* filePath){
	if(!filePath) return NULL;
	if(!FileExist(filePath)) return NULL;
	CXmlNodeData* pData=NULL;
	CoInitialize(NULL);
	try {
		CComPtr<IXMLDOMDocument> pXml;
		HRESULT hr=pXml.CoCreateInstance(__uuidof(DOMDocument));
		if(SUCCEEDED(hr)){
			VARIANT_BOOL bSuccess = VARIANT_FALSE;
			hr=pXml->load(CComVariant(filePath),&bSuccess);
			if(SUCCEEDED(hr)&&(bSuccess==VARIANT_TRUE)){
				CComPtr<IXMLDOMElement> pRoot;
				hr=pXml->get_documentElement(&pRoot);
				pData=new CXmlNodeData(pRoot,NULL,ROOT,filePath);
			}
		}
	}
	catch(...) {
	}
	CoUninitialize();
	return pData;
}
CXmlNodeData* CXmlNodeData::LoadData(list<_tstring> filePathList,const TCHAR* rootName){
	CXmlNodeData* pRet=new CXmlNodeData(rootName);
	list<_tstring>::iterator it;
	for(it=filePathList.begin();it!=filePathList.end();++it){
		CXmlNodeData* pChild=LoadData((*it).c_str());
		if(pChild){
			pRet->childNodes.push_back(pChild);
			if(pChild->id!=_T("")) pRet->childNodesIdMap[pChild->id]=pChild;
		}
		else{
			delete pRet;
			pRet=NULL;
			break;
		}
	}
	return pRet;
}
CXmlNodeData* CXmlNodeData::LoadDataByString(const TCHAR* str){
	CXmlNodeData* pData=NULL;
	CoInitialize(NULL);
	try {
		CComPtr<IXMLDOMDocument> pXml;
		HRESULT hr=pXml.CoCreateInstance(__uuidof(DOMDocument));
		if(SUCCEEDED(hr)){
			VARIANT_BOOL bSuccess = VARIANT_FALSE;
			hr=pXml->loadXML(CComBSTR(T2w(str).c_str()),&bSuccess);
			if(SUCCEEDED(hr)&&(bSuccess==VARIANT_TRUE)){
				CComPtr<IXMLDOMElement> pRoot;
				hr=pXml->get_documentElement(&pRoot);
				pData=new CXmlNodeData(pRoot,NULL,ROOT,_T(""));
			}
		}
	}
	catch(...) {
	}
	CoUninitialize();
	return pData;
}
CXmlNodeData* CXmlNodeData::LoadDataByUrl(const TCHAR* url){
	CXmlNodeData* pData=NULL;
	CoInitialize(NULL);
	try {
		CComPtr<IXMLDOMDocument> pXml;
		HRESULT hr=pXml.CoCreateInstance(__uuidof(DOMDocument));
		if(SUCCEEDED(hr)){
			VARIANT_BOOL bSuccess = VARIANT_FALSE;
			hr=pXml->load(CComVariant(url),&bSuccess);
			if(SUCCEEDED(hr)&&(bSuccess==VARIANT_TRUE)){
				CComPtr<IXMLDOMElement> pRoot;
				hr=pXml->get_documentElement(&pRoot);
				pData=new CXmlNodeData(pRoot,NULL,ROOT,_T(""));
			}
		}
	}
	catch(...) {
	}
	CoUninitialize();
	return pData;
}
CXmlNodeData* CXmlNodeData::LoadDataByData(BYTE* pData,DWORD dataLength){
	if(!pData||dataLength==0) return NULL;
	CXmlNodeData* pXmlData=NULL;
	CoInitialize(NULL);
	CComPtr<IStream> pStream;
	CreateStreamOnHGlobal(NULL,TRUE,&pStream);
	if(pStream){
		DWORD wn=0;
		if(SUCCEEDED(pStream->Write(pData,dataLength,&wn))&&wn==dataLength){
			ULARGE_INTEGER ui = {0};
			LARGE_INTEGER pos={0};
			pStream->Seek(pos,STREAM_SEEK_SET,&ui);
			if(ui.LowPart==0&&ui.HighPart==0){
				CComVariant varStream=pStream;
				try {
					CComPtr<IXMLDOMDocument> pXml;
					HRESULT hr=pXml.CoCreateInstance(__uuidof(DOMDocument));
					if(SUCCEEDED(hr)){
						VARIANT_BOOL bSuccess = VARIANT_FALSE;
						hr=pXml->load(varStream,&bSuccess);
						if(SUCCEEDED(hr)&&(bSuccess==VARIANT_TRUE)){
							CComPtr<IXMLDOMElement> pRoot;
							hr=pXml->get_documentElement(&pRoot);
							pXmlData=new CXmlNodeData(pRoot,NULL,ROOT,_T(""));
						}
					}
				}
				catch(...) {
				}
			}
		}
	}
	CoUninitialize();
	return pXmlData;
}
CXmlNodeData* CXmlNodeData::NewDocument(const TCHAR* filePath,_tstring id,_tstring _name,_tstring _value){
	return new CXmlNodeData(NULL,ROOT,filePath,id,_name,_value);
}
bool CXmlNodeData::CreateDocumentObject(IXMLDOMDocument** ppXMLDOMDocument,const TCHAR* rootName,list<CXmlNodeData*>& childNodes){
	if(!ppXMLDOMDocument) return false;
	*ppXMLDOMDocument=NULL;
	try {
		CComPtr<IXMLDOMDocument> pXml;
		HRESULT hr=pXml.CoCreateInstance(__uuidof(DOMDocument));
		if(!SUCCEEDED(hr)) return false;
		CComPtr<IXMLDOMProcessingInstruction> pProcessingInstruction;
		hr=pXml->createProcessingInstruction(L"xml",L"version='1.0' encoding='utf-8'",&pProcessingInstruction);
		if(!SUCCEEDED(hr)) return false;
		hr=pXml->appendChild(pProcessingInstruction,NULL);
		if(!SUCCEEDED(hr)) return false;

		CComPtr<IXMLDOMElement> pRoot;
		CComBSTR name_bstr=rootName; //wtot;
		hr=pXml->createElement(name_bstr,&pRoot);
		if(!SUCCEEDED(hr)) return false;

		hr=pXml->appendChild(pRoot,NULL);
		if(!SUCCEEDED(hr)) return false;

		if(childNodes.size()>0){
			list<CXmlNodeData*>::iterator it_cn;
			for(it_cn=childNodes.begin();it_cn!=childNodes.end();it_cn++){
				if(!((*it_cn)->SaveToDom(pXml,pRoot,1))) return false;
			}

			CComPtr<IXMLDOMText> pTextChild;
			hr=pXml->createTextNode(L"\r\n",&pTextChild);
			if(!SUCCEEDED(hr)) return false;
			hr=pRoot->appendChild(pTextChild,NULL);
			if(!SUCCEEDED(hr)) return false;
		}
		*ppXMLDOMDocument=pXml.Detach();
		return true;
	}
	catch(...) {
	}
	return false;
}
bool CXmlNodeData::GetDocumentObjectData(IXMLDOMDocument* pXMLDOMDocument,vector<BYTE>* pData){
	if(!pData) return false;
	try {
		CComPtr<IXMLDOMDocument> pXml=pXMLDOMDocument;
		if(pXml){
			CComPtr<IStream> pStream;
			CreateStreamOnHGlobal(NULL,TRUE,&pStream);
			if(pStream){
				CComVariant varStream=pStream;
				if(SUCCEEDED(pXml->save(varStream))){
					LARGE_INTEGER li;
					li.HighPart =0;
					li.LowPart =0;
					ULARGE_INTEGER ulnewpos;
					pStream->Seek( li,STREAM_SEEK_SET,&ulnewpos);

					ULONG uReadCount=1;
					BYTE buf[1024];
					while(uReadCount>0){
						pStream->Read(buf,sizeof(buf),&uReadCount);
						if(uReadCount>0){
							VectorAddBYTE(*pData,buf,uReadCount);
						}
					}
					return true;
				}
			}
		}
	}
	catch(...) {
	}
	return false;
}

CXmlNodeData::CXmlNodeData(IXMLDOMNode* pIXMLDOMNode,CXmlNodeData* _pParentNode,TYPE _type,_tstring _src){
	pParentNode=_pParentNode;
	type=_type;
	src=_src;
	id=_T("");
	CComPtr<IXMLDOMNode> pNode(pIXMLDOMNode);

	CComBSTR bstr_name;
	pNode->get_nodeName(&bstr_name);
	name=bstr_name;
	//transform(name.begin(),name.end(),name.begin(),_ttolower);

	CComPtr<IXMLDOMNamedNodeMap> pAtts = NULL;
	pNode->get_attributes(&pAtts);

	if(pAtts){
		CComPtr<IXMLDOMNode> pAttNode = NULL;
		pAtts->nextNode(&pAttNode);
		while(pAttNode){
			CComBSTR attname;
			pAttNode->get_nodeName(&attname);
			CComBSTR attvale;
			pAttNode->get_text(&attvale);

			_tstring _attname=attname;
			//transform(_attname.begin(),_attname.end(),_attname.begin(),_ttolower);
			attributes[_attname]=_tstring(attvale);
			if(_attname==_T("id")) id=attvale;
			pAttNode=NULL;
			pAtts->nextNode(&pAttNode);
		}
	}

	CComPtr<IXMLDOMNodeList> pChildList;
	pNode->get_childNodes(&pChildList);
	
	if(pChildList){
		CComPtr<IXMLDOMNode> pChildNode;
		pChildList->nextNode(&pChildNode);
		while(pChildNode){
			DOMNodeType nt;
			pChildNode->get_nodeType(&nt);
			if(nt!=NODE_TEXT){
				CXmlNodeData* pCXmlNodeData=new CXmlNodeData(pChildNode,this,CHILD,_T(""));
				childNodes.push_back(pCXmlNodeData);
				if(pCXmlNodeData->id!=_T("")) childNodesIdMap[pCXmlNodeData->id]=pCXmlNodeData;
			}
			else{
				CComBSTR bstr_value;
				pChildNode->get_text(&bstr_value);
				value=bstr_value;
			}
			pChildNode=NULL;
			pChildList->nextNode(&pChildNode);
		}
	}
}
CXmlNodeData::CXmlNodeData(const TCHAR* rootName){
	pParentNode=NULL;
	type=SUPPER;
	src=_T("");
	name=rootName;
	//transform(name.begin(),name.end(),name.begin(),_ttolower);
	id=rootName;
	value=_T("");
}
CXmlNodeData::CXmlNodeData(CXmlNodeData* _pParentNode,TYPE _type,_tstring _src,_tstring _id,_tstring _name,_tstring _value){
	pParentNode=_pParentNode;
	type=_type;
	src=_src;
	name=_name;
	//transform(name.begin(),name.end(),name.begin(),_ttolower);
	id=_id;
	value=_value;
	if(id!=_T("")) SetAttribute(_T("id"),id.c_str());
}

CXmlNodeData::~CXmlNodeData()
{
	list<CXmlNodeData*>::iterator it;
	for(it=childNodes.begin();it!=childNodes.end();++it)
	{
		if(*it)
		{
			delete *it;
			*it=NULL;
		}
	}
}
_tstring CXmlNodeData::GetAttributeValue(const TCHAR* attributeName,bool* pResult){
	_tstring attName=attributeName;
	//transform(attName.begin(),attName.end(),attName.begin(),_ttolower);

	map<_tstring,_tstring>::iterator it=attributes.find(attName);
	if(it!=attributes.end()){
		if(pResult) (*pResult)=true;
		return it->second;
	}
	else{
		if(pResult) (*pResult)=false;
		return _T("");
	}
}

CXmlNodeData* CXmlNodeData::AddChild(_tstring id,_tstring name,_tstring value){
	CXmlNodeData* pNode=new CXmlNodeData(this,CHILD,_T(""),id,name,value);
	childNodes.push_back(pNode);
	if(id!=_T("")) childNodesIdMap[id]=pNode;
	return pNode;
}
void CXmlNodeData::SetAttribute(const TCHAR* attributeName,const TCHAR* attributeValue){
	_tstring attName=attributeName;
	//transform(attName.begin(),attName.end(),attName.begin(),_ttolower);
	attributes[attributeName]=attributeValue;
}

void CXmlNodeData::SetAttributeInt(const TCHAR* attributeName,int attributeValue){
	TCHAR ch[50];
	_stprintf(ch,_T("%d"),attributeValue);
	SetAttribute(attributeName,ch);
}
void CXmlNodeData::SetAttributeLong(const TCHAR* attributeName,long attributeValue){
	TCHAR ch[50];
	_stprintf(ch,_T("%d"),attributeValue);
	SetAttribute(attributeName,ch);
}
void CXmlNodeData::SetAttributeDouble(const TCHAR* attributeName,double attributeValue){
	TCHAR ch[50];
	_stprintf(ch,_T("%f"),attributeValue);
	SetAttribute(attributeName,ch);
}
void CXmlNodeData::SetAttributeBool(const TCHAR* attributeName,bool attributeValue){
	SetAttribute(attributeName,attributeValue?_T("true"):_T("false"));
}
void CXmlNodeData::RemoveAttribute(const TCHAR* attributeName){
	attributes.erase(attributeName);
}
int CXmlNodeData::GetChildInt(const TCHAR* szChildName)
{
	int nRet = 0;

	CXmlNodeData* pXmlNode = FindChild(szChildName);
	if ( pXmlNode)
	{
		nRet = _ttoi(pXmlNode->value.c_str());
	}
	return nRet;
}
long CXmlNodeData::GetChildLong(const TCHAR* szChildName)
{
	long lRet = 0;
	CXmlNodeData* pXmlNode = FindChild(szChildName);
	if ( pXmlNode)
	{
		lRet = _ttol(pXmlNode->value.c_str());
	}
	return lRet;
}
_tstring CXmlNodeData::GetChildText(const TCHAR* szChildName)
{
	_tstring strRet = _T("");
	CXmlNodeData* pXmlNode = FindChild(szChildName);
	if ( pXmlNode)
	{
		strRet = pXmlNode->value.c_str();
	}
	return strRet;
}
double CXmlNodeData::GetChildDouble(const TCHAR* szChildName)
{
	double dRet = 0.0;
	CXmlNodeData* pXmlNode = FindChild(szChildName);
	if ( pXmlNode)
	{
		dRet = _tcstod(pXmlNode->value.c_str(),NULL);
	}
	return dRet;
}
bool CXmlNodeData::GetChildBool(const TCHAR* szChildName)
{
	_tstring strRet = _T("");
	CXmlNodeData* pXmlNode = FindChild(szChildName);
	if ( pXmlNode)
	{
		strRet = pXmlNode->value.c_str();
	}

	transform(strRet.begin(),strRet.end(),strRet.begin(),_ttolower);
	if(strRet.find(_T("true"))!=_tstring::npos) return true;
	if(strRet.find(_T("false"))!=_tstring::npos) return false;
	if(strRet==_T("1")) return true;
	if(strRet==_T("0")) return false;
}
void CXmlNodeData::Remove(){
	if(pParentNode){
		if(id!=_T("")) pParentNode->childNodesIdMap.erase(id);
		list<CXmlNodeData*>::iterator it;
		for(it=pParentNode->childNodes.begin();it!=pParentNode->childNodes.end();it++){
			if((*it)==this){
				pParentNode->childNodes.erase(it);
				break;
			}
		}
	}
	delete this;
}
_tstring CXmlNodeData::GetAttributeText(const TCHAR* attributeName,_tstring defValue,bool* pResult){
	bool bRet=false;
	_tstring textValue=GetAttributeValue(attributeName,&bRet);
	if(pResult) (*pResult)=bRet;
	return bRet?textValue:defValue;
}
int CXmlNodeData::GetAttributeInt(const TCHAR* attributeName,int defValue,bool* pResult){
	bool bRet=false;
	_tstring textValue=GetAttributeValue(attributeName,&bRet);
	if(pResult) (*pResult)=bRet;
	return bRet?_ttoi(textValue.c_str()):defValue;
}
long CXmlNodeData::GetAttributeLong(const TCHAR* attributeName,long defValue,bool* pResult){
	bool bRet=false;
	_tstring textValue=GetAttributeValue(attributeName,&bRet);
	if(pResult) (*pResult)=bRet;
	return bRet?_ttol(textValue.c_str()):defValue;
}
double CXmlNodeData::GetAttributeDouble(const TCHAR* attributeName,double defValue,bool* pResult){
	bool bRet=false;
	_tstring textValue=GetAttributeValue(attributeName,&bRet);
	if(pResult) (*pResult)=bRet;
	return bRet?_tcstod(textValue.c_str(),NULL):defValue;
}
bool CXmlNodeData::GetAttributeBool(const TCHAR* attributeName,bool defValue,bool* pResult){
		bool bRet=false;
	_tstring textValue=GetAttributeValue(attributeName,&bRet);
	if(pResult) (*pResult)=bRet;
	if(!bRet) return defValue;

	transform(textValue.begin(),textValue.end(),textValue.begin(),_ttolower);
	if(textValue.find(_T("true"))!=_tstring::npos) return true;
	if(textValue.find(_T("false"))!=_tstring::npos) return false;
	if(textValue==_T("1")) return true;
	if(textValue==_T("0")) return false;

	if(pResult) (*pResult)=false;
	return defValue;
}
bool CXmlNodeData::Save(){
	if(type!=ROOT){
		CXmlNodeData* pRoot=GetRoot();
		if(!pRoot) return false;
		return pRoot->Save();
	}
	else{
		if(src==_T("")) return false;
		else return SaveTo(src.c_str());
	}
}
bool CXmlNodeData::SaveToDom(IXMLDOMDocument* pDoc,IXMLDOMElement* pParent,int level){
	CComPtr<IXMLDOMDocument> pXml=pDoc;
	CComPtr<IXMLDOMElement> pParentElement=pParent;
	CComPtr<IXMLDOMElement> pElement;

	CComBSTR endlText=L"\r\n";
	for(int i=0;i<level;++i){
		endlText.Append(L"\t");
	}

	CComPtr<IXMLDOMText> pText;
	HRESULT hr=pXml->createTextNode(endlText,&pText);
	if(!SUCCEEDED(hr)) return false;
	hr=pParent->appendChild(pText,NULL);
	if(!SUCCEEDED(hr)) return false;

	CComBSTR name_bstr=name.c_str(); 
	hr=pXml->createElement(name_bstr,&pElement);
	if(!SUCCEEDED(hr)) return false;

	map<_tstring,_tstring>::iterator it_att;
	for(it_att=attributes.begin();it_att!=attributes.end();it_att++){
		CComBSTR attname_bstr=it_att->first.c_str(); 
		hr=pElement->setAttribute(attname_bstr,CComVariant(it_att->second.c_str()));
		if(!SUCCEEDED(hr)) return false;
	}


	hr=pParent->appendChild(pElement,NULL);
	if(!SUCCEEDED(hr)) return false;

	if(childNodes.size()>0){

		list<CXmlNodeData*>::iterator it_cn;
		for(it_cn=childNodes.begin();it_cn!=childNodes.end();it_cn++){
			if(!((*it_cn)->SaveToDom(pXml,pElement,level+1))) return false;
		}

		CComPtr<IXMLDOMText> pTextChild;
		hr=pXml->createTextNode(endlText,&pTextChild);
		if(!SUCCEEDED(hr)) return false;
		hr=pElement->appendChild(pTextChild,NULL);
		if(!SUCCEEDED(hr)) return false;
	}
	if(value!=_T("")){
		pElement->put_text(CComBSTR(value.c_str()));
	}

	return true;
}
bool CXmlNodeData::SaveTo(const TCHAR* filePath){
	if(type!=ROOT){
		CXmlNodeData* pRoot=GetRoot();
		if(!pRoot) return false;
		return pRoot->SaveTo(filePath);
	}
	else{
		if(!filePath) return false;

		CoInitialize(NULL);
		bool bRet=DoSaveTo(filePath);
		CoUninitialize();
		return bRet;
	}
}
bool CXmlNodeData::GetTextData(vector<BYTE>* pData){
	if(!pData) return false;
	if(type!=ROOT){
		CXmlNodeData* pRoot=GetRoot();
		if(!pRoot) return false;
		return pRoot->GetTextData(pData);
	}
	else{
		CoInitialize(NULL);
		bool bRet=DoGetTextData(pData);
		CoUninitialize();
		return bRet;
	}
}
_tstring CXmlNodeData::GetText(){
	if(type!=ROOT){
		CXmlNodeData* pRoot=GetRoot();
		if(!pRoot) _T("");
		return pRoot->GetText();
	}
	else{
		CoInitialize(NULL);
		_tstring retStr=DoGetText();
		CoUninitialize();
		return retStr;
	}
}
bool CXmlNodeData::GetDocumentObject(IXMLDOMDocument** ppXMLDOMDocument){
	if(!ppXMLDOMDocument) return false;
	*ppXMLDOMDocument=NULL;
	try {
		CComPtr<IXMLDOMDocument> pXml;
		HRESULT hr=pXml.CoCreateInstance(__uuidof(DOMDocument));
		if(!SUCCEEDED(hr)) return false;
		CComPtr<IXMLDOMProcessingInstruction> pProcessingInstruction;
		hr=pXml->createProcessingInstruction(L"xml",L"version='1.0' encoding='utf-8'",&pProcessingInstruction);
		if(!SUCCEEDED(hr)) return false;
		hr=pXml->appendChild(pProcessingInstruction,NULL);
		if(!SUCCEEDED(hr)) return false;

		CComPtr<IXMLDOMElement> pRoot;
		CComBSTR name_bstr=name.c_str(); //wtot;
		hr=pXml->createElement(name_bstr,&pRoot);
		if(!SUCCEEDED(hr)) return false;

		map<_tstring,_tstring>::iterator it_att;
		for(it_att=attributes.begin();it_att!=attributes.end();it_att++){
			CComBSTR attname_bstr=it_att->first.c_str(); //wtot;
			hr=pRoot->setAttribute(attname_bstr,CComVariant(it_att->second.c_str()));//wtot;
			if(!SUCCEEDED(hr)) return false;
		}
		hr=pXml->appendChild(pRoot,NULL);
		if(!SUCCEEDED(hr)) return false;

		if(childNodes.size()>0){
			list<CXmlNodeData*>::iterator it_cn;
			for(it_cn=childNodes.begin();it_cn!=childNodes.end();it_cn++){
				if(!((*it_cn)->SaveToDom(pXml,pRoot,1))) return false;
			}

			CComPtr<IXMLDOMText> pTextChild;
			hr=pXml->createTextNode(L"\r\n",&pTextChild);
			if(!SUCCEEDED(hr)) return false;
			hr=pRoot->appendChild(pTextChild,NULL);
			if(!SUCCEEDED(hr)) return false;
		}
		if(value!=_T("")){
			pRoot->put_nodeValue(CComVariant(value.c_str()));
		}
		*ppXMLDOMDocument=pXml.Detach();
		return true;
	}
	catch(...) {
	}
	return false;
}
void SplitString(_tstring str,_tstring regex,vector<_tstring>& strArray){
	strArray.resize(0);
	int from=0;
	while(true){
		int index=str.find(regex,from);
		if(index!=(int)_tstring::npos){
			strArray.push_back(str.substr(from,index-from));
			from=index+regex.length();
		}
		else{
			_tstring s=str.substr(from);
			strArray.push_back(s);
			break;
		}
	}
}
void ClearDir(const TCHAR* path){
	_tstring dirPath=path;
	_tstring findPath=dirPath+_T("\\*");
	HANDLE handle=NULL;
	WIN32_FIND_DATA findDate;
	handle=FindFirstFile(findPath.c_str(),&findDate);
	if(INVALID_HANDLE_VALUE!=handle){
		do{
			if(_tcscmp(findDate.cFileName,_T("."))!=0&&_tcscmp(findDate.cFileName,_T(".."))!=0){
				_tstring currentPath=dirPath+_T("\\")+findDate.cFileName;
				if(((findDate.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)==FILE_ATTRIBUTE_DIRECTORY)){
					ClearDir(currentPath.c_str());
					RemoveDirectory(currentPath.c_str());
				}
				else{
					DeleteFile(currentPath.c_str());
				}
			}
		}
		while(FindNextFile(handle,&findDate));
		FindClose(handle);
	}
}
bool DeleteDir(const TCHAR* path){
	ClearDir(path);
	RemoveDirectory(path);
	return !FileExist(path);
}
bool CreateDirByPath(const TCHAR* path){
	_tstring fpath=path;
	TrimFilePath(fpath);

	vector<_tstring> dn;
	SplitString(fpath,_T("\\"),dn);

	if(dn.size()<1) return false;
	if(dn.size()==1)
	{
		if (FileExist(dn[0].c_str()))
			return true;
		else
			return false;
	}

	_tstring beginpath=_T("");
	bool beginCreate=false;
	_tstring cp=dn[0];
	size_t i;
	for(i=1;i<dn.size();++i){
		if(dn[i]!=_T("")){
			cp=cp+_T("\\")+dn[i];
			if(!FileExist(cp.c_str())){
				BOOL bres=CreateDirectory(cp.c_str(),NULL);
				if(bres&&beginCreate==false){
					beginCreate=true;
					beginpath=cp;
				}
				if(!bres){
					break;
				}
			}
		}
	}

	DWORD attr=GetFileAttributes(path);
	if(attr==0xFFFFFFFF){
		if(beginCreate){
			DeleteDir(path);
		}
		return false;
	}
	else if((attr&FILE_ATTRIBUTE_DIRECTORY)!=FILE_ATTRIBUTE_DIRECTORY){
		return false;
	}
	else{
		return true;
	}
	return true;
}
bool CXmlNodeData::DoSaveTo(const TCHAR* filePath){
	try {
		CComPtr<IXMLDOMDocument> pXml;
		if(GetDocumentObject(&pXml)&&pXml){
			CreateDirByPath(GetFileDir(filePath).c_str());
			HRESULT hr=pXml->save(CComVariant(filePath));
			if(SUCCEEDED(hr)) return true;
		}
	}
	catch(...) {
	}
	return false;
}
bool CXmlNodeData::DoGetTextData(vector<BYTE>* pData){
	if(!pData) return false;
	try {
		CComPtr<IXMLDOMDocument> pXml;
		if(GetDocumentObject(&pXml)&&pXml){
			return GetDocumentObjectData(pXml,pData);
		}
	}
	catch(...) {
	}
	return false;
}
_tstring CXmlNodeData::DoGetText(){
	try {
		CComPtr<IXMLDOMDocument> pXml;
		if(GetDocumentObject(&pXml)&&pXml){
			CComBSTR xmlStr;
			pXml->get_xml(&xmlStr);
			return w2T(xmlStr);
		}
	}
	catch(...) {
	}
	return _T("");
}
CXmlNodeData* CXmlNodeData::GetRoot(){
	if(type==SUPPER) return NULL;
	else if(type==ROOT) return this;
	else if(type==CHILD){
		if(pParentNode) return pParentNode->GetRoot();
	}
	return NULL;
}
_tstring CXmlNodeData::GetPath(){
	if(type==SUPPER) return _T("");
	else if(type==ROOT) return _T("");
	else if(type==CHILD){
		if(pParentNode){
			if(pParentNode->type!=CHILD){
				return name;
			}
			else{
				return pParentNode->GetPath()+_T("\\")+name;
			}
		}
	}
	return _T("");
}
_tstring CXmlNodeData::GetSrc(){
	return src;
}