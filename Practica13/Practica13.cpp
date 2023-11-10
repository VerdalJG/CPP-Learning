#include <iostream>

class Image
{
public:
	int m_resolutionX, m_resolutionY = 0;
	int m_colorDepth = 0;
	int DrawRGBImage(unsigned char* buffer)
	{
		return 0;
	}
	enum class ImageType
	{
		Invalid,
		JPG,
		PNG
	};
	ImageType type = ImageType::Invalid;
};

class JPG : public Image
{
public:
	JPG()
	{
		type = ImageType::JPG;
	}
	//CCodecPNG m_Codec;
	int DrawPNGImage(unsigned char* buffer)
	{
		return 0;
	}
};

class PNG : public Image
{
public:
	PNG()
	:	m_alpha(0)
	{
		type = ImageType::PNG;
	}


	//CCodecPNG m_Codec;
	int DrawJPGImage(unsigned char* buffer)
	{
		return 0;
	}

	bool RemoveAlphaChannel()
	{
		m_alpha = 0;
		printf("Alpha removed\n");
		return m_alpha == 0;
	}

private:
	unsigned short m_alpha;
};

void RemoveAlphaChannels(Image* imagePtr, int tableLength);

int main()
{
	PNG png;
	png.RemoveAlphaChannel();

	int tableLength = 10;
	Image imageTable[10]
	{
		PNG(),
		Image(),
		JPG(),
		Image(),
		JPG(),
		JPG(),
		Image(),
		JPG(),
		PNG(),
		Image()
	};

	Image* imageTablePtr = imageTable;
	RemoveAlphaChannels(imageTablePtr, tableLength);
}

void RemoveAlphaChannels(Image* imagePtr, int tableLength)
{
	PNG* pngPtr = static_cast<PNG*>(imagePtr);
	for (int i = 0; i < tableLength; i++)
	{
		if ((pngPtr + i)->type == PNG::ImageType::PNG)
		{
			(pngPtr + i)->RemoveAlphaChannel();
		}
		
	}
}
