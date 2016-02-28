#include "ScissorsMainWindow.h"
#include "IntelliScissorsControl.h"
#include <cassert>

Fl_Menu_Item ScissorsMainWindow::menu_table[] = {
	{ "&File", 0, 0, 0, FL_SUBMENU },
		{ "&Open...", FL_F + 2, cb_open_file, 0, FL_MENU_DIVIDER },
		{ "&Save Contour", FL_CTRL + 'c' },
		{ "&Save Mask", FL_CTRL + 'm', 0, 0, FL_MENU_DIVIDER },
		{ "&Exit", FL_ALT + 'q', cb_exit },
		{ 0 },
	{ "&Tool", 0, 0, 0, FL_SUBMENU },
		{"&Brush", 0, cb_brush_config},
		{ "&Scissor", 0, cb_scissors_panel},
		{ 0 },
	{ "&Help", 0, 0, 0, FL_SUBMENU },
		{ "&About...", FL_F + 1},
		{ 0 },
	{ 0 }
};

ScissorsMainWindow::ScissorsMainWindow()
{
	mainWindow = new Fl_Double_Window(445, 450, "Intelligent Scissors");
	mainWindow->user_data((void *)(this));

	menubar = new Fl_Menu_Bar(0, 0, 445, 30);
	menubar->menu(menu_table);

	imgView = new ImgView(0, 30, 445, 400, "draw window");

	mainWindow->end();
	mainWindow->resizable(imgView);
}


ScissorsMainWindow::~ScissorsMainWindow()
{
}

void ScissorsMainWindow::cb_exit(Fl_Widget * w, void *)
{
	((Fl_Menu_ *)w)->parent()->hide();
}

void ScissorsMainWindow::cb_open_file(Fl_Widget *, void *)
{
	Fl_File_Chooser fc(".", "BitMaps (*.bmp)", Fl_File_Chooser::SINGLE, "Open a image");
	fc.preview(false);
	fc.previewButton->deactivate();
	fc.show();
	while (fc.visible()) {
		Fl::wait();
	}
	char relative_filename[FL_PATH_MAX];
	int file_count = fc.count();
	if (file_count > 0) {
		assert(file_count == 1);
		fl_filename_relative(relative_filename, sizeof(relative_filename), fc.value());
		printf("%s\n", relative_filename);
		IntelliScissorsControl::getInstance()->loadImage(relative_filename);
	}
	fc.hide();
}

void ScissorsMainWindow::cb_scissors_panel(Fl_Widget *, void *)
{
	IntelliScissorsControl::getInstance()->panelWindow->show();
	while (IntelliScissorsControl::getInstance()->panelWindow->visible()) {
		Fl::wait();
	}
}

void ScissorsMainWindow::cb_brush_config(Fl_Widget *, void *)
{
	IntelliScissorsControl::getInstance()->brushWindow->show();
	while (IntelliScissorsControl::getInstance()->brushWindow->visible()) {
		Fl::wait();
	}
}

void ScissorsMainWindow::show()
{
	Fl::visual(FL_DOUBLE | FL_INDEX);
	mainWindow->show();
}

void ScissorsMainWindow::hide()
{
	mainWindow->hide();
}
