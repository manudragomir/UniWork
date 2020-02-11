#pragma once
#include "GRASPController.h"
#include <QWidget>

class ConsolaGUI: public QWidget
{
private:
	GRASPController serv;
public:
	ConsolaGUI(GRASPController _serv) : serv{ _serv } {};
	~ConsolaGUI()=default;
};

