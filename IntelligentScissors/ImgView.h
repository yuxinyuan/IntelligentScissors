#ifndef _IMG_VIEW_H_
#define _IMG_VIEW_H_

#include <FL/Fl.h>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/GL.h>
#include <GL/glut.h>

class ImgView : public Fl_Gl_Window {
public:
	ImgView(int x, int y, int w, int h, const char* l);
	~ImgView();
public:
	void draw();

	void registerBitmap(unsigned char* pixelarray, int w, int h);

	int handle(int event);

	void drawImage();

	void saveCurrentContent();

private:
	enum class EventType
	{
		NO_EVENT,
		SET_SEED,
		ZOOM_IN,
		ZOOM_OUT,
		MOUSE_MOVE
	};

private:
	int _imgWidth, _imgHeight;
	unsigned char* _ucPixelArray;
	int _mouse_x, _mouse_y;
	EventType eventTag;
};

#endif // !_IMG_VIEW_H_

