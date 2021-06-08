#include "tablemodel.h"

#include <QFile>
#include <QTextStream>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void TableModel::fillModelWithData(QString path)
{
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    QString line = inputStream.readLine();
    headerList = line.split(",");

    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();

        QList<QVariant> dataRow;
        for (QString& item : line.split(",")) {
            bool ok = false;
            QVariant itemnum = item.toInt(&ok);
            if (ok)
            {
                dataRow.append(itemnum);
                continue;
            }
            itemnum = item.toDouble(&ok);
            if (ok)
            {
                dataRow.append(itemnum);
                continue;
            }
            dataRow.append(item);
        }
        appendRow(dataRow);
    }
    inputFile.close();
}

void TableModel::saveModelAsFile(QString path)
{
    QFile outFile(path);
    outFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&outFile);

    for (int i = 0; i < columnCount(); ++i)
    {
        out << headerList[i];
        if (i != columnCount() - 1)
        {
            out << ",";
        }
    }

    out << "\n";

    for (int i = 0; i < rowCount(); ++i)
    {
        for (int j = 0; j < columnCount(); ++j)
        {
            QModelIndex idx = index(i, j);
            out << data(idx).toString();
            if (j != columnCount() - 1)
            {
                out << ",";
            }
        }
        out << "\n";
    }
    outFile.close();
}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if((role == Qt::DisplayRole) && (orientation == Qt::Horizontal))
    {
        if(section == 0)
            return QString("ID");
        if(section == 1)
            return QString("Trending date");
        if(section == 2)
            return QString("Title of a video");
        if(section == 3)
            return QString("Title of a channel");
        if(section == 4)
            return QString("Category (ID)");
        if(section == 5)
            return QString("Time of publishing");
        if(section == 6)
            return QString("Tags");
        if(section == 7)
            return QString("Number of views");
        if(section == 8)
            return QString("Number of likes");
        if(section == 9)
            return QString("Number of dislikes");
        if(section == 10)
            return QString("Number of comments");
        if(section == 11)
            return QString("Thumbnail link");
        if(section == 12)
            return QString("Comments are disabled");
        if(section == 13)
            return QString("Ratings are disabled");
        if(section == 14)
            return QString("Video error/removed");
        if(section == 15)
            return QString("Description");
    }
    return QVariant();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return vData.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if(vData.empty())
        return 0;

    return vData[0].size();
}

int TableModel::likesCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if(vData.empty())
        return 0;

    int num = 0;

    for(QList<QVariant> row : vData)
    {
        num += row[8].toInt();
    }
    return num;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int row = index.row();
        int column = index.column();

        return vData[row][column];
    }
    return QVariant();
}

void TableModel::appendRow(QList<QVariant> newRow)
{
    bool columnFlag = false;
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    if (vData.isEmpty())
    {
        deleteAll();
        columnFlag = true;
        beginInsertColumns(QModelIndex(), 0, newRow.size()-1);
    }
    vData.append(newRow);

    if (columnFlag)
    {
        endInsertColumns();
    }
    endInsertRows();
}

void TableModel::deleteRow(int idx)
{
    beginRemoveRows(QModelIndex(), idx, idx);
    vData.removeAt(idx);
    endRemoveRows();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {
        vData[index.row()][index.column()] = value.toString();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void TableModel::deleteAll()
{

    beginRemoveColumns(QModelIndex(), 0, columnCount() - 1);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    vData.clear();
    endRemoveRows();
    endRemoveColumns();
}
