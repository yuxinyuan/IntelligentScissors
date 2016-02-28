#pragma once
#ifndef _SCISSORSALGORITHM_H_
#define _SCISSORSALGORITHM_H_

#include "ImgBuffer.h"

const double SQRT2 = 1.4142135623730950488016887242097;
const double SQINV = 1.0 / SQRT2;

// BEGIN eight filter kernels
const double kernels[8][9] = {
	{ // 0
		0.0000, 0.2500, 0.2500 ,
		0.0000, 0.0000, 0.0000 ,
		0.0000, -0.2500, 0.2500
	},
	{ // 1
		0.0000, -SQINV, 0.0000 ,
		0.0000, 0.0000, SQINV ,
		0.0000, 0.0000, 0.0000
	},
	{ // 2
		0.2500, 0.0000, -0.2500 ,
		0.2500, 0.0000, -0.2500 ,
		0.0000, 0.0000, 0.0000
	},
	{ // 3
		0.0000, SQINV, 0.0000 ,
		-SQINV, 0.0000, 0.0000 ,
		0.0000, 0.0000, 0.0000
	},
	{ // 4
		-0.2500, -0.2500, 0.0000 ,
		0.0000, 0.0000, 0.0000 ,
		0.2500, 0.2500, 0.0000
	},
	{ // 5
		0.0000, 0.0000, 0.0000 ,
		SQINV, 0.0000, 0.0000 ,
		0.0000, -SQINV, 0.0000
	},
	{ // 6
		0.0000, 0.0000, 0.0000 ,
		-0.2500, 0.0000, 0.2500 ,
		-0.2500, 0.0000, 0.2500
	},
	{ // 7
		0.0000, 0.0000, 0.0000 ,
		0.0000, 0.0000, -SQINV ,
		0.0000, SQINV, 0.0000
	}
};
// END eight filter kernels


void initNodeBuffer(Node * nodeBuffer, ImgBuffer* imgBuffer);

/**
 * apply filter kernel to image at (x, y) pixel
 * x:				a column index,
 * y:				a row index,
 * imgBuffer:		a image buffer storing the original image
 *
 * kernel:			the 2D filter kernel,
 * knlWidth:		the width of the kernel
 * knlHeight:		the height of the kernel
 *
 * scale, offset:	after convolving the kernel with the image,
 *					the result pixel should be divided by scale and then added by offset
 *
 * rsltPixel[0], rsltPixel[1], rsltPixel[2]:
 *					the filtered pixel R, G, B values at row y , column x;
 */
void pixelFilter(double rsltPixel[3],
	int x, int y, ImgBuffer* imgBuffer,
	const double *kernel, int knlWidth, int knlHeight,
	double scale, double offset);

/**
 * apply filter kernel to the whole image
 * imgBuffer:		a image buffer storing the original image
 * selection:       a byte array of the same size as the image,
 *					indicating where in the original image should be filtered
 *
 * kernel:			the 2D filter kernel,
 * knlWidth:		the width of the kernel
 * knlHeight:		the height of the kernel
 *
 * scale, offset:	after convolving the kernel with the image,
 *					the result pixel should be divided by scale and then added by offset
 *
 * rsltImg:			the filtered image of the same size as original image.
 *					note that the pointer should be valid ( allocated already ),
 *					of size (3 * imgWidth * imgHeight).
 */
void imageFilter(double *rsltImg, ImgBuffer* imgBuffer,
	const unsigned char* selection,
	const double *kernel, int knlWidth, int knlHeight,
	double scale, double offset);

/**
 * compute minimum path tree on nodeBuffer, starting from seed
 * seed:			seed position in nodeBuffer
 * nodeBuffer:		node buffer of size width by height;
 * width, height:   dimensions of the node buffer;
 * selection:		if selection != NULL, search path only when selection[j * width + i] = 1;
 *					otherwise, search in the whole set of nodes.
 * numExpanded:		compute the only the first numExpanded number of nodes; (for debugging)
 */
void liveWireDP(Point seed, Node *nodeBuffer, int width, int height, 
	const unsigned char *selection = nullptr, int expanded = -1);

#endif // !_SCISSORSALGORITHM_H_