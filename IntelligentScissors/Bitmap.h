#ifndef _BITMAP_H_
#define _BITMAP_H_

unsigned char * readBMP(const char * filename, int & width, int & height);

void writeBMP(const char* filename, int width, int height, unsigned char* pixelarray);

#endif // !_BITMAP_H_


