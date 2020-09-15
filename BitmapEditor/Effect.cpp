#include "stdafx.h"
#include "Bitmap.h"

Bitmap AdjustSaturation(Bitmap &bmp, double delta_S)	// -0.5 <= delta_S <= + 0.5
{
	Bitmap new_bmp;
	new_bmp.height = bmp.height;
	new_bmp.width = bmp.width;
	new_bmp.rowSize = bmp.rowSize;

	if (bmp.Pixels2D_HSV.empty())
		BGR2HSV(bmp);
	
	new_bmp.Pixels2D_HSV.resize(bmp.height);
	for (int row = 0; row < bmp.height; row++)
	{
		new_bmp.Pixels2D_HSV[row].resize(bmp.width);
		for (int col = 0; col < bmp.width; col++)
		{
			new_bmp.Pixels2D_HSV[row][col].H = bmp.Pixels2D_HSV[row][col].H;
			new_bmp.Pixels2D_HSV[row][col].V = bmp.Pixels2D_HSV[row][col].V;

			new_bmp.Pixels2D_HSV[row][col].S = bmp.Pixels2D_HSV[row][col].S + delta_S;
			if (new_bmp.Pixels2D_HSV[row][col].S > 1)
				new_bmp.Pixels2D_HSV[row][col].S = 1;
			else if (new_bmp.Pixels2D_HSV[row][col].S < 0)
				new_bmp.Pixels2D_HSV[row][col].S = 0;
		}
	}
	
	HSV2BGR(new_bmp);
	Pixels2D_to_pixels(new_bmp);

	return new_bmp;
}

Bitmap AdjustBrightness(Bitmap &bmp, double delta_V)	// -0.5 <= delta_V <= + 0.5
{
	Bitmap new_bmp;
	new_bmp.height = bmp.height;
	new_bmp.width = bmp.width;
	new_bmp.rowSize = bmp.rowSize;

	if (bmp.Pixels2D_HSV.empty())
		BGR2HSV(bmp);

	new_bmp.Pixels2D_HSV.resize(bmp.height);
	for (int row = 0; row < bmp.height; row++)
	{
		new_bmp.Pixels2D_HSV[row].resize(bmp.width);
		for (int col = 0; col < bmp.width; col++)
		{
			new_bmp.Pixels2D_HSV[row][col].H = bmp.Pixels2D_HSV[row][col].H;
			new_bmp.Pixels2D_HSV[row][col].S = bmp.Pixels2D_HSV[row][col].S;

			new_bmp.Pixels2D_HSV[row][col].V = bmp.Pixels2D_HSV[row][col].V + delta_V;
			if (new_bmp.Pixels2D_HSV[row][col].V > 1)
				new_bmp.Pixels2D_HSV[row][col].V = 1;
			else if (new_bmp.Pixels2D_HSV[row][col].V < 0)
				new_bmp.Pixels2D_HSV[row][col].V = 0;
		}
	}

	HSV2BGR(new_bmp);
	Pixels2D_to_pixels(new_bmp);

	return new_bmp;
}

Bitmap CropIm(Bitmap &bmp, int Tung1, int Tung2, int Hoanh1, int Hoanh2)
{
	Bitmap new_bmp;
	int col = 0, row = 0;
	if (Tung1 < 0 || Tung2 < 0 || Hoanh1 < 0 || Hoanh2 < 0 ||
		Tung1 > bmp.height || Tung2 > bmp.height || Hoanh1 > bmp.width || Hoanh2 > bmp.width ||
		Tung1 >= Tung2 || Hoanh1 >= Hoanh2)
		return bmp;
	else
	{
		new_bmp.height = Tung2 - Tung1;
		new_bmp.width = Hoanh2 - Hoanh1;
		new_bmp.rowSize = ((3 * new_bmp.width + 3) / 4) * 4;
		
		new_bmp.Pixels2D.resize(new_bmp.height);
		for (int i = Tung1; i < Tung2; i++)
		{
			new_bmp.Pixels2D[row].resize(new_bmp.width);
			for (int j = Hoanh1; j < Hoanh2; j++)
			{
				new_bmp.Pixels2D[row][col].B = bmp.Pixels2D[i][j].B;
				new_bmp.Pixels2D[row][col].G = bmp.Pixels2D[i][j].G;
				new_bmp.Pixels2D[row][col].R = bmp.Pixels2D[i][j].R;
				col++;
			}
			row++;
			col = 0;
		}
	}
	Pixels2D_to_pixels(new_bmp);
	return new_bmp;
}

Bitmap BGR2Gray(Bitmap &bmp)
{
	Bitmap new_bmp;
	new_bmp.height = bmp.height;
	new_bmp.width = bmp.width;
	new_bmp.rowSize = bmp.rowSize;

	new_bmp.Pixels2D.resize(bmp.height);
	for (int row = 0; row < bmp.height; row++)
	{
		new_bmp.Pixels2D[row].resize(bmp.width);
		for (int col = 0; col < bmp.width; col++)
		{
			int I = 0.114 * bmp.Pixels2D[row][col].B + 0.587 * bmp.Pixels2D[row][col].G + 0.299 * bmp.Pixels2D[row][col].R;
			new_bmp.Pixels2D[row][col].B = new_bmp.Pixels2D[row][col].G = new_bmp.Pixels2D[row][col].R = I;
		}
	}
	Pixels2D_to_pixels(new_bmp);

	return new_bmp;
}

Bitmap Invert(Bitmap &bmp)
{
	Bitmap new_bmp;
	new_bmp.height = bmp.height;
	new_bmp.width = bmp.width;
	new_bmp.rowSize = bmp.rowSize;

	new_bmp.Pixels2D.resize(bmp.height);
	for (int row = 0; row < bmp.height; row++)
	{
		new_bmp.Pixels2D[row].resize(bmp.width);
		for (int col = 0; col < bmp.width; col++)
		{
			new_bmp.Pixels2D[row][col].B = 255 - bmp.Pixels2D[row][col].B;
			new_bmp.Pixels2D[row][col].G = 255 - bmp.Pixels2D[row][col].G;
			new_bmp.Pixels2D[row][col].R = 255 - bmp.Pixels2D[row][col].R;
		}
	}
	Pixels2D_to_pixels(new_bmp);

	return new_bmp;
}

//tính giá trị ngưỡng nhị phân
double adaptiveThreshold(Bitmap bitmap)
{
	int sum = 0;
	for (int row = 0; row < bitmap.height; row++)
		for (int col = 0; col < bitmap.width; col++)
		{
			int offset = (bitmap.height - 1 - row)*bitmap.rowSize + col * 3;
			sum += bitmap.pixels[offset];
		}
	return sum * 1.0 / (bitmap.height*bitmap.width);
}

Bitmap BGR2Binary(Bitmap &bitmap)
{
	Bitmap new_bmp = BGR2Gray(bitmap);
	
	double T = adaptiveThreshold(new_bmp);			//T là ngưỡng nhị phân
	for (int row = 0; row < new_bmp.height; row++)
		for (int col = 0; col < new_bmp.width; col++)
		{
			Color color;
			GetPixel(new_bmp, row, col, color);

			int bin = 0;
			if (color.R > T)
				bin = 255;

			color.B = color.G = color.R = bin;
			SetPixel(new_bmp, row, col, color);
		}

	return new_bmp;
}


Bitmap resizeIm(Bitmap &bmp, int new_width, int new_height)
{
	Bitmap new_bmp;
	new_bmp.height = new_height;
	new_bmp.width = new_width;
	new_bmp.rowSize = ((3 * new_bmp.width + 3) / 4) * 4;
	
	double fy = bmp.width / (float)new_width;
	double fx = bmp.height / (float)new_height;
	double fix = 1 / fx;
	double fiy = 1 / fy;
	double fxStep = fx * 0.9999;
	double fyStep = fy * 0.9999;
	double dx, dy;
	double destB;
	double destG;
	double destR;
	float AP;

	new_bmp.Pixels2D.resize(new_bmp.height);
	for (int row = 0; row < new_height; row++)
		new_bmp.Pixels2D[row].resize(new_bmp.width);

	for (int y = 0; y < new_width; y++)
	{
		double sy1 = y * fy;
		double sy2 = sy1 + fyStep;
		int jstart = sy1;
		int jend = sy2;
		double devY1 = 1 - sy1 + jstart;
		double devY2 = jend + 1 - sy2;
		for (int x = 0; x < new_height; x++)
		{
			double sx1 = x * fx;
			double sx2 = sx1 + fxStep;
			int istart = sx1;
			int iend = sx2;
			double devX1 = 1 - sx1 + istart;
			double devX2 = iend + 1 - sx2;
			destB = 0;
			destG = 0;
			destR = 0;
			dy = devY1;
			for (int j = jstart; j <= jend; j++)
			{
				if (j == jend) dy = dy - devY2;
				dx = devX1;
				for (int i = istart; i <= iend; i++)
				{
					if (i == iend) dx = dx - devX2;
					AP = dx * dy * fix * fiy;
					destB += bmp.Pixels2D[i][j].B * AP;
					destG += bmp.Pixels2D[i][j].G * AP;
					destR += bmp.Pixels2D[i][j].R * AP;
					dx = 1;
				}
				dy = 1;
			}
			new_bmp.Pixels2D[x][y].B = round(destB);
			new_bmp.Pixels2D[x][y].G = round(destG);
			new_bmp.Pixels2D[x][y].R = round(destR);
		}
	}
	Pixels2D_to_pixels(new_bmp);
	return new_bmp;
}

Bitmap Rotate(Bitmap &bmp) {
	Bitmap new_bmp;
	//pixels_to_Pixels2D(bmp);

	new_bmp.Pixels2D.resize(bmp.width);
	for (int i = 0; i < bmp.width; i++)
		new_bmp.Pixels2D[i].resize(bmp.height);
	
	for (int x = 0; x < bmp.height; x++)
		for (int y = 0; y < bmp.width; y++)
			new_bmp.Pixels2D[y][x] = bmp.Pixels2D[bmp.height - 1 - x][y];
	
	new_bmp.width = bmp.height;
	new_bmp.height = bmp.width;
	new_bmp.rowSize = ((3 * new_bmp.width + 3) / 4) * 4;
	Pixels2D_to_pixels(new_bmp);
	return new_bmp;
}


Bitmap Flip(Bitmap &bmp, int type)
{
	Bitmap new_bmp = bmp;

	new_bmp.Pixels2D.resize(bmp.height);
	
	if (type == 1)//lat doc
		for (int row = 0; row < bmp.height; row++)
		{
			new_bmp.Pixels2D[row].resize(bmp.width);
			for (int col = 0; col < bmp.width; col++)
				new_bmp.Pixels2D[row][col] = bmp.Pixels2D[bmp.height - 1 - row][col];
		}

	else //lat ngang
		for (int row = 0; row < bmp.height; row++)
		{
			new_bmp.Pixels2D[row].resize(bmp.width);
			for (int col = 0; col < bmp.width; col++)
				new_bmp.Pixels2D[row][col] = bmp.Pixels2D[row][bmp.width - 1 - col];
		}

	Pixels2D_to_pixels(new_bmp);
	return new_bmp;
}

Bitmap Blur(Bitmap &bmp, int n)
{
	if (n == 0)
		return bmp;

	Bitmap new_bmp;
	new_bmp.height = bmp.height;
	new_bmp.width = bmp.width;
	new_bmp.rowSize = bmp.rowSize;
	new_bmp.Pixels2D.resize(bmp.height);

	new_bmp.Pixels2D[0].resize(bmp.width);
	new_bmp.Pixels2D[bmp.height - 1].resize(bmp.width);

	new_bmp.Pixels2D[0][0].B = (bmp.Pixels2D[0][0].B + bmp.Pixels2D[0][1].B + bmp.Pixels2D[1][0].B + bmp.Pixels2D[1][1].B) / 4;
	new_bmp.Pixels2D[0][0].G = (bmp.Pixels2D[0][0].G + bmp.Pixels2D[0][1].G + bmp.Pixels2D[1][0].G + bmp.Pixels2D[1][1].G) / 4;
	new_bmp.Pixels2D[0][0].R = (bmp.Pixels2D[0][0].R + bmp.Pixels2D[0][1].R + bmp.Pixels2D[1][0].R + bmp.Pixels2D[1][1].R) / 4;

	new_bmp.Pixels2D[0][bmp.width - 1].B = (bmp.Pixels2D[0][bmp.width - 1].B + bmp.Pixels2D[0][bmp.width - 2].B + bmp.Pixels2D[1][bmp.width - 1].B + bmp.Pixels2D[1][bmp.width - 2].B) / 4;
	new_bmp.Pixels2D[0][bmp.width - 1].G = (bmp.Pixels2D[0][bmp.width - 1].G + bmp.Pixels2D[0][bmp.width - 2].G + bmp.Pixels2D[1][bmp.width - 1].G + bmp.Pixels2D[1][bmp.width - 2].G) / 4;
	new_bmp.Pixels2D[0][bmp.width - 1].R = (bmp.Pixels2D[0][bmp.width - 1].R + bmp.Pixels2D[0][bmp.width - 2].R + bmp.Pixels2D[1][bmp.width - 1].R + bmp.Pixels2D[1][bmp.width - 2].R) / 4;

	new_bmp.Pixels2D[bmp.height - 1][0].B = (bmp.Pixels2D[bmp.height - 1][0].B + bmp.Pixels2D[bmp.height - 1][1].B + bmp.Pixels2D[bmp.height - 2][0].B + bmp.Pixels2D[bmp.height - 2][1].B) / 4;
	new_bmp.Pixels2D[bmp.height - 1][0].G = (bmp.Pixels2D[bmp.height - 1][0].G + bmp.Pixels2D[bmp.height - 1][1].G + bmp.Pixels2D[bmp.height - 2][0].G + bmp.Pixels2D[bmp.height - 2][1].G) / 4;
	new_bmp.Pixels2D[bmp.height - 1][0].R = (bmp.Pixels2D[bmp.height - 1][0].R + bmp.Pixels2D[bmp.height - 1][1].R + bmp.Pixels2D[bmp.height - 2][0].R + bmp.Pixels2D[bmp.height - 2][1].R) / 4;

	new_bmp.Pixels2D[bmp.height - 1][bmp.width - 1].B = (bmp.Pixels2D[bmp.height - 1][bmp.width - 1].B + bmp.Pixels2D[bmp.height - 1][bmp.width - 2].B + bmp.Pixels2D[bmp.height - 2][bmp.width - 1].B + bmp.Pixels2D[bmp.height - 2][bmp.width - 2].B) / 4;
	new_bmp.Pixels2D[bmp.height - 1][bmp.width - 1].G = (bmp.Pixels2D[bmp.height - 1][bmp.width - 1].G + bmp.Pixels2D[bmp.height - 1][bmp.width - 2].G + bmp.Pixels2D[bmp.height - 2][bmp.width - 1].G + bmp.Pixels2D[bmp.height - 2][bmp.width - 2].G) / 4;
	new_bmp.Pixels2D[bmp.height - 1][bmp.width - 1].R = (bmp.Pixels2D[bmp.height - 1][bmp.width - 1].R + bmp.Pixels2D[bmp.height - 1][bmp.width - 2].R + bmp.Pixels2D[bmp.height - 2][bmp.width - 1].R + bmp.Pixels2D[bmp.height - 2][bmp.width - 2].R) / 4;

	for (int col = 1; col < bmp.width - 1; col++)
	{
		new_bmp.Pixels2D[0][col].B = (bmp.Pixels2D[0][col].B + bmp.Pixels2D[0][col - 1].B + bmp.Pixels2D[0][col + 1].B + bmp.Pixels2D[1][col].B + bmp.Pixels2D[1][col - 1].B + bmp.Pixels2D[1][col + 1].B) / 6;
		new_bmp.Pixels2D[0][col].G = (bmp.Pixels2D[0][col].G + bmp.Pixels2D[0][col - 1].G + bmp.Pixels2D[0][col + 1].G + bmp.Pixels2D[1][col].G + bmp.Pixels2D[1][col - 1].G + bmp.Pixels2D[1][col + 1].G) / 6;
		new_bmp.Pixels2D[0][col].R = (bmp.Pixels2D[0][col].R + bmp.Pixels2D[0][col - 1].R + bmp.Pixels2D[0][col + 1].R + bmp.Pixels2D[1][col].R + bmp.Pixels2D[1][col - 1].R + bmp.Pixels2D[1][col + 1].R) / 6;

		new_bmp.Pixels2D[bmp.height - 1][col].B = (bmp.Pixels2D[bmp.height - 1][col].B + bmp.Pixels2D[bmp.height - 1][col - 1].B + bmp.Pixels2D[bmp.height - 1][col + 1].B + bmp.Pixels2D[bmp.height - 2][col].B + bmp.Pixels2D[bmp.height - 2][col - 1].B + bmp.Pixels2D[bmp.height - 2][col + 1].B) / 6;
		new_bmp.Pixels2D[bmp.height - 1][col].G = (bmp.Pixels2D[bmp.height - 1][col].G + bmp.Pixels2D[bmp.height - 1][col - 1].G + bmp.Pixels2D[bmp.height - 1][col + 1].G + bmp.Pixels2D[bmp.height - 2][col].G + bmp.Pixels2D[bmp.height - 2][col - 1].G + bmp.Pixels2D[bmp.height - 2][col + 1].G) / 6;
		new_bmp.Pixels2D[bmp.height - 1][col].R = (bmp.Pixels2D[bmp.height - 1][col].R + bmp.Pixels2D[bmp.height - 1][col - 1].R + bmp.Pixels2D[bmp.height - 1][col + 1].R + bmp.Pixels2D[bmp.height - 2][col].R + bmp.Pixels2D[bmp.height - 2][col - 1].R + bmp.Pixels2D[bmp.height - 2][col + 1].R) / 6;
	}

	for (int row = 1; row < bmp.height - 1; row++)
	{
		new_bmp.Pixels2D[row].resize(bmp.width);

		new_bmp.Pixels2D[row][0].B = (bmp.Pixels2D[row][0].B + bmp.Pixels2D[row - 1][0].B + bmp.Pixels2D[row + 1][0].B + bmp.Pixels2D[row][1].B + bmp.Pixels2D[row - 1][1].B + bmp.Pixels2D[row + 1][1].B) / 6;
		new_bmp.Pixels2D[row][0].G = (bmp.Pixels2D[row][0].G + bmp.Pixels2D[row - 1][0].G + bmp.Pixels2D[row + 1][0].G + bmp.Pixels2D[row][1].G + bmp.Pixels2D[row - 1][1].G + bmp.Pixels2D[row + 1][1].G) / 6;
		new_bmp.Pixels2D[row][0].R = (bmp.Pixels2D[row][0].R + bmp.Pixels2D[row - 1][0].R + bmp.Pixels2D[row + 1][0].R + bmp.Pixels2D[row][1].R + bmp.Pixels2D[row - 1][1].R + bmp.Pixels2D[row + 1][1].R) / 6;
	
		new_bmp.Pixels2D[row][bmp.width - 1].B = (bmp.Pixels2D[row][bmp.width - 1].B + bmp.Pixels2D[row - 1][bmp.width - 1].B + bmp.Pixels2D[row + 1][bmp.width - 1].B + bmp.Pixels2D[row][bmp.width - 2].B + bmp.Pixels2D[row - 1][bmp.width - 2].B + bmp.Pixels2D[row + 1][bmp.width - 2].B) / 6;
		new_bmp.Pixels2D[row][bmp.width - 1].G = (bmp.Pixels2D[row][bmp.width - 1].G + bmp.Pixels2D[row - 1][bmp.width - 1].G + bmp.Pixels2D[row + 1][bmp.width - 1].G + bmp.Pixels2D[row][bmp.width - 2].G + bmp.Pixels2D[row - 1][bmp.width - 2].G + bmp.Pixels2D[row + 1][bmp.width - 2].G) / 6;
		new_bmp.Pixels2D[row][bmp.width - 1].R = (bmp.Pixels2D[row][bmp.width - 1].R + bmp.Pixels2D[row - 1][bmp.width - 1].R + bmp.Pixels2D[row + 1][bmp.width - 1].R + bmp.Pixels2D[row][bmp.width - 2].R + bmp.Pixels2D[row - 1][bmp.width - 2].R + bmp.Pixels2D[row + 1][bmp.width - 2].R) / 6;
	}
	
	for (int row = 1; row < bmp.height - 1; row++)
		for (int col = 1; col < bmp.width - 1; col++)
		{
			new_bmp.Pixels2D[row][col].B = (bmp.Pixels2D[row][col].B + bmp.Pixels2D[row - 1][col - 1].B + bmp.Pixels2D[row][col - 1].B + bmp.Pixels2D[row + 1][col - 1].B + bmp.Pixels2D[row - 1][col].B + bmp.Pixels2D[row + 1][col].B + bmp.Pixels2D[row - 1][col + 1].B + bmp.Pixels2D[row][col + 1].B + bmp.Pixels2D[row + 1][col + 1].B) / 9;
			new_bmp.Pixels2D[row][col].G = (bmp.Pixels2D[row][col].G + bmp.Pixels2D[row - 1][col - 1].G + bmp.Pixels2D[row][col - 1].G + bmp.Pixels2D[row + 1][col - 1].G + bmp.Pixels2D[row - 1][col].G + bmp.Pixels2D[row + 1][col].G + bmp.Pixels2D[row - 1][col + 1].G + bmp.Pixels2D[row][col + 1].G + bmp.Pixels2D[row + 1][col + 1].G) / 9;
			new_bmp.Pixels2D[row][col].R = (bmp.Pixels2D[row][col].R + bmp.Pixels2D[row - 1][col - 1].R + bmp.Pixels2D[row][col - 1].R + bmp.Pixels2D[row + 1][col - 1].R + bmp.Pixels2D[row - 1][col].R + bmp.Pixels2D[row + 1][col].R + bmp.Pixels2D[row - 1][col + 1].R + bmp.Pixels2D[row][col + 1].R + bmp.Pixels2D[row + 1][col + 1].R) / 9;
		}

	if (n == 1)
	{
		Pixels2D_to_pixels(new_bmp);
		return new_bmp;
	}
	return Blur(new_bmp, n - 1);
}
// tính lại mỗi pixel bằng trung bình cộng của 9 pixel xung quanh
// riêng các pixel ở viền thì ko tính


string _getName(char c)
{
	string name;
	if ('a' <= c && c <= 'z')
	{
		name = c;
		name += "_";
	}
	else
	{
		name = c;
	}
	name = "font\\" + name + ".bmp";
	return name;
}

void _printChar(Bitmap &bmp, int row, int col, char c, int size, COLORREF color)
{
	string fileName = _getName(c);
	Bitmap char_bmp = LoadBitmap(fileName);
	if (c == 'I' || c == 'l' || c == 'i' || c == 'j')
		char_bmp = resizeIm(char_bmp, size * 2.5, size * 10);
	else if (c == 'f' || c == 'r' || c == 't')
		char_bmp = resizeIm(char_bmp, size * 3, size * 10);
	else if (c == 'm' || c == 'W' || c == 'M' || c == 'W')
		char_bmp = resizeIm(char_bmp, size * 6, size * 10);
	else
		char_bmp = resizeIm(char_bmp, size * 5, size * 10);
	Color char_color = { GetRValue(color), GetGValue(color), GetBValue(color) };
	
	for (int i = 0; i < char_bmp.height; i++)
	{
		for (int j = 0; j < char_bmp.width; j++)
		{
			if (char_bmp.Pixels2D[i][j].B < 50 && char_bmp.Pixels2D[i][j].G < 50 && char_bmp.Pixels2D[i][j].R < 50)
			{
				if (i + row >= 0 && i + row < bmp.height && j + col >= 0 && j + col < bmp.width)
					bmp.Pixels2D[i + row][j + col] = char_color;
			}
		}
	}
	Pixels2D_to_pixels(bmp);
}

void _getNextPos(Bitmap &bmp, char c, int size, int &row, int &col)
{
	if (c == 'I' || c == 'l' || c == 'i' || c == 'j')
		col += (size * 2.5);
	else if (c == 'f' || c == 'r' || c == 't')
		col += (size * 3);
	else if (c == 'm' || c == 'W' || c == 'M' || c == 'W')
		col += (size * 6);
	else
		col += (size * 5);
}

Bitmap insertText(Bitmap &bmp, int row, int col, string str, int size, COLORREF color)
{
	Bitmap new_bmp;
	new_bmp.width = bmp.width;
	new_bmp.height = bmp.height;
	new_bmp.rowSize = bmp.rowSize;
	copyPixels2D(bmp, new_bmp);

	for (int i = 0; i < str.length(); i++)
	{
		if ((str.at(i) < '0' || str.at(i) > '9') && (str.at(i) < 'A' || str.at(i) > 'Z') && (str.at(i) < 'a' || str.at(i) > 'z'))
			_getNextPos(bmp, str.at(i), size, row, col);
		else
		{
			_printChar(new_bmp, row, col, str.at(i), size, color);
			_getNextPos(bmp, str.at(i), size, row, col);
			if (row >= bmp.height || col >= bmp.width) break;
		}

	}
	Pixels2D_to_pixels(new_bmp);

	return new_bmp;
}



Bitmap histogramEqualisation(Bitmap &bitmap)
{
	Bitmap new_bitmap;
	new_bitmap.width = bitmap.width;
	new_bitmap.height = bitmap.height;
	new_bitmap.rowSize = bitmap.rowSize;
	copyPixels2D(bitmap, new_bitmap);

	double  aryHistogramR[256] = { 0 };
	double  aryTransformR[256] = { 0 };
	double  dobSumR = 0.0f;
	double  aryHistogramG[256] = { 0 };
	double  aryTransformG[256] = { 0 };
	double  dobSumG = 0.0f;
	double  aryHistogramB[256] = { 0 };
	double  aryTransformB[256] = { 0 };
	double  dobSumB = 0.0f;
	int     iJ = 0;
	int     iK = 0;

	for (int i = 0; i < new_bitmap.height; i++)
	{
		for (int j = 0; j < new_bitmap.width; j++)
		{
			aryHistogramR[new_bitmap.Pixels2D[i][j].R]++;
			aryHistogramG[new_bitmap.Pixels2D[i][j].G]++;
			aryHistogramB[new_bitmap.Pixels2D[i][j].B]++;
		}
	}
	for (iJ = 0; iJ <= 255; iJ++)
	{
		dobSumR = 0.0f;
		dobSumG = 0.0f;
		dobSumB = 0.0f;
		// The length of the gray degree.
		for (iK = 0; iK <= iJ; iK++)
		{
			// The sum of gray degree.
			dobSumR = dobSumR + aryHistogramR[iK];
			dobSumG = dobSumG + aryHistogramG[iK];
			dobSumB = dobSumB + aryHistogramB[iK];
			// Transform old gray to new gray.
			aryTransformR[iJ] = (255.0 * dobSumR / (new_bitmap.height*new_bitmap.width));
			aryTransformG[iJ] = (255.0 * dobSumG / (new_bitmap.height*new_bitmap.width));
			aryTransformB[iJ] = (255.0 * dobSumB / (new_bitmap.height*new_bitmap.width));
		}
	}
	for (int i = 0; i < new_bitmap.height; i++)
	{
		for (int j = 0; j < new_bitmap.width; j++)
		{

			new_bitmap.Pixels2D[i][j].B = aryTransformB[new_bitmap.Pixels2D[i][j].B];
			new_bitmap.Pixels2D[i][j].G = aryTransformG[new_bitmap.Pixels2D[i][j].G];
			new_bitmap.Pixels2D[i][j].R = aryTransformR[new_bitmap.Pixels2D[i][j].R];
		}
	}
	Pixels2D_to_pixels(new_bitmap);

	return new_bitmap;
}

Bitmap Hue(Bitmap &bmp, int deltaH)
{
	Bitmap new_bmp;
	new_bmp.height = bmp.height;
	new_bmp.width = bmp.width;
	new_bmp.rowSize = bmp.rowSize;

	copyPixels2D_HSV(bmp, new_bmp);

	for (int row = 0; row < new_bmp.height; row++)
		for (int col = 0; col < new_bmp.width; col++)
		{
			new_bmp.Pixels2D_HSV[row][col].H += deltaH;
			if (new_bmp.Pixels2D_HSV[row][col].H < 0)
				new_bmp.Pixels2D_HSV[row][col].H += 360;
			new_bmp.Pixels2D_HSV[row][col].H = (int)new_bmp.Pixels2D_HSV[row][col].H % 360;
		}
	HSV2BGR(new_bmp);
	Pixels2D_to_pixels(new_bmp);

	return new_bmp;
}


int _X_Grad(const Bitmap &bmp, int row, int col)
{
	return (bmp.Pixels2D[row - 1][col + 1].B + bmp.Pixels2D[row][col + 1].B * 2 + bmp.Pixels2D[row + 1][col + 1].B - bmp.Pixels2D[row - 1][col - 1].B - bmp.Pixels2D[row][col - 1].B * 2 - bmp.Pixels2D[row + 1][col - 1].B);
}

int _Y_Grad(const Bitmap &bmp, int row, int col)
{
	return (bmp.Pixels2D[row - 1][col - 1].B + bmp.Pixels2D[row - 1][col].B * 2 + bmp.Pixels2D[row - 1][col + 1].B - bmp.Pixels2D[row + 1][col - 1].B - bmp.Pixels2D[row + 1][col].B * 2 - bmp.Pixels2D[row + 1][col + 1].B);
}

Bitmap edgeDetect(Bitmap &bmp) //Using Sobel Operator
{
	Bitmap new_bmp = BGR2Gray(bmp);

	int gradient, xGrad, yGrad;
	for (int row = 0; row < new_bmp.height; row++)
		for (int col = 0; col < new_bmp.width; col++)
		{
			if (row == 0 || col == 0 || row == (new_bmp.height - 1) || col == (new_bmp.width - 1))
				new_bmp.Pixels2D[row][col].B = new_bmp.Pixels2D[row][col].G = new_bmp.Pixels2D[row][col].R = 0;
			else
			{
				xGrad = _X_Grad(bmp, row, col);
				yGrad = _Y_Grad(bmp, row, col);
				//gradient = sqrt(xGrad * xGrad + yGrad * yGrad);
				gradient = abs(xGrad) + abs(yGrad);
				if (gradient > 255)
					gradient = 255;
				new_bmp.Pixels2D[row][col].B = new_bmp.Pixels2D[row][col].G = new_bmp.Pixels2D[row][col].R = gradient;
			}
		}
	Pixels2D_to_pixels(new_bmp);
	return new_bmp;
}

Bitmap Contrast(Bitmap &bmp, double value)
{
	double contrast = pow((1 + value / 100.0), 2);

	Bitmap new_bmp;
	new_bmp.height = bmp.height;
	new_bmp.width = bmp.width;
	new_bmp.rowSize = bmp.rowSize;

	copyPixels2D_HSV(bmp, new_bmp);

	for (int row = 0; row < new_bmp.height; row++)
		for (int col = 0; col < new_bmp.width; col++)
		{
			new_bmp.Pixels2D_HSV[row][col].V = (new_bmp.Pixels2D_HSV[row][col].V - 0.5) * contrast + 0.5;
			if (new_bmp.Pixels2D_HSV[row][col].V > 1)
				new_bmp.Pixels2D_HSV[row][col].V = 1;
			else if (new_bmp.Pixels2D_HSV[row][col].V < 0)
				new_bmp.Pixels2D_HSV[row][col].V = 0;
		}
	HSV2BGR(new_bmp);
	Pixels2D_to_pixels(new_bmp);

	return new_bmp;
}