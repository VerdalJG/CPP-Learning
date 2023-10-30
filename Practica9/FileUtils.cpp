#include "FileUtils.h"
#include <cstdio>

namespace FileUtils
{
	// Mode is read/write etc
	bool CFile::OpenFile(const char* path, const char* mode)
	{
		CloseFile();

		std::FILE* pFile;
		fopen_s(&pFile, path, mode);

		if (pFile)
		{
			m_pFile = pFile;
			return true;
		}
		return false;
		
	}


	bool CFile::CloseFile()
	{
		if (m_pFile)
		{
			std::FILE* pFile = reinterpret_cast<std::FILE*>(m_pFile);
			bool bResult = fclose(pFile) == 0;
			pFile = nullptr;
			return bResult;
		}
		return false;
	}


	unsigned int CFile::ReadFile(char* _pBuffer, unsigned int _uBufferSize)
	{
		if (m_pFile)
		{
			std::FILE* pFile = reinterpret_cast<std::FILE*>(m_pFile);
			unsigned int uResult = static_cast<unsigned int>(fread(_pBuffer, sizeof(char), _uBufferSize, pFile));
			return uResult;
		}
		return 0;
	}


	unsigned int CFile::WriteFile(char* _sToWrite, unsigned int _uBufferSize)
	{
		if (m_pFile)
		{
			std::FILE* pFile = reinterpret_cast<std::FILE*>(m_pFile);
			unsigned int uResult = static_cast<unsigned int>(fwrite(_sToWrite, sizeof(char), _uBufferSize, pFile));
			return uResult;
		}
		return 0;
	}
}
