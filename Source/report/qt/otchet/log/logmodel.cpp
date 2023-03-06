#include "logmodel.h"
#include <QtGui/QColor>

LogModel::LogModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

LogModel::~LogModel()
{
}

QModelIndex LogModel::index(int row, int column, const QModelIndex& _parent) const
{
    return createIndex(row, column, nullptr);
}

QModelIndex LogModel::parent(const QModelIndex& _index) const
{
    return QModelIndex();
}

int LogModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : mMessages.size();
}

int LogModel::columnCount(const QModelIndex& _parent) const
{
    return COL_CNT;
}

QVariant LogModel::data(const QModelIndex& _index, int role) const
{
    auto &msgNode = mMessages.at(_index.row());
    if (role == Qt::ToolTipRole)
        return msgNode.message;
    switch (_index.column())
    {
    case TIMESTAMP_COL:
        if (role != Qt::DisplayRole) break;
        return msgNode.timestamp.toString("hh:mm:ss.zzz");
    case AREA_COL:
        if (role != Qt::DisplayRole) break;
        return mAreas.value(msgNode.area);
    case MESSAGE_COL:
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            return msgNode.message;
        case Qt::ForegroundRole:
            return QColor(msgNode.color);
        }
    case REPEAT_COL:
        if (msgNode.count > 0 && role == Qt::DisplayRole)
            return msgNode.count;
    }
    return QVariant();
}

QVariant LogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case TIMESTAMP_COL: return tr("Timestamp");
        case AREA_COL: return tr("Area");
        case MESSAGE_COL: return tr("Message");
        case REPEAT_COL: return "#";
        }
    }
    return QVariant();
}

Qt::ItemFlags LogModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags fl = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    return fl;
}

void LogModel::addLog(const QString& msg, int area, quint32 color, const QDateTime& timestamp)
{
    int msgCount = mMessages.size();
    auto node = msgCount > 0 && mMessages.at(msgCount - 1).message == msg ? &mMessages[msgCount - 1] : nullptr;
    if (node)
    {
        node->count++;
        auto msgIdx = createIndex(msgCount - 1, REPEAT_COL);
        emit dataChanged(msgIdx, msgIdx);
        return;
    }
    if (msgCount == mDepth)
    {
        mMessages.removeFirst();
        mMessages.append({ msg, area, 0, color, timestamp });
        emit dataChanged(index(0, 0), index(mDepth - 1, COL_CNT - 1));
    }
    else
    {
        beginInsertRows(QModelIndex(), msgCount, msgCount);
        mMessages.append({ msg, area, 0, color, timestamp });
        endInsertRows();
    }
}

void LogModel::setMessageDepth(int cnt)
{
    if (cnt == mDepth) return;
    mDepth = cnt;
    cnt = mMessages.size();
    if (mDepth >= cnt) return;
    beginRemoveRows(QModelIndex(), mDepth, cnt - 1);
    mMessages.erase(mMessages.begin() + mDepth, mMessages.end());
    endRemoveRows();
}

void LogModel::clearMessages()
{
    beginResetModel();
    mMessages.clear();
    endResetModel();
}

void LogModel::setTimestampFormat(const QString& _format)
{
    if (mTimestampFormat == _format) return;
    mTimestampFormat = _format;
}

void LogModel::addArea(int id, const QString& _name)
{
    mAreas.insert(id, _name);
}
