#include "JointHeader.h"

//--------------------------------------
// Desc: 
//--------------------------------------
BitmapMin::BitmapMin()
{
	map = new rgb*[MAX_INDEX];
	for (int i = 0; i < MAX_INDEX; i++)
	{
		map[i] = new rgb[MAX_INDEX];
	}
	
	width = MAX_INDEX;
	height = MAX_INDEX;
}


//------------------------------
// Desc: Destructor
//------------------------------
BitmapMin::~BitmapMin()
{
	/*
	for (int i = 0; i < MAX_INDEX; i++)
	{
		delete[] map[i];
	}
	delete[] map;
	*/
}

//------------------------------
// Desc: Free allocated memory as needed
//------------------------------
void BitmapMin::shutDown()
{
	for (int i = 0; i < MAX_INDEX; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

//--------------------------------------
// Desc: Draw a line on a bitmap (1 pixel width)
//--------------------------------------
void BitmapUtils::drawLine(BitmapMin *input, float degrees, float magnitude, int stX, int stY, rgb color)
{
	//Line is made of 2 equal segments
	int r1 = color.r;
	int g1 = color.g;
	int b1 = color.b;

	int r2 = color.r;
	int g2 = color.g;
	int b2 = color.b;

	for (int n = 0; n < magnitude / 2; n++)
	{
		int x = stX + cos(degrees * 0.0174533) * n;
		int y = stY + sin(degrees * 0.0174533) * n;

		if (degrees == 0 || degrees == 180 || degrees == 360)
		{
			x = stX + n;
			y = stY;
		}

		if (degrees == 90 || degrees == 270 || degrees == -90)
		{
			x = stX;
			y = stY + n;
		}

		if (x >= 0 && x < input->height && y >= 0 && y < input->width)
		{
			input->map[x][y].r = r1;
			input->map[x][y].g = g1;
			input->map[x][y].b = b1;
		}
	}

	for (int n = 0; n < magnitude / 2; n++)
	{
		int x = stX - cos(degrees * 0.0174533) * n;
		int y = stY - sin(degrees * 0.0174533) * n;

		if (degrees == 0 || degrees == 180 || degrees == 360)
		{
			x = stX - n;
			y = stY;
		}

		if (degrees == 90 || degrees == 270 || degrees == -90)
		{
			x = stX;
			y = stY - n;
		}

		if (x >= 0 && x < input->height && y >= 0 && y < input->width)
		{
			input->map[x][y].r = r2;
			input->map[x][y].g = g2;
			input->map[x][y].b = b2;
		}
	}
}


//--------------------------------------
// Desc: Resample a BitmapMin object to new dimensions
//--------------------------------------
void BitmapUtils::resample(BitmapMin *input, int width, int height)
{
	double scaleWidth = (double)width / (double)input->width;
	double scaleHeight = (double)height / (double)input->height;

	BitmapMin tmpBmp;
	for (int cy = 0; cy < MAX_INDEX; cy++)
	{
		for (int cx = 0; cx < MAX_INDEX; cx++)
		{
			tmpBmp.map[cx][cy] = input->map[cx][cy];
		}
	}

	for (int cy = 0; cy < height; cy++)
	{
		for (int cx = 0; cx < width; cx++)
		{
			int nearestMatchY = (int)(cy / scaleHeight);
			int nearestMatchX = (int)(cx / scaleWidth);

			input->map[cx][cy] = tmpBmp.map[nearestMatchX][nearestMatchY];
		}
	}

	for (int cy = 0; cy < MAX_INDEX; cy++)
	{
		for (int cx = 0; cx < MAX_INDEX; cx++)
		{
			if (cx >= width || cy >= height)
			{
				input->map[cx][cy].r = 0;
				input->map[cx][cy].g = 255;
				input->map[cx][cy].b = 0;
			}
		}
	}

	input->width = height;
	input->height = width;

	//stringstream d;
	//d << input->width << " " << input->height << endl;
	//MessageBox(NULL, d.str().c_str(), "", MB_ICONASTERISK | MB_OK);
}


//--------------------------------------
// Desc: x and y are flipped in the for blocks
//--------------------------------------
void BitmapUtils::drawRectangle(BitmapMin *input, int sx, int sy, int ex, int ey)
{
	for (int a = sx - (rectWidth); a < ex + (rectWidth); a++)
	{
		for (int b = -rectWidth; b < rectWidth; b++)
		{
			if (b + sy >= 0 && a >= 0)
			{
				input->map[a][b + sy].r = rectColor.r;
				input->map[a][b + sy].g = rectColor.g;
				input->map[a][b + sy].b = rectColor.b;
			}
		}
	}

	for (int a = sx; a < ex + rectWidth * 2; a++)
	{
		for (int b = -rectWidth; b < rectWidth; b++)
		{
			if (b + ey >= 0 && a - rectWidth >= 0)
			{
				input->map[a - rectWidth][b + ey].r = rectColor.r;
				input->map[a - rectWidth][b + ey].g = rectColor.g;
				input->map[a - rectWidth][b + ey].b = rectColor.b;
			}
		}
	}

	for (int a = sy; a < ey; a++)
	{
		for (int b = -rectWidth; b < rectWidth; b++)
		{
			if (b + sx >= 0)
			{
				input->map[b + sx][a].r = rectColor.r;
				input->map[b + sx][a].g = rectColor.g;
				input->map[b + sx][a].b = rectColor.b;
			}
		}
	}

	for (int a = sy; a < ey; a++)
	{
		for (int b = -rectWidth; b < rectWidth; b++)
		{
			if (b + ex >= 0)
			{
				input->map[b + ex][a].r = rectColor.r;
				input->map[b + ex][a].g = rectColor.g;
				input->map[b + ex][a].b = rectColor.b;
			}
		}
	}

	for (int a = sx; a < ex + rectWidth * 2; a++)
	{
		for (int b = -rectWidth; b < rectWidth; b++)
		{
			if (b + ey >= 0 && a - rectWidth >= 0)
			{
				input->map[a - rectWidth][b + ey].r = rectColor.r;
				input->map[a - rectWidth][b + ey].g = rectColor.g;
				input->map[a - rectWidth][b + ey].b = rectColor.b;
			}
		}
	}
}


//--------------------------------------
// Desc:
//--------------------------------------
void BitmapUtils::RGBFill(BitmapMin *input, int r, int g, int b)
{
	for (int i = 0; i < MAX_INDEX; i++)
	{
		for (int j = 0; j < MAX_INDEX; j++)
		{
			input->map[j][i].r = r;
			input->map[j][i].g = g;
			input->map[j][i].b = b;
		}
	}
}

//--------------------------------------
// Desc:
//--------------------------------------
BitmapUtils::BitmapUtils()
{
	temporary = new BitmapMin;
	temporary->width = MAX_INDEX;
	temporary->height = MAX_INDEX;
}

//--------------------------------------
// Desc:
//--------------------------------------
BitmapUtils::~BitmapUtils()
{
	delete temporary;
}

//--------------------------------------
// Desc:
//--------------------------------------
void BitmapUtils::flipHorizontal(BitmapMin *input)
{
	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			temporary->map[j][i].r = input->map[j][i].r;
			temporary->map[j][i].g = input->map[j][i].g;
			temporary->map[j][i].b = input->map[j][i].b;
		}
	}

	int depth = input->width;
	int select = 0;
	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			int p = i;
			select = depth - p;
			input->map[j][i].r = temporary->map[j][select].r;
			input->map[j][i].g = temporary->map[j][select].g;
			input->map[j][i].b = temporary->map[j][select].b;
		}
	}
}


//--------------------------------------
// Desc:
//--------------------------------------
void BitmapUtils::flipVertical(BitmapMin *input)
{
	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			temporary->map[j][i].r = input->map[j][i].r;
			temporary->map[j][i].g = input->map[j][i].g;
			temporary->map[j][i].b = input->map[j][i].b;
		}
	}

	//cout << input->width << " " << input->height;

	int depth = input->height;
	int select = 0;
	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			int p = j;

			select = depth - p - 1;

			input->map[j][i].r = temporary->map[select][i].r;
			input->map[j][i].g = temporary->map[select][i].g;
			input->map[j][i].b = temporary->map[select][i].b;
		}
	}
}

//--------------------------------------
// Desc:
//--------------------------------------
void BitmapUtils::rotate90deg(BitmapMin *input)
{
	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			temporary->map[j][i].r = input->map[j][i].r;
			temporary->map[j][i].g = input->map[j][i].g;
			temporary->map[j][i].b = input->map[j][i].b;
		}
	}

	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			input->map[input->height - j - 1][i].r = temporary->map[i][j].r;
			input->map[input->height - j - 1][i].g = temporary->map[i][j].g;
			input->map[input->height - j - 1][i].b = temporary->map[i][j].b;
		}
	}
}



