#pragma once

#include "contexmenuwidget.h"
#include <functional>

class QPushButton;
class QTreeView;
class LogModel;
class QLineEdit;
class QLabel;
class QSpinBox;

class LogWidget : public ContexMenuWidget
{
    Q_OBJECT

public:
    LogWidget(QWidget* parent = nullptr, Qt::WindowFlags fl = 0);
    ~LogWidget();

    void addLog(const QString& msg, int area = 0, QRgb msgColor = 0);
    void selectAll();
    void copySelected();
    void clear();
    void setFilter(const QString& filter = QString());

    void setMessageDepth(int cnt);
    int messageDepth() const;

    bool isTimestampEnabled() const { return mTimestampEnabled; }
    void enableTimestamp(bool on);

public slots:
    void style_changed(bool style);

protected:
    void setupUi();
    void createContextMenuActions();
    void retranslateUi();
    void changeEvent(QEvent* e) override;

protected:
    LogModel* mModel = nullptr;
    QTreeView* mView = nullptr;

    QLineEdit* mFilter = nullptr;
    QLabel* mFilterLbl = nullptr;

    QPushButton* mFilterClear = nullptr;
    QSpinBox* mLineCountEdit = nullptr;

    bool mTimestampEnabled = true;
};
