#pragma once

template<class Tp>
class  MessageHandler
{
public:
   virtual long HandleMessage(Tp& message)=0;


   enum EErrorCode
   {
      eHandlerNotFound = -1,
   };
};


template<class Tp>
class EventHandler
{
public:
   virtual long HandleEvent(Tp& event) = 0;
};