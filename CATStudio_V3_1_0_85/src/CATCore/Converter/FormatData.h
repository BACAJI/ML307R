#pragma once


#define RAW_DATA_FORMAT_BYTE	0
#define RAW_DATA_FORMAT_WORD	1
#define RAW_DATA_FORMAT_DWORD	2

#define RAW_DATA_PRES_DEC		0
#define RAW_DATA_PRES_HEX		1

#define RAW_MESSAGE_PRES_ASCII	0
#define RAW_MESSAGE_PRES_NUMERIC	1
#define RAW_MESSAGE_PRES_BOTH	2

#define STRUCT_PRES_NAME		0
#define STRUCT_PRES_DATA		1

#define TIME_STAMP_FORMAT_TICKS				0
#define TIME_STAMP_FORMAT_COTULLA_TIME		1
#define TIME_STAMP_FORMAT_WHITESAIL_SLOW	2
#define TIME_STAMP_FORMAT_WHITESAIL_FAST	3

#define TIME_STAMP_TEXT_FORMAT_MINUTES	0
#define TIME_STAMP_TEXT_FORMAT_SECONDS	1
#define TIME_STAMP_TEXT_FORMAT_HOUR		2

#define ENUM_PRES_DEC			0
#define ENUM_PRES_HEX			1
#define ENUM_PRES_CHAR			2
#define ENUM_PRES_NAME			3

#ifdef _CATCORE_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT CFormatData
{
public:
	virtual ~CFormatData();
	static CFormatData* Instance();
	static void DestroyInstance();

	void SetParameters();
	void ReadParemeters();

protected:
	CFormatData();
	static CFormatData* m_pInstance;

public:
	int		m_RawFormat;
	int		m_RawPres;
	int		m_TimeStampFormat;
	int		m_RawMessagePresentation;
	int		m_StructPres;
	BOOL	m_bLeadingZeros;
	int		m_TimeStampTextFormat;
	char	m_FormatLetter;
};