#ifndef _SCISSORSBRUSH_H_
#define _SCISSORSBRUSH_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Button.H>

class ScissorsBrush
{
public:
	ScissorsBrush();
	ScissorsBrush(ScissorsBrush& other) = delete;
	ScissorsBrush(ScissorsBrush&& other) = delete;
	ScissorsBrush& operator=(ScissorsBrush& other) = delete;
	~ScissorsBrush();
public:
	Fl_Window *mainWindow;
	Fl_Round_Button *round;
private:
	static void cb_round(Fl_Round_Button*, void*);
public:
	Fl_Check_Button *square;
private:
	static void cb_square(Fl_Check_Button*, void*);
public:
	Fl_Value_Slider *brushSize;
private:
	static void cb_brushSize(Fl_Value_Slider*, void*);
public:
	Fl_Value_Slider *brushOpacity;
private:
	static void cb_brushOpacity(Fl_Value_Slider*, void*);
	static void cb_Clean(Fl_Button*, void*);
	static void cb_Close(Fl_Button*, void*);
public:
	void show();
	void hide();
	bool visible();
private:
	enum class BrushType {
		SQUARE,
		ROUND
	};
public:
	BrushType brushType;
	int bSize;
	double bOpacity;
};

#endif // !_SCISSORSBRUSH_H_



