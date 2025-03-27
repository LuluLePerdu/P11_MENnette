#include "ThreadCutterView.h"
#include <iostream>
using namespace std;

ThreadCutterView::ThreadCutterView(QWidget* parent) : QWidget(parent) {

}

void ThreadCutterView::render(const ThreadCutterModel& model) {
    cout << "Diode Rouge (1) : " << (model.getLEDstatus(0) ? "Allumee" : "Eteinte") << endl;
    cout << "Diode Verte (2) : " << (model.getLEDstatus(1) ? "Allumee" : "Eteinte") << endl;
    cout << "Diode Bleue (3) : " << (model.getLEDstatus(2) ? "Allumee" : "Eteinte") << endl;
    cout << "Diode Jaune (4) : " << (model.getLEDstatus(3) ? "Allumee" : "Eteinte") << endl;
}