#pragma once
#include "ShakeItModel.h"
#include "ShakeItView.h"

#include "MainMenuView.h"
#include "MainMenuController.h"
#include <iostream>
#include <qwidget.h>

class ShakeItController //: public QWidget
{
public:
	ShakeItController(ShakeItView& view);
	~ShakeItController();
	//void returnToMainMenu();
	void update();
	void run();

protected:
	//void keyPressEvent(QKeyEvent* event) override;

	
private:
	ShakeItModel model;
	ShakeItView& view;
};
