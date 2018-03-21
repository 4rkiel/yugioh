#include "../inc/zButt.h"

void zButt::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::RightButton){
		emit rightClicked();
	} else if (e->button() == Qt::LeftButton){
		emit clicked();
	}
}
