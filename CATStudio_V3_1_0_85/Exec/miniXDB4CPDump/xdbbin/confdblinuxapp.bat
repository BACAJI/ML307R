:--------------------------------------------------------------------------------
:
:Copyright(C) 2006-2008 Marvell International Ltd.
:All Rights Reserved  
:
:--------------------------------------------------------------------------------

: --------------------------------------------------------------------------------
:
: INTEL CONFIDENTIAL
:
: Copyright 2001-2006 Intel Corporation All Rights Reserved.
: 
: The source code contained or described herein and all documents related to
: the source code ("Material") are owned by Intel Corporation or its 
: suppliers or licensors. Title to the Material remains with Intel 
: Corporation or its suppliers and licensors. The Material contains trade
: secrets and proprietary and confidential information of Intel or its 
: suppliers and licensors. The Material is protected by worldwide copyright 
: and trade secret laws and treaty provisions. No part of the Material may be
: used, copied, reproduced, modified, published, uploaded, posted, 
: transmitted, distributed, or disclosed in any way without Intel's prior 
: express written permission.
:
: No license under any patent, copyright, trade secret or other intellectual 
: property right is granted to or conferred upon you by disclosure or 
: delivery of the Materials, either expressly, by implication, inducement, 
: estoppel or otherwise. Any license under such intellectual property rights 
: must be express and approved by Intel in writing.
:
:
: --------------------------------------------------------------------------------
@REM ----------------------------------------------------------------------------------------------
@REM MARVELL INTERNATIONAL LTD., ON BEHALF OF ITSELF AND ITS WORLDWIDE 
@REM AFFILIATES(COLLECTIVELY, "MARVELL"), MAKES NO WARRANTY OF ANY KIND WITH 
@REM REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
@REM OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
@REM MARVELL ASSUMES NO RESPONSIBILITY FOR ANY ERRORS THAT MAY 
@REM APPEAR IN THIS DOCUMENT. MARVELL MAKES NO COMMITMENT TO 
@REM UPDATE NOR TO KEEP CURRENT THE INFORMATION CONTAINED IN THIS DOCUMENT.
@REM ------------------------------------------------------------------------------------------------
@ECHO OFF
@REM Edit confdb.ini for Monitor
IF NOT EXIST .\edconfdb.exe GOTO end1
IF NOT EXIST ..\xdb\confdb.ini GOTO end2
.\edconfdb.exe -confdb ..\xdb\confdb.ini -addcore CPU -cpu .\..\plugin\marvellpxa\cpu\xscpu.dll
.\edconfdb.exe -confdb ..\xdb\confdb.ini -addconnection LinuxApp -core CPU -tci .\tci\marvellpxa\mon\sc\tci.dll -startupdll pplinapp.dll -startuppage linapp
@REM .\edconfdb.exe -confdb ..\xdb\confdb.ini -addtarget "Application Debugger for Linux Serial COM1" -core CPU -connection LinuxApp -versiondll "xdbmonxs.dll" -defaultargs -l com1:115200,n,8,1 -plg \"..\plugin\marvellpxa\linuxapp\linuxapp.dll,..\plugin\marvellpxa\trace\linuxapp\trace.dll\"
@REM .\edconfdb.exe -confdb ..\xdb\confdb.ini -addtarget "Application Debugger for Linux Serial COM2" -core CPU -connection LinuxApp -versiondll "xdbmonxs.dll" -defaultargs -l com2:115200,n,8,1 -plg \"..\plugin\marvellpxa\linuxapp\linuxapp.dll,..\plugin\marvellpxa\trace\linuxapp\trace.dll\"
@REM .\edconfdb.exe -confdb ..\xdb\confdb.ini -addtarget "Application Debugger for Linux UDP/IP" -core CPU -connection LinuxApp -versiondll "xdbmonxs.dll" -defaultargs -l udpip:192.168.1.101:8911 -plg \"..\plugin\marvellpxa\linuxapp\linuxapp.dll,..\plugin\marvellpxa\trace\linuxapp\trace.dll\"
.\edconfdb.exe -confdb ..\xdb\confdb.ini -addtarget "Application Debugger for Linux UDP/IP" -core CPU -connection LinuxApp -versiondll "xdbmonxs.dll" -defaultargs -l udpip:192.168.1.101:8911 -plg \"..\plugin\marvellpxa\linuxapp\linuxapp.dll\"
goto end
:end1
echo ".\edconfdb.exe not exists"
goto end
:end2
echo "..\xdb\confdb.ini not exists"
goto end
:end
