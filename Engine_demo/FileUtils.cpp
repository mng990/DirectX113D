#include "pch.h"
#include "FileUtils.h"

FileUtils::FileUtils()
{

}

FileUtils::~FileUtils()
{
	if (_handle != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(_handle);
		_handle = INVALID_HANDLE_VALUE;
	}
}

void FileUtils::Open(wstring filePath, FileMode mode)
{
	if (mode == FileMode::Write)
	{
		_handle = ::CreateFile
		(
			filePath.c_str(), 
			GENERIC_WRITE,
			0,
			nullptr,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			nullptr
		);
	}
	else
	{
		_handle = ::CreateFile
		(
			filePath.c_str(),
			GENERIC_READ,
			FILE_SHARE_READ,
			nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr
		);
	}

	assert(_handle != INVALID_HANDLE_VALUE);
}

void FileUtils::Write(void* data, uint32 dataSize)
{
	uint32 numOfBytes = 0;
	assert(::WriteFile(_handle, data, dataSize, reinterpret_cast<LPDWORD>(&numOfBytes), nullptr));
}

void FileUtils::Write(const string& data)
{
	uint32 size = (uint32)data.size();

	// 문자열 길이를 버퍼에 우선적으로 삽입
	Write(size);

	if (data.size() == 0) return;

	// 이후 문자열 작성
	Write((void*)data.data(), size);
}

void FileUtils::Read(void** data, uint32 dataSize)
{
	uint32 numOfBytes = 0;
	assert(::ReadFile(_handle, *data, dataSize, reinterpret_cast<LPDWORD>(&numOfBytes), nullptr));
}

void FileUtils::Read(OUT string& data)
{
	uint32 size = Read<uint32>();
	if (size == 0) return;

	char* temp = new char[size + 1];

	temp[size] = 0;
	Read((void**)&temp, size);
	data = temp;

	delete[] temp;
}
