#ifndef TABLEMODEL_H
#define TABLEMODEL_H

//#include "mainwindow.h"

#include <QAbstractTableModel>
#include <QList>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);

    void fillModelWithData(QString path);
    void saveModelAsFile(QString path);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    int likesCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void appendRow(QList<QVariant> newRow);

    void deleteRow(int idx);

    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void deleteAll();

private:
    QList<QList<QVariant>> vData;
    QList<QString> headerList;
    int numberOfLikes = 0;
    int numberOfVideos = 0;
};

#endif // TABLEMODEL_H
