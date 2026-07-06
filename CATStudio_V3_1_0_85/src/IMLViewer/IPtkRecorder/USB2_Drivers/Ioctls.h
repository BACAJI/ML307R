// IOCTLS.H -- IOCTL code definitions for COTULLAUSB driver
// Copyright (C) 2002 by Ido Alperovich
// All rights reserved

#ifndef IOCTLS_H
#define IOCTLS_H

typedef struct _VCR_PARAM
{
	UCHAR Function;
	UCHAR request;
	USHORT reserved;
	ULONG Direction;
	PVOID Buffer;
	ULONG BufferLength;
}VCR_PARAM, *PVCR_PARAM;

/*
#ifndef CTL_CODE
	#pragma message("CTL_CODE undefined. Include winioctl.h or wdm.h")
#endif
*/
#define VENDOR_CALASS_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)

#endif
