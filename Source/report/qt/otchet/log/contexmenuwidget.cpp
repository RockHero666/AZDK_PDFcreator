#include "contexmenuwidget.h"
#include <QtWidgets/QAction>

ContexMenuWidget::ContexMenuWidget(QWidget *parent, Qt::WindowFlags fl)
    : QWidget(parent, fl)
{
}

QAction* ContexMenuWidget::addMenuAction(const QString& name, const QKeySequence& key)
{
    QAction* a = new QAction(name, this);

    if (name.isEmpty())
    {
        a->setSeparator(true);
        addAction(a);
        return nullptr;
    }

    if (key != 0)
    {
        a->setShortcutContext(Qt::WidgetShortcut);
        a->setShortcut(key);
    }

    mContextMenuActions << a;
    addAction(a);

    return a;
}

using ftype1 = void(ContexMenuWidget::*)(bool);
using ftype2 = void(ContexMenuWidget::*)();

template<>
QAction* ContexMenuWidget::addMenuAction(const QString& name, ftype1 fun, const QKeySequence& key)
{
    auto a = addMenuAction(name, key);
    a->setCheckable(true);
    connect(a, &QAction::toggled, this, fun);
    return a;
}

template<>
QAction* ContexMenuWidget::addMenuAction(const QString& name, ftype2 fun, const QKeySequence& key)
{
    auto a = addMenuAction(name, key);
    connect(a, &QAction::triggered, this, fun);
    return a;
}
