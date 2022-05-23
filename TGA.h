#pragma once

struct TGAFILE
{
	unsigned char typeCode;
	short int width;
	short int height;
	unsigned char bitCount;
	unsigned char *data;
};

class TGA
{
public:
	TGA();
	~TGA();

	bool writeTGA(string filename, BitmapMin *bmp);
	bool readTGA(string filename, BitmapMin *bmp);
};
