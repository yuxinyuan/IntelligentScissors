#include "ImgBuffer.h"
#include "Bitmap.h"
#include "ScissorsAlgorithm.h"
#include <cstring>

ImgBuffer::ImgBuffer():
	_imgWidth(0), _imgHeight(0),
	originalPixelArray(nullptr),
	contourPixelArray(nullptr),
	nodeBuffer(nullptr)
{
}


ImgBuffer::~ImgBuffer()
{
	delete[] originalPixelArray;
	delete[] contourPixelArray;
	delete[] nodeBuffer;
}

void ImgBuffer::cleanBuffer()
{
	delete[] originalPixelArray;
	originalPixelArray = nullptr;
	delete[] contourPixelArray;
	contourPixelArray = nullptr;
	delete[] nodeBuffer;
	nodeBuffer = nullptr;
	_imgHeight = _imgWidth = 0;
	firstSeed._x = activeSeed._x = 0;
	firstSeed._y = activeSeed._y = 0;
	selectedNodes.clear();
}


void ImgBuffer::loadImage(const char * filename)
{
	originalPixelArray = readBMP(filename, _imgWidth, _imgHeight);
	padWidth = _imgWidth * 3;	// 3 bytes per pixel
	int pad = 0;
	if (padWidth % 4 != 0) {
		// width is require to be multiple of 4
		pad = 4 - (padWidth % 4);
		padWidth += pad;
	}
	contourPixelArray = new unsigned char[_imgHeight * padWidth];
	memcpy(contourPixelArray, originalPixelArray, _imgHeight * padWidth);
	nodeBuffer = new Node[_imgHeight * _imgWidth];
	initNodeBuffer(nodeBuffer, this);
}

unsigned char * ImgBuffer::generatePixelNode()
{
	return nullptr;
}

unsigned char * ImgBuffer::generateCostGraph()
{
	return nullptr;
}

void ImgBuffer::liveWireDP(Point seed)
{
}

void ImgBuffer::recordLastWire(Point pos)
{
}

RGBTuple ImgBuffer::getOriginalPixel(Point pos)
{
	return getOriginalPixel(pos._x, pos._y);
}

RGBTuple ImgBuffer::getOriginalPixel(int x, int y)
{
	if (x < 0 || x >= _imgWidth ||
		y < 0 || y >= _imgHeight) {
		// the coordinate is out of bound
		// return dummy value
		return RGBTuple(0, 0, 0);
	}
	unsigned char* pixel = originalPixelArray + (y * padWidth + x);
	return std::make_tuple(pixel[0], pixel[1], pixel[2]);
}
