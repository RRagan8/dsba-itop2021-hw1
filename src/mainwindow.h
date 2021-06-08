#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTransposeProxyModel>
#include <QSortFilterProxyModel>

#include "tablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    friend void accept();
    ~MainWindow();

signals:
    void dataChanged();

public slots:
    void onUpdateLabel();

private slots:
    void on_actionAbout_triggered();
    void on_actionLoad_data_triggered();
    void on_actionSave_data_as_a_file_triggered();
    void onRemoveButtonClicked();
    void onAddButtonClicked();
    void onTableViewCurrentChanged(QModelIndex next, QModelIndex prev);

private:
    Ui::MainWindow *ui;
    TableModel *table;
    QTransposeProxyModel *list;
    QSortFilterProxyModel *sort;
};

#endif // MAINWINDOW_H
