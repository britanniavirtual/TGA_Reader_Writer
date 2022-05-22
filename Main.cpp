#include "pch.h"
#include "JointHeader.h"

int main()
{
	BitmapMin bmp;
	TGA tg;

	tg.readTGA("test.tga", &bmp);
	tg.writeTGA("output.tga", &bmp);

	cout << "Read: test.tga" << endl;
	cout << "Wrote: output.tga" << endl;

	system("PAUSE");
}