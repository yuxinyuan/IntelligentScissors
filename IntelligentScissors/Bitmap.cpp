#define _CRT_SECURE_NO_WARNINGS 1
#include "Bitmap.h"
#include <windows.h>
#include <stdio.h>

unsigned char* readBMP(const char* filename, int& width, int& height) {
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	FILE* file = fopen(filename, "rb");
	if (file == nullptr) {
		return nullptr;
	}
	// first read the two header struct of bitmap file
	if (!fread(&bfh, sizeof(bfh), 1, file)) {
		fclose(file);
		return nullptr;
	}
	if (!fread(&bih, sizeof(bih), 1, file)) {
		fclose(file);
		return nullptr;
	}

	if (bfh.bfType != 0x4d42) {		// magic constant "BM" actually
		fclose(file);
		return nullptr;
	}
	else if (bih.biBitCount != 24) {	// require the img to be 24 bit per pixel
		fclose(file);
		return nullptr;
	}
	else {
		if (fseek(file, bfh.bfOffBits, SEEK_SET) != 0) {
			fclose(file);
			return nullptr;
		}
		width = bih.biWidth;
		height = bih.biHeight;
		int padWidth = width * 3;	// 3 bytes per pixel
		int pad = 0;
		if (padWidth % 4 != 0) {
			// width is require to be multiple of 4
			pad = 4 - (padWidth % 4);
			padWidth += pad;
		}

		unsigned char* pixelarray = new unsigned char[height * padWidth];
		if (!fread(pixelarray, height * padWidth, 1, file)) {
			delete[] pixelarray;
			fclose(file);
			return nullptr;
		}
		fclose(file);

		// the original pixel data are in blue, green, red order for 24bpp
		// shuffle bitmap data such that it is (R,G,B) tuples in row-major order
		unsigned char* in = pixelarray;
		unsigned char* out = pixelarray;
		unsigned char temp;
		for (int j = 0; j < height; ++j) {
			for (int i = 0; i < width; ++i) {
				out[1] = in[1];
				temp = in[2];
				out[2] = in[0];
				out[0] = temp;

				in += 3;
				out += 3;
			}
			in += pad;
		}
		return pixelarray;
	}
}

void writeBMP(char * filename, int width, int height, unsigned char * pixelarray)
{
	// TODO: implement this function
	return;
}
