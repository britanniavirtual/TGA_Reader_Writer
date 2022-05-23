#include "JointHeader.h"

TGA::TGA()
{
}

TGA::~TGA()
{
}

bool TGA::readTGA(string filename, BitmapMin *bmp)
{
	TGAFILE tgaFile;

	FILE *filePtr;
	unsigned char ucharBad;
	short int sintBad;
	long imageSize;
	int colorMode;
	unsigned char colorSwap;

	//Open TGA file
	filePtr = fopen(filename.c_str(), "rb");
	if (filePtr == NULL)
	{
		return false;
	}

	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&tgaFile.typeCode, sizeof(unsigned char), 1, filePtr);

	//Type code 2 (uncompressed RGB image)
	//Type code 3 (uncompressed black-and-white images).
	if (tgaFile.typeCode != 2 && tgaFile.typeCode != 3)
	{
		fclose(filePtr);
		return false;
	}

	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);
	fread(&sintBad, sizeof(short int), 1, filePtr);

	//Read the image's width and height.
	fread(&tgaFile.width, sizeof(short int), 1, filePtr);
	fread(&tgaFile.height, sizeof(short int), 1, filePtr);

	//Read the bit depth.
	fread(&tgaFile.bitCount, sizeof(unsigned char), 1, filePtr);

	//Read one byte of data we don't need.
	fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

	//Color mode -> 3 = BGR, 4 = BGRA.
	colorMode = tgaFile.bitCount / 8;
	imageSize = tgaFile.width * tgaFile.height * colorMode;

	//Allocate memory for the image data.
	tgaFile.data = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

	//Read the image data.
	fread(tgaFile.data, sizeof(unsigned char), imageSize, filePtr);

	for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
	{
		colorSwap = tgaFile.data[imageIdx];
		tgaFile.data[imageIdx] = tgaFile.data[imageIdx + 2];
		tgaFile.data[imageIdx + 2] = colorSwap;
	}

	bmp->width = tgaFile.width;
	bmp->height = tgaFile.height;

	//Load filedata to bitmap object
	int curX = -1;
	int curY = 0;
	int n1 = 0;
	int n = 0;

	for (int a = 0; a < tgaFile.width; a++)
	{
		for (int b = 0; b < tgaFile.height; b++)
		{
			bmp->map[tgaFile.height - curY - 1][curX].b = int(tgaFile.data[n1 + 2]);
			bmp->map[tgaFile.height - curY - 1][curX].g = int(tgaFile.data[n1 + 1]);
			bmp->map[tgaFile.height - curY - 1][curX].r = int(tgaFile.data[n1]);

			curX++;
			if (n >= tgaFile.width)
			{
				n = 0;
				curX = 0;
				curY++;
			}

			n++;
			n1 += 3;
		}
	}

	fclose(filePtr);
	return true;
}


//--------------------------------------
// Desc: Write a BitmapMin object to a TGA image file
//--------------------------------------
bool TGA::writeTGA(string filename, BitmapMin *bmp)
{
	unsigned width = bmp->width;
	unsigned height = bmp->height;
	ofstream tgafile(filename.c_str(), ios::binary);
	if (!tgafile)
	{
		tgafile.close();
		return false;
	}

	//The image header
	char header[18] = { 0 };
	header[2] = 2;  // truecolor
	header[12] = bmp->width & 0xFF;
	header[13] = (bmp->width >> 8) & 0xFF;
	header[14] = bmp->height & 0xFF;
	header[15] = (bmp->height >> 8) & 0xFF;
	header[16] = 24;  // bits per pixel
	tgafile.write((const char*)header, 18);
	for (int y = bmp->height - 1; y >= 0; y--)
	{
		for (int x = 0; x < bmp->width; x++)
		{
			//cout << "y:" << y << " , x:" << x << endl;

			tgafile.put((char)bmp->map[y][x].b);//b
			tgafile.put((char)bmp->map[y][x].g);//g
			tgafile.put((char)bmp->map[y][x].r);//ra
		}
	}
	tgafile.close();
	return true;
}


