#include <iostream>

class Image
{
protected:
	int m_resolutionX, m_resolutionY;
	int m_colorDepth;
	int r, g, b = 0;
	int DrawRGBImage(unsigned char* buffer)
	{
		return 0;
	}
};

class JPG : public Image
{
	//CCodecPNG m_Codec;
	int DrawPNGImage(unsigned char* buffer)
	{
		return 0;
	}
};

class PNG : public Image
{
	PNG(int r, int g, int b, int a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{

	}
	int a = 0;
	//CCodecPNG m_Codec;
	int DrawJPGImage(unsigned char* buffer)
	{
		return 0;
	}

	int RemoveAlphaChannel(unsigned char* buffer)
	{

	}
};

int main()
{
	
}
