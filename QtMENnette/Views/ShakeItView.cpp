//#include "ShakeItView.h"
//#include "ShakeItModel.h"
//#include "MainWindow.h"
//#include <QKeyEvent>
//#include <qprogressbar.h>
//#include <QTimer>
//
//ShakeItView::ShakeItView(QWidget* parent) : QWidget(parent) {
//    ui.setupUi(this);
//    setFocusPolicy(Qt::StrongFocus);
//    setFocus(Qt::ActiveWindowFocusReason);
//    qDebug() << "ShakeItView initialisée, focusPolicy =" << focusPolicy();
//
//    QTimer::singleShot(1000, this, [this]() {
//        this->raise();
//        this->activateWindow();
//        this->setFocus(); 
//        QWidget* w = QApplication::focusWidget();
//        });
//
//}
//
//void ShakeItView::render(ShakeItModel& model) {
//    ui.prbBargraph->setValue(model.getLength()); 
//}
//
//void ShakeItView::link(ShakeItModel* model) {
//    this->model = model; 
//    connect(model, &ShakeItModel::lengthChanged, ui.prbBargraph, &QProgressBar::setValue);
//}
//
//void ShakeItView::keyPressEvent(QKeyEvent* event) {
//    qDebug() << "Touche pressée :" << event->text(); 
//    emit keyPressed(event); 
//}
//
//void ShakeItView::focusInEvent(QFocusEvent* event) {
//    QWidget::focusInEvent(event); 
//    qDebug() << "ShakeItView a le focus"; 
//}
