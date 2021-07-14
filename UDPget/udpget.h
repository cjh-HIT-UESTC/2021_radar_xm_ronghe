#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_udpget.h"

class udpget : public QMainWindow
{
    Q_OBJECT

public:
    udpget(QWidget *parent = Q_NULLPTR);

private:
    Ui::udpgetClass ui;

public slots:
    void udpgetc(QWidget* parent = Q_NULLPTR);
    void on_PathChoose_clicked(QWidget* parent = Q_NULLPTR);
    void endcode(QWidget* parent = Q_NULLPTR);
};
