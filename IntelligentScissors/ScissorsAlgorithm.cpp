#include "ScissorsAlgorithm.h"

void initNodeBuffer(Node* nodeBuffer, ImgBuffer* imgBuffer) {
	int imgWidth = imgBuffer->_imgWidth;
	int imgHeight = imgBuffer->_imgHeight;
	double** d_link = new double*[8];
	double* result = new double[imgWidth * imgHeight * 3];
	double max_d = 0;
	for (int i = 0; i < 8; ++i) {
		d_link[i] = new double[imgWidth * imgHeight];
		// "For debugging perpose, you may want to scale down each link cost by a factor of 1.5 or 2 
		// so that they can be converted to byte format without clamping to[0,255]"
		imageFilter(result, imgBuffer, nullptr, kernels[i], 3, 3, 0.5, 0);
		for (int row = 0; row < imgHeight; ++row) {
			for (int col = 0; col < imgWidth; ++col) {
				double red = result[3 * (row * imgWidth + col) + 0];
				double green = result[3 * (row * imgWidth + col) + 1];
				double blue = result[3 * (row * imgWidth + col) + 2];
				d_link[i][row * imgWidth + col] = (red*red + green*green + blue*blue) / 3;
				if (max_d < d_link[i][row*imgWidth + col]) {
					max_d = d_link[i][row*imgWidth + col];
				}
			}
		}
	}
	delete[] result;
	for (int row = 0; row < imgHeight; ++row) {
		for (int col = 0; col < imgWidth; ++col) {
			nodeBuffer[row * imgWidth + col]._x = col;
			nodeBuffer[row * imgWidth + col]._y = row;
			nodeBuffer[row * imgWidth + col].pathStatus = nodePathStatus::INITIAL;
			nodeBuffer[row * imgWidth + col].totalCost = -1.0;
			for (int i = 0; i < 8; ++i) {
				double d = d_link[i][row * imgWidth + col];
				double cost = (max_d - d) * ((i % 2 == 0) ? 1 : SQRT2);
				nodeBuffer[row * imgWidth + col].linkCost[i] = cost;
			}
		}
	}
	for (int i = 1; i < 8; ++i) {
		delete[] d_link[i];
	}
	delete[] d_link;
}

void pixelFilter(double rsltPixel[3],
	int x, int y, ImgBuffer* imgBuffer,
	const double * kernel, int knlWidth, int knlHeight,
	double scale, double offset)
{
	if (knlWidth % 2 != 1 || knlHeight % 2 != 1) {
		printf("pixel_filter assumes an odd matrix!");
		return;
	}
	//i is the row# and j is the col# in the kernel
	for (int i = 0; i < knlHeight; ++i) {
		for (int j = 0; j < knlWidth; ++j) {
			// corresponding x, y coordinate at original image
			int xCord = x - knlWidth / 2 + j;
			int yCord = y - knlHeight / 2 + i;
			double knlV = kernel[i * knlWidth + j];
			double origR, origG, origB;
			std::tie(origR, origG, origB) = imgBuffer->getOriginalPixel(xCord, yCord);
			// result at RGB channel
			rsltPixel[0] += origR * knlV;
			rsltPixel[1] += origG * knlV;
			rsltPixel[2] += origB * knlV;
		}
	}
	for (int i = 0; i < 3; ++i) {
		rsltPixel[i] = rsltPixel[i] * scale + offset;
	}
}

void imageFilter(double * rsltImg, ImgBuffer * imgBuffer,
	const unsigned char * selection,
	const double * kernel, int knlWidth, int knlHeight,
	double scale, double offset)
{
	int imgHeight = imgBuffer->_imgHeight;
	int imgWidth = imgBuffer->_imgWidth;
	for (int i = 0; i < imgHeight; ++i) {
		for (int j = 0; j < imgWidth; ++j) {
			double result[3] = { 0.0, 0.0, 0.0 };
			if (selection == nullptr || selection[i * imgWidth + j] == 1) {
				pixelFilter(result, j, i, imgBuffer, kernel, knlWidth, knlHeight, scale, offset);
				
			}
			for (int k = 0; k < 3; ++k) {
				rsltImg[3 * (i * imgWidth + j) + k] = result[k];
			}

		}
	}
}

void liveWireDP(Point seed, Node * nodeBuffer, int width, int height, const unsigned char * selection, int expanded)
{

}
