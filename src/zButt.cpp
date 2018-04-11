#include "../inc/zButt.h"

void zButt::mousePressEvent (QMouseEvent * e){
	if (e->button() == Qt::RightButton){
		emit rightClicked();
	} else if (e->button() == Qt::LeftButton){
		emit clicked();
	}

    QPushButton::mousePressEvent(e);
}


void zButt::mouseDoubleClickEvent (QMouseEvent * e){
    if (e->button() == Qt::LeftButton){
        emit doubleClicked();
    }

    QPushButton::mouseDoubleClickEvent(e);
}
