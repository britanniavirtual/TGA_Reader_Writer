#include "pch.h"
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
// Desc: Free allocated memory as required
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
// Desc: Draw a line on a bitmap
//--------------------------------------
void BitmapUtils::drawLine(BitmapMin *input, float degs, float magnitude, int stX, int stY, string color)
{
	int r1 = 0;
	int g1 = 0;
	int b1 = 255;

	int r2 = 255;
	int g2 = 255;
	int b2 = 0;

	if (color == "red")
	{
		r1 = 255;
		g1 = 0;
		b1 = 0;

		r2 = 0;
		g2 = 255;
		b2 = 0;
	}

	if (color == "white")
	{
		r1 = 255;
		g1 = 255;
		b1 = 255;

		r2 = 255;
		g2 = 255;
		b2 = 255;
	}


	for (int n = 0; n < magnitude / 2; n++)
	{
		int x = stX + cos(degs * 0.0174533) * n;
		int y = stY + sin(degs * 0.0174533) * n;

		if (degs == 0 || degs == 180 || degs == 360)
		{
			x = stX + n;
			y = stY;
		}

		if (degs == 90 || degs == 270 || degs == -90)
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
		int x = stX - cos(degs * 0.0174533) * n;
		int y = stY - sin(degs * 0.0174533) * n;

		if (degs == 0 || degs == 180 || degs == 360)
		{
			x = stX - n;
			y = stY;
		}

		if (degs == 90 || degs == 270 || degs == -90)
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
// Desc: Resample a BitmapMin object to the new dimensions
//--------------------------------------
void BitmapUtils::resize(BitmapMin *input, int width, int height)
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
// 
//--------------------------------------
void BitmapUtils::drawRect(BitmapMin *input)
{
	int stX = 32;
	int stY = 32;
	int enX = 128;
	int enY = 128;

	for (int a = stX; a < enX; a++)
	{
		input->map[a][stY].r = 255;
		input->map[a][stY].g = 0;
		input->map[a][stY].b = 0;
	}

	for (int a = stY; a < enY; a++)
	{
		input->map[stX][a].r = 255;
		input->map[stX][a].g = 0;
		input->map[stX][a].b = 0;
	}

	for (int a = stY; a < enY; a++)
	{
		input->map[enX][a].r = 255;
		input->map[enX][a].g = 0;
		input->map[enX][a].b = 0;
	}


	for (int a = stX; a < enX; a++)
	{
		input->map[a][enY].r = 255;
		input->map[a][enY].g = 0;
		input->map[a][enY].b = 0;
	}
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
	tmp = new BitmapMin;
	tmp->width = MAX_INDEX;
	tmp->height = MAX_INDEX;
}

//--------------------------------------
// Desc:
//--------------------------------------
BitmapUtils::~BitmapUtils()
{
	delete tmp;
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
			tmp->map[j][i].r = input->map[j][i].r;
			tmp->map[j][i].g = input->map[j][i].g;
			tmp->map[j][i].b = input->map[j][i].b;
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
			input->map[j][i].r = tmp->map[j][select].r;
			input->map[j][i].g = tmp->map[j][select].g;
			input->map[j][i].b = tmp->map[j][select].b;
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
			tmp->map[j][i].r = input->map[j][i].r;
			tmp->map[j][i].g = input->map[j][i].g;
			tmp->map[j][i].b = input->map[j][i].b;
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

			input->map[j][i].r = tmp->map[select][i].r;
			input->map[j][i].g = tmp->map[select][i].g;
			input->map[j][i].b = tmp->map[select][i].b;
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
			tmp->map[j][i].r = input->map[j][i].r;
			tmp->map[j][i].g = input->map[j][i].g;
			tmp->map[j][i].b = input->map[j][i].b;
		}
	}

	for (int i = 0; i < input->width; i++)
	{
		for (int j = 0; j < input->height; j++)
		{
			input->map[input->height - j - 1][i].r = tmp->map[i][j].r;
			input->map[input->height - j - 1][i].g = tmp->map[i][j].g;
			input->map[input->height - j - 1][i].b = tmp->map[i][j].b;
		}
	}
}



