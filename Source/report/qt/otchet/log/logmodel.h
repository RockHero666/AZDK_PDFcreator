#pragma once

#include <QtCore/QAbstractItemModel>
#include <QtCore/QDateTime>

class LogModel : public QAbstractItemModel
{
    Q_OBJECT

    struct MessageNode {
        QString message;
        int area;
        int count;
        quint32 color;
        QDateTime timestamp;
    };

public:
    enum
    {
        TIMESTAMP_COL,
        AREA_COL,
        REPEAT_COL,
        MESSAGE_COL,
        COL_CNT
    };
    LogModel(QObject *parent = nullptr);
    ~LogModel();

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void addLog(const QString& msg, int area, quint32 color = 0, const QDateTime& timestamp = QDateTime::currentDateTime());
    void setMessageDepth(int cnt);
    int messageDepth() const { return mDepth; }
    void clearMessages();

    void setTimestampFormat(const QString& _format);
    const QString& timestampFormat() const { return mTimestampFormat; }

    void addArea(int id, const QString& _name);


    void style_change(bool style);

protected:
    QList<MessageNode> mMessages;
    QHash<int, QString> mAreas;
    QString mTimestampFormat;

    int mDepth = 100;
};
