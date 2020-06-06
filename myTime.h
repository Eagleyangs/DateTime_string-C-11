#ifndef MYTIME_H
#define MYTIME_H

#include <time.h>
#include <string>
#include <Windows.h>
#include <sstream>
#include <iomanip>

#pragma warning(disable:4996)//加上可去掉unsafe 请使用localtime_s的编译报错  

using namespace std;

const string c_strDefaultFormat = "%Y-%m-%d %H:%M:%S";
const string c_str_Format = "%Y_%m_%d_%H_%M_%S";
const string c_strYmdFormat = "%Y-%m-%d";
const string c_strHMSFormat = "%H:%M:%S";

const string c_strSysFormat = "%04ld-%02ld-%02ld %02ld:%02ld:%02ld.%03ld";

class myTime 
{
public:
	// 按格式获取当前时间,默认Y-m-d H:M:S
	static string getCurrentTime(const string sFormat = c_strDefaultFormat)
	{
		time_t timep;
		time(&timep);
		char tmp[64];
		strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
		return tmp;
	}

	// 获取指定时间,默认当前时间Y-m-d H:M:S,offset为偏移数据以分钟为单位,向后三个小时 offset = 60*3,向前2小时,offset = -2*60
	static string getCustomTime(int offset = 0, const string sFormat = c_strDefaultFormat) // offset + 向后偏移 - 向前偏移 以分钟数为单位
	{
		time_t timep;
		time(&timep);
		char tmp[64];
		timep += (1 * 60 * offset);
		strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
		return tmp;
	}

	// 获取指定时间,默认当前时间Y-m-d H:0:0,offset为偏移数据以分钟为单位,向后三个小时 offset = 60*3,向前2小时,offset = -2*60
	static string getCustomDateTime(int offset = 0, const string sFormat = c_strDefaultFormat) // offset + 向后偏移 - 向前偏移 以分钟数为单位
	{
		time_t timep;
		time(&timep);
		char tmp[64];
		timep += (1 * 60 * offset);
		tm* tms = localtime(&timep);
		tms->tm_min = 0;
		tms->tm_sec = 0;
		strftime(tmp, sizeof(tmp), sFormat.c_str(), tms);
		return tmp;
	}

	// 获取time_t
	static time_t getTime_t()
	{
		time_t timep;
		time(&timep);
		return timep;
	}

	// 获取之前一个小时的时间
	static string getLastHourTime(const string sFormat = c_strDefaultFormat)
	{
		time_t timep;
		time(&timep);
		char tmp[64];
		timep -= 3600; // 当前时间减去3600s
		tm* t = localtime(&timep);

		strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
		return tmp;
	}

	// 获取年月日
	static string getYearMonthDay(const string sFormat = c_strYmdFormat)
	{
		time_t timep;
		time(&timep);
		char tmp[64];
		strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
		return tmp;
	}

	// 获取时分秒
	static string getHourMinSec(const string sFormat = c_strHMSFormat)
	{
		time_t timep;
		time(&timep);
		char tmp[64];
		strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
		return tmp;
	}

	// 获取时间的 tm* 结构体
	static tm* getTm() {
		time_t timep;
		time(&timep);
		return localtime(&timep);
	}

	// 获取年
	static int getYear()
	{
		time_t timep;
		time(&timep);
		tm* tmp = localtime(&timep);
		return tmp->tm_year + 1900;
	}

	// 获取月
	static int getMonth()
	{
		time_t timep;
		time(&timep);
		tm* tmp = localtime(&timep);
		return tmp->tm_mon;
	}

	// 获取日
	static int getDay()
	{
		time_t timep;
		time(&timep);
		tm* tmp = localtime(&timep);
		return tmp->tm_mday;
	}

	// 获取指定天数
	static int getCustomDay(int offset = 0)  // offset + 向后偏移 - 向前偏移 以天数为单位
	{
		time_t timep;
		time(&timep);
		timep += (1 * 60 * 60 * 24 * offset);// 天 * offset
		tm* tmp = localtime(&timep);
		return tmp->tm_mday;
	}

	// 获取前一天
	static int getLastDay()
	{
		time_t timep;
		time(&timep);
		timep -= (1 * 60 * 60 * 24);// 秒
		tm* tmp = localtime(&timep);
		return tmp->tm_mday;
	}

	// 获取当前小时
	static int getHour()
	{
		time_t timep;
		time(&timep);
		tm* tmp = localtime(&timep);
		return tmp->tm_hour;
	}

	// 获取指定小时数
	static int getCustomHour(int offset = 0)  // offset + 向后偏移 - 向前偏移 以分钟数为单位
	{
		time_t timep;
		time(&timep);
		timep += (1 * 60 * offset);// 秒
		tm* tmp = localtime(&timep);
		return tmp->tm_hour;
	}

	// 获取之前一小时数
	static int getLastHour()
	{
		time_t timep;
		time(&timep);
		timep -= (1 * 60 * 60);// 秒
		tm* tmp = localtime(&timep);
		return tmp->tm_hour;
	}

	// 获取分钟数
	static int getMinute()
	{
		time_t timep;
		time(&timep);
		tm* tmp = localtime(&timep);
		return tmp->tm_min;
	}

	//获取前一分钟
	static int getLastMin()
	{
		time_t timep;
		time(&timep);
		timep -= (1 * 60);// 秒
		tm* tmp = localtime(&timep);
		return tmp->tm_min;
	}

	// 获取系统时间
	static void getSystemTimeString(string& timeStr)
	{
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		char timeChar[128] = { 0 };
		sprintf(timeChar, c_strSysFormat.c_str(), 
			sysTime.wYear, 
			sysTime.wMonth, 
			sysTime.wDay, 
			sysTime.wHour, 
			sysTime.wMinute, 
			sysTime.wSecond, 
			sysTime.wMilliseconds);
		timeStr = timeChar;
	}

	// 时间字符串(如：2020-06-06 14:40:31.015)
	static string getTimeString(bool bLocal = true, bool bIncludeMS = true, const string sFormat = c_strDefaultFormat)
	{
		auto tNow = chrono::system_clock::now();
		auto tSeconds = chrono::duration_cast<chrono::seconds>(tNow.time_since_epoch());
		auto secNow = tSeconds.count();
		tm tmNow;
		if (bLocal) {
			localtime_s(&tmNow, &secNow);
		}
		else {
			gmtime_s(&tmNow, &secNow);
		}

		ostringstream oss;
		oss << put_time(&tmNow, sFormat.c_str());
		if (bIncludeMS) {
			auto tMilli = chrono::duration_cast<chrono::milliseconds>(tNow.time_since_epoch());
			auto ms = tMilli - tSeconds;
			oss << "." << setfill('0') << setw(3) << ms.count();
		}

		return oss.str();
	}
};

#endif // !MYTIME_H
