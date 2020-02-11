#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication5.h"

class QtGuiApplication5 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication5(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtGuiApplication5Class ui;
};
