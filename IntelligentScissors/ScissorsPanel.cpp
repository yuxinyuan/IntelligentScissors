#include "ScissorsPanel.h"
#include "IntelliScissorsControl.h"

ScissorsPanel::ScissorsPanel()
{
	Fl_Window* w;
	{
		Fl_Window* o = mainWindow = new Fl_Window(522, 191, "Scissors Panel");
		w = o;
		o->user_data((void*)(this));
		{
			Fl_Group* o = new Fl_Group(0, 0, 520, 156);
			o->align(FL_ALIGN_TOP_LEFT);
			{
				Fl_Box* o = new Fl_Box(1, 3, 95, 21, "Work Mode:");
				o->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
			}
			{
				Fl_Box* o = new Fl_Box(0, 24, 264, 32);
				o->box(FL_ENGRAVED_FRAME);
			}
			{
				Fl_Round_Button* o = new Fl_Round_Button(1, 26, 103, 28, "Image Only");
				o->type(102);
				o->down_box(FL_ROUND_DOWN_BOX);
				o->callback((Fl_Callback*)cb_Image);
			}
			{
				Fl_Round_Button* o = new Fl_Round_Button(109, 26, 148, 28, "Image with Contour");
				o->type(102);
				o->down_box(FL_ROUND_DOWN_BOX);
				o->callback((Fl_Callback*)cb_contour);
			}
			{
				Fl_Box* o = new Fl_Box(1, 59, 95, 22, "Debug Mode:");
				o->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
			}
			{
				Fl_Box* o = new Fl_Box(0, 81, 520, 75);
				o->box(FL_ENGRAVED_FRAME);
			}
			{
				Fl_Round_Button* o = new Fl_Round_Button(1, 83, 107, 28, "Pixel Nodes");
				o->type(102);
				o->down_box(FL_ROUND_DOWN_BOX);
				o->callback((Fl_Callback*)cb_Pixel);
			}
			{
				Fl_Round_Button* o = new Fl_Round_Button(110, 83, 147, 28, "Cost Graph");
				o->type(102);
				o->down_box(FL_ROUND_DOWN_BOX);
				o->callback((Fl_Callback*)cb_Cost);
			}
			{
				Fl_Round_Button* o = new Fl_Round_Button(273, 83, 115, 28, "Path Tree");
				o->type(102);
				o->down_box(FL_ROUND_DOWN_BOX);
				o->callback((Fl_Callback*)cb_Path);
			}
			{
				Fl_Round_Button* o = new Fl_Round_Button(390, 83, 130, 28, "Minimum Path");
				o->type(102);
				o->down_box(FL_ROUND_DOWN_BOX);
				o->callback((Fl_Callback*)cb_Minimum);
			}
			o->end();
		}
		{
			Fl_Group* o = new Fl_Group(268, 0, 256, 56);
			o->align(FL_ALIGN_TOP_LEFT);
			{
				Fl_Box* o = new Fl_Box(268, 24, 252, 32);
				o->box(FL_ENGRAVED_FRAME);
			}
			{
				Fl_Round_Button* o = new Fl_Round_Button(272, 26, 116, 28, "Whole Image");
				o->type(102);
				o->down_box(FL_ROUND_DOWN_BOX);
				o->callback((Fl_Callback*)cb_whole);
			}
			{
				Fl_Round_Button* o = new Fl_Round_Button(389, 26, 127, 28, "Brush Selection");
				o->type(102);
				o->down_box(FL_ROUND_DOWN_BOX);
				o->callback((Fl_Callback*)cb_Brush);
			}
			{
				Fl_Box* o = new Fl_Box(268, 2, 132, 22, "Scissor Range:");
				o->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
			}
			o->end();
		}
		{
			Fl_Button* o = new Fl_Button(189, 159, 152, 28, "Close");
			o->callback((Fl_Callback*)cb_Close);
		}
		o->end();
	}
}


ScissorsPanel::~ScissorsPanel()
{
	//TODO: do we care about the memory leak here ?
}

void ScissorsPanel::cb_Image(Fl_Round_Button *, void *)
{
	IntelliScissorsControl::getInstance()->imageOnlyMode();
}


void ScissorsPanel::cb_contour(Fl_Round_Button *, void *)
{
	IntelliScissorsControl::getInstance()->contourImageMode();
}

void ScissorsPanel::cb_Pixel(Fl_Round_Button *, void *)
{
	IntelliScissorsControl::getInstance()->pixelNodeMode();
}

void ScissorsPanel::cb_Cost(Fl_Round_Button *, void *)
{
	IntelliScissorsControl::getInstance()->costGraphMode();
}

void ScissorsPanel::cb_Path(Fl_Round_Button *, void *)
{
	IntelliScissorsControl::getInstance()->pathTreeMode();
}

void ScissorsPanel::cb_Minimum(Fl_Round_Button *, void *)
{
	IntelliScissorsControl::getInstance()->minPathMode();
}

void ScissorsPanel::cb_whole(Fl_Round_Button *, void *)
{
	IntelliScissorsControl::getInstance()->brushWholeImage();
}

void ScissorsPanel::cb_Brush(Fl_Round_Button *, void *)
{
	IntelliScissorsControl::getInstance()->brushOnlyImage();
}

void ScissorsPanel::cb_Close(Fl_Button * o, void *)
{
	((ScissorsPanel*)(o->parent()->user_data()))->hide();
}

void ScissorsPanel::show()
{
	mainWindow->show();
}

void ScissorsPanel::hide()
{
	mainWindow->hide();
}

bool ScissorsPanel::visible()
{
	return mainWindow->visible();
}
