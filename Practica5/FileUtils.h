#pragma once

namespace FileUtils 
{
	class CFile
	{
	public:
		bool OpenFile(const char* filename, const char* mode);
		bool CloseFile();
		unsigned int ReadFile(char* _pBuffer, unsigned int _uBufferSize);
		unsigned int WriteFile(char* _pBuffer, unsigned int _uBufferSize);

	private:
		void* m_pFile = nullptr;
	};
	
}
