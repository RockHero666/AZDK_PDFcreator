#define _USE_MATH_DEFINES
#include "orientedit.h"
#include "../linalg_lib/quaterniond.h"
#include "../linalg_lib/vector3d.h"
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QLabel>
#include <QtCore/QSettings>
#include <QtGui/QClipboard>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>

static quaternion qm;
static quaternion qmi;

#ifndef R2D
#define R2D 57.29577951308232
#endif // R2D

__inline double sqr(double x) { return x * x; }

OrientEdit::OrientEdit(QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* hbl = new QHBoxLayout;
    mVarNames << "RA" << "DE" << "Phi";
    for (int i = 0; i < 3; i++)
    {
        mAngles[i] = new QDoubleSpinBox;
        mAngles[i]->setDecimals(3);
        connect(mAngles[i], static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [this](double) {
            switch (mType)
            {
            case OE_QUAT:
                emit quatChanged(getQuaternion());
                break;
            case OE_VECTOR:
                emit vectorChanged(getVector());
                break;
            }
            emit valueChanged();
            });
        connect(mAngles[i], &QAbstractSpinBox::editingFinished, [this]() {
            if (!isValueChanged(true)) return;
            switch (mType)
            {
            case OE_QUAT:
                emit quatEdited(getQuaternion());
                break;
            case OE_VECTOR:
                emit vectorEdited(getVector());
                break;
            }
            });
        hbl->addWidget(mAngles[i]);
        mAngles[i]->setPrefix(mVarNames.at(i) + ": ");
        mAngles[i]->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(mAngles[i], &QWidget::customContextMenuRequested, this, &OrientEdit::customContextMenuEvent);
    }
    mAngles[0]->setRange(0, 360);
    mAngles[1]->setRange(-90, 90);
    mAngles[2]->setRange(0, 360);

    hbl->setContentsMargins(0, 0, 0, 0);
    setLayout(hbl);

    connect(this, &QWidget::customContextMenuRequested, this, &OrientEdit::customContextMenuEvent);
}

OrientEdit::~OrientEdit()
{

}

double OrientEdit::value(int w) const
{
    if (w < 0 || w>2) return NANd;
    return mAngles[w]->value();
}

void OrientEdit::setValue(int w, double v)
{
    if (w < 0 || w>2) return;
    mAngles[w]->setValue(v);
}

quaternion OrientEdit::getQuaternion() const
{
    if (mOrieinAngles)
        return quaternion::fromAngles(mAngles[0]->value() / R2D, mAngles[1]->value() / R2D, mAngles[2]->value() / R2D);
    else
        return quaternion::fromAngles2(mAngles[0]->value() / R2D, mAngles[1]->value() / R2D, mAngles[2]->value() / R2D);
}

vector3d OrientEdit::getVector() const
{
    vector3d v;
    double vl = mAngles[2]->value() / R2D;
    double cd = vl * cos(mAngles[1]->value() / R2D);
    v.x = cd * cos(mAngles[0]->value() / R2D);
    v.y = cd * sin(mAngles[0]->value() / R2D);
    v.z = vl * sin(mAngles[1]->value() / R2D);
    return v;
}

void OrientEdit::setQuaternion(const quaternion& q)
{
    auto _q = q;
    _q.normalize();
    if (_q.mW < 0) _q.inv();
    vector3d a = _q.toAngles(mOrieinAngles);
    //auto qq = quaternion::fromAngles(a, mOrieinAngles);
    if (mOrieinAngles)
    {
        auto lst0 = -pow(10.0, -2 * mAngles[0]->decimals());
        auto lst2 = -pow(10.0, -2 * mAngles[2]->decimals());
        if (a.x < lst0) a.x += 2 * M_PI;
        if (a.z < lst2) a.z += 2 * M_PI;
    }
    blockAllSignals(true);
    for (int k = 0; k < 3; k++)
        mAngles[k]->setValue(a[k] * R2D);
    blockAllSignals(false);
    mType = OE_QUAT;
    if (isValueChanged(true))
    {
        emit valueChanged();
        emit quatChanged(_q);
    }
}

void OrientEdit::setVector(const vector3d& v)
{
    blockAllSignals(true);
    double z = v.length();
    double y = asin(v.z / z) * R2D;
    double x = atan2(v.y, v.x) * R2D;
    if (x < 0) x += 360.0;
    mAngles[0]->setValue(x);
    mAngles[1]->setValue(y);
    mAngles[2]->setValue(z * R2D);
    blockAllSignals(false);
    mType = OE_VECTOR;
    emit vectorChanged(v);
    emit valueChanged();
}

void OrientEdit::setRange(int w, double min, double max, double step /*= -1.0*/)
{
    if (w < 0 || w > 2) return;
    mAngles[w]->setRange(min, max);
    if (step > 0)
        mAngles[w]->setSingleStep(step);
}

void OrientEdit::fromSettings(QSettings& s)
{
    s.beginGroup(objectName());
    for (int k = 0; k < 3; k++)
    {
        mAngles[k]->setValue(s.value(mVarNames.at(k)).toDouble());
        auto s_min = mVarNames.at(k) + "_min";
        if (s.contains(s_min)) mAngles[k]->setMinimum(s.value(s_min).toDouble());
        auto s_max = mVarNames.at(k) + "_max";
        if (s.contains(s_max)) mAngles[k]->setMaximum(s.value(s_max).toDouble());
    }
    s.endGroup();
}

void OrientEdit::toSettings(QSettings& s)
{
    s.beginGroup(objectName());
    for (int k = 0; k < 3; k++)
        s.setValue(mVarNames.at(k), mAngles[k]->value());
    s.endGroup();
}

void OrientEdit::setDecimals(int n, int k /*= -1*/)
{
    if (k >= 0 && k < 2) mAngles[k]->setDecimals(n);
    else for (k = 0; k < 2; ++k) mAngles[k]->setDecimals(n);
}

void OrientEdit::setStep(double st, int k /*= -1*/)
{
    if (k >= 0 && k < 2) mAngles[k]->setSingleStep(st);
    else for (k = 0; k < 2; ++k) mAngles[k]->setSingleStep(st);
}

void OrientEdit::setAngles(double _ra, double _de, double _phi)
{
    double d = sqr(_ra - mAngles[0]->value() / R2D)
        + sqr(_de - mAngles[1]->value() / R2D)
        + sqr(_phi - mAngles[2]->value() / R2D);
    for (int k = 0; k < 3; k++) mAngles[k]->blockSignals(true);
    mAngles[0]->setValue(R2D * _ra);
    mAngles[1]->setValue(R2D * _de);
    mAngles[2]->setValue(R2D * _phi);
    for (int k = 0; k < 3; k++) mAngles[k]->blockSignals(false);
    if (d > 1e-6)
        emit quatChanged(getQuaternion());
}

void OrientEdit::copyValue(QDoubleSpinBox* w) const
{
    auto cb = qApp->clipboard();
    if (!cb) return;

    QString s;
    if (w)
        s = QString::asprintf("%.6lf", w->value());
    else
        s = QString::asprintf("%.6lf, %.6lf, %.6lf", mAngles[0]->value(), mAngles[2]->value(), mAngles[2]->value());

    cb->setText(s);
}

void OrientEdit::pasteValue(QDoubleSpinBox* w)
{
    auto cb = qApp->clipboard();
    if (!cb) return;
    QString s = cb->text();

    vector3d v;
    static QRegularExpression re("([-+]?\\d*\\.?\\d+([eE][-+]?\\d+)?)");
    auto it = re.globalMatch(s);

    bool changed = false;
    if (!w)
    {
        double v[3];
        int k = 0;
        while (k < 3 && it.hasNext())
            v[++k] = it.next().captured(0).toDouble();
        if (k == 3)
        {
            while (--k >= 0) mAngles[k]->setValue(v[k]);
            changed = true;
        }
    }
    else if (it.hasNext())
    {
        auto v = it.next().captured(0).toDouble();
        w->setValue(v);
        changed = true;
    }

    if (changed)
    {
        switch (mType)
        {
        case OE_QUAT:
            emit quatEdited(getQuaternion());
            break;
        case  OE_VECTOR:
            emit vectorEdited(getVector());
            break;
        }
    }
}

void OrientEdit::customContextMenuEvent(const QPoint& p)
{
    auto w = dynamic_cast<QWidget*>(sender());
    if (!w) return;

    auto m = new QMenu(tr("Context menu"), this);
    auto aCopy = m->addAction(tr("Copy"));
    auto aPaste = m->addAction(tr("Paste"));

    auto a = m->exec(w->mapToGlobal(p));

    if (a == aCopy)
        copyValue(dynamic_cast<QDoubleSpinBox*>(w));
    else if (a == aPaste)
        pasteValue(dynamic_cast<QDoubleSpinBox*>(w));
}

void OrientEdit::blockAllSignals(bool on)
{
    mAngles[0]->blockSignals(on);
    mAngles[1]->blockSignals(on);
    mAngles[2]->blockSignals(on);
}

bool OrientEdit::isValueChanged(bool update)
{
    bool sameVals = true;
    for (int k = 0; k < 3; ++k)
    {
        auto newVal = mAngles[k]->value();
        sameVals = sameVals && (fabs(newVal - mOldVals[k]) < 1e-6 * (fabs(newVal) + fabs(mOldVals[k])));
        if (update) mOldVals[k] = newVal;
    }
    return !sameVals;
}
