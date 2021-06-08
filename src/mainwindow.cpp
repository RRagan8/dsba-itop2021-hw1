#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"
#include "tablemodel.h"
#include "dialogadd.h"

#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , list(new QTransposeProxyModel)
    , sort(new QSortFilterProxyModel)
{
    ui->setupUi(this);
    table = new TableModel(this);

    ui->tableView->setModel(table);

    ui->listView->setModelColumn(0);
    list->setSourceModel(table);
    ui->listView->setModel(list);

    sort->setSourceModel(table);
    ui->tableView->setModel(sort);
    ui->tableView->setSortingEnabled(true);

    ui->menuBar->setNativeMenuBar(false);

    connect(ui->pushButton_2,
            SIGNAL(clicked()),
            this,
            SLOT(onAddButtonClicked()));

    connect(table,
            SIGNAL(dataChanged(QModelIndex, QModelIndex)),
            this,
            SLOT(onUpdateLabel()));

    connect(table,
            SIGNAL(rowsInserted( const QModelIndex&, int, int)),
            this,
            SLOT(onUpdateLabel()));

    connect(table,
            SIGNAL(rowsRemoved( const QModelIndex&, int, int)),
            this,
            SLOT(onUpdateLabel()));

    connect(ui->tableView->selectionModel(),
            SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,
            SLOT(onTableViewCurrentChanged(QModelIndex,QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete table;
    delete list;
    delete sort;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::on_actionLoad_data_triggered()
{
    QString path = QFileDialog::getOpenFileName(this);
    if(path.isNull())
        return;
    table->deleteAll();
    table->fillModelWithData(path);
}

void MainWindow::on_actionSave_data_as_a_file_triggered()
{
    QString path = QFileDialog::getSaveFileName(this);
    if(path.isNull())
        return;
    table->saveModelAsFile(path);
}

void MainWindow::onRemoveButtonClicked()
{
    QModelIndex idx = ui->tableView->currentIndex();
    if(idx.isValid())
    {
        int row = idx.row();
        table->deleteRow(row);
    }
    else
        return;
}

void MainWindow::onAddButtonClicked()
{
    Dialog dialog;
    dialog.exec();
    QList<QVariant> vList = dialog.getData();
    if(dialog.getSaveOrCancel() == true)
        table->appendRow(vList);
    else
        return;
}

void MainWindow::onUpdateLabel()
{
    ui->label_2->setText(QString::number(table->rowCount()));
    ui->label->setText(QString::number(table->likesCount()));
}

void MainWindow::onTableViewCurrentChanged(QModelIndex next, QModelIndex prev)
{
    int row = sort->mapToSource(next).row();
    ui->listView->setModelColumn(row);
}
