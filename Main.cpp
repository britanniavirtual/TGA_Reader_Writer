#include "JointHeader.h"

int main()
{
	BitmapMin bmp;
	TGA tg;

	tg.readTGA("test.tga", &bmp);

	//[Test utility routines]
	//BitmapUtils u;
	//u.drawLine(&bmp, 45, 128, 0, 0, rgb(0,255,0));
	//u.drawRectangle(&bmp, 32, 32, 128, 128);
	//u.resample(&bmp, 128, 256);

	tg.writeTGA("output.tga", &bmp);

	cout << "Read: test.tga" << endl;
	cout << "Wrote: output.tga" << endl;

	system("PAUSE");
}