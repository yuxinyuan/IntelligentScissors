#include "ImgView.h"
#include <cassert>
#include <iostream>

static const float POINT_SIZE = 5.0;

ImgView::ImgView(int x, int y, int w, int h, const char * l) :
	Fl_Gl_Window(x, y, w, h, l),
	_ucPixelArray(nullptr),
	_imgWidth(-1),
	_imgHeight(-1),
	_mouse_x(0),
	_mouse_y(0),
	eventTag(EventType::NO_EVENT)
{
}

ImgView::~ImgView()
{
}

void ImgView::draw()
{
#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
#endif // !MESA

	if (!valid()) {
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);
		// We're only using 2-D, so turn off depth 
		glDisable(GL_DEPTH_TEST);
		// Tell openGL to read from the front buffer when capturing
		// out paint strokes 
		glReadBuffer(GL_FRONT);
		glClear(GL_COLOR_BUFFER_BIT);
		// set the left-bottom corner to be the origin
		ortho();
	}

	if (_ucPixelArray) {
		if (eventTag != EventType::NO_EVENT) {
			if (eventTag == EventType::ZOOM_IN) {
				std::cout << "zooming in" << std::endl;
				// TODO: implement zoom in of the image

			}
			else if (eventTag == EventType::ZOOM_OUT) {
				std::cout << "zooming out" << std::endl;
				// TODO: implement zoom out of the image
			}
			else if (eventTag == EventType::SET_SEED) {
				// draw a point at mouse position
				glPointSize(POINT_SIZE);
				glBegin(GL_POINTS);
				glColor3ub(255, 0, 0);
				glVertex2i(_mouse_x, _mouse_y);
				glEnd();
				// TODO: send out notification to indicate a seed set
			}
			saveCurrentContent();
			eventTag = EventType::NO_EVENT;
		}
		drawImage();
	}
	eventTag = EventType::NO_EVENT;
	glFlush();

#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
#endif // !MESA
}

void ImgView::registerBitmap(unsigned char * pixelarray, int w, int h)
{
	_ucPixelArray = pixelarray;
	_imgWidth = w;
	_imgHeight = h;
}

int ImgView::handle(int event)
{
	int ret = 0;
	switch (event)
	{
	case FL_PUSH:
		if (Fl::event_button() == FL_LEFT_MOUSE) {
			_mouse_x = Fl::event_x();
			// when using opengl to draw, the left-bottom of the window is considered to be origin
			_mouse_y = _imgHeight - Fl::event_y();
			eventTag = EventType::SET_SEED;
			redraw();
			ret = 1;
		}
		break;
	case FL_FOCUS:
		ret = 1;
		break;
	case FL_KEYDOWN:
		std::cout << "key down: " << Fl::event_key() << std::endl;
		if (Fl::event_key('=')) {
			eventTag = EventType::ZOOM_IN;
			redraw();
			ret = 1;
		}
		else if (Fl::event_key('-')) {
			eventTag = EventType::ZOOM_OUT;
			redraw();
			ret = 1;
		}
		break;
	default:
		ret = Fl_Gl_Window::handle(event);
		break;
	}
	return ret;
}

void ImgView::drawImage()
{
	glClear(GL_COLOR_BUFFER_BIT);

	resize(x(), y(), _imgWidth, _imgHeight);

	GLvoid* bitstart = _ucPixelArray;

	// just copy image to GLwindow conceptually
	glRasterPos2i(0, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, _imgWidth);
	glDrawBuffer(GL_BACK);
	glDrawPixels(_imgWidth, _imgHeight, GL_RGB, GL_UNSIGNED_BYTE, bitstart);
}

void ImgView::saveCurrentContent()
{
	std::cout << "saving content" << std::endl;
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, _imgWidth);

	glReadPixels(0, 0, _imgWidth, _imgHeight, GL_RGB, GL_UNSIGNED_BYTE, _ucPixelArray);
}
