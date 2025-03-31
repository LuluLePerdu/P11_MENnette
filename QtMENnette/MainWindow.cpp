//#include "stdafx.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    ui.setupUi(this);

	snakeWidget = new SnakeMazeWidget();
	ui.stackedWidget->addWidget(snakeWidget);

	connect(ui.btnSnake, &QPushButton::clicked, this, &MainWindow::on_btnSnake_clicked);

}

MainWindow::~MainWindow()
{
	delete snakeWidget;
}



MainWindow* MainWindow::instance() {
    if (w == NULL) { w = new MainWindow(); }
    return w;
}

Ui::MainWindow* MainWindow::getUI() const
{
	return const_cast<Ui::MainWindow*>(&ui);
}

void MainWindow::on_btnHome_clicked() {
	ui.stackedWidget->setCurrentIndex(0);
	ui.labDebug->setText("Home");
	OutputDebugString(L"Home\n");
}

void MainWindow::on_btnSnake_clicked() {

	ui.stackedWidget->setCurrentWidget(snakeWidget);

	//ui.stackedWidget->setCurrentIndex(1); 

	ui.labDebug->setText("Snake");
}

void MainWindow::on_btnLED_clicked() {
	ui.stackedWidget->setCurrentIndex(3);
	ui.labDebug->setText("LED");
	//ThreadCutterView tcv(ui.labInstruc, ui.labResult);
	//tcv.render();
}

void MainWindow::on_btnSimon_clicked() {
	ui.stackedWidget->setCurrentIndex(4);
	ui.labDebug->setText("Simon");
}

void MainWindow::on_btnAccel_clicked() {
	ui.stackedWidget->setCurrentIndex(2);
	ui.labDebug->setText("Accel");
}

void MainWindow::on_btnPoten_clicked() {
	ui.stackedWidget->setCurrentIndex(5);
	ui.labDebug->setText("Poten");
	

}