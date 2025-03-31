//#include "ShakeItController.h"
//#include <chrono>
//#include <thread>
//#include <conio.h>
//#include "common.hpp"
//
//#include "MainWindow.h"
//#include <qwidget.h>
//#include <QKeyEvent>
//#include <QObject>
//#include <QDebug>
//
//ShakeItController::ShakeItController(ShakeItView& view) : view(view) {
//    view.link(&model); 
//    connect(&view, &ShakeItView::keyPressed, this, &ShakeItController::onKeyPressed);
//}
//
//ShakeItController::~ShakeItController() {}
//
//void ShakeItController::update() {
//	MainMenuView menuView;
//	MainMenuController menuController(menuView);
//	menuController.run();
//}
//
//void ShakeItController::run() {
//	view.render(model);
//}
//
//void ShakeItController::onKeyPressed(QKeyEvent* event) {
//    qDebug() << "Touche pressée : " << event->key();
//	printf("Touche pressée : %d\n", event->key());
//    float currentValue = model.getValue();
//    switch (event->key()) {
//    case Qt::Key_Up:
//        model.setValue(currentValue + 10);
//        break;
//    case Qt::Key_Down:
//        model.setValue(currentValue - 10);
//        break;
//    default:
//        break;
//    }
//}