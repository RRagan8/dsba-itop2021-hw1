#ifndef GETINFO_H
#define GETINFO_H

#include <QDialog>

namespace Ui {
class GetInfo;
}

class GetInfo : public QDialog
{
    Q_OBJECT

public:
    explicit GetInfo(QWidget *parent = nullptr);
    ~GetInfo();

private:
    Ui::GetInfo *ui;
};

#endif // GETINFO_H
