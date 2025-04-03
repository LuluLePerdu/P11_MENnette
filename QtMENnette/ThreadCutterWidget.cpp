#include "ThreadCutterWidget.h"

ThreadCutterWidget::ThreadCutterWidget(QWidget* parent) : QWidget(parent) 
{

}

void ThreadCutterWidget::startGame() {
	logic.run();
	emit outcomeSubmitted(logic.getCompleted());
	if (!logic.getCompleted()) {
		emit timePenalty(timeOnLoss);
	}
}