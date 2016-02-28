#include "IntelliScissorsControl.h"

IntelliScissorsControl* IntelliScissorsControl::iScissorsCtrl = nullptr;

IntelliScissorsControl::IntelliScissorsControl()
{

}


IntelliScissorsControl::~IntelliScissorsControl()
{
	
}

IntelliScissorsControl * IntelliScissorsControl::getInstance()
{
	if (iScissorsCtrl == nullptr) {
		iScissorsCtrl = new IntelliScissorsControl();
	}
	return iScissorsCtrl;
}
