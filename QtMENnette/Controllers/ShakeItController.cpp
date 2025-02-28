#include "ShakeItController.h"
#include <chrono>
#include <thread>
#include <conio.h>
#include "common.hpp"

#include "QtMENnette.h"
#include <qwidget.h>
#include <QKeyEvent>

ShakeItController::ShakeItController(ShakeItView& view) : view(view) {

}
ShakeItController::~ShakeItController() {

}

void ShakeItController::update() {
	MainMenuView menuView;
	MainMenuController menuController(menuView);
	menuController.run();
}

void ShakeItController::run() {
	view.render(model);
	model.setValue(1050);
}

// TODO: Faire que ca fonctionne pour de vrai
//void ShakeItController::keyPressEvent(QKeyEvent* event) {
//   
//    switch (event->key()) {
//    case Qt::Key_Up:
//        model.setValue(1000);
//        break;
//    case Qt::Key_Down:
//        model.setValue(0);
//        break;
//        // Add more cases for other keys if needed
//    default:
//        QWidget::keyPressEvent(event);
//    }
//    
//}