/*--------------------------------------------------------------------------------------------------------------------

 (C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved  

-------------------------------------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////
//GsmMsgDefines.h

#ifndef GSMMSGDEFINES_H
#define GSMMSGDEFINES_H


	enum EStructArrIndices
	{
		kStrType	= 0,
		kStrName	= 1
	};
	

	enum EDataOffsets
	{
		PROT_DISCR_SIZE			=	1, 
		L3_MSG_TYPE_OFFSET		=	4,
		MSG_HEADER_SIZE			=   8,
		MSG_STAT_SIZE			=	32,
		MSG_BODY_OFFSET			=   MSG_STAT_SIZE + MSG_HEADER_SIZE
	};


#endif