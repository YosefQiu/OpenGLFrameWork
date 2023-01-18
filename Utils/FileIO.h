#pragma once
#include "../YosefGL.h"
#include "../YosefPrefix.h"

inline unsigned char* LoadFileContent(const char* path, int& filesize) 
{
	unsigned char* fileContent = nullptr;
	filesize = 0;
	FILE* pFile = fopen(path, "rb");
	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		int nLen = ftell(pFile);
		if (nLen > 0) 
		{
			rewind(pFile);
			fileContent = new unsigned char[nLen + 1];
			fread(fileContent, sizeof(unsigned char), nLen, pFile);
			fileContent[nLen] = '\0';
			filesize = nLen;
		}
		fclose(pFile);
	}
	else
	{
		perror("[ERROR] file system ");
	}
	return fileContent;
}


class CFILE {
public:
	enum Mode {
		READ,
		WRITE
	};

	CFILE(const std::string& fileName, Mode mode) {
		this->fileName = fileName;
		this->mode = mode;
		int err = fopen_s(&pFile, fileName.c_str(), ModeToStr(mode).c_str());
		if (err != 0)
			perror("[ERROR] ");
	}
	~CFILE() {
		if (pFile != NULL) {
			fclose(pFile);
			pFile = NULL;
		}
	}
public:
	bool Check(Mode mode) const
	{
		if (mode == this->mode && IsValid())
			return true;
		else
			return false;
	}
	int Printf(const char* format, ...)
	{
		if (!Check(WRITE)) 
		{
			fprintf(stderr, "%s can't not write\n", fileName.c_str());
			return -1;
		}
		va_list args;
		va_start(args, format);
		int rst = vfprintf(pFile, format, args);
		va_end(args);
		return rst;
	}
	int Scanf(const char* format, ...) const
	{
		if (!Check(READ)) 
		{
			fprintf(stderr, "%s can't not read\n", fileName.c_str());
			return -1;
		}
		va_list args;
		va_start(args, format);
		int rst = vfscanf(pFile, format, args);
		va_end(args);
		return rst;
	}
	std::string ReadLine() const
	{
		if (!Check(READ))
		{
			fprintf(stderr, "%s can't not read\n", fileName.c_str());
			return "";
		}
		char buffer[1024] = "";
		fgets(buffer, 1024, pFile);
		return buffer;
	}
	std::string ReadAll() const
	{
		if (!Check(READ))
		{
			fprintf(stderr, "%s can't not read\n", fileName.c_str());
			return "";
		}
		std::string rst;
		while (!IsEnd())
			rst += ReadLine();
		return rst;
	}
	std::vector<std::string> ReadAllLines() const
	{
		std::vector<std::string> rst;

		if (!Check(READ)) 
		{
			fprintf(stderr, "%s can't not read\n", fileName.c_str());
			return rst;
		}

		while (!IsEnd())
			rst.push_back(ReadLine());

		return rst;
	}
	bool IsEnd() const
	{
		return feof(pFile);
	}
	bool IsValid() const 
	{
		return pFile != NULL;
	}
	void Close() 
	{
		if (!IsValid())
			return;

		fclose(pFile);
		pFile = NULL;
	}

public: // static
	static const std::string ReadAll(const std::string& fileName) 
	{
		CFILE file(fileName, Mode::READ);
		return file.ReadAll();
	}
	static const std::vector<std::string> ReadAllLines(const std::string& fileName) 
	{
		CFILE file(fileName, Mode::READ);
		return file.ReadAllLines();
	}
	static bool IsSame(const std::string& fileName0, const std::string& fileName1) 
	{
		auto str0 = ReadAll(fileName0);
		auto str1 = ReadAll(fileName1);
		return str0 == str1;
	}

private:
	std::string ModeToStr(Mode mode) 
	{
		switch (mode)
		{
		case READ:
			return "r";
			break;
		case WRITE:
			return "w";
			break;
		default:
			return "";
			break;
		}
	}
private:
	FILE* pFile;
	Mode mode;
	std::string fileName;
};
