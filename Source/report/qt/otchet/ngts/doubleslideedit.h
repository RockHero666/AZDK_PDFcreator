#ifndef DOUBLESLIDEEDIT_H
#define DOUBLESLIDEEDIT_H

#include <QtWidgets/QWidget>
class QDoubleSpinBox;
class QSlider;

class DoubleSlideEdit : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double minimum READ absMinimum WRITE setAbsMinimum)
    Q_PROPERTY(double maximum READ absMaximum WRITE setAbsMaximum)
    Q_PROPERTY(double singleStep READ singleStep WRITE setSingleStep)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(bool showTicks READ showTicks WRITE setShowTicks)
    Q_PROPERTY(bool logarithmic READ isLog WRITE setLog)
    Q_PROPERTY(double value READ value WRITE setValue DESIGNABLE false)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix DESIGNABLE false)

public:
    DoubleSlideEdit(QWidget *parent = 0);
    ~DoubleSlideEdit();

    void setupTicks(double interval, int sides);

    void setRange(double min, double max);
    void setAbsRange(double min, double max);

    double value() const;
    double minimum() const;
    double maximum() const;
    inline double absMinimum() const { return mMin; }
    inline double absMaximum() const { return mMax; }

    double singleStep() const;
    void setSingleStep(double step);

    int decimals() const;
    void setDecimals(int d);

    bool showTicks() const;
    void setShowTicks(bool on = true);

    bool isLog() const { return mLog; }
    void setLog(bool on);

    QString suffix() const;
    void setSuffix(const QString &);

public slots:
    void setMinimum(double v);
    void setValue(double v);
    void setMaximum(double v);
    void setAbsMinimum(double v);
    void setAbsMaximum(double v);

signals:
    void valueChanged(double);

private:
    QDoubleSpinBox *mBox;
    QSlider *mSlider;
    double mMin, mMax;
    bool mLog = false;

protected:
    void boxValueChanged(double);
    void sliderValueChanged(int);
};

#endif // DOUBLESLIDEEDIT_H
