#include "logw.h"
#include "logmodel.h"
#include <QtGui/QClipboard>
#include <QtGui/QIcon>
#include <QtCore/QEvent>
#include <QtCore/QSortFilterProxyModel>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpinBox>

enum ContextMenuActions {
//    CMA_SelectAll,
    CMA_Copy,
    CMA_Clear,
    CMA_Timestamp,
    CMA_COUNT
};

LogWidget::LogWidget(QWidget *parent, Qt::WindowFlags fl)
    : ContexMenuWidget(parent, fl)
    , mModel(new LogModel)
    , mView(new QTreeView)
    , mFilter(new QLineEdit)
    , mFilterLbl(new QLabel)
    , mFilterClear(new QPushButton)
    , mLineCountEdit(new QSpinBox)
{
    setupUi();
    createContextMenuActions();
    connect(mFilter, &QLineEdit::textChanged, this, &LogWidget::setFilter);
    connect(mFilterClear, &QPushButton::clicked, mFilter, &QLineEdit::clear);
    connect(mLineCountEdit, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), mModel, &LogModel::setMessageDepth);
    retranslateUi();
}

LogWidget::~LogWidget()
{
}

void LogWidget::addLog(const QString& msg, int area, QRgb msgColor)
{
    mModel->addLog(msg, area, msgColor);
}

void LogWidget::selectAll()
{
}

void LogWidget::copySelected()
{
    auto indices = mView->selectionModel()->selectedIndexes();
    auto cb = qApp->clipboard();
    if (!cb || indices.isEmpty()) return;
    QString msg;
    int row = indices.first().row();
    for (auto& idx : indices)
    {
        if (idx.row() != row)
        {
            row = idx.row();
            msg += '\n';
        }
        else msg += ' ';
        msg += idx.data().toString();
    }
    cb->setText(msg);
}

void LogWidget::clear()
{
    mModel->clearMessages();
}

void LogWidget::setFilter(const QString& filter)
{
    auto sfpmodel = dynamic_cast<QSortFilterProxyModel*>(mView->model());
    if (!sfpmodel) return;
    //sfpmodel->setFilterRegularExpression(".*" + filter + ".*");
    sfpmodel->setFilterWildcard("*" + filter + "*");
}

using ftype1 = void(LogWidget::*)(bool);
using ftype2 = void(LogWidget::*)();

template<>
QAction* ContexMenuWidget::addMenuAction(const QString& name, ftype1 fun, const QKeySequence& key)
{
    auto a = addMenuAction(name, key);
    a->setCheckable(true);
    connect(a, &QAction::toggled, dynamic_cast<LogWidget*>(this), fun);
    return a;
}

template<>
QAction* ContexMenuWidget::addMenuAction(const QString& name, ftype2 fun, const QKeySequence& key)
{
    auto a = addMenuAction(name, key);
    connect(a, &QAction::triggered, dynamic_cast<LogWidget*>(this), fun);
    return a;
}

void LogWidget::setMessageDepth(int cnt)
{
    //mModel->setMessageDepth(cnt);
    mLineCountEdit->setValue(cnt);
}

int LogWidget::messageDepth() const
{
    return mLineCountEdit->value();
}

void LogWidget::enableTimestamp(bool on)
{
    if (on == mTimestampEnabled) return;
    mTimestampEnabled = on;
    if (on) mView->showColumn(LogModel::TIMESTAMP_COL);
    else mView->hideColumn(LogModel::TIMESTAMP_COL);
    auto a = mContextMenuActions[CMA_Timestamp];
    a->blockSignals(true);
    a->setChecked(on);
    a->blockSignals(false);
}

void LogWidget::setupUi()
{
    auto sfpmodel = new QSortFilterProxyModel;
    sfpmodel->setSourceModel(mModel);
    sfpmodel->setFilterRole(Qt::EditRole);
    sfpmodel->setFilterKeyColumn(LogModel::MESSAGE_COL);
    mView->setModel(sfpmodel);
    //mView->setModel(mModel);
    mView->hideColumn(LogModel::AREA_COL);
    mView->header()->setSectionResizeMode(LogModel::TIMESTAMP_COL, QHeaderView::ResizeToContents);
    mView->header()->setSectionResizeMode(LogModel::REPEAT_COL, QHeaderView::ResizeToContents);
    mView->header()->setStretchLastSection(true);

    mFilterClear->setIcon(QIcon(":/actions/cancel"));
    mFilterClear->setFlat(true);

    auto vbl = new QVBoxLayout;
    vbl->setContentsMargins(2, 2, 2, 2);
    auto filterLayout = new QHBoxLayout;
    filterLayout->setContentsMargins(2, 2, 2, 2);
    filterLayout->addWidget(mFilterLbl);
    filterLayout->addWidget(mFilter, 1);
    filterLayout->addWidget(mFilterClear);
    filterLayout->addWidget(mLineCountEdit);
    //filterLayout->addStretch(2);

    vbl->addLayout(filterLayout);
    vbl->addWidget(mView);
    setLayout(vbl);

    mView->setSelectionBehavior(QAbstractItemView::SelectRows);

    mLineCountEdit->setRange(10, 800);
    mLineCountEdit->setValue(mModel->messageDepth());
}

void LogWidget::createContextMenuActions()
{
    QAction* a;

    mContextMenuActions.clear();
    
    //addMenuAction("SelectAll", &LogWidget::selectAll, Qt::Key_A | Qt::ControlModifier);
    addMenuAction("Copy", &LogWidget::copySelected, Qt::Key_C | Qt::ControlModifier);
    addMenuAction();
    addMenuAction("Clear", &LogWidget::clear, Qt::Key_C | Qt::ControlModifier);
    addMenuAction("Timestamp", &LogWidget::enableTimestamp, Qt::Key_C | Qt::ControlModifier);

    mContextMenuActions[CMA_Timestamp]->setChecked(mTimestampEnabled);

    setContextMenuPolicy(Qt::ActionsContextMenu);
}

void LogWidget::retranslateUi()
{
    mFilterLbl->setText(tr("Filter"));
    mView->reset();
    //mContextMenuActions.at(CMA_SelectAll)->setText(tr("Select All"));
    mContextMenuActions.at(CMA_Copy)->setText(tr("Copy"));
    mContextMenuActions.at(CMA_Clear)->setText(tr("Clear"));
    mContextMenuActions.at(CMA_Timestamp)->setText(tr("Timestamp"));
    mLineCountEdit->setToolTip(tr("Maximum number of message records in view"));
}

void LogWidget::changeEvent(QEvent* e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        retranslateUi();
    }
    else QWidget::changeEvent(e);
}
