#include "getinfo.h"
#include "ui_getinfo.h"

GetInfo::GetInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetInfo)
{
    ui->setupUi(this);
}

GetInfo::~GetInfo()
{
    delete ui;
}
