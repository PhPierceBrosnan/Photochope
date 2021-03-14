#include "window1.h"
#include "ui_window1.h"

window1::window1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window1)
{
    ui->setupUi(this);
}

window1::~window1()
{
    delete ui;
}
