#pragma once

#include <QtWidgets/QWidget>
#include <QAction>

class ContexMenuWidget : public QWidget
{
    Q_OBJECT

public:
    ContexMenuWidget(QWidget *parent = nullptr, Qt::WindowFlags fl = 0);

    template<typename Func>
    QAction* addMenuAction(const QString& name = QString(), Func fun = nullptr, const QKeySequence& key = 0)
    {
        auto a = addMenuAction(name, key);
        connect(a, &QAction::triggered, fun);
        return a;
    }

protected:
    QAction* addMenuAction(const QString& name = QString(), const QKeySequence& key = 0);

    QList<QAction*> mContextMenuActions;

};
