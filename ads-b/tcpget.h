#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_tcpget.h"
#include<winsock2.h>
#include<windows.h>

class tcpget : public QMainWindow
{
    Q_OBJECT

public:
    tcpget(QWidget *parent = Q_NULLPTR);


private:
    Ui::tcpgetClass ui;

public slots:
    void begin(QWidget* parent = Q_NULLPTR);
    
    void endbutton(QWidget* parent = Q_NULLPTR);
    
};
