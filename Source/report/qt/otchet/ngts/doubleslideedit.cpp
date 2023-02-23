#include "doubleslideedit.h"
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QSlider>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QAction>
#include <math.h>

#define SLIDER_MAX 10000

DoubleSlideEdit::DoubleSlideEdit(QWidget *parent)
    : QWidget(parent)
    , mBox(new QDoubleSpinBox)
    , mSlider(new QSlider)
{
    QHBoxLayout *hbl = new QHBoxLayout;
    hbl->addWidget(mSlider, 1);
    hbl->addWidget(mBox, 0);
    hbl->setContentsMargins(0, 0, 0, 0);
    setLayout(hbl);

    mSlider->setMinimum(0);
    mSlider->setMaximum(SLIDER_MAX);
    mSlider->setTickInterval(500);
    mSlider->setOrientation(Qt::Horizontal);
    mSlider->setTickPosition(QSlider::TicksBothSides);

    connect(mBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &DoubleSlideEdit::boxValueChanged);
    connect(mSlider, &QSlider::valueChanged, this, &DoubleSlideEdit::sliderValueChanged);

    setAbsRange(0, 100);
}

DoubleSlideEdit::~DoubleSlideEdit()
{

}

void DoubleSlideEdit::setRange(double min, double max)
{
    if (min < mMin) min = mMin;
    if (max > mMax) max = mMax;
    mBox->setRange(min, max);
}

void DoubleSlideEdit::setAbsRange(double min, double max)
{
    if (min >= max) return;
    mMin = min;
    mMax = max;
    setRange(mMin, mMax);
    setSingleStep(mBox->singleStep());
    mSlider->blockSignals(true);
    double v = 0;
    if (mLog) v = log(mBox->value() / mMin) / log(mMax / mMin);
    else v = (mBox->value() - mMin) / (mMax - mMin);
    mSlider->setValue((int)(v*(double)SLIDER_MAX + 0.5));
    mSlider->blockSignals(false);
}

void DoubleSlideEdit::setDecimals(int d)
{
    mBox->setDecimals(d);
}

bool DoubleSlideEdit::showTicks() const
{
    return mSlider->tickPosition() == QSlider::TicksBothSides;
}

void DoubleSlideEdit::setShowTicks(bool on /*= true*/)
{
    if (on)
        mSlider->setTickPosition(QSlider::TicksBothSides);
    else
        mSlider->setTickPosition(QSlider::NoTicks);
}

void DoubleSlideEdit::setLog(bool on)
{
    mLog = on;
    double max = qMax(mMax, 1.0);
    double min = mMin <= 0 || mMin > mMax ? 0.001*mMax : mMin;
    setAbsRange(min, max);
}

QString DoubleSlideEdit::suffix() const
{
    return mBox->suffix();
}

void DoubleSlideEdit::setSuffix(const QString & sfx)
{
    mBox->setSuffix(sfx);
}

double DoubleSlideEdit::value() const
{
    return mBox->value();
}

void DoubleSlideEdit::setSingleStep(double v)
{
    mBox->setSingleStep(v);
    v = v / (mMax - mMin);
    mSlider->setSingleStep(v * (double)SLIDER_MAX + 0.5);
    mSlider->setPageStep(v * (double)SLIDER_MAX + 0.5);
}

void DoubleSlideEdit::setupTicks(double interval, int sides)
{
    mSlider->setTickInterval(SLIDER_MAX / ((mMax - mMin) / interval));
    mSlider->setTickPosition((QSlider::TickPosition)(sides & QSlider::TicksBothSides));
}

void DoubleSlideEdit::setValue(double v)
{
    mBox->setValue(v);
}

void DoubleSlideEdit::setMinimum(double v)
{
    if (v < mMin) v = mMin;
    mBox->setMinimum(v);
}

void DoubleSlideEdit::setMaximum(double v)
{
    if (v > mMax) v = mMax;
    mBox->setMaximum(v);
}

double DoubleSlideEdit::minimum() const
{
    return mBox->minimum();
}

double DoubleSlideEdit::maximum() const
{
    return mBox->maximum();
}

void DoubleSlideEdit::setAbsMinimum(double v)
{
    setAbsRange(v, mMax);
}

void DoubleSlideEdit::setAbsMaximum(double v)
{
    setAbsRange(mMin, v);
}

double DoubleSlideEdit::singleStep() const
{
    return mBox->singleStep();
}

int DoubleSlideEdit::decimals() const
{
    return mBox->decimals();
}

void DoubleSlideEdit::boxValueChanged(double)
{
    double v = mBox->value(), fv;
    mSlider->blockSignals(true);
    if (mLog) fv = log(v/mMin) / log(mMax/mMin);
    else fv = (v - mMin) / (mMax - mMin);
    mSlider->setValue((int)(fv*(double)SLIDER_MAX + 0.5));
    mSlider->blockSignals(false);
    emit valueChanged(v);
}

void DoubleSlideEdit::sliderValueChanged(int)
{
    double fac = mLog ? log(mMax / mMin) : (mMax - mMin), f0 = mLog ? log(mMin) : mMin;
    double v = mSlider->value() / (double)SLIDER_MAX * fac + f0;
    if (mLog) v = exp(v);
    mBox->blockSignals(true);
    if (v < mBox->minimum())
    {
        v = mBox->minimum();
        boxValueChanged(v);
    }
    if (v > mBox->maximum())
    {
        v = mBox->maximum();
        boxValueChanged(v);
    }
    mBox->setValue(v);
    mBox->blockSignals(false);
    emit valueChanged(v);
}
