#pragma once
#include "../YosefGL.h"
#include "../YosefPrefix.h"
#ifdef _WIN32 || _WIN64
//sleep for ms
#include <windows.h>
#define YosefSleep(ms) Sleep(ms)
#define YOSEF_PLATFORM_WIN
#elif __GNUC__
#include <sys/time.h>
#define YosefSleep(ms) CanRead(0,0,ms)
#define YOSEF_PLATFORM_UNIX
#endif


class Timer 
{
public:
	Timer() : m_startTime(0), m_threadHandle(::GetCurrentThread())
	{
		DWORD_PTR systemMask;
		GetProcessAffinityMask(GetCurrentProcess(), &m_processAffinityMask, &systemMask);
		SetThreadAffinityMask(m_threadHandle, 1);
		QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_frequency));
		SetThreadAffinityMask(m_threadHandle, m_processAffinityMask);
	}
	void Start()
	{
		m_startTime = GetTime();
	}
	float GetTimeInMs() const
	{
		if (m_startTime == 0)
		{
			return 0.0f;
		}
		__int64 const elapsedTime = GetTime() - m_startTime;
		double const seconds = double(elapsedTime) / double(m_frequency);
		return (float)(seconds * 1000.0f);
	}
	YosefUInt64 GetTimeInMsi()
	{
		__int64 const elapsedTime = GetTime() - m_startTime;
		double const seconds = double(elapsedTime) / double(m_frequency);
		return YosefUInt64(seconds * 1000.0f);
	}
	void Reset()
	{
		Start();
	}
private:
#ifdef YOSEF_PLATFORM_WIN
	__int64 GetTime() const
	{
		LARGE_INTEGER curTime;
		SetThreadAffinityMask(m_threadHandle, 1);
		QueryPerformanceCounter(&curTime);
		SetThreadAffinityMask(m_threadHandle, m_processAffinityMask);
		return curTime.QuadPart;
	}
	void* m_threadHandle;
	unsigned long m_processAffinityMask;
	__int64 m_startTime;
	__int64 m_frequency;
#elif YOSEF_PLATFORM_UNIX
    timeval mStartTime;
	YosefUInt64 mStartTimeInMS;
#endif
};

