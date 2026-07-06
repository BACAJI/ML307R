#ifndef _MEED_H_
#define _MEED_H_


/*  | Length  | Preamble |  Index  | Reserved |  Type   |  SubType  |  Data     | Paddings   |
 *  | 2 Bytes | 2 Bytes  | 2 Bytes | 2 Bytes  | 2 Bytes |  2 Bytes  |  N Bytes  | 0 ~ 3 Bytes|
 *  
 *  Length:   整个PDU的长度，包括头部和数据部分，必须为4字节整数倍，如果不足4字节，则在Data尾部补Paddings.
 *  Preamble: PDU的标识码，0xA9A9
 *  Index :   PDU的索引号，从0开始，递增到0xFFFF后回到0
 *  Reserved: 保留字
 *  Type:     PDU类型ID
 *  SubType:  PDU子类型ID
 *  Data:     PDU载荷
 *  Paddings: 0~3个0x00，使整个PDU长度为4字节倍数
 */

#define MEED_LEN_INDEX           0
#define MEED_PREAMBLE_INDEX      2
#define MEED_INDEX_INDEX         4
#define MEED_RESERVED_INDEX      6
#define MEED_TYPE_INDEX          8
#define MEED_SUBTYPE_INDEX       10
#define MEED_DATA_INDEX          12

#define MEED_PREAMBLE            0xA9A9
#define MEED_HEAD_LEN            12

#define GetMeedLen(buf)          (*(WORD*) (((BYTE*)(buf))+MEED_LEN_INDEX))
#define GetMeedPreamble(buf)     (*(WORD*) (((BYTE*)(buf))+MEED_PREAMBLE))
#define GetMeedIndex(buf)        (*(WORD*) (((BYTE*)(buf))+MEED_INDEX_INDEX))
#define GetMeedReserved(buf)     (*(WORD*) (((BYTE*)(buf))+MEED_RESERVED_INDEX))
#define GetMeedType(buf)         (*(WORD*) (((BYTE*)(buf))+MEED_TYPE_INDEX))
#define GetMeedSubType(buf)      (*(WORD*) (((BYTE*)(buf))+MEED_SUBTYPE_INDEX))
#define GetMeedData(buf)         ((BYTE*) ((BYTE*)buf)+MEED_DATA_INDEX))

struct MeedHeader
{
   WORD  wPduLen;
   WORD  wPreamble;
   WORD  wIndex;
   WORD  wReserved;
   WORD  wType;
   WORD  wSubType;
};





#endif //_MEED_H_