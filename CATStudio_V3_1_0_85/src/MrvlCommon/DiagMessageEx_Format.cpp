// DiagMessageEx.cpp: implementation of the CDiagMessageEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiagMessageEx.h"
#include "Converter\FormatData.h"
//#include "UE_Rec.h"
//#include "ASN1Interface.h"


char cFormatLetter[2] = {'u', 'X'};

void CDiagMessageEx::FormatTimeStamp(DWORD timeStamp, CString &strFormat)
{
	int nFormat = CFormatData::Instance()->m_TimeStampFormat;//(m_pDataFormatDlg == NULL) ? TIME_STAMP_FORMAT_WHITESAIL_SLOW : m_pDataFormatDlg->m_TimeStampFormat;
	switch (nFormat)
	{
	case TIME_STAMP_FORMAT_TICKS:
		strFormat.Format(_T("%lu"), timeStamp);
		break;
		
	case TIME_STAMP_FORMAT_COTULLA_TIME:
		{
			UINT64 cotullaTime = (UINT64)(((UINT64)timeStamp * (UINT64)(10000) + 1843)/3686);
			USHORT usNano = (USHORT)(cotullaTime%10);
			cotullaTime /= 10;
			USHORT usMicro = (USHORT)(cotullaTime%1000);
			cotullaTime /= 1000;
			USHORT usMilli = (USHORT)(cotullaTime%1000);
			cotullaTime /= 1000;
			USHORT usSec = (USHORT)(cotullaTime%60);
			cotullaTime /= 60;
			USHORT usMin = (USHORT)cotullaTime;
			int nTSFormat = CFormatData::Instance()->m_TimeStampTextFormat;//(m_pDataFormatDlg == NULL) ? TIME_STAMP_TEXT_FORMAT_MINUTES : m_pDataFormatDlg->m_TimeStampTextFormat;
 			if ( nTSFormat == TIME_STAMP_TEXT_FORMAT_MINUTES )
 				strFormat.Format(_T("%2.2u:%2.2u.%3.3u.%3.3u.%u"), usMin, usSec, usMilli, usMicro, usNano);
			else
 				strFormat.Format(_T("%u.%3.3u.%3.3u.%u"), (usMin*60) + usSec, usMilli, usMicro, usNano);
			
			break;
		}
		
	case TIME_STAMP_FORMAT_WHITESAIL_SLOW:
		{
			UINT64 whiteSailSlow = ((UINT64)(((UINT64)timeStamp)*((UINT64)1000000)))/32768;
			USHORT usMicro = (USHORT)(whiteSailSlow%1000);
			whiteSailSlow /= 1000;
			USHORT usMilli = (USHORT)(whiteSailSlow%1000);
			whiteSailSlow /= 1000;
			USHORT usSec = (USHORT)(whiteSailSlow%60);
			whiteSailSlow /= 60;
			USHORT usMin = (USHORT)(whiteSailSlow%60);//(USHORT)(whiteSailSlow%60);
			
			whiteSailSlow /= 60;
			USHORT usHour = (USHORT)(whiteSailSlow);
			int nTSFormat = CFormatData::Instance()->m_TimeStampTextFormat;
			if ( nTSFormat == TIME_STAMP_TEXT_FORMAT_HOUR )
			{
				//Chaim - change the look of the format to be as it appears to user "MM:SS.milli.micro" 
				//if needed more format it can be added
				//Wenjie - Change for CATS user request to show time format with hour infomation.
				strFormat.Format(_T("%2.2u:%2.2u:%2.2u.%3.3u.%3.3u"), usHour, usMin, usSec, usMilli, usMicro);
			}
			else if(nTSFormat == TIME_STAMP_TEXT_FORMAT_MINUTES)
			{
				strFormat.Format(_T("%2.2u:%2.2u.%3.3u.%3.3u"), usHour*60 + usMin, usSec, usMilli, usMicro);
			}
			else if(nTSFormat == TIME_STAMP_TEXT_FORMAT_SECONDS)
			{
				strFormat.Format(_T("%u.%3.3u.%3.3u"), usHour*3600+usMin*60 + usSec, usMilli, usMicro);
			}
			break;
		}
		
	case TIME_STAMP_FORMAT_WHITESAIL_FAST:
		{
			UINT64 whiteSailFast = ((UINT64)(((UINT64)timeStamp)*((UINT64)10000000)))/3250000;
			USHORT usNano = (USHORT)(whiteSailFast%10);
			whiteSailFast /= 10;
			USHORT usMicro = (USHORT)(whiteSailFast%1000);
			whiteSailFast /= 1000;
			USHORT usMilli = (USHORT)(whiteSailFast%1000);
			whiteSailFast /= 1000;
			USHORT usSec = (USHORT)(whiteSailFast%60);
			whiteSailFast /= 60;
			USHORT usMin = (USHORT)whiteSailFast;
			int nTSFormat = CFormatData::Instance()->m_TimeStampTextFormat;//(m_pDataFormatDlg == NULL) ? TIME_STAMP_TEXT_FORMAT_MINUTES : m_pDataFormatDlg->m_TimeStampTextFormat;
 			if ( nTSFormat/*m_DataFormatDlg.m_TimeStampTextFormat*/ == TIME_STAMP_TEXT_FORMAT_MINUTES )
 				strFormat.Format(_T("%2.2u:%2.2u.%3.3u.%3.3u.%u"), usMin, usSec, usMilli, usMicro, usNano);
 			else
 				strFormat.Format(_T("%u.%3.3u.%3.3u.%u"), (usMin*60) + usSec, usMilli, usMicro, usNano);
			
			break;
		}
	}
}

/////////////////////////////////////////////////////////////

static TCHAR LUT[] = {'0','1','2','3','4','5','6','7','8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
void CDiagMessageEx::FormatData(BYTE *pData, int len, CString &retStr)
{
	CString tempstr, fmt;
	retStr.Empty();

	if (pData == NULL)
	{
		return;
	}
	int nRawFormat = CFormatData::Instance()->m_RawFormat;
	char chFormatLet = CFormatData::Instance()->m_FormatLetter;
	int size = (int)(1 << nRawFormat);//((m_pDataFormatDlg == NULL) ? RAW_DATA_FORMAT_BYTE : m_pDataFormatDlg->m_RawFormat));

   if(chFormatLet=='X' && size==1)
   {
      TCHAR* buf = retStr.GetBuffer(size*3*len);
      for(int i=0, index=0; i<len; ++i)
      {
         DWORD val = pData[i];
         buf[index++] = LUT[(val>>4)];
         buf[index++] = LUT[(val&0x0F)];
         buf[index++] = ' ';
      }

      retStr.ReleaseBuffer();
   }
   else
   {
      fmt.Format(_T("%%%d.%d%c "), size*2, size*2, chFormatLet);
      DWORD val;
      for (int i=0; i<len; i+=size)
      {
         val = 0;
         memcpy(&val, &pData[i], size);		

         tempstr.Format(fmt, val);
         retStr += tempstr;
      }
   }
	m_strCurrentRawData = retStr;
	m_strCurrentRawData.TrimRight();
}


void CDiagMessageDiagEx::FormatLocalData(CString & retStr)
{
	FormatData(GetData(), GetDataLen(), retStr);
}

void CDiagMessageDspEx::FormatLocalData(CString & retStr)
{
	int maxLength = GetDataLen() - 4;
	int len2 = GetDspDataLen();

	if ( maxLength < len2 )
		len2 = maxLength;

	FormatData(GetData(4), len2, retStr);
}

/////////////////////////////////////////////////////////////

bool CDiagMessageDiagEx::FormatExportedFunctionData(CString &retStr)
{
	const CString & formatStr = m_pRec->m_ReportLine;
	int nOpenBrackets = formatStr.Find('(', 0);
	if ( nOpenBrackets == -1 )
		return false;
	
	CString strFuncionArgs = formatStr.Mid(nOpenBrackets+1);
	strFuncionArgs.TrimLeft();
	if ( strFuncionArgs.Left(4).CompareNoCase(_T("char")) == 0 )
	{
		retStr = CString((char*)GetData(), GetDataLen());
		return true;
	}
	int nEnd = strFuncionArgs.Find('*');
	/* cf. CCommandsDlg::OnSelchangedCommandsTree() */
	while (nEnd >= 0 && strFuncionArgs.Find(',') < 0 && m_pMessageConversionData)
	{
		CString strStruct;
		strStruct = strFuncionArgs.Left(nEnd);
		strStruct.Trim();
		if (strStruct.IsEmpty())
		{
			break;
		}
		int nStart = 0;
		if ((nStart = strStruct.Find(' ', 0)) > 0)
		{
			strStruct = strStruct.Mid(nStart + 1);
			strStruct.Trim();
		}
		CString strTmp = strStruct;
		strTmp.MakeLower();

		if (strTmp == _T("void") || strTmp == _T("char") || strTmp == _T("short") ||
			strTmp == _T("int") || strTmp == _T("long") || strTmp.Find(_T("int8")) >= 0 ||
			strTmp.Find(_T("int16")) >= 0 || strTmp.Find(_T("int32")) >= 0 ||
			strTmp.Find(_T("int64")) >= 0)
		{
			/* hard coded special cases */
			if (m_pRec->m_Cat2 == _T("Transport") && m_pRec->m_Cat1 == _T("FDI"))
			{
				if (m_pRec->m_Cat3 == _T("Fopen"))
				{
					m_pMessageConversionData->strStruct = _T("FOpenInputStruct");
				}
				else if (m_pRec->m_Cat3 == _T("Fwrite"))
				{
					m_pMessageConversionData->strStruct = _T("WriteInputStruct");
				}
				else if (m_pRec->m_Cat3 == _T("Fread"))
				{
					m_pMessageConversionData->strStruct = _T("ReadInputStruct");
				}
				else if (m_pRec->m_Cat3 == _T("FwriteEx"))
				{
					m_pMessageConversionData->strStruct = _T("WriteInputStruct_Ex");
				}
				else if (m_pRec->m_Cat3 == _T("FreadEx"))
				{
					m_pMessageConversionData->strStruct = _T("ReadInputStruct_Ex");
				}
				else if (m_pRec->m_Cat3 == _T("RenameFile"))
				{
					m_pMessageConversionData->strStruct = _T("RenameInputStruct");
				}
				else if (m_pRec->m_Cat3 == _T("FchangeMode"))
				{
					m_pMessageConversionData->strStruct = _T("ChangModeStruct");
				}
				else if (m_pRec->m_Cat3 == _T("Fseek"))
				{
					m_pMessageConversionData->strStruct = _T("FSeekStruct");
				}
				else if (m_pRec->m_Cat3 == _T("MkDir"))
				{
					m_pMessageConversionData->strStruct = _T("MkDirStruct");
				}
				else if (m_pRec->m_Cat3 == _T("RmDir"))
				{
					m_pMessageConversionData->strStruct = _T("RmDirStruct");
				}
			}
			else if (m_pRec->m_Cat2 == _T("Calibration") && m_pRec->m_Cat1 == _T("Audio"))
			{
				if (m_pRec->m_Cat3 == _T("ConfigVE"))
				{
					m_pMessageConversionData->strStruct = _T("ACMDSP_VEParametersT");
				}
				else if (m_pRec->m_Cat3 == _T("ConfigCodec"))
				{
					m_pMessageConversionData->strStruct = _T("ACMCodec_GainT");
				}
				if (m_pRec->m_Cat3 == _T("ConfigMediaVE"))
				{
					m_pMessageConversionData->strStruct = _T("ACMCP_MediaVEarametersT");
				}
			}
		}
		else
		{
			m_pMessageConversionData->strStruct = strStruct;
		}
		break;
	}
	
	return false;
}

////////////////////////////////////////////////////////////////

CString CDiagMessageDiagEx::ConvertParam(TCHAR type, bool longType, BYTE **ppParams, int nParamSize)
{
	CString ret;
	
	char	c;
	BYTE	b;
	short	s;
	USHORT	us;
	long	l;
	ULONG	ul;
	
	CConverterManager *pCM = CConverterManager::Instance(m_pIcatMessage->GetDevice());
	eTargetDBType TargetDBType = IsApp() ? eTargetDBTypeApp : eTargetDBTypeCom;
	bool bAppSide = IsApp();
	bool bAligned = IsAligned();

	switch (type)
	{

		case 'b':	if (nParamSize == 0)
						nParamSize = sizeof(BYTE);

					if ((*ppParams) + nParamSize > m_pLastByteOfData)
						return _T("");
					b = *(*ppParams);	
					*ppParams += nParamSize;
					ret.Format(_T("%d"), b);
					break;			
				
		case 'c':	if (nParamSize == 0)
						nParamSize = sizeof(BYTE);
					if ((*ppParams) + nParamSize > m_pLastByteOfData)
						return _T("");
					c = *(*ppParams);
					*ppParams += nParamSize;
					ret.Format(_T("%c"), c);
					break;

		case 'd':	if (!longType)
					{
						if (nParamSize == 0)
							nParamSize = sizeof(short);

						if (bAligned)
							ALIGN(*ppParams, nParamSize);
						if ((*ppParams) + nParamSize > m_pLastByteOfData)
							return _T("");
						s = *(*(short **)ppParams);
						*ppParams += nParamSize;
						ret.Format(_T("%d"), s);
					}
					else
					{
						if (nParamSize == 0)
							nParamSize = sizeof(long);

						if (bAligned && (UINT)(*ppParams) % nParamSize)
							ALIGN(*ppParams, nParamSize);
						if ((*ppParams) + nParamSize > m_pLastByteOfData)
							return _T("");
						l = *(*(long **)ppParams);
						*ppParams += nParamSize;
						ret.Format(_T("%ld"), l);
					}
					break;

		case 'o':	if (!longType)
					{
						if (nParamSize == 0)
							nParamSize = sizeof(USHORT);

						if (bAligned)
						ALIGN(*ppParams,nParamSize);
						if ((*ppParams) + nParamSize > m_pLastByteOfData)
							return _T("");
						us = *(*(USHORT **)ppParams);
						*ppParams += nParamSize;
						ret.Format(_T("%o"), us);
					}
					else
					{
						if (nParamSize == 0)
							nParamSize = sizeof(ULONG);

						if (bAligned && (UINT)(*ppParams) % nParamSize)
							ALIGN(*ppParams, nParamSize);
						if ((*ppParams) + nParamSize > m_pLastByteOfData)
							return _T("");
						ul = *(*(ULONG **)ppParams);
						*ppParams += nParamSize;
						ret.Format(_T("%lo"), ul);
					}
					break;

		case 'u':	if (!longType)
					{
						if (nParamSize == 0)
							nParamSize = sizeof(USHORT);

						if (bAligned)
							ALIGN(*ppParams, nParamSize);
						if ((*ppParams) + nParamSize > m_pLastByteOfData)
							return _T("");
						us = *(*(USHORT **)ppParams);
						*ppParams += nParamSize;
						ret.Format(_T("%u"), us);
					}
					else
					{
						if (nParamSize == 0)
							nParamSize = sizeof(ULONG);

						if (bAligned && (UINT)(*ppParams) % nParamSize)
							ALIGN(*ppParams, nParamSize);
						if ((*ppParams) + nParamSize > m_pLastByteOfData)
							return _T("");
						ul = *(*(ULONG **)ppParams);
						*ppParams += nParamSize;
						ret.Format(_T("%lu"), ul);
					}
					break;

		case 'x':	if (!longType)
					{
						if (nParamSize == 0)
							nParamSize = sizeof(USHORT);

						if (bAligned)
							ALIGN(*ppParams, nParamSize);
						if ((*ppParams) + nParamSize > m_pLastByteOfData)
							return _T("");
						us = *(*(USHORT **)ppParams);
						*ppParams += nParamSize;
						BOOL bLeadingZero = CFormatData::Instance()->m_bLeadingZeros;
						if (bLeadingZero)
 							ret.Format(_T("%4.4x"), us);
						else
							ret.Format(_T("%x"), us);
					}
					else
					{
						if (nParamSize == 0)
							nParamSize = sizeof(ULONG);

						if (bAligned && (UINT)(*ppParams) % nParamSize)
							ALIGN(*ppParams, nParamSize);
						if ((*ppParams) + nParamSize > m_pLastByteOfData)
							return _T("");
						ul = *(*(ULONG **)ppParams);
						*ppParams += nParamSize;
						BOOL bLeadingZero = CFormatData::Instance()->m_bLeadingZeros;
						if(bLeadingZero) 					
						ret.Format(_T("%8.8lx"), ul);
						else
						ret.Format(_T("%lx"), ul);
					}
					break;

		case 'X':	if (!longType)
					{
						if (nParamSize == 0)
							nParamSize = sizeof(USHORT);

						if (bAligned)
							ALIGN(*ppParams, nParamSize);
						if ((*ppParams) + nParamSize > m_pLastByteOfData)
							return _T("");
						us = *(*(USHORT **)ppParams);
						*ppParams += nParamSize;
						BOOL bLeadingZero = CFormatData::Instance()->m_bLeadingZeros;
						if (bLeadingZero)
							ret.Format(_T("%4.4X"), us);
	 					else
							ret.Format(_T("%X"), us);
					}
					else
					{
						if (nParamSize == 0)
							nParamSize = sizeof(ULONG);

						if (bAligned && (UINT)(*ppParams) % nParamSize)
							ALIGN(*ppParams, nParamSize);
						if ((*ppParams) + nParamSize > m_pLastByteOfData)
							return _T("");
						ul = *(*(ULONG **)ppParams);
						*ppParams += nParamSize;
						BOOL bLeadingZero = CFormatData::Instance()->m_bLeadingZeros;
						if (bLeadingZero)
							ret.Format(_T("%8.8lX"), ul);
						else
							ret.Format(_T("%lX"), ul);
					}
					break;

		case 's':	
			{
				
				ret = CString(*ppParams);
				//int nLen = ret.GetLength();
				const char* pSrc = (char*)*ppParams;
				size_t nStrLen = 0;
				nStrLen = strlen(pSrc);
				*ppParams += nStrLen+1; /*ret.GetLength()*/// +1 for the NULL-terminator.
                if (!bAppSide && m_pRec->m_EnumType == 0 /* report */)
                {
                    CString strTranslation;
                    if (pCM->GetReportStringParamTranslation(m_pRec->m_EnumVal, ret, strTranslation))
                    {
                        ret = strTranslation;
                    }
                }
			}
					break;

		case 't':	if (nParamSize == 0)
						nParamSize = sizeof(ULONG);
					if (bAligned && (UINT)(*ppParams) % nParamSize)
							ALIGN(*ppParams, sizeof(ULONG));
					if ((*ppParams) + nParamSize > m_pLastByteOfData)
						return _T("");
					ul = *(*(ULONG **)ppParams);
					*ppParams += nParamSize;
					FormatTimeStamp(ul, ret);
					break;

		case 'E':
		case 'T':
		case 'e':{
					bool bFound = true;
					int nEnumSize = pCM->GetEnumSizeByName(m_CurrentTableName, bAppSide);
					CString strFmt;

					if ( nEnumSize == 0 )	// Unknown enum - assuming 1 byte (may corrupt the conversion)
					{
						if (nParamSize == 0)
							nParamSize = sizeof(BYTE);

						if ((*ppParams) + nParamSize > m_pLastByteOfData)
							return _T("");
						b = *(*ppParams);	
						*ppParams += nParamSize;
						ret.Format(_T("%d (*Unknown enum*)"), b);
						break;			
					}

					if (nParamSize == 0)
						nParamSize = nEnumSize;

					if (bAligned)
						ALIGN(*ppParams, nParamSize);

					if ((*ppParams) + nParamSize > m_pLastByteOfData)
						return _T("");


					if ( nEnumSize == 1 )
					{
						b = *(*ppParams);
						c = *(*(char **)ppParams);
						if ( !pCM->GetEnumFromTable(m_CurrentTableName, b, ret, TargetDBType) && !pCM->GetEnumFromTable(m_CurrentTableName, c, ret, TargetDBType) )
						{
							ret.Format(_T("0x%2.2X"), b);
						}
						else
							ret += ' ';
					}
					else if ( nEnumSize == 2  )
					{
						us = *(*(USHORT **)ppParams);
						s = *(*(short **)ppParams);
						if ( !pCM->GetEnumFromTable(m_CurrentTableName, us, ret, TargetDBType) && !pCM->GetEnumFromTable(m_CurrentTableName, s, ret, TargetDBType) )
						{
							ret.Format(_T("0x%4.4X"), us);
						}
						else
							ret += ' ';
					}
					else if ( nEnumSize == 4  )
					{
						ul = *(*(ULONG **)ppParams);
						l = *(*(long **)ppParams);
						if ( !pCM->GetEnumFromTable(m_CurrentTableName, ul, ret, TargetDBType) && !pCM->GetEnumFromTable(m_CurrentTableName, l, ret, TargetDBType) )
						{
							ret.Format(_T("0x%8.8X"), ul);
						}
						else
							ret += ' ';
					}

					*ppParams += nParamSize; 		
					break;
				 }
	}

	return ret;
}

//communication message
bool CDiagMessageDiagEx::ConvertString(CString &retStr)
{
	BYTE *pParams = GetData();
	int nPrmLen = GetDataLen();

//////////
	int firstData = m_pRec->m_ReportLine.Find('\"', 0) + 1;
	int lastQuotes = m_pRec->m_ReportLine.Find('\"', firstData);
	CString tmpStruct;

	if (lastQuotes < 0)
		return false;
	
	CString formatStr = m_pRec->m_ReportLine.Mid(firstData, lastQuotes - firstData);

	firstData = lastQuotes + 1;
	while (firstData < m_pRec->m_ReportLine.GetLength())
	{
		int c = m_pRec->m_ReportLine.GetAt(firstData);
		if (c == '\"')
		{
			firstData++;
			lastQuotes = m_pRec->m_ReportLine.Find('\"', firstData);
			if (lastQuotes < 0)
				break;

			formatStr += m_pRec->m_ReportLine.Mid(firstData, lastQuotes - firstData);
			firstData = lastQuotes + 1;
			continue;
		}
		else if ((c == ' ') || (c == '\t'))
		{
			firstData++;
			continue;
		}
		else
			break;

	}




	// diagTextPrintf
	if (m_pRec->m_ReportLine.Left(14) == _T("diagTextPrintf"))
	{
		retStr = formatStr;
		return true;
	}
	// diagStructPrintf
	else if(m_pRec->m_ReportLine.Left(16) == _T("diagStructPrintf"))
	{
		int index = formatStr.Find(_T("%S"), 0);
		if ( index > -1 )
		{
			int openBracket = formatStr.Find('{', index);
			int closeBracket = formatStr.Find('}', index);
			if ( openBracket != -1 && closeBracket != -1 )
			{
				tmpStruct = formatStr.Mid(openBracket+1, closeBracket-(openBracket+1));
				if (m_pMessageConversionData)
				{
					m_pMessageConversionData->strStruct = tmpStruct;
				}

				int nStruct = CFormatData::Instance()->m_StructPres;
				if(nStruct == STRUCT_PRES_DATA)
				{
					CString strData;
					FormatData(GetData(), GetDataLen(), strData);
					formatStr.Replace(_T("{") + tmpStruct + _T("}"), _T("{ ") + strData + _T("}"));
				}
			}
			formatStr.Delete(index,2); // remove the '%S'
		}

		retStr = formatStr;

		if (tmpStruct.IsEmpty())	
		{
			retStr += _T(" - ");
			CString strFmt;

			FormatLocalData(strFmt);

			retStr += strFmt;
		}

		return true;
	}
	
	// diagPrintf
	if ( m_pRec->m_ReportLine.Left(10) != _T("diagPrintf") )
	{
		retStr = _T("Error in Database - 'Printf' line is not understandable.");
		return false;
	}

	int nParamSize = 0;

	if (m_pRec->m_ReportLine.GetAt(10) == '_')
	{
		if (m_pRec->m_ReportLine.GetAt(11) == '4')
			nParamSize = 4;
	}

	bool bAppSide = IsApp();
	bool bAligned = IsAligned();

	int length = formatStr.GetLength();

	m_pLastByteOfData = pParams + nPrmLen;

	long start	  = 0;
	long oldIndex = 0;
	long lngCount = 0;

	CConverterManager *pCM = CConverterManager::Instance(m_pIcatMessage->GetDevice());
	eTargetDBType TargetDBType = IsApp() ? eTargetDBTypeApp : eTargetDBTypeCom;

	while(TRUE)
	{
		bool longType = false;

		int perIndex = formatStr.Find('%', start);
		if (perIndex == -1)
			break;
		
		lngCount = perIndex - start;
		if((lngCount < 0) || (start < 0) || (start > formatStr.GetLength()) || (nPrmLen == 0))
			break;

		retStr += formatStr.Mid(start, lngCount);
		
		if ( length <= perIndex + 1 )
		{
			break;
		}
		else if (formatStr[perIndex+1] == ' ' || formatStr[perIndex+1] == '%')
		{
			start = formatStr.Find('%',perIndex + 1);
			
			lngCount = start - perIndex;
			if((lngCount < 0) || (perIndex < 0))
				break;

			retStr += formatStr.Mid(perIndex, lngCount);
			continue;
		}

		TCHAR type = formatStr.GetAt(perIndex+1);
		int closeBracket = -1; 
		if (type == 'T' || type == 'e' || type == 'E')
			closeBracket = formatStr.Find('}', perIndex);
		
		bool bIsArray = false;
		
		if (closeBracket != -1)
		{
			if ( (formatStr.GetLength() > closeBracket+1 && formatStr.GetAt(closeBracket+1) == '[' ) ||
					(formatStr.GetLength() > closeBracket+2 && formatStr.GetAt(closeBracket+2) == '[' ) )
				bIsArray = true;
		}
		else if (formatStr.GetLength() >= perIndex+4)
		{
			if (formatStr.GetAt(perIndex+2) == '[' || formatStr.GetAt(perIndex+3) == '[' ||
					(formatStr.GetLength() >= perIndex+5 && formatStr.GetAt(perIndex+4) == '[') )  
				bIsArray = true;
		}

		if (closeBracket != -1) // Enum or Table 
			m_CurrentTableName =  formatStr.Mid(perIndex+3, (closeBracket-perIndex-3));

		if ( !bIsArray )
		{
			if (closeBracket != -1) // Enum or Table 
				start = closeBracket + 1;  // skip over the Enum/Table type
			else if (type == 'l')
			{
				longType = true;
				type = formatStr.GetAt(perIndex + 2);
				start = perIndex + 3;
			}
			else
				start = perIndex + 2;
			
// 			//Shmulik
// 			if (theConverterManager->IsIntSizeAlwaysLong(bAppSide))// m_CompilerOptionsDlg.m_pOptionsPage[bAppSide]->m_bIntAlwaysLong)
// 				longType = true;

			CString numStr;
			TRY 
			{
				numStr = ConvertParam(type, longType, &pParams, nParamSize);
			}
			CATCH_ALL(e)
			{
				e->Delete();
			}
			END_CATCH_ALL

			if (!numStr.IsEmpty())
			{
				retStr += numStr;
			}
		}
		else	// array
		{
			int openIndex = formatStr.Find('[', perIndex);
			int closeIndex = formatStr.Find(']', perIndex);
			CString loopStr = formatStr.Mid(openIndex+1, closeIndex-(openIndex+1));
			
			int loop = _tstoi(loopStr.GetBuffer(loopStr.GetLength()));
			
			if (type == 'l')
			{
				longType = true;
				type = formatStr.GetAt(perIndex+2);
			}

// 			//Shmulik
// 			if (theConverterManager->IsIntSizeAlwaysLong(bAppSide))// m_CompilerOptionsDlg.m_pOptionsPage[bAppSide]->m_bIntAlwaysLong)
// 				longType = true;


			if (loop <= 0) // array of UNKNOWN size.
			{
				///////////////////////////////////////////////////////////
				///////////////////////////////////////////////////////////
				if (bAligned)
					ALIGN(pParams, sizeof(USHORT));
				loop = (int)(*((USHORT *)pParams));

				switch (type)
 				{
 					case 'b':
 					case 'c': //loop = (int)(*pParams);
 							  loop /= sizeof(BYTE);
 							  break;
 					
					case 'd': if (!longType)
							  {
								//loop = (int)(*((short *)pParams));
								loop /= sizeof(short);	/*buffer size in bytes -> num of params*/
							  }
							  else
							  {
								//loop = (int)(*((long *)pParams));
								loop /= sizeof(long);	/*buffer size in bytes -> num of params*/
							  }
							  break;

					case 'o':
					case 'u': 
					case 'x': 
					case 'X': if (!longType)
							  {
								//	loop = (int)(*((USHORT *)pParams));
								loop /= sizeof(USHORT);	/*buffer size in bytes -> num of params*/
							  }
							  else
							  {
								loop /= sizeof(ULONG);	/*buffer size in bytes -> num of params*/
							  }
							  break;
		
					case 'e':
					case 'E':
					case 'T': {
								int nEnumSize = pCM->GetEnumSizeByName(m_CurrentTableName, bAppSide);
								loop /= nEnumSize;
							  }
							break;
				}
				pParams += sizeof(USHORT);
			}

			for (int i = 0; i < loop; i++)
			{
				CString numStr;
				TRY 
				{
					numStr = ConvertParam(type, longType, &pParams, nParamSize);
				}
				CATCH_ALL(e)
				{
					e->Delete();
				}
				END_CATCH_ALL

				if (numStr == _T(""))
				{
					return false;
				}
				retStr += numStr;
				if (i<loop-1)
					retStr += _T(", ");
			}

			start = closeIndex+1;
		}

		oldIndex = perIndex;

	}// while(TRUE)

	retStr += formatStr.Mid(start);

	return true;
}

bool CDiagMessageGKIEx::ConvertString(CString &retStr)
{
	CString strSignalName, strSignalGroup,tmpStruct;
	CString tmpstrASN1MessageName,tmpstrASN1Details;
	CConverterManager *pCM = theConverterManager(m_pIcatMessage->GetDevice());
	DWORD signalID = GetSignalId();

	if ( pCM->LookupSignal(signalID, strSignalName, strSignalGroup) )
	{
		tmpStruct = strSignalName;
		if (m_pMessageConversionData)
		{
			m_pMessageConversionData->strStruct = tmpStruct;
		}
		
		if(m_pMessageReaderEx->m_bIsOffline)
		{
			if ( pCM->IsAsn1Message(signalID) )
			{			
				// Get the ASN.1 message name:
				if (!pCM->GetASN1MessageName(signalID, GetDataEx(), tmpstrASN1MessageName))
				{
					// GKI signal which carry ASN.1 message, but its not recognized:
					tmpstrASN1MessageName.Format(_T("Unknown ASN.1 Message of signal: 0x%4.4x, Data is: "), signalID);
					CString strAsn1Data;
					FormatData (GetDataEx(), GetDataExLen(), strAsn1Data);
					tmpstrASN1MessageName += strAsn1Data;
					
					strSignalName = tmpstrASN1MessageName;
				}
				else
					// Get the ASN.1 message group details:
				{
					if (pCM->GetASN1MsgDetails (signalID,  GetDataEx(), tmpstrASN1Details))
					{
						//							signalGroup.Format ("%s %s %s", direction, rb, trCh);
					}
					
					CString temp;
					temp.Format(_T("%s : %s"), strSignalName, tmpstrASN1MessageName);
					strSignalName = temp;
				}								
			}
			else if ( pCM->IsCSN1Message(signalID))
			{
				if (pCM->GetCSN1MessageName(signalID, GetDataEx(), tmpstrASN1MessageName))
				{
					CString temp;
					temp.Format(_T("%s : %s"), strSignalName, tmpstrASN1MessageName);
					strSignalName = temp;
				}						
			}
			else if (pCM->IsGsmMessage(signalID))
			{
				if (!pCM->GetGsmMessageName(signalID, GetDataEx(), tmpstrASN1MessageName))
				{
					// GKI signal which carry GSM message, but its not recognized:
					tmpstrASN1MessageName.Format(_T("Unknown GSM Message of signal: 0x%4.4x, Data is: "), signalID);
					CString strGsmData;
					FormatData (GetDataEx(), GetDataExLen(), strGsmData);
					tmpstrASN1MessageName += strGsmData;
				}
			}

			if (m_pMessageConversionData)
			{
				m_pMessageConversionData->strASN1MessageName = tmpstrASN1MessageName;
				m_pMessageConversionData->strASN1Details	 = tmpstrASN1Details;
			}
		}

		retStr = strSignalName;

		if (m_pMessageReaderEx->m_StructPres == STRUCT_PRES_DATA) 
		{
			CString strData;
			FormatData(GetDataEx(), GetDataExLen(), strData);
			retStr.AppendFormat(_T(" { %s}"), strData);
		}
	}
	else
	{
		if ( GetSignalIdSize() == 2 )
			retStr.Format(_T("Unknown Signal - 0x%4.4x"), signalID);
		else // == 4
			retStr.Format(_T("Unknown Signal - 0x%8.8x"), signalID);
	}
	return true;
}

bool CDiagMessageISEx::ConvertString(CString &retStr)
{
	BYTE service = GetService();
	switch (service)
	{
	case VERSION_ID: 
		{
			CString strVersion = CString(GetData());
			retStr = _T("Database Version ID - ") + strVersion;
			
			int len1 = strVersion.GetLength();
			
			if (GetDataLen() > (len1 + 3))
			{
				strVersion = GetData(len1 + 1);
				retStr += ", PreDefined DB Version ID - ";
				retStr += strVersion;
			}
		}
		break;
		
	case TRANSFER_DATABASE:
		{
			CString strFmt;
			retStr = _T("Database Transfer - ");
			FormatData(GetData(), GetDataLen(), strFmt);
			retStr += strFmt;
		}
		break;
		
	case GET_CLOCK_RATE:
		{
			CString strFmt;
			retStr = _T("Clock Rate - ");
			FormatData(GetData(), GetDataLen(), strFmt);
			retStr += strFmt;
		}
		break;
		
	case IS_ICAT_DIAG_READY_NOTIFY:
		retStr = _T("Diag Ready Notification");
		break;
// 	case IS_PING_PONG_HANDSHAKE:
// 		{
// 			retStr.Format(_T("Pong Response - Counter: %lu, Log Channel: %d, Trace Enable: %d - ["),
// 				*(ULONG*)GetData(), *GetData(sizeof(ULONG)), *GetData(sizeof(ULONG)+1));
// 			
// 			CString strFmt;
// 			FormatData(GetData(), GetDataLen(), strFmt);
// 			retStr += strFmt;
// 			retStr += "]";
// 			break;
// 		}
// 	case IS_DIAG_RESET:
// 		{
// 			ULONG counter = 0;
// 			int enable = 0;
// 
// 			BYTE * pData = GetData();
// 
// 			if (pData && GetDataLen() >= sizeof(ULONG))
// 			{
// 				counter = *(ULONG*)pData;
// 			}
// 
// 			pData = GetData(sizeof(ULONG));
// 			if (pData)
// 			{
// 				enable = *pData;
// 			}
// 
// 			retStr.Format(_T("Diag Reset - Counter: %lu, , Trace Enable: %d - ["), counter, enable);
// 
// 			CString strFmt;
// 			FormatData(GetData(), GetDataLen(), strFmt);
// 			retStr += strFmt;
// 			retStr += "]";
// 			break;
// 		}
	case ClientDB_REQ_STATUS:
		{

#define MHEADER	12			

			if (GetDataLen() < MHEADER)
			{
				retStr = "Unknown ClientDB Status!";
				return true;
			}

			int type =  *((short int *)GetData());
			int RequestClient = *((int *)GetData(4));
			DWORD dwRequestVersion = *((DWORD *)GetData(8));

			switch (type)
			{
			case -1: retStr = "Unknown ClientDB Status!";
				return true;
			case 0: retStr.Format(_T("ClientDB exist, DBversion fits, Client %d, Version 0x%08X"), RequestClient, dwRequestVersion);
				break;
			case 1: retStr.Format(_T("ClientDB file does not exist, Client %d, Version 0x%08X"), RequestClient, dwRequestVersion);
				break;
			case 2: retStr.Format(_T("ClientDB file exist, but DBversion does not fit, Client %d, Version 0x%08X"), RequestClient, dwRequestVersion);
				break;
			case 3: retStr.Format(_T("ClientDb file Deleted, Client %d, Version 0x%08X"), RequestClient, dwRequestVersion);
				break;
			case 4: retStr.Format(_T("ClientDb Transmission file will start , Client %d, Version 0x%08X"), RequestClient, dwRequestVersion);
				break;
			case 5: retStr.Format(_T("ClientDB Operation rejected due to other-DB-transmission in process,Client %d, Version 0x%08X"), RequestClient, dwRequestVersion);
				break;
			case 6: retStr.Format(_T("ClientDB file exist, but size is too small, Client %d, Version 0x%08X"), RequestClient, dwRequestVersion);
				break;
			case 7: retStr.Format(_T("ClientDB Status error, TARGET_RESOURCE_ISSUE, Client %d, Version 0x%08X"), RequestClient, dwRequestVersion);
				break;
			case 8: retStr.Format(_T("ClientDB Status error, TARGET_INTERNAL_FILE_ERROR, Client %d, Version 0x%08X"), RequestClient, dwRequestVersion);
				break;
			case 9: retStr.Format(_T("ClientDB Status error, NACK_ACK_WRONG_CLIENT, Client %d, Version 0x%08X"), RequestClient, dwRequestVersion);
				break;
			case 10: retStr.Format(_T("ClientDB Status error, NACK_PACKETNUM_TOO_BIG, Client %d, Version 0x%08X"), RequestClient, dwRequestVersion);
				break;
			}

			if ((type == 0 || type == 2 || type == 4 || type == 6) && GetDataLen() > (MHEADER + 16))
			{
				int TotalSize = *((DWORD *)GetData(12));
				int client = *((DWORD *)GetData(12 + 4));
				DWORD dwVersion = *((DWORD *)GetData(12 + 8));

				int nHeaderLength = *((short *)GetData(12 + 12));
				int AcatData = *((short *)GetData(12 + 14));

				retStr.AppendFormat(_T(", Total Size = %d, client = %d, Version = 0x%08X, Header Length = %d, Acat Data = %d"),
					TotalSize, client, dwVersion, nHeaderLength, AcatData);

				int index = MHEADER + 16;

				if (GetDataLen() >= (nHeaderLength + MHEADER))
					while ((index + 4) < (nHeaderLength + MHEADER)) 
					{
						int TlvType = *((short *)GetData(index));
						int TlvLen = *((short *)GetData(index + 2));

						index += 4;

						if ((index + TlvLen) < (nHeaderLength + MHEADER))
						{
							if (TlvType == 0x10)
							{
								int client = *((int *)GetData(index));
								DWORD dwVersion = *((DWORD *)GetData(index + 4));

								retStr.AppendFormat(_T(", [Client %d, Version 0x%08X]"), client, dwVersion);
							}
							else
							{
								retStr.AppendFormat(_T(", [type = %X, "), TlvType);
								for (int i = 0 ; i < TlvLen; ++i)
								{
									BYTE data = *GetData(index + i);
									retStr.AppendFormat(_T(" %02X"), data);
								}
								retStr.AppendFormat(_T(" ]"));
							}

						}

						index += TlvLen;
					}

				if ((type == 6) && GetDataLen() > (nHeaderLength + MHEADER + 4))
				{
					DWORD nActLength = *((DWORD *)GetData(nHeaderLength + MHEADER));
					retStr.AppendFormat(_T(", Actual length = %lu"), nActLength);
				}
			}

			break;
		}
	case ClientDB_DATA:
		{
			int client = (GetData() == NULL) ? -1 : *((int *)GetData(0));
			DWORD dwVersion = (GetData(4) == NULL) ? -1 : *((DWORD *)GetData(4));
			DWORD filesize = (GetData(8) == NULL) ? -1 : *((DWORD *)GetData(8));
			DWORD StartByte = (GetData(12) == NULL) ? -1 : *((DWORD *)GetData(12));
			DWORD EndByte = (GetData(16) == NULL) ? -1 : *((DWORD *)GetData(16));

			int PacketNumber = (GetData(20) == NULL) ? -1 : *((short *)GetData(20));
			int Packets = (GetData(22) == NULL) ? -1 : *((short *)GetData(22));

			//CString strFmt;
			//FormatData(GetData(24), GetDataLen() - 24, strFmt);

			retStr.Format(_T("Client DB Data: Client %d, version %08x, size %lu, from %ld, to %lu, packet %d / %d"),
				client, dwVersion, filesize, StartByte, EndByte, PacketNumber, Packets);
			break;
		}
	default:
		{
			CString strFmt;
			FormatData(GetData(), GetDataLen(), strFmt);
			retStr += strFmt;
		}
	}
	return true;
}

#define DSP_COMMAND_ENUM	_T("plpCommands_Strings")
#define DSP_MESSAGE_ENUM	_T("plpMessages_Strings")

bool CDiagMessageDspEx::ConvertString(CString &retStr)
{
	CString strEnumName =  (IsPLPMsg()) ? DSP_MESSAGE_ENUM : DSP_COMMAND_ENUM;
	CString strTemp,tmpStruct;
	if (!theConverterManager(m_pIcatMessage->GetDevice())->GetEnumFromTable(strEnumName, GetDspOpCode(), strTemp))
		return CDiagMessageDiagEx::ConvertString(retStr);

	tmpStruct = strTemp.Mid(2);

	if (m_pMessageConversionData)
	{
		m_pMessageConversionData->strStruct = tmpStruct;
	}

	strTemp.Empty();

	FormatLocalData(strTemp);

	retStr.Format(_T("{%s} %s - %s"),  tmpStruct, (IsPLPMsg()) ? _T("PLP") : _T("IPC"), strTemp);

	return true;
}

bool CDiagMessageISEx::ConvertCCString(CString &retStr)
{
	BYTE bServiceID = GetService();
	///////////////////////////////////////////////////////////////
	///////////////////// Data ////////////////////////////////////
	switch (bServiceID)
	{
	case VERSION_ID: retStr = _T("Database Version ID Request"); 
		break;
		
	case TRANSFER_DATABASE: retStr = _T("Transfer Database Request"); 
		break;
		
	case GET_CLOCK_RATE: retStr = _T("Clock Rate Request"); 
		break;
		
	case SET_FILTER_LEVEL:
		{
			CString strFmt;
			retStr = _T("Set Filter Level - ");
			FormatData(GetData(), GetDataLen(), strFmt);
			retStr += strFmt;
		}
		break;
		
	case ICAT_READY_NOTIFY: retStr = _T("ACAT Ready Notification");
		break;
		
	case ENTER_BOOTLOADER_MODE: retStr = _T("Enter Boot-Loader Mode");
		break;
		
	case SEND_FULL_FRAME_NUM: retStr = _T("Send Full Frame Number");
		break;
	case UE_CP_INFO: retStr = _T("UE CP Info Request");
		break;
	case ACAT_DISCONNECT_NOTIFY: retStr = _T("ACAT Disconnect Notification");
		break;
	case ACAT_KEEP_ALIVE: retStr = _T("ACAT Keep Alive");
		break;
// 	case IS_PING_PONG_HANDSHAKE: retStr = _T("Ping-Pong Handshake Request");
// 		break;
// 	case IS_DIAG_RESET: retStr = _T("Diag Connection Reset");
// 		break;
	case ClientDB_REQ:
		{
			int type = (GetData() == NULL) ? -1 : *((short int *)GetData());
			int client = (GetData(4) == NULL) ? -1 : *((int *)GetData(4));
			DWORD dwVersion = (GetData() == NULL) ? -1 : *((DWORD *)GetData(8));

			switch(type)
			{
			case 0: retStr.Format(_T("Query about client %d, version 0x%08X"), client, dwVersion);
				break;
			case 1: retStr.Format(_T("Request to start transmission client %d, version 0x%08X"), client, dwVersion);
				break;
			case 2: retStr.Format(_T("Request to delete on target the clientDB file, client %d, version 0x%08X"), client, dwVersion);
				break;
			default:retStr.Format(_T("Unknown request (%d), client %d, version 0x%08X"), type, client, dwVersion);
				break;
			}
		break;
		}

	case ClientDB_DATA_STATUS:
		{
			int type = (GetData() == NULL) ? -1 : *((short int *)GetData());
			int count = (GetData(2) == NULL) ? -1 : *((short int *)GetData(2));
			int client = (GetData(4) == NULL) ? -1 : *((int *)GetData(4));
			DWORD dwVersion = (GetData(8) == NULL) ? -1 : *((DWORD *)GetData(8));
			switch(type)
			{
			case 1: retStr.Format(_T("NACK, Timeout waiting to Data packet,client %d, version 0x%08X"), client, dwVersion);
				break;
			case 2: retStr.Format(_T("NACK, Missing packet #%d, client %d, version 0x%08X"), count, client, dwVersion);
				break;
			case 10: retStr.Format(_T("ACK, Receive full compressed file, client %d, version 0x%08X"), client, dwVersion);
				break;
			default:retStr.Format(_T("Unknown Data status (%d), client %d, version 0x%08X"), type, client, dwVersion);
				break;
			}
			break;
		}

	default:
		FormatData(GetData(), GetDataLen(), retStr);
	}
	return true;
}

bool CDiagMessageDiagEx::ConvertCCString(CString &retStr)
{
	if ( !FormatExportedFunctionData(retStr) )
		FormatData(GetData(), GetDataLen(), retStr);
	return true;
}

bool CDiagMessageDspEx::ConvertCCString(CString &retStr)
{
	WORD opCode = GetEntireDspOpCode();
	
	
	WORD bDataBit = (opCode & 0x2000);
	if ( bDataBit )
	{	
		if (m_pRec->m_bIsExtReport)
		{
			WORD extLen = GetDspDataLen();
			
			///////////////////////////////////////////////////////////////////////
			///////////////////// Data Packet //////////////////////////////////////
//			FormatData(GetData(4) + (extLen * 2), GetDataLen() - (4 + (extLen * 2)), tmpDataPacket);
			
			FormatData(GetData(4), extLen * 2, retStr);
		}
		else
		{
			WORD regularDataLen = *((WORD *)(GetData(4)));
			
			WORD dataChannelLength = *((WORD *)(GetData(8)));
			FormatData(GetData(14), regularDataLen, retStr);
		}
	}
	else
	{
		FormatData(GetData(4), GetDataLen() - 4, retStr);
	}
	return true;	
}

bool CDiagMessageGKIEx::ConvertCCString(CString &retStr)
{
	switch(GetDiagSap())
	{
	case  DIAG_MI_COMMAND:
		{
			BYTE GKICommandID = *GetData(); 
						
			CString GKICommandName;
			if ( !theConverterManager(m_pIcatMessage->GetDevice())->LookupGKICommand((WORD)GKICommandID, GKICommandName) )
				GKICommandName.Format(_T("Unknown Signal - 0x%4.4x"), GKICommandID);
						
			///////////////////////////////////////////////////////////////
			///////////////////// Data ////////////////////////////////////
			retStr = GKICommandName;
			
			if (m_pMessageConversionData)
			{
				m_pMessageConversionData->strStruct = GKICommandName;
			}
			
		}
		break;
	
	case DIAG_MI_SIGNAL:
		{
			DWORD signalID = GetSignalId();

			CString strSignalName, strSignalGroup;
			if (!theConverterManager(m_pIcatMessage->GetDevice())->LookupSignal(signalID, strSignalName, strSignalGroup) )
			{
				if (  GetSignalIdSize() == 2 )
					strSignalName.Format(_T("Unknown Signal - 0x%4.4x"), signalID);
				else // == 4
					strSignalName.Format(_T("Unknown Signal - 0x%8.8x"), signalID);
			}
							
			retStr = strSignalName;
		}
		break;
	}
	return true;
}

bool CDiagMessageEx::GetClientName( int nId, CString &strName )
{
	switch(nId)
	{
	case UE_None: 
		strName = "None";
		break;
	case UE_Comm_Side: 
		strName = "Comm";
		break;
	case UE_App_Side:
		strName = "App";
		break;
	case UE_MTSD_cid:
		strName = "MTSD";
		break;
	case UE_Audio_cid:
		strName = "Audio";
		break;
	case UE_Error_Handler_cid:
		strName = "Error Handler";
		break;
	case UE_VAL_IF_cid:
		strName = "Val IF";
		break;
	case UE_Apps_Diag_Server_cid:
		strName = "Apps_Diag_Server";
		break;
	case UE_AP_Diag_Server_cid:
		strName = "AP_Diag_Server";
		break;
	case UE_DSP_cid:
		strName = "DSP";
		break;
	case UE_RF_Bin_cid:
		strName = "RF_Bin";
		break;
	case UE_ALL_Clients:
		strName = "ALL";
		break;
	case UE_Diag_Server_cid:
		strName = "Diag_Server";
		break;
	case 0xFF:
		strName = "ACAT";
		break;
	default:
		strName.Format(_T("%d"), nId);
	}
	return true;
}


bool CDiagMessageEx::GetClientID(const CString &strName , int &nId)
{
	if (strName.Compare(_T("None")) == 0)
	{
		nId = UE_None;
		return true;
	}
	if (strName.Compare(_T("Comm")) == 0)
	{
		nId = UE_Comm_Side;
		return true;
	}
	if (strName.Compare(_T("App")) == 0)
	{
		nId = UE_App_Side;
		return true;
	}
	if (strName.Compare(_T("MTSD")) == 0)
	{
		nId = UE_MTSD_cid;
		return true;
	}
	if (strName.Compare(_T("Audio")) == 0)
	{
		nId = UE_Audio_cid;
		return true;
	}
	if (strName.Compare(_T("Error Handler")) == 0)
	{
		nId = UE_Error_Handler_cid;
		return true;
	}
	if (strName.Compare(_T("Val IF")) == 0)
	{
		nId = UE_VAL_IF_cid;
		return true;
	}
	if (strName.Compare(_T("Apps_Diag_Server")) == 0)
	{
		nId = UE_Apps_Diag_Server_cid;
		return true;
	}
	if (strName.Compare(_T("AP_Diag_Server")) == 0)
	{
		nId = UE_AP_Diag_Server_cid;
		return true;
	}
	if (strName.Compare(_T("DSP")) == 0)
	{
		nId = UE_DSP_cid;
		return true;
	}
	if (strName.Compare(_T("RF_Bin")) == 0)
	{
		nId = UE_RF_Bin_cid;
		return true;
	}
	if (strName.Compare(_T("ALL")) == 0)
	{
		nId = UE_ALL_Clients;
		return true;
	}
	if (strName.Compare(_T("Diag_Server")) == 0)
	{
		nId = UE_Diag_Server_cid;
		return true;
	}
	if (strName.Compare(_T("ACAT")) == 0)
	{
		nId = 0xFF;
		return true;
	}


	return false;
}

bool CStringMessageEx::ConvertCCString(CString &retStr)
{
	return ConvertString(retStr);
}

bool CStringMessageEx::ConvertString(CString &retStr)
{
	retStr.Empty();
	
	if ( m_pMessageReaderEx->m_RawMessagePresentation == RAW_MESSAGE_PRES_ASCII  || IsPrintMessage() )
	{
		retStr = CString((char*)GetData(), GetDataLen());
		retStr.Replace(_T("\r"), _T(" "));
		retStr.Replace(_T("\n"), _T(" "));
		retStr.Replace(_T("\t"), _T("  "));
		retStr.Replace(_T("\b"), _T(""));
		retStr.Remove(_T('\0'));
	}
	else if ( m_pMessageReaderEx->m_RawMessagePresentation == RAW_MESSAGE_PRES_NUMERIC )
	{
		FormatData(GetData(), GetDataLen(), retStr);
	}
	else if ( m_pMessageReaderEx->m_RawMessagePresentation == RAW_MESSAGE_PRES_BOTH )
	{
		retStr = CString((char*)GetData(), GetDataLen());
		retStr.Replace(_T("\r"), _T(" "));
		retStr.Replace(_T("\n"), _T(" "));
		retStr.Replace(_T("\t"), _T("  "));
		retStr.Replace(_T("\b"), _T(""));
		retStr.Remove(_T('\0'));

		CString tempstr;
		FormatData(GetData(), GetDataLen(), tempstr);

		retStr += _T(" [ ") + tempstr + _T("]");
	}

	return true;
}


bool CDiagMessageHexEx::ConvertCCString( CString &retStr )
{
	return ConvertString(retStr);
}

bool CDiagMessageHexEx::ConvertString( CString &retStr )
{
	retStr.Empty();
	BYTE * pData = GetDataBuffer();
	if (pData == NULL)
		return false;

	FormatData(pData, GetDataBufferLen(), retStr);
	return true;
}

bool CErrorMessageEx::ConvertCCString( CString &retStr )
{
	return ConvertString(retStr);
}

bool CErrorMessageEx::ConvertString( CString &retStr )
{
	retStr.Empty();
	BYTE * pData = GetDataBuffer();
	if (pData == NULL)
		return false;

	FormatData(pData, GetDataBufferLen(), retStr);
	return true;
}
