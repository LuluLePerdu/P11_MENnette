#include "ShakeItView.h"
#include "ShakeItModel.h"

#include "QtMENnette.h"
#include <qprogressbar.h>


void ShakeItView::render(ShakeItModel& model)
{
	QtMENnette* w = QtMENnette::instance();

	QProgressBar* prbBargraph = w->findChild<QProgressBar*>("prbBargraph");
	prbBargraph->setValue(model.getLength());
}