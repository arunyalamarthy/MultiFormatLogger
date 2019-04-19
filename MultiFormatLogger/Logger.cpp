// Logger.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <ILogger.h>
#include "Logger.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <atlstr.h>
#include <atltime.h>

using namespace std;

CLogger :: CLogger()
{
   m_filename = nullptr;
   m_LogLevel = LOG_LEVEL_ERROR;
   m_LogType = OUTPUT_DEBUG_LOG;
}


CLogger ::~CLogger(void)
{
	//ending html
	if (m_LogType == HTML_FILE_LOG)
	m_File << "</body></html>";
	//myfile.close();
   m_File.close();
}


bool CLogger ::EnableLog(LogLevel level, LogType type, const TCHAR* filename)
{
   USES_CONVERSION;
   m_LogLevel = level;
   m_filename = filename;
   LogType prevLogtype = m_LogType;
   m_LogType = type;

   if (m_LogType == FILE_LOG)
   {
	   if (m_filename)
	   {
		   m_File.open((m_filename));
		   //ofstream myfile;
		   //m_File.open("report.html");
		   m_File << "<!DOCTYPE html><html><head></head><body>"; //starting html

	   }
      else
      {
         m_LogType = prevLogtype;
         return false;
      }
   }

   if (m_LogType == HTML_FILE_LOG)
   {
	   if (m_filename)
	   {
		   //ensure it ends with html or append it
		   m_File.open((m_filename));
		   m_File << "<!DOCTYPE html><html><head></head><body>"; //starting html

	   }
	   else
	   {
		   m_LogType = prevLogtype;
		   return false;
	   }
   }

   return true;
}


void CLogger ::DisableLog()
{
   m_LogLevel = LOG_LEVEL_NONE;
}


void CLogger ::LOG_ERROR(const TCHAR *lpszFormat, ...)
{
   va_list args;
   va_start(args, lpszFormat);

   TCHAR szBuffer[8192] = {};
   _vsntprintf_s(szBuffer, _countof(szBuffer), _TRUNCATE,lpszFormat, args);
   CString strDebug;
   strDebug.Format(_T("%s:%s"), _T("[ERROR]:"), szBuffer);
   log(strDebug, LOG_LEVEL_ERROR);

   va_end(args);
}


void CLogger ::LOG_DEBUG(const TCHAR *lpszFormat, ...)
{
   va_list args = nullptr;
   va_start(args, lpszFormat);
   TCHAR szBuffer[8192] = {};
   _vsntprintf_s(szBuffer, _countof(szBuffer), _TRUNCATE, lpszFormat, args);
   CString strDebug;
   strDebug.Format(_T("%s:%s"), _T("[DEBUG]:"), szBuffer);
   log(strDebug, LOG_LEVEL_DEBUG);
   va_end(args);

}

void CLogger ::LOG_INFO(const TCHAR *lpszFormat, ...)
{
   va_list args;
   va_start(args, lpszFormat);
   TCHAR szBuffer[8192] = {};
   _vsntprintf_s(szBuffer, _countof(szBuffer), _TRUNCATE,lpszFormat, args);
   CString strDebug;
   strDebug.Format(_T("%s:%s"), _T("[INFO]:"), szBuffer);
   log(strDebug, LOG_LEVEL_INFO);
   va_end(args);
}

void CLogger ::log(CString& data, LogLevel level)
{
   if (level <= m_LogLevel)
   {
      if(m_LogType == FILE_LOG)
      {
         logIntoFile(data);
      }
      else if(m_LogType == CONSOLE_LOG)
      {
         logOnConsole(data);
      }
      else if (m_LogType == HTML_FILE_LOG)
      {
		  logHtml(data, level);
      }
      else
      {
		  ::OutputDebugString(data);
      }
   }
}

void CLogger ::logIntoFile(CString& data)
{
   USES_CONVERSION;
   CTime atime = CTime::GetCurrentTime();
   CString cur_time = atime.Format(_T("%x:%X"));
   m_File << (cur_time.GetString()) << (data.GetString()) << endl;
}

void CLogger ::logOnConsole(CString& data)
{
   CTime atime;
   atime = CTime::GetCurrentTime();
   CStringW cur_time = atime.Format(_T("%x:%X"));
   printf("\n %s:%s", cur_time.GetString(), data.GetString());
}

void CLogger::logHtml(CString& data, LogLevel level)
{
	CTime atime;
	atime = CTime::GetCurrentTime();
	CStringW cur_time = atime.Format(_T("%x:%X"));
	CString prefix;
	if (level == LOG_LEVEL_INFO)
	{
		prefix = "<p style = 'color:green'>";
	}
	else if (level == LOG_LEVEL_DEBUG)
	{
		prefix = "<p style = 'color:blue'>";
	}
	else //error
	{
		prefix = "<p style = 'color:red'>";
	}


	m_File <<prefix<< (cur_time.GetString()) << (data.GetString()) << "</p>"<<endl;
}


void CLogger ::logRelease()
{
   //not needed right now
}

/********************************************************************************************/
LOGAPI ILogger* GetLogger()
{
   static CLogger aLogger;
   return &aLogger;
}
