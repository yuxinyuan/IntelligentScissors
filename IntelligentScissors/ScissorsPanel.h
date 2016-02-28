#ifndef _SCISSORSPANEL_H_
#define _SCISSORSPANEL_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Button.H>

class ScissorsPanel
{
public:
	ScissorsPanel();
	ScissorsPanel(ScissorsPanel& other) = delete;
	ScissorsPanel(ScissorsPanel&& other) = delete;
	ScissorsPanel& operator=(ScissorsPanel& other) = delete;
	~ScissorsPanel();
public:
	Fl_Window *mainWindow;
private:
	static void cb_Image(Fl_Round_Button*, void*);
	static void cb_contour(Fl_Round_Button*, void*);
	static void cb_Pixel(Fl_Round_Button*, void*);
	static void cb_Cost(Fl_Round_Button*, void*);
	static void cb_Path(Fl_Round_Button*, void*);
	static void cb_Minimum(Fl_Round_Button*, void*);
	static void cb_whole(Fl_Round_Button*, void*);
	static void cb_Brush(Fl_Round_Button*, void*);
	static void cb_Close(Fl_Button*, void*);
public:
	void show();
	void hide();
	bool visible();
};

#endif // !_SCISSORSPANEL_H_


