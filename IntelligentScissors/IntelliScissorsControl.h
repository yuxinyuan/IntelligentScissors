#ifndef _INTELLISCISSORSCONTROL_H_

#include "ScissorsPanel.h"
#include "ScissorsMainWindow.h"
#include "ScissorsBrush.h"
#include "ImgBuffer.h"

class IntelliScissorsControl
{
public:
	IntelliScissorsControl(IntelliScissorsControl& other) = delete;
	IntelliScissorsControl(IntelliScissorsControl&& other) = delete;
	IntelliScissorsControl& operator=(IntelliScissorsControl& other) = delete;
	~IntelliScissorsControl();
	static IntelliScissorsControl* getInstance();
public:
	// functions for ScissorsPanel
	void imageOnlyMode();
	void contourImageMode();
	void pixelNodeMode();
	void costGraphMode();
	void pathTreeMode();
	void minPathMode();
	void brushWholeImage();
	void brushOnlyImage();
public:
	// functions for ScissorsMainWindow
	void loadImage(char* relativeFilename);

public:
	ScissorsMainWindow* mainWindow;
	ScissorsBrush* brushWindow;
	ScissorsPanel* panelWindow;
	ImgBuffer* imgBuffer;
private:
	// private class constructor
	IntelliScissorsControl();
	// singleton instance
	static IntelliScissorsControl* iScissorsCtrl;
};

#endif // !_INTELLISCISSORSCONTROL_H_
