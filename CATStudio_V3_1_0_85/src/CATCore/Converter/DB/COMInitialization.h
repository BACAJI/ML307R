#ifndef __COMINITIALIZATION_H__
#define __COMINITIALIZATION_H__
/*------------------------------------------------------------------------------------------*
 |(C) Copyright 2006,2007 Marvell Semiconductor Israel Ltd. All Rights Reserved				|
 *------------------------------------------------------------------------------------------*/



// #define USE_COM_MTA

#ifndef USE_COM_MTA
#define CoInitializeEx(n,t) CoInitialize(n)
#endif



#endif //__COMINITIALIZATION_H__