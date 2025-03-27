#include "ThreadCutterView.h"
#include <iostream>
using namespace std;

ThreadCutterView::ThreadCutterView(QLabel* instructionLabel, QLabel* resultLabel) : labInstruc(instructionLabel), labResult(resultLabel) {
	labResult->setVisible(false);
}

void ThreadCutterView::render() {
	labInstruc->setText(QString::fromLatin1("Si la DEL rouge et 2 autres DELs sont allum�es, appuyez sur le bouton rouge."
							"\n\nSinon, si la DEL rouge et la DEL bleue sont allum�es mais aucune autre, appuyez sur le bouton bleu pendant 3 secondes."
							"\n\nSinon, si les 4 DELs sont allum�es, appuyez sur le bouton bleu."
							"\n\nSinon, si les 4 DELs sont �teintes, appuyez sur le bouton la plus � droite."
							"\n\nSinon, appuyez sur le deuxi�me bouton � partir de la gauche."));
}

void ThreadCutterView::moduleState(bool isDeactivated) {
	if (isDeactivated) {
		labResult->setText("Module d�samorce");
	} else {
		labResult->setText("ERREUR");
	}
}