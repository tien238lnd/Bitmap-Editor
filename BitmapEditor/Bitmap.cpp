#include "stdafx.h"
#include "Bitmap.h"

#pragma pack(1)

struct BMFHeader
{
	char signature[2];
	unsigned int size;
	unsigned int reserved;
	unsigned int pixelAddress;
};

struct DIBHeader
{
	unsigned int size;
	unsigned int width;
	unsigned int height;
	unsigned short colorPlane;
	unsigned short colorDepth;
	unsigned char reserved[24];
};

Bitmap LoadBitmap(string fname)
{
	Bitmap bmp;
	bmp.height = 0;
	FILE *f = fopen(fname.c_str(), "rb");
	if (f == NULL)
		return bmp;

	// read BMFHeader
	BMFHeader bmfhd;
	if (fread(&bmfhd, sizeof(BMFHeader), 1, f) == 0)
		return bmp;

	if (bmfhd.signature[0] != 'B' || bmfhd.signature[1] != 'M')
		return bmp;

	// read DIBHeader
	DIBHeader dibhd;
	if (fread(&dibhd, sizeof(DIBHeader), 1, f) == 0)
		return bmp;

	if (dibhd.colorDepth != 24 || dibhd.height < 0)
		return bmp;

	// read pixels (24 bits = 3 bytes/pixel)

	bmp.width = dibhd.width;
	bmp.height = dibhd.height;
	bmp.rowSize = ((3 * bmp.width + 3) / 4) * 4;

	fseek(f, bmfhd.pixelAddress, SEEK_SET);

	if (bmp.pixels.empty())
		bmp.pixels.resize(bmp.height * bmp.rowSize);
	
	if (fread(&bmp.pixels[0], bmp.rowSize, bmp.height, f) < bmp.height)
	{
		bmp.height = 0;
		return bmp;
	}
		
	fclose(f);

	pixels_to_Pixels2D(bmp);
	BGR2HSV(bmp);

	return bmp;
}

int SaveBitmap(string fname, Bitmap &bmp)
{
	FILE *f = fopen(fname.c_str(), "wb");
	if (f == NULL)
		return 0;

	// write BMFHeader
	BMFHeader bmfhd;
	bmfhd.signature[0] = 'B';
	bmfhd.signature[1] = 'M';
	bmfhd.size = sizeof(BMFHeader) + sizeof(DIBHeader) + bmp.rowSize*bmp.height;
	bmfhd.reserved = 0;
	bmfhd.pixelAddress = sizeof(BMFHeader) + sizeof(DIBHeader);
	if (fwrite(&bmfhd, sizeof(BMFHeader), 1, f) == 0)
		return 0;

	// write DIBHeader
	DIBHeader dibhd;
	dibhd.size = sizeof(DIBHeader);
	dibhd.width = bmp.width;
	dibhd.height = bmp.height;
	dibhd.colorPlane = 1;
	dibhd.colorDepth = 24;
	memset(&dibhd.reserved, 0, sizeof(dibhd.reserved));		// fill all bytes of dibhd.reserved with 0
	if (fwrite(&dibhd, sizeof(DIBHeader), 1, f) == 0)
		return 0;

	// write pixels

	if (bmp.pixels.empty())
		Pixels2D_to_pixels(bmp);

	if (fwrite(&bmp.pixels[0], bmp.rowSize, bmp.height, f) < bmp.height)
		return 0;

	fclose(f);

	return 1;
}


// O(1)
bool SetPixel(Bitmap &bmp, int row, int col, Color color)
{
	if (row < 0 || row >= bmp.height
		|| col < 0 || col >= bmp.width)
		return 0;

	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col * 3;
	bmp.pixels[offset] = color.B;
	bmp.pixels[offset + 1] = color.G;
	bmp.pixels[offset + 2] = color.R;

	return 1;
}

bool GetPixel(const Bitmap &bmp, int row, int col, Color &color)
{
	if (row < 0 || row >= bmp.height
		|| col < 0 || col >= bmp.width)
		return 0;

	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col * 3;
	color.B = bmp.pixels[offset];
	color.G = bmp.pixels[offset + 1];
	color.R = bmp.pixels[offset + 2];

	return 1;
}

void pixels_to_Pixels2D(Bitmap &bmp)
{
	if (bmp.Pixels2D.empty())
	{
		bmp.Pixels2D.resize(bmp.height);
		for (int row = 0; row < bmp.height; row++)
		{
			bmp.Pixels2D[row].resize(bmp.width);
			for (int col = 0; col < bmp.width; col++)
				GetPixel(bmp, row, col, bmp.Pixels2D[row][col]);
		}
	}
	else
		for (int row = 0; row < bmp.height; row++)
			for (int col = 0; col < bmp.width; col++)
				GetPixel(bmp, row, col, bmp.Pixels2D[row][col]);
		
}

void Pixels2D_to_pixels(Bitmap &bmp)
{
	if (bmp.Pixels2D.empty())
		HSV2BGR(bmp);
		
	if (bmp.pixels.empty())
		bmp.pixels.resize(bmp.height * bmp.rowSize);

	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
			SetPixel(bmp, row, col, bmp.Pixels2D[row][col]);
}

void BGR2HSV(Bitmap &bmp)
{
	if (bmp.Pixels2D.empty())
		pixels_to_Pixels2D(bmp);

	if (bmp.Pixels2D_HSV.empty())
	{
		bmp.Pixels2D_HSV.resize(bmp.height);
		for (int row = 0; row < bmp.height; row++)
		{
			bmp.Pixels2D_HSV[row].resize(bmp.width);
			for (int col = 0; col < bmp.width; col++)
			{
				unsigned char R = bmp.Pixels2D[row][col].R;
				unsigned char G = bmp.Pixels2D[row][col].G;
				unsigned char B = bmp.Pixels2D[row][col].B;

				double H, S, V;

				V = max(R, max(G, B));
				double m = min(R, min(G, B));

				if (V == 0)		// R = G = B = 0
					S = 0;
				else
					S = (V - m) / V;

				if (S == 0)		// R = G = B
					H = 0;
				else if (V == R)
				{
					H = 60 * (G - B) / (V - m);			// -60 <= H <= 60
					if (H < 0)
						H += 360;						// H thuoc [0, 60] U [300, 360)
				}
				else if (V == G)
					H = 120 + 60 * (B - R) / (V - m);	// 60 <= H <= 180
				else
					H = 240 + 60 * (R - G) / (V - m);	// 180 <= H <= 300

				bmp.Pixels2D_HSV[row][col].H = H;
				bmp.Pixels2D_HSV[row][col].S = S;
				bmp.Pixels2D_HSV[row][col].V = V / 255;
			}
		}
	}
	else
		for (int row = 0; row < bmp.height; row++)
			for (int col = 0; col < bmp.width; col++)
			{
				unsigned char R = bmp.Pixels2D[row][col].R;
				unsigned char G = bmp.Pixels2D[row][col].G;
				unsigned char B = bmp.Pixels2D[row][col].B;

				double H, S, V;

				V = max(R, max(G, B));
				double m = min(R, min(G, B));

				if (V == 0)		// R = G = B = 0
					S = 0;
				else
					S = (V - m) / V;

				if (S == 0)		// R = G = B
					H = 0;
				else if (V == R)
				{
					H = 60 * (G - B) / (V - m);			// -60 <= H <= 60
					if (H < 0)
						H += 360;						// H thuoc [0, 60] U [300, 360)
				}
				else if (V == G)
					H = 120 + 60 * (B - R) / (V - m);	// 60 <= H <= 180
				else
					H = 240 + 60 * (R - G) / (V - m);	// 180 <= H <= 300

				bmp.Pixels2D_HSV[row][col].H = H;
				bmp.Pixels2D_HSV[row][col].S = S;
				bmp.Pixels2D_HSV[row][col].V = V / 255;
			}
}

void HSV2BGR(Bitmap &bmp)
{
	if (bmp.Pixels2D.empty())
	{
		bmp.Pixels2D.resize(bmp.height);
		for (int row = 0; row < bmp.height; row++)
		{
			bmp.Pixels2D[row].resize(bmp.width);
			for (int col = 0; col < bmp.width; col++)
			{
				double H = bmp.Pixels2D_HSV[row][col].H;
				double S = bmp.Pixels2D_HSV[row][col].S;
				double V = bmp.Pixels2D_HSV[row][col].V;

				double B1, G1, R1;
				B1 = G1 = R1 = 0;

				double C = V*S;			// C = max - min

				double X = C*(1 - abs(fmod(H / 60, 2) - 1));

				double m = V - C;		// m = min

				if (H < 60)
				{
					R1 = C; G1 = X;
				}
				else if (H < 120)
				{
					R1 = X; G1 = C;
				}
				else if (H < 180)
				{
					G1 = C; B1 = X;
				}
				else if (H < 240)
				{
					G1 = X; B1 = C;
				}
				else if (H < 300)
				{
					R1 = X; B1 = C;
				}
				else
				{
					R1 = C; B1 = X;
				}

				bmp.Pixels2D[row][col].R = (R1 + m) * 255;
				bmp.Pixels2D[row][col].G = (G1 + m) * 255;
				bmp.Pixels2D[row][col].B = (B1 + m) * 255;
			}
		}
	}
	else
		for (int row = 0; row < bmp.height; row++)
			for (int col = 0; col < bmp.width; col++)
			{
				double H = bmp.Pixels2D_HSV[row][col].H;
				double S = bmp.Pixels2D_HSV[row][col].S;
				double V = bmp.Pixels2D_HSV[row][col].V;

				double B1, G1, R1;
				B1 = G1 = R1 = 0;

				double C = V*S;			// C = max - min

				double X = C*(1 - abs(fmod(H / 60, 2) - 1));

				double m = V - C;		// m = min

				if (H < 60)
				{
					R1 = C; G1 = X;
				}
				else if (H < 120)
				{
					R1 = X; G1 = C;
				}
				else if (H < 180)
				{
					G1 = C; B1 = X;
				}
				else if (H < 240)
				{
					G1 = X; B1 = C;
				}
				else if (H < 300)
				{
					R1 = X; B1 = C;
				}
				else
				{
					R1 = C; B1 = X;
				}

				bmp.Pixels2D[row][col].R = (R1 + m) * 255;
				bmp.Pixels2D[row][col].G = (G1 + m) * 255;
				bmp.Pixels2D[row][col].B = (B1 + m) * 255;
			}
}


void copyPixels2D(Bitmap &bmp, Bitmap &new_bmp)
{
	if (bmp.Pixels2D.empty())
		pixels_to_Pixels2D(bmp);

	new_bmp.Pixels2D.resize(bmp.height);
	for (int row = 0; row < bmp.height; row++)
	{
		new_bmp.Pixels2D[row].resize(bmp.width);
		for (int col = 0; col < bmp.width; col++)
			new_bmp.Pixels2D[row][col] = bmp.Pixels2D[row][col];
	}
}

void copyPixels2D_HSV(Bitmap &bmp, Bitmap &new_bmp)
{
	if (bmp.Pixels2D_HSV.empty())
		BGR2HSV(bmp);

	new_bmp.Pixels2D_HSV.resize(bmp.height);
	for (int row = 0; row < bmp.height; row++)
	{
		new_bmp.Pixels2D_HSV[row].resize(bmp.width);
		for (int col = 0; col < bmp.width; col++)
			new_bmp.Pixels2D_HSV[row][col] = bmp.Pixels2D_HSV[row][col];
	}
		
}