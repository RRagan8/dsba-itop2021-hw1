#include "dialogadd.h"
#include "ui_dialogadd.h"
#include <QMessageBox>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_2,
            SIGNAL(clicked()),
            this,
            SLOT(save()));

    connect(ui->pushButton,
            SIGNAL(clicked()),
            this,
            SLOT(cancel()));
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::callError()
{
    QMessageBox error;
    error.setText("You've entered data of the wrong type. Please try again");
    error.exec();
}

void Dialog::checkAndGetData(QVariant data)
{
    bool ok = false;
    data.toInt(&ok);
    if(ok)
        vList.append(data);
    else
    {
        callError();
        saveOrCancel = false;
    }
}

QList<QVariant> Dialog::getData()
{
    QVariant data = ui->lineEdit->text();
    vList.append(data);
    //data = ui->lineEdit->text();
    //vList.append(data);
    data = ui->lineEdit_2->text();
    vList.append(data);
    data = ui->lineEdit_3->text();
    vList.append(data);
    data = ui->lineEdit_4->text();
    vList.append(data);
    data = ui->lineEdit_5->text();
    vList.append(data);
    data = ui->lineEdit_6->text();
    vList.append(data);
    data = ui->lineEdit_7->text();
    vList.append(data);
    data = ui->lineEdit_8->text();
    checkAndGetData(data);
    data = ui->lineEdit_9->text();
    checkAndGetData(data);
    data = ui->lineEdit_10->text();
    checkAndGetData(data);
    data = ui->lineEdit_11->text();
    checkAndGetData(data);
    data = ui->lineEdit_12->text();
    vList.append(data);
    data = ui->lineEdit_13->text();
    vList.append(data);
    data = ui->lineEdit_14->text();
    vList.append(data);
    data = ui->lineEdit_15->text();
    vList.append(data);
    data = ui->textEdit->toPlainText();
    vList.append(data);
    return vList;
}

bool Dialog::getSaveOrCancel()
{
    return saveOrCancel;
}

void Dialog::save()
{
    this->close();
}

void Dialog::cancel()
{
    saveOrCancel = false;
    this->close();
}
