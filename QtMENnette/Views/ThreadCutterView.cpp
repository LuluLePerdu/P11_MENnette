#include "ThreadCutterView.h"
#include <iostream>
using namespace std;

ThreadCutterView::ThreadCutterView(QLabel* instructionLabel, QLabel* resultLabel) : labInstruc(instructionLabel), labResult(resultLabel) {
	labResult->setVisible(false);
}

void ThreadCutterView::render() {
	labInstruc->setText(QString::fromLatin1("Si la DEL rouge et 2 autres DELs sont allumées, appuyez sur le bouton rouge."
							"\n\nSinon, si la DEL rouge et la DEL bleue sont allumées mais aucune autre, appuyez sur le bouton bleu pendant 3 secondes."
							"\n\nSinon, si les 4 DELs sont allumées, appuyez sur le bouton bleu."
							"\n\nSinon, si les 4 DELs sont éteintes, appuyez sur le bouton la plus à droite."
							"\n\nSinon, appuyez sur le deuxième bouton à partir de la gauche."));
}

void ThreadCutterView::moduleState(bool isDeactivated) {
	if (isDeactivated) {
		labResult->setText("Module désamorce");
	} else {
		labResult->setText("ERREUR");
	}
}