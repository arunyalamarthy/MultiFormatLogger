#pragma once
#ifdef LOGGER_EXPORTS // inside DLL
   #define LOGAPI   //__declspec(dllexport)
#else // outside DLL
   #define LOGAPI   //__declspec(dllimport)
#endif

#include <atlstr.h>

typedef enum LOG_LEVEL
{
   LOG_LEVEL_NONE = 0,
   LOG_LEVEL_ERROR = 1,
   LOG_LEVEL_DEBUG = 2,
   LOG_LEVEL_INFO  = 3,
} LogLevel;

typedef enum LOG_TYPE
{
   OUTPUT_DEBUG_LOG	= 1,
   CONSOLE_LOG		= 2,
   FILE_LOG			= 3,
} LogType;


class LOGAPI ILogger
{
 public:
   virtual bool EnableLog(LogLevel level, LogType type=OUTPUT_DEBUG_LOG, const TCHAR* filename=NULL)=0;
   virtual void DisableLog()=0;
   virtual void LOG_ERROR(const wchar_t* text,...)=0;
   virtual void LOG_DEBUG(const wchar_t *lpszFormat, ...)=0;
   virtual void LOG_INFO(const wchar_t *lpszFormat, ...)=0;
   virtual void logRelease()=0;
};

// Factory function that creates instances of the Logger object.
extern "C" LOGAPI ILogger* GetLogger();
