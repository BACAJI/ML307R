// GraphComDefs.h

#ifndef _GRAPH_COM_DEFS_
#define _GRAPH_COM_DEFS_

struct GraphPoint
{
   double   x;
   double   y;
   double   z;       // 对于二维点，z是x坐标参数的辅助参数
   DWORD    type;    // 点的类型，二维，三维，，，。需要预定义Enum  
   DWORD    action;  // 控制画图的行为，需要预定义的Enum
   CString  tips;    // 简短的字符串，在Graph中用气球显示
   CString  msg;     // 可以存放额外的较长的信息，在output窗口中显示
};

struct PlugInInfo
{
   CString sPluginInf;
};


bool inline PlugInInfoSerialize(void* buffer, int nBufLen, PlugInInfo& inf)
{  
   int nBytes = sizeof(size_t) + inf.sPluginInf.GetLength()*sizeof(TCHAR);
   if( nBufLen<nBytes )
      return false;

   *(size_t*)buffer = sizeof(TCHAR);
   
   memcpy( ((char*)buffer)+sizeof(size_t), 
      inf.sPluginInf.GetBuffer(0), 
      nBytes-sizeof(size_t) );
   
   return true;
}

bool inline GraphPointSerialize(void* buffer, int nBufLen, GraphPoint& pt)
{
   int nBytes = sizeof(size_t) +  3*sizeof(double)+2*sizeof(long)+2*sizeof(size_t)
      +pt.tips.GetLength()*sizeof(TCHAR) + pt.msg.GetLength()*sizeof(TCHAR);

   if( nBufLen< nBytes )
      return false;


   char* buf = reinterpret_cast<char*>(buffer);


   int off=0;
   *reinterpret_cast<size_t*>(buf+off) = sizeof(TCHAR);
   off += sizeof(long);

   *reinterpret_cast<double*>(buf+off) = pt.x;
   off += sizeof(double);

   *reinterpret_cast<double*>(buf+off) = pt.y;
   off += sizeof(double);

   *reinterpret_cast<double*>(buf+off) = pt.z;
   off += sizeof(double);

   *reinterpret_cast<long*>(buf+off) = pt.type;
   off += sizeof(long);

   *reinterpret_cast<long*>(buf+off) = pt.action;
   off += sizeof(long);

   nBytes = pt.tips.GetLength()*sizeof(TCHAR);
   *reinterpret_cast<size_t*>(buf+off) = nBytes;
   off += sizeof(size_t);

   memcpy(reinterpret_cast<char*>(buf+off), pt.tips.GetBuffer(0), nBytes);
   off += nBytes;

   nBytes = pt.msg.GetLength()*sizeof(TCHAR);
   *reinterpret_cast<size_t*>(buf+off) = nBytes;
   off += sizeof(size_t);

   memcpy(reinterpret_cast<char*>(buf+off), pt.msg.GetBuffer(0), nBytes);
   off += nBytes;

   return true;
}

#endif