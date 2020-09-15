#ifndef _BITMAP_
#define _BITMAP_


struct Color
{
	unsigned char R, G, B;
};

struct ColorHSV
{
	double H, S, V;			// 0 <= H < 360, 0 <= S <= 1, 0 <= V <= 1
};

struct Bitmap
{
	int width;
	int height;
	int rowSize;
	vector<unsigned char> pixels;
	vector<vector<Color>> Pixels2D;
	vector<vector<ColorHSV>> Pixels2D_HSV;
};

// Functions in Bitmap.cpp

Bitmap LoadBitmap(string fname);
int SaveBitmap(string fname, Bitmap &bmp);

bool SetPixel(Bitmap &bmp, int row, int col, Color color);
bool GetPixel(const Bitmap &bmp, int row, int col, Color &color);

void pixels_to_Pixels2D(Bitmap &bmp);
void Pixels2D_to_pixels(Bitmap &bmp);

void BGR2HSV(Bitmap &bmp);
void HSV2BGR(Bitmap &bmp);

void copyPixels2D(Bitmap &bmp, Bitmap &new_bmp);
void copyPixels2D_HSV(Bitmap &bmp, Bitmap &new_bmp);

// Functions in Effect.cpp

Bitmap AdjustBrightness(Bitmap &bmp, double delta_V);
Bitmap AdjustSaturation(Bitmap &bmp, double delta_S);
Bitmap Contrast(Bitmap &bmp, double value);
Bitmap BGR2Gray(Bitmap &bitmap);
Bitmap Invert(Bitmap &bmp);
Bitmap BGR2Binary(Bitmap &bitmap);
Bitmap resizeIm(Bitmap &bmp, int new_width, int new_height);
Bitmap CropIm(Bitmap &bmp, int Tung1, int Tung2, int Hoanh1, int Hoanh2);
Bitmap Rotate(Bitmap &bmp);
Bitmap Flip(Bitmap &bmp, int type = 1);
Bitmap Blur(Bitmap &bmp, int n);
Bitmap insertText(Bitmap &bmp, int row, int col, string str, int size, COLORREF color);
Bitmap histogramEqualisation(Bitmap &bitmap);
Bitmap Hue(Bitmap &bmp, int deltaH);
Bitmap edgeDetect(Bitmap &bmp);


#endif

