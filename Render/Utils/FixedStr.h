#pragma once
#ifdef _WIN32 || _WIN64
#include <Windows.h>
#endif
#include "../YosefGL.h"
inline const std::string Head(const std::string& str, int n) 
{
	assert(n >= 0);
	return str.substr(0, std::min(static_cast<size_t>(n), str.size()));
}
inline const std::string Tail(const std::string& str, int n)
{
	assert(n >= 0);
	return str.substr(str.size() - n, n);
}
inline const std::string TailAfter(const std::string& str, char c)
{
	auto idx = str.find_last_of(c);
	if (idx == std::string::npos)
		return "";
	return str.substr(idx + 1);
}
inline const std::vector<std::string> Spilt(const std::string& str, const std::string& separator)
{
	std::vector<std::string> rst;

	if (separator.empty())
		return rst;

	size_t beginIdx = 0;
	while (true) 
	{
		size_t targetIdx = str.find(separator, beginIdx);
		if (targetIdx == std::string::npos) 
		{
			rst.push_back(str.substr(beginIdx, str.size() - beginIdx));
			break;
		}

		rst.push_back(str.substr(beginIdx, targetIdx - beginIdx));
		beginIdx = targetIdx + separator.size();
	}

	return rst;
}
inline inline const std::vector<std::string> Spilt(const std::string& str, char separator) 
{
	return Spilt(str, std::string(1, separator));
}
inline const std::string Join(const std::vector<std::string>& strs, const std::string& separator = "") 
{
	std::string rst;

	for (size_t i = 0; i < strs.size() - 1; i++) 
	{
		rst += strs[i];
		rst += separator;
	}

	rst += strs.back();

	return rst;
}
inline const std::string Replace(const std::string& str, const std::string& orig, const std::string& target)
{
	return Join(Spilt(str, orig), target);
}
inline const std::string DelTailAfter(const std::string& str, char c)
{
	for (auto i = static_cast<int>(str.size()) - 1; i >= 0; i--) 
	{
		if (str[i] == c)
			return str.substr(0, i);
	}

	return str;
}
inline const std::string Between(const std::string& str, char left, char right)
{
	auto start = str.find_first_of(left, 0);
	if (start == std::string::npos)
		return "";

	auto end = str.find_last_of(right);
	if (end == std::string::npos || end == start)
		return "";

	return str.substr(start + 1, end - (start + 1));
}
inline const std::string LowerCase(const std::string& str) 
{
	std::string rst;
	for (auto c : str)
	{
		if ('A' <= c && c <= 'Z')
			c += 'a' - 'A';
		rst.push_back(c);
	}
	return rst;
}
inline const std::string UpperCase(const std::string& str) 
{
	std::string rst;
	for (auto c : str) 
	{
		if ('a' <= c && c <= 'z')
			c += 'A' - 'a';
		rst.push_back(c);
	}
	return rst;
}
inline bool IsBeginWith(const std::string& str, const std::string& suffix) 
{
	return Head(str, static_cast<int>(suffix.size())) == suffix;
}
inline bool IsEndWith(const std::string& str, const std::string& postfix)
{
	return Tail(str, static_cast<int>(postfix.size())) == postfix;
}