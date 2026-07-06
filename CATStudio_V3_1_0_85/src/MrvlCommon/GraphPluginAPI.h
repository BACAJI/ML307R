// GraphPlugin.h
// API
#ifndef _GRAPH_PLUGIN_2012_03_07_
#define _GRAPH_PLUGIN_2012_03_07_


long __declspec(dllexport) Initialize();
long __declspec(dllexport) GetPluginInformation(void* buffer, int nBufLen);
long __declspec(dllexport) HandleMessage(EMessageType eMsgType, void* pMessage, void* pOutBuffer, int nOutBufLen);
void __declspec(dllexport) Terminate();

#endif