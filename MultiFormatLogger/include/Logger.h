#pragma once
#include <ILogger.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <atlstr.h>

class CLogger : public ILogger
{
 public:
   CLogger(void);
   ~CLogger(void);
   virtual bool EnableLog(LogLevel level=LOG_LEVEL_ERROR, LogType type=OUTPUT_DEBUG_LOG, const TCHAR* filename=NULL);
   //virtual void EnableLog(LogLevel level);
   virtual void DisableLog();
   virtual void LOG_ERROR(const TCHAR *lpszFormat, ...);
   virtual void LOG_DEBUG(const TCHAR *lpszFormat, ...);
   virtual void LOG_INFO(const TCHAR *lpszFormat, ...);
   virtual void logRelease();
 private:
   LogLevel m_LogLevel;
   LogType  m_LogType;
   std::wofstream m_File;
   const TCHAR* m_filename;
 private:
   void logIntoFile(CString& data);
   void logOnConsole(CString& data);
   void log(CString& data, LogLevel level);
   void logHtml(CString& data, LogLevel level);
};