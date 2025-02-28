#include "stdafx.h"
#include "QtMENnette.h"

QtMENnette::QtMENnette(QMainWindow* parent) : QMainWindow(parent)
{
    ui.setupUi(this);
}

QtMENnette::~QtMENnette()
{}

QtMENnette* QtMENnette::instance() {
    if (w == NULL) { w = new QtMENnette(); }
    return w;
}
