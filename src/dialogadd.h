#ifndef DIALOGADD_H
#define DIALOGADD_H

#include <QDialog>
#include "renderarea.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void checkAndGetData(QVariant data);
    QList<QVariant> getData();
    bool getSaveOrCancel();
    void callError();
    ~Dialog();

    /*
public slots:
    virtual void save();
    virtual void cancel();
    //virtual void close();
*/

public slots:
    virtual void save();
    virtual void cancel();
    //void onSaveButtonClicked(TableModel *table);

signals:
    //void accepted();
    //void rejected();

private:
    Ui::Dialog *ui;
    QList<QVariant> vList;
    bool saveOrCancel = true;
};

#endif // DIALOGADD_H
