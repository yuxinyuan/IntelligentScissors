#ifndef _SCISSORSMAINWINDOW_H_
#define _SCISSORSMAINWINDOW_H_

#include "ImgView.h"
#include <FL/Fl.h>
#include <FL/Fl_Double_Window.h>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>

class ScissorsMainWindow {
public:
	ScissorsMainWindow();
	ScissorsMainWindow(ScissorsMainWindow& other) = delete;
	ScissorsMainWindow(ScissorsMainWindow&& other) = delete;
	ScissorsMainWindow& operator=(ScissorsMainWindow& other) = delete;
	~ScissorsMainWindow();
public:
	Fl_Double_Window* mainWindow;
	Fl_Menu_Bar* menubar;
	ImgView* imgView;
private:
	static Fl_Menu_Item menu_table[];
private:
	static void cb_exit(Fl_Widget*, void*);
	static void cb_open_file(Fl_Widget*, void*);
	static void cb_scissors_panel(Fl_Widget*, void*);
	static void cb_brush_config(Fl_Widget*, void*);
public:
	void show();
	void hide();
};

#endif // !_SCISSORSMAINWINDOW_H_


