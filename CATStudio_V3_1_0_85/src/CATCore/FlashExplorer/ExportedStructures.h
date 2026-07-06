/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/


#if !defined(AFX_EXPORTEDSTRUCTURES_H__INCLUDED_)
#define AFX_EXPORTEDSTRUCTURES_H__INCLUDED_

#define MAX_FILES_NAME_BUFFER			1024
#define MAX_FILE_NAME_LENGTH			256
#define MAX_FILE_BUFFER_SIZE			1024
#define FDI_EX_MAX_READFILE_BUFFER_SIZE     4096
#define FDI_EX_MAX_WRITEFILE_BUFFER_SIZE     2048
#define ERR_NONE						0
#define ERR_EOF							0x22

#define FFS_WRAPPER_NUM_VOLUMES           6
#define FFS_WRAPPER_VOLUME_NAME_LENGTH    10


typedef struct
{
    short  nFileID;			
    short  bufferSize;
}ReadInputStruct5;

typedef struct
{
    UINT32 nFileID;			
    short  bufferSize;
}ReadInputStruct6;

typedef struct 
{
	short  PacketOK;		// 2 bytes
	short  LastPacket;		// 2 byte
	short  PacketSize;		// 2 bytes
	BYTE   readBuf[1024];	// 1024 bytes
} ReadReturnStruct;

typedef struct
{
	short	nFileID;		// 2 bytes
	short	PacketSize;		// 2 bytes
	BYTE	writeBuf[1024];	// 1024 bytes
} WriteInputStruct5; 

typedef struct
{
	UINT32	nFileID;		// 4 bytes
	short	PacketSize;		// 2 bytes
	BYTE	writeBuf[1024];	// 1024 bytes
} WriteInputStruct6; 

typedef struct
{
	short	nFileID;		// 2 bytes
	short	PacketSize;		// 2 bytes
	UINT32  filePos;       //数据块在文件中的起始位置
	UINT32  remainBytes;   //剩余数据大小
	BYTE	writeBuf[FDI_EX_MAX_WRITEFILE_BUFFER_SIZE];	// 2048 bytes
} WriteInputStruct5_Ex; 

typedef struct
{
	UINT32	nFileID;		// 4 bytes
	short	PacketSize;		// 2 bytes
	UINT32  filePos;       //数据块在文件中的起始位置
	UINT32  remainBytes;   //剩余数据大小
	BYTE	writeBuf[FDI_EX_MAX_WRITEFILE_BUFFER_SIZE];	// 2048 bytes
} WriteInputStruct6_Ex;

typedef struct 
{
	short	nFileID;		// 4 bytes
	short  PacketOK;		// 2 bytes
	short  PacketSize;		// 2 bytes
	UINT32 filepos;         //数据块在文件中的起始位置
	UINT32 reserved;        //resreved

} WriteReturnStruct5_Ex;

typedef struct 
{
	UINT32	nFileID;		// 4 bytes
	short  PacketOK;		// 2 bytes
	short  PacketSize;		// 2 bytes
	UINT32 filepos;         //数据块在文件中的起始位置
	UINT32 reserved;        //resreved

} WriteReturnStruct6_Ex;

typedef struct
{
	short  nFileID;			
	short  bufferSize;
	UINT32 filepos;        //数据块在文件中的起始位置
	UINT32 sizetoread;     //数据块在文件中的长度
	UINT32  nDataBlockSize; //数据块size
}ReadInputStruct5_Ex;

typedef struct
{
	UINT32 nFileID;			
	short  bufferSize;
	UINT32 filepos;        //数据块在文件中的起始位置
	UINT32 sizetoread;     //数据块在文件中的长度
	UINT32  nDataBlockSize;  //数据块size
}ReadInputStruct6_Ex;

typedef struct 
{
	short  nFileID;	
	short  PacketOK;		// 2 bytes
	short  LastPacket;		// 2 byte
	short  PacketSize;		// 2 bytes
	UINT32 filepos;        //数据块在文件中的起始位置
	BYTE   readBuf[FDI_EX_MAX_READFILE_BUFFER_SIZE];	// 2048 bytes
} ReadReturnStruct5_Ex;

typedef struct 
{
	UINT32  nFileID;	
	short  PacketOK;		// 2 bytes
	short  LastPacket;		// 2 byte
	short  PacketSize;		// 2 bytes
	UINT32 filepos;        //数据块在文件中的起始位置
	BYTE   readBuf[FDI_EX_MAX_READFILE_BUFFER_SIZE];	// 2048 bytes
} ReadReturnStruct6_Ex;
//FDI8 Structure definition
typedef struct
{
	UINT32	u32Checksum;					// Checksum of this structure except checksum itself //<CHS>校验和，异或数据以及加位置</CHS>
    char   fileName[MAX_FILE_NAME_LENGTH];
    char   mode[MAX_FILE_NAME_LENGTH];
}FOpenInputStruct8;
//ICAT EXPORTED STRUCT
typedef struct
{
	UINT32	 u32Checksum;					// Checksum of this structure except checksum itself //<CHS>校验和，异或数据以及加位置</CHS>
	UINT16	 u16FileID;                        // an ID of an already open file in Flash memory.
	UINT16   u16FileAttr;					// file attribute
	UINT32   u32SizeLow;					// low 32bits part of file size
	UINT32   u32SizeHigh;					// low 32bits part of file size
	UINT32   u32ModifyTime;					// file modification time
	char   szFileName[MAX_FILE_NAME_LENGTH];	// name of file located in Flash (or to be create)
} FOpenReturnStruct8;

//ICAT EXPORTED STRUCT
typedef struct
{
	UINT32	u32Checksum;					// Checksum of this structure except checksum itself //<CHS>校验和，异或数据以及加位置</CHS>
    UINT16  u16FileID; 
	UINT16  u16Padding;
	UINT32	u32Offset;
	UINT32	u32WhereFrom;
}FSeekStruct8;

typedef struct
{
	UINT32	u32Checksum;					// Checksum of this structure except checksum itself //<CHS>校验和，异或数据以及加位置</CHS>
    UINT16  u16FileID;
    UINT16  u16Option;						// 0: NORMAL, 1: Cancel writing, 2: Validate filesize and checksum, if failed then cancel writing //<CHS></CHS>
    UINT32  u32FileSize;					// File size of writing file //<CHS></CHS>
	UINT32  u32FileDigest;					// digest of writing file for checksum, such as CRC32 //<CHS></CHS>
}FCloseInputStruct8;
//ICAT EXPORTED STRUCT
typedef struct
{
	UINT32  u32Checksum;					// Checksum of this structure except checksum itself //<CHS>校验和，异或数据以及加位置</CHS>
	UINT16	u16FileID;						// File ID of the file being handled. //<CHS>16位文件ID</CHS>
	UINT16  u16PacketSize;					// size of packet being transfered. //<CHS>当前包的acWriteBuf数据长度，<=MAX_RFDI_WRITE_BUFFER_SIZE</CHS>
	UINT32  u32FilePos;						// offset to start to write //<CHS>文件位置</CHS>
	UINT32  u32RemainBytes;					// offset to start to write //<CHS>文件剩余大小，不包含本数据包，如果=0表示此包是文件的最后一个数据包</CHS>
	char    WriteBuf[FDI_EX_MAX_WRITEFILE_BUFFER_SIZE];	// buffer of bytes to be written //<CHS>数据，最大长度取决于传输通道特性</CHS>
}WriteInputStruct8;

//ICAT EXPORTED STRUCT
typedef struct
{
	UINT32	u32Checksum;					// Checksum of this structure except checksum itself //<CHS>校验和，异或数据以及加位置</CHS>
	UINT16  u16FileID;						// File ID of the file being handled. //<CHS></CHS>
	UINT16  u16ErrCode;						// Contian the error code see FDI Doc (e.g. ERR_OK) //<CHS></CHS>
	UINT32  u32InputChecksum;				// Checksum of WritInputStruct,use to compare with input structure. //<CHS></CHS>
}WriteReturnStruct8;

//ICAT EXPORTED STRUCT
typedef struct
{
	UINT32	u32Checksum;					// Checksum of this structure except checksum itself //<CHS>余下数据的校验和</CHS>
    UINT16  u16FileID;						// File ID of the file being handled //<CHS>16位文件ID</CHS>
    UINT16  u16PacketSize;					// each packet size to read from current filepos //<CHS>希望ＵＥ返回数据的每包大小</CHS>
    UINT32  u32FilePos;						// offset to start to read//<CHS>文件位置</CHS>
    UINT32  u32SizetoRead;					// total size to read from current filepos //<CHS>想从UE读到的数据总长</CHS>
}ReadInputStruct8;

//ICAT EXPORTED STRUCT
typedef struct
{
	UINT32	u32Checksum;					// Checksum of this structure except checksum itself //<CHS>校验和，异或数据以及加位置</CHS>
    UINT16  u16FileID;						// File ID of the file being handled //<CHS>16位文件ID</CHS>
    UINT16  u16ErrCode;						// Contian the error code see FDI Doc (e.g. ERR_OK) //<CHS>16位错误返回值</CHS>
    UINT16  u16Flag;						// equal to 1 if it's the last packet, 0 - otherwise. //<CHS></CHS>
    UINT16  u16PacketSize;					// size in bytes of the buffer being read from file. //<CHS>此包包括的数据长度</CHS>
    UINT32  u32Offset;						 // offset to first packet to read //<CHS>距离第一个包位置，第一个包是０</CHS>
    char    readBuf[FDI_EX_MAX_READFILE_BUFFER_SIZE];  // buffer of bytes contains the Flash file data. //<CHS></CHS>
} ReadReturnStruct8;

#define RFDI_CLOSE_OPTION_NORMAL 0
#define RFDI_CLOSE_OPTION_CANCEL 1
#define RFDI_CLOSE_OPTION_CHECK 2

//ICAT EXPORTED STRUCT
typedef struct
{
	UINT32	u32Checksum;					// Checksum of this structure except checksum itself //<CHS>校验和，异或数据以及加位置</CHS>
    UINT32  fileID;
    UINT16  u16Option;		          // 0: NORMAL, 1: Cancel writing, 2: Validate filesize and checksum, if failed then cancel writing //<CHS></CHS>
    UINT32  u32FileSize;             // File size of writing file //<CHS></CHS>
	UINT32  u32FileDigest;             // digest of writing file for checksum, such as CRC32 //<CHS></CHS>
}FCloseInputStruct;

#define RFDI_CONTEXT_FLAG_NOT_USED	0
#define RFDI_CONTEXT_FLAG_WRITE	1
#define RFDI_CONTEXT_FLAG_READ	2
#define RFDI_CONTEXT_FLAG_ERROR	0x8000

typedef struct
{
    UINT16  u16Flag;                         // Flag=0: not used, 0x1: writing, 0x2: reading, 0x8000: error //<CHS></CHS>
    UINT32  fileID;                         // File ID of the file being handled, 0xFFFF: invalid //<CHS></CHS>
	char   szFilename[FDI_EX_MAX_READFILE_BUFFER_SIZE];
//    UINT32  u32WrNum;                       // number of valid items in au32WrFilePos //<CHS></CHS>
//    UINT32  au32WrFilePos[MAX_RFDI_WRITE_BURST_NUM];                     // support MAX_RFDI_WRITE_BURST_NUM each burst time, matching PC CATStudio FlashExplorer //<CHS></CHS>
//    UINT32  au32WrCheckSum[MAX_RFDI_WRITE_BURST_NUM];                     // support MAX_RFDI_WRITE_BURST_NUM each burst time, matching PC CATStudio FlashExplorer //<CHS></CHS>
    UINT32  u32WrFirstContPos;                       // first filepos of continuous packets after fseek //<CHS></CHS>
    UINT32  u32WrLastContPos;                       // last filepos of continuous packets //<CHS></CHS>
//    UINT32  u32WrFirstMissPos;                       // first filepos of missed packet //<CHS></CHS>
//    UINT32  u32WrFirstMissLen;                       //  length of first missed filepos //<CHS></CHS>
    WriteReturnStruct8 sWrRetBuf;		// reduce malloc //<CHS></CHS>
    ReadReturnStruct8 sRdRetBuf;		// reduce malloc //<CHS></CHS>
}SRfdiContext;

typedef struct 
{
	UINT32	nBeginPos;
	UINT32	nsize;
}FailedPackageStruct;

typedef struct 
{
	UINT32	PacketId;
	UINT32	Checksum;
	UINT32	FilePos;
	UINT32	Offset;
	UINT32  PacketSize;
	
}SentPacketStruct;

typedef struct
{
    BYTE   fNamesList[MAX_FILES_NAME_BUFFER];
    short  fNamesListLen;
		BYTE   isLastPacket;
}FNamesReturnStruct;

typedef struct
{
    BYTE   fOldName[256];
    BYTE   fNewName[256];
}RenameInputStruct;

typedef struct
{
    BYTE   fileName[MAX_FILE_NAME_LENGTH];
    BYTE   mode[MAX_FILE_NAME_LENGTH];
}FOpenInputStruct;

typedef struct
{
	short	nFileID;
    BYTE	fileName[MAX_FILE_NAME_LENGTH];
} FOpenReturnStruct5;

typedef struct
{
	UINT32	nFileID;
    BYTE	fileName[MAX_FILE_NAME_LENGTH];
} FOpenReturnStruct6;

typedef struct
{
    BYTE      fileName[MAX_FILE_NAME_LENGTH];                         // File ID of the file being handled.
    UINT32	  newMode;
}ChangModeStruct;

typedef struct
{
    unsigned char second;	//  Seconds after minute: 0 - 59
    unsigned char minute;	//  Minutes after hour: 0 - 59
    unsigned char  hour;	//  Hours after midnight: 0 - 23
    unsigned char day;		//  Day of month: 1 - 31
    unsigned char month;	//  Month of year: 1 - 12
    unsigned short year;	//  Calendar year: e.g 2001
}RTC_CalendarTime;

typedef struct
{
    short nFileID; 
	int	  offset;
	int	  whereFrom;
}FSeekStruct5;

typedef struct
{
    UINT32	nFileID; 
	int		offset;
	int		whereFrom;
}FSeekStruct6;

typedef struct
{
	UINT32	 fdvAvailableSpace;
}FdvAvailableSpaceStruct;

typedef struct
{
    UINT64   fdvSize;
}FdvSizeStruct;


typedef struct
{
    BYTE    dirName[MAX_FILE_NAME_LENGTH];
	short	mode;
}MkDirStruct;


typedef struct
{
    BYTE	dirName[MAX_FILE_NAME_LENGTH];
}RmDirStruct;


typedef struct
{
	BYTE	 ffs_num_volumes;
	TCHAR   volumes[FFS_WRAPPER_NUM_VOLUMES][FFS_WRAPPER_VOLUME_NAME_LENGTH];
}FdvVolumesStruct;

typedef struct 
{
	UINT32	size;
}SizeStruct;

#endif // !defined(AFX_EXPORTEDSTRUCTURES_H__INCLUDED_)
