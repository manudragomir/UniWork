#pragma once
#include "Observer.h"
#include "qboxlayout.h"
#include "GRASPController.h"
#include "qwidget.h"
#include "qpainter.h"

class CosReadOnlyGUI: public QWidget, public Observer
{
	GRASPController& serv;
	void initGUIComp() {
		this->setBaseSize(1000, 1000);
	}
public:
	CosReadOnlyGUI(GRASPController& _serv) : serv{ _serv } {
		serv.addObserver(this);
		initGUIComp();
		update();
	};

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		for (int i = 0; i < serv.getContract().size(); i++) {
			p.drawEllipse(QPoint({ width() / 2, height() / 2 }), (i+1)*25, (i+1)*25);
		}
	}
	~CosReadOnlyGUI() {};
};

