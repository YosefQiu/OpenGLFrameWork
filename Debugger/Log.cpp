#include "Log.h"

char szEngineLog[MAX_PATH_FOR_LOG];
static void(*gEngineErrorReporter)(const char* msg) = nullptr;

void SetEngineErrorReporter(void(*foo)(const char* msg))
{
	gEngineErrorReporter = foo;
}

void ReportEngineError(const char* msg) 
{
	if (gEngineErrorReporter != nullptr) 
	{
		gEngineErrorReporter(msg);
	}
	else {
		Error("%s", msg);
	}
}

int  FormatCurrDate(char* szTime, char* szDate)
{
	time_t t;
	time(&t);
	struct tm* today;
	today = localtime(&t);
	strftime(szTime, 32, "%H:%M:%S", today);
	strftime(szDate, 32, "%y-%m-%d", today);
	return 0;
}

int InitEngineLog(const char* engineLog)
{
	int nLen = strlen(engineLog);
	if ((nLen >= MAX_PATH_FOR_LOG) || (nLen <= 0))
		return -1;
	memset(szEngineLog, 0, MAX_PATH_FOR_LOG);
	strcpy(szEngineLog, engineLog);
	return 0;
}

void WriteLog(const char* tag, const char* file, int nLine, const char* szLogContent)
{
	char szTime[32];
	char szDate[32];
	memset(szTime, 0, sizeof(szTime));
	memset(szDate, 0, sizeof(szDate));
	FormatCurrDate(szTime, szDate);
#if RELEASE
	std::string fn;
	fn = szEngineLog;
	fn += ".";
	fn += szDate;
	std::ofstream fd;
	try {
		fd.open(fn.c_str(), std::ios::app);
		fd << szTime << " : " << tag << " " << szLogContent << std::endl;
		fd.close();
	}
	catch (...) {
		printf("open log file exception!\n");
		return;
	}
#else
	printf("%s %s %s\n", szTime, tag, szLogContent);
#endif
}

void DebugLog(const char* file, int nLine, const char* format, ...) 
{
	if (strlen(format) == 0)
		return;
	char szBuffer[MAX_LOG_LENGTH];
	memset(szBuffer, 0, MAX_LOG_LENGTH);
	va_list	l_va;
	va_start(l_va, format);
	vsnprintf(szBuffer, sizeof(szBuffer), format, l_va);
	va_end(l_va);
#if _DEBUG
	WriteLog("[DEBUG] ", file, nLine, szBuffer);
#endif
}

void InfoLog(const char* file, int nLine, const char* format, ...) 
{
	if (strlen(format) == 0)
		return;
	char szBuffer[MAX_LOG_LENGTH];
	memset(szBuffer, 0, MAX_LOG_LENGTH);
	va_list	l_va;
	va_start(l_va, format);
	vsnprintf(szBuffer, sizeof(szBuffer), format, l_va);
	va_end(l_va);
	WriteLog(" [INFO] ", file, nLine, szBuffer);
}

void ErrorLog(const char* file, int nLine, const char* format, ...)
{
	if (strlen(format) == 0)
		return;
	char szBuffer[MAX_LOG_LENGTH];
	memset(szBuffer, 0, MAX_LOG_LENGTH);

	va_list	l_va;
	va_start(l_va, format);
	vsnprintf(szBuffer, sizeof(szBuffer), format, l_va);
	va_end(l_va);
	WriteLog("[ERROR]", file, nLine, szBuffer);
}

void EditorErrorLog(const char* file, int nLine, const char* format, ...)
{
	if (strlen(format) == 0)
		return;
	char szBuffer[MAX_LOG_LENGTH];
	memset(szBuffer, 0, MAX_LOG_LENGTH);
	va_list	l_va;
	va_start(l_va, format);
	vsnprintf(szBuffer, sizeof(szBuffer), format, l_va);
	va_end(l_va);
	if (gEngineErrorReporter) 
	{
		char szTime[32];
		char szDate[32];
		std::string fn;
		memset(szTime, 0, sizeof(szTime));
		memset(szDate, 0, sizeof(szDate));
		FormatCurrDate(szTime, szDate);
		fn = szEngineLog;
		fn += ".";
		fn += szDate;
		gEngineErrorReporter(fn.c_str());
	}
	else 
	{
		WriteLog("[ERRORC]", file, nLine, szBuffer);
	}
}
